/*
 * Copyright (C) 2025 Loiudice Michele
 *
 * Permission is granted to use, copy, modify, and distribute this software freely, provided that:
 * 1. This software **MAY NOT be sold or used for commercial purposes**.  
 * 2. Proper credit must be given to the original author.
 * 3. This notice must be included in all copies or substantial portions of the software.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
 * THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHOR BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER LIABILITY, ARISING FROM THE USE OF THIS SOFTWARE.
 */

#ifndef DICTIONARY
#define DICTIONARY

#include <iostream>
using namespace std;

template <class T>
class _hash {
public:
    size_t operator () (const T key) const;
};

template <>
// Hash function for string keys.
class _hash <string> {
public:
    // Operator ()
	size_t operator () (const string key) const {
		unsigned long hash_value = 0;
		int lenght = (int) key.length();
		for (int i = 0; i < lenght; i ++) {
			hash_value = 5 * hash_value + key.at (i);
		}
		return (size_t (hash_value));
	}
};

template <>
// Hash function for integers keys.
class _hash <int> {
public:
	size_t operator () (const int key) const {
        string ch (to_string(key));
		unsigned long hash_value = 0;
		int lenght = (int) ch.length ();
		for (int i = 0; i < lenght; i ++) {
			hash_value = 5 * hash_value + ch.at (i);
		}
		return (size_t (hash_value));        
	}
};

template <class K, class V> class dictionary;
template <class K, class V>
// Manages the hash_table pair information.
class bucket{
    friend class dictionary<K,V>;
    public:
        static const int _not_set = 0;
        static const int _set = 1;
        static const int _deleted = -1;
        bucket(): _pair(), state(_not_set){}
        bucket(pair<K,V>p): _pair(p), state(_set){}
        ~bucket(){};
        void delete_pair(){ _pair = pair<K,V>(); state = _deleted; }
        void insert_pair(pair<K,V>p){ _pair = p; state = _set; }
        void set_state(int state_in) { state = state_in; }
        pair<K,V> get_pair(){ return _pair; }
        int get_state(){ return state; }
        bool not_set(){ return (state == _not_set); }
        bool set(){ return (state == _set); }
        bool deleted(){ return (state == _deleted); }

        //Deep copy of bucket elements.
        void operator =(bucket<K,V>& b){
            _pair = b._pair;
            state = b.state;
        }
    private:
        pair<K,V> _pair;
        int state;
};

#include "./abstract_dictionary.hpp"

template <class K, class V>
class dictionary : public abstract_dictionary<K,V>{  
    public:
        template <class T, class N>
        friend ostream& operator << (ostream &output, const dictionary<T,N> &d);

        /*** Default Constructor ***/
        dictionary();
        dictionary(int);
        /*** Destructor ***/
        ~dictionary();
        /*** Copy Constructor ***/
        dictionary(const dictionary<K,V>&);
        /*** Move Constructor ***/
        dictionary(dictionary<K,V>&&) noexcept;
        
        /*** Methods ***/
        bool empty() const; // Returns true if the dictionary is empty.
        int size() const; // Returns the number of elements of the dictionary.
        void insert(pair<K,V>); // Inserts a pair key-value into the dictionary.
        V find(K) const; // Returns the value of a pair with a certain key.
        void erase(K); // Removes a pair from the dictionary.
        bool contains(K); // Returns true if a key is contained in the dictionary.
        /*** OPERATORS ***/

    private:
        /*** PRIVATE CONSTANT ***/
        const int default_dimension = 20;
        const int not_found = -1;
        /*** PRIVATE METHODS ***/
        bool compare_keys(K,K) const; //Compares two keys.
        void doubling(); // Doubles the length of the pairs array.
        K get_key(int) const; // Returns the key in a certaint position.
        V get_value(int) const; // Returns the value in a certain position.
        int find_next_empty_position(int); //Finds the first empty spot or doubles the array if it is full.
        int linear_search(K) const; // Finds the next pair with the same hash value. 
        bool is_empty_position(int) const; // Returns true if the position is avaible.
        void inzialize_dictionary(int); // Inizialize the inital state of the dictionary.
        /*** PRIVATE ATTRIBUTES ***/
        // The hash table is an array of pair.
        bucket<K,V> *hash_table;
        // Generic type for hash function.
        _hash<K> hash;
        int total_elements;
        int n_elements;
};

/*** Default Constructor ***/
template <class K,class V>
dictionary<K,V>::dictionary(){
    inzialize_dictionary(default_dimension);
}

template <class K,class V>
dictionary<K,V>::dictionary(int size){
    inzialize_dictionary(size);
}

// Inizialize the inital state of the dictionary
template <class K, class V>
void dictionary<K,V>::inzialize_dictionary(int total_elements_in){
    total_elements = total_elements_in;
    n_elements = 0;
    hash_table = new bucket<K,V>[total_elements];
}

/*** Destructor ***/
template <class K,class V>
dictionary<K,V>::~dictionary(){
    delete[] hash_table;
}

/*** Copy Constructor ***/
template <class K,class V>
dictionary<K,V>::dictionary(const dictionary<K,V>& dictionary){

}

/*** Move Constructor ***/
template <class K,class V>
dictionary<K,V>::dictionary(dictionary<K,V>&& dictionary) noexcept{
    total_elements = dictionary.total_elements;
    n_elements = dictionary.n_elements;
    hash_table = dictionary.hash_table;
    dictionary.hash_table = nullptr;
}

/*** Methods ***/

// Returns true if the dictionary is empty.
template <class K,class V>
bool dictionary<K,V>::empty() const{
    return (n_elements == 0);
}

// Returns the number of elements of the dictionary.
template <class K,class V>
int dictionary<K,V>::size() const{
    return n_elements;
} 

// Returns the key in a certaint position. *
template <class K,class V>
K dictionary<K,V>::get_key(int position) const{
    if(is_empty_position(position)) return nullptr;
    return hash_table[position]._pair.first;
}

// Returns the value in a certain position. *
template <class K,class V>
V dictionary<K,V>::get_value(int position) const{
    if(is_empty_position(position)) throw runtime_error("No position found!");
    return hash_table[position]._pair.second;
}

// Returns true if the position is avaible.
template <class K,class V>
bool dictionary<K,V>::is_empty_position(int position) const{
    return (!hash_table[position].set());
}

//Compares two keys.
template <class K,class V>
bool dictionary<K,V>::compare_keys(K k1,K k2) const{
    return (k1 == k2);
}

//Finds the first empty spot or doubles the array if it is full.
template <class K,class V>
int dictionary<K,V>::find_next_empty_position(int position){
    if(n_elements == total_elements) doubling();
    int free_position = (position+1)%total_elements;
    while(free_position!=position){
        if(is_empty_position(free_position)){
            hash_table[position].set_state(bucket<K,V>::_set);
            return free_position;
        } 
        free_position = (free_position+1)%total_elements;
    }
    return free_position;
}

// Inserts a pair key-value into the dictionary.
template <class K,class V>
void dictionary<K,V>::insert(pair<K,V> value){
    int position = hash(value.first)%total_elements;
    if(!is_empty_position(position) && compare_keys(get_key(position),value.first)) return;
    if(linear_search(value.first) != not_found) return;
    if(is_empty_position(position)) hash_table[position].insert_pair(value);
    else{
        position = find_next_empty_position(position);
        hash_table[position].insert_pair(value);
    }
    n_elements++;
}

// Returns the value of a pair with a certain key.
template <class K,class V>
V dictionary<K,V>::find(K key) const{
    int position = hash(key)%total_elements;
    if( !is_empty_position(position) && compare_keys(get_key(position), key) ) return get_value(position);
    do{
        position = linear_search(key);
        if(position == not_found) break;
        if(compare_keys(get_key(position), key)) return get_value(position);
    } while(not_found);
    //Key was not found, operator violates the PRE-Condition
    if(position) throw runtime_error("No key found!");
    return get_value(position);
}

// Removes a pair from the dictionary.
template <class K,class V>
void dictionary<K,V>::erase(K key){
    int position = hash(key)%total_elements;
    if( !is_empty_position(position) && compare_keys(get_key(position), key) ){
        hash_table[position].set_state(bucket<K,V>::_deleted);
        n_elements--;
        return;
    }
    position = linear_search(key);
    if(linear_search(key) == not_found) throw runtime_error("No key found!");
    hash_table[position].set_state(bucket<K,V>::_deleted);
    n_elements--;
}

// Returns true if a key is contained in the dictionary.
template <class K,class V>
bool dictionary<K,V>::contains(K key){
    int position = hash(key)%total_elements;
    if( !is_empty_position(position) && compare_keys(get_key(position), key) ) return true;
    do{
        position = linear_search(key);
        if(position == not_found) break;
        if(compare_keys(get_key(position), key)) return true;
    } while(not_found);
    //Key was not found, operator violates the PRE-Condition
    return false;
}

// Doubles the length of the pairs array.
template <class K,class V>
void dictionary<K,V>::doubling(){
    //Saving the old hash table.
    bucket<K,V> *old_hash_table = hash_table;
    int old_total_elements = total_elements;
    //Declaring the new one.
    total_elements *= 2;
    n_elements = 0;
    hash_table = new bucket<K,V>[total_elements];
    for(int i = 0; i < old_total_elements; i++){
        if(old_hash_table[i].get_state() != bucket<K,V>::_not_set){
            pair<K,V> p = old_hash_table[i].get_pair();
            insert(p);
        }
    }
    delete[] old_hash_table;
}

// Finds the next pair with the same key value. 
template <class K,class V>
int dictionary<K,V>::linear_search(K key) const{
    int end = (hash(key)%total_elements);
    int position = (end+1)%total_elements;
    while(position != end){
        // I dont want to check if it is empty, but if it has never been assigned.
        //if(hash_table[position].get_state() == bucket<K,V>::_not_set){
        if(is_empty_position(position)){
            position = (position+1)%total_elements;
            continue;
        }
        if(get_key(position) == key) return position;
        position = (position+1)%total_elements;
    }
    return not_found;
} 

/*** OPERATORS ***/
template <class K,class V>
ostream& operator << (ostream &output, const dictionary<K,V> &d){
    cout << "Dictionary Pairs [<Key|Value|Hash|Arr. Pos>]: " << endl;
    for(int i = 0; i < d.total_elements; i++){
        if(!d.is_empty_position(i)){
            output << "<" << d.get_key(i) << "|" << d.get_value(i) 
            << "|" << d.hash(d.get_key(i))%d.total_elements << "|" << i << ">" << endl;
        }
    }
    return output;
}


#endif
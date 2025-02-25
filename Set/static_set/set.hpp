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

#ifndef SET
#define SET

#include <iostream>
#include "../abstract_set.hpp"
using namespace std;

template <class T>
class set : public abstract_set<T,int>{
   //typedef int position;
    public:
    typedef typename abstract_set<T,int>::position position;
        const position empty_set = -1;
        const int default_dimension = 10;
        /*** Constructors ***/
        set();/*** Default Constructor ***/
        set(position);/*** Default Constructor ***/
        ~set();/*** Destructor ***/
        set(const set<T> &);/*** Copy Constructor ***/
        set(set<T>&&) noexcept; /*** Move Constructor ***/
        /*** Methods ***/
        bool empty() const override; //Checks if the set is empty.
        void erase(const T&) override; //Removes an element from the set.
        void insert(const T&) override; //Inserts a new element to the bottom of the set.
        int size() const override; //Returns the size of the set.
        bool contains(const T&)const override; //Search the value in the set and returns the search result.
        void print_test();
        //Intersection Operator (Set intersection|Returns a set with the common elements between the two sets).
        set<T>& intersect(const set<T>&);
        /*** Operators ***/
        //Union Operator (set concatenation|Duplicates are not allowed as per definition)
        set<T>& operator +( const set<T>& ); 
        //Difference Operator (Set Difference) -> Returns the elements of set1 that doesn't belong to set2
        set<T>& operator -( const set<T>& );
        void operator =( set<T>&& ); //Operator =(Assigment by copy).
        set<T>& operator =( const set<T>& ); //Operator =(Move equal).
        bool operator ==( const set<T>& ); //Operator ==(Compares two sets.)
        
    private:
        /*** PRIVATE METHODS ***/
        void right_shift(position,position);
        void left_shift(position,position);
        void doubling(); //Doubles the length of the array.
        position find(const T &) const override; //Search the value in the set and return his position.
        void clear() override; //Clears the elements of the set.
        /*** PRIVATE ATTRIBUTES ***/
        position insert_index;
        position total_elements;
        T *values;
};

/*** Constructors ***/
/*** Default Constructor ***/
template <class T>
set<T>::set(){
    total_elements = default_dimension;
    insert_index = empty_set;
    values = new T[default_dimension];
}

/*** Default Constructor ***/
template <class T>
set<T>::set( position n_elements_in ){
    total_elements = n_elements_in;
    insert_index = empty_set;
    values = new T[total_elements];
}

/*** Destructor ***/
template <class T>
set<T>::~set(){
    clear();
}

/*** Copy Constructor ***/
template <class T>
set<T>::set(const set<T> &s){
    insert_index = s.insert_index;
    total_elements = s.total_elements;
    values = new T[total_elements];
    for( position i = 0; i < insert_index; i++ ){
        values[i] = s.values[i];
    }
}

/*** Move Constructor ***/
template <class T>
set<T>::set(set<T>&& s) noexcept{
    total_elements = s.total_elements;
    insert_index = s.insert_index;
    values = s.values;
    s.values = nullptr;
} 

/*** Methods ***/
template <class T>
void set<T>::clear(){
    delete[] values;
} 

//Checks if the set is empty.
template <class T>
bool set<T>::empty() const{
    return insert_index == empty_set;
} 

//Removes an element from the set.
template <class T>
void set<T>::erase(const T& value){
    if( insert_index == empty_set ) return;
    position i = find(value);
    if( i == -1 ) return;
    else{
        left_shift(i,1);
        insert_index--;
    } 
} 

//Inserts a new element respectin the order of elements.
template <class T>
void set<T>::insert(const T& value){
    if( contains(value) ) return;
    if( insert_index == empty_set ){
        insert_index = 0;
        values[insert_index] = value;
        insert_index++;
        return;
    }
    if( insert_index == total_elements ) doubling();
    position i = 0;
    while( i+1 < insert_index && values[i+1] < value ) i++;
    right_shift(i+1,1);
    values[i+1] = value;
    insert_index++;
} 

//Returns the size of the set.
template <class T>
int set<T>::size() const{
    if( insert_index == empty_set ) return 0;
    else return insert_index;
} 

//Search the value in the set and returns the search result.
template <class T>
bool set<T>::contains(const T& value)const{
    return( find(value) != -1 );
} 

//Doubles the length of the array.
template <class T>
void set<T>::doubling(){
    total_elements *= 2;
    T *new_values = new T[total_elements];
    for(position i = 0; i < insert_index; i++){
        new_values[i] = values[i];
    }
    delete[] values;
    values = new_values;
}

//Search the value in the set and return his position.
template <class T>
typename set<T>::position set<T>::find(const T& value) const{
    position i = 0;
    while( i < insert_index && values[i] <= value ){
        if(values[i] == value) return i;
        i++;
    }
    return -1;
}

template <class T>
void set<T>::right_shift(position start_position, position n_positions){
    if( start_position < 0 || start_position > insert_index )return;
    if( n_positions + insert_index >= total_elements) doubling();
    for( position i = insert_index+n_positions-1, k = 0; i > start_position+n_positions-1; i--, k++ ){
        values[i] = values[insert_index-k-1];
        values[insert_index-k-1] = -1;
    }
}

//Shift to the left all the elements 
template <class T>
void set<T>::left_shift(position start_position, position n_positions){
    if( start_position < 0 || start_position > insert_index || n_positions + insert_index <= 0 )return;
    for( position i = start_position; i < insert_index-n_positions; i++ ){
        values[i] = values[i+n_positions];
    }
}

// Use this function if you want to see the state of the set
template <class T>
void set<T>::print_test(){
    cout << "Set: {";
    for( position i = 0; i < insert_index; i++){
        cout << " [" << values[i] << "] ";
    }
    cout << "}";
}

template <class T>
set<T>& set<T>::intersect( const set<T>& s ){
    set<T> *intersection = new set<T>( total_elements + s.total_elements );
    for( position i = 0; i < s.insert_index; i++ ){
        if(contains(s.values[i])) intersection->insert(s.values[i]);
    }
    return *intersection;
}

/*** Operators ***/
//Union Operator (set concatenation|Duplicates are not allowed as per definition)
template <class T>
set<T>& set<T>::operator +( const set<T>& s ){
    set<T> *union_set = new set<T>( total_elements + s.total_elements );
    for( position i = 0; i < insert_index; i++ ){
        union_set->insert(values[i]);
    }
    for( position i = 0; i < s.insert_index; i++ ){
        union_set->insert(s.values[i]);
    }
    return *union_set;
}

//Difference Operator (Set Difference) -> Returns the elements of set1 that doesn't belong to set2
template <class T>
set<T>& set<T>::operator -( const set<T>& s ){
    set<T> *difference_set = new set<T>( total_elements );
    for( position i = 0; i < insert_index; i++ ){
        if(!s.contains(values[i])) difference_set->insert(s.values[i]);
    }
    return *difference_set;
}

//Operator =(Assigment by copy)
template <class T>
void set<T>::operator =( set<T>&& s ){
    total_elements = s.total_elements;
    insert_index = s.insert_index;
    delete[] values;
    values = s.values;
    s.values = nullptr;
}
//Operator =(Assigment by copy)
template <class T>
set<T>& set<T>::operator =( const set<T>& s ){
    total_elements = s.total_elements;
    insert_index = s.insert_index;
    delete[] values;
    values = new T[total_elements];
    for( position i = 0; i < s.insert_index; i++ ){
        values[i] = s.values[i];
    }
    return *this;
}
//Operator ==(Compares two sets.)
template <class T>
bool set<T>::operator ==( const set<T>& s ){
    if(insert_index != s.insert_index) return false;
    for( position i = 0; i < insert_index; i++ ){
        if(values[i] != s.values[i]) return false;
    }
    return true;
}

#endif // SET
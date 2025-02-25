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
#include "./abstract_set.hpp"
using namespace std;

template <class T> class set;
template <class T>
class set_node{
    typedef set_node<T>* nodeptr;
    friend class set<T>;
    private:
        T value;
        nodeptr next_node;
    public:
        //Constructor
        set_node( T value_in ): value(value_in), next_node(nullptr){}
        //Destructors
        ~set_node(){
            delete next_node;
        }
};

template <class T>
class set : public abstract_set<T, set_node<T>*> {
   //typedef int position;
    public:
    typedef typename abstract_set<T, set_node<T>*>::position nodeptr;
        /*** Constructors ***/
        set();/*** Default Constructor ***/
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
        void operator =( set<T>&& ); //Operator =(Assigment by copy)
        set<T>& operator =( const set<T>& ); //Operator =(Assigment by copy)
        bool operator ==( const set<T>& ); //Operator ==(Compares two sets.)
    private:
        /*** PRIVATE METHODS ***/
        nodeptr find(const T &) const override; //Search the value in the set and return his pointer.
        void clear() override; //Clears the elements of the set.
        /*** PRIVATE ATTRIBUTES ***/
        int n_elements;
        nodeptr head;
};

/*** Constructors ***/
/*** Default Constructor ***/
template <class T>
set<T>::set(){
    head = nullptr;
    n_elements = 0;
}

/*** Destructor ***/
template <class T>
set<T>::~set(){
    clear();
}

/*** Copy Constructor ***/
template <class T>
set<T>::set( const set<T> &s ){
    if(s.empty()){
        head = nullptr;
        n_elements = 0;
        return;
    }
    nodeptr s_iterator = s.head;
    head = new set_node<T>(s_iterator->value);
    nodeptr new_node = head;
    while( s_iterator->next_node != nullptr){
        s_iterator = s_iterator->next_node;
        new_node->next_node = new set_node<T>(s_iterator->value);
        new_node = new_node->next_node;
    }
}

/*** Move Constructor ***/
template <class T>
set<T>::set(set<T>&& s) noexcept{
    head = s.head;
    n_elements = s.n_elements;
    s.head = nullptr;
} 

/*** Methods ***/
//Checks if the set is empty.
template <class T>
bool set<T>::empty() const{
    return (head == nullptr);
} 

//Removes an element from the set.
template <class T>
void set<T>::erase( const T& value ){
    nodeptr to_delete;
    //In case the first element is the one to delete;
    if( head->value == value ){
        to_delete = head;
        head = head->next_node;
        to_delete->next_node = nullptr;
        delete to_delete;
        n_elements--;
        return;
    }
    nodeptr iterator = head;
    while(iterator->next_node != nullptr && iterator->next_node->value < value ){
        iterator = iterator->next_node;
    }
    if( iterator->next_node->value == value ){
        to_delete = iterator->next_node;
        iterator->next_node = iterator->next_node->next_node;
        to_delete->next_node = nullptr;
        n_elements--;  
        delete to_delete;
    } 
} 

//Inserts a new element to the bottom of the set.
template <class T>
void set<T>::insert(const T &value){
    nodeptr new_node = new set_node<T>(value);
    if( head == nullptr ){
        head = new_node;
        n_elements++;
        return;
    } 
    if(contains(value)) return; //Elements are unique.
    else{
        nodeptr iterator = head;
        while(iterator->next_node != nullptr && iterator->next_node->value < value ){
            iterator = iterator->next_node;
        }
        new_node->next_node = iterator->next_node;
        iterator->next_node = new_node;
    }
    n_elements++;
} 

//Returns the size of the set.
template <class T>
int set<T>::size() const{
    return n_elements;
} 

//Search the value in the set and returns the search result.
template <class T>
bool set<T>::contains( const T& value ) const{
    return(find(value) != nullptr);
}

//Search the value in the set.
template <class T>
typename set<T>::nodeptr set<T>::find(const T &value) const{
    nodeptr iterator = head;
    while( iterator != nullptr && iterator->value <= value ){
        if( iterator->value == value ) return iterator;
        iterator = iterator->next_node;
    }
    return nullptr;
}

//Clears the elements of the set.
template <class T>
void set<T>::clear(){
    while( head != nullptr ){
        nodeptr p = head;
        head = head->next_node;
        p->next_node = nullptr;
        delete p;
    }
}

//Intersection Operator (Set intersection|Returns a set with the common elements between the two sets).
template <class T>
set<T>& set<T>::intersect(const set<T>& s){
    set<T> *intersection = new set<T>;
    nodeptr iterator_s1 = head;
    while( iterator_s1 != nullptr ){
        if( s.find(iterator_s1->value) ) intersection->insert(iterator_s1->value);
        iterator_s1 = iterator_s1->next_node;
    }
    return *intersection;
}

/*** Operators ***/

//Union Operator (set concatenation|Duplicates are not allowed as per definition)
template <class T>
set<T>& set<T>::operator +( const set<T>& s ){
    set<T> *sum = new set<T>;
    nodeptr iterator_s1 = head;
    nodeptr iterator_s2 = s.head;
    while( iterator_s2 != nullptr || iterator_s1 != nullptr ){
        if( iterator_s1 != nullptr ){
            sum->insert(iterator_s1->value);
            iterator_s1 = iterator_s1->next_node;    
        }
        if( iterator_s2 != nullptr ){
            sum->insert(iterator_s2->value);
            iterator_s2 = iterator_s2->next_node;
        }
    }
    return *sum;
} 

//Difference Operator (Set Difference) -> Returns the elements of set1 that doesn't belong to set2
template <class T>
set<T>& set<T>::operator -( const set<T>& s ){
    set<T> *difference = new set<T>;
    nodeptr iterator_s1 = head;
    while( iterator_s1 != nullptr ){
        if( !s.find(iterator_s1->value) ) difference->insert(iterator_s1->value);
        iterator_s1 = iterator_s1->next_node;
    }
    return *difference;
} 

//Operator =(Assigment by copy)
template <class T>
void set<T>::operator =( set<T>&& s ){
    clear();
    n_elements = s.n_elements;
    head = s.head;
    s.head = nullptr;
} 

//Operator =(Assigment by copy)
template <class T>
set<T>& set<T>::operator =( const set<T>& s ){
    clear();
    if(s.head == nullptr) return *this;
    n_elements = s.n_elements;
    head = new set_node<T>(s.head->value);
    nodeptr iterator_s1 = head;
    nodeptr iterator_s2 = s.head->next_node;
    while(iterator_s2 != nullptr ){
        iterator_s1->next_node = new set_node<T>(iterator_s2->value);
        iterator_s1 = iterator_s1->next_node;
        iterator_s2 = iterator_s2->next_node;
    }
    return *this;
} 

//Operator ==(Compares two sets.)
template <class T>
bool set<T>::operator ==( const set<T>& s ){
    if( this == &s ) return true;
    if( n_elements != s.n_elements ) return false;
    nodeptr iterator_s1 = head;
    nodeptr iterator_s2 = s.head;
    while( iterator_s1 != nullptr ){
        if( iterator_s1->value != iterator_s2->value ) return false;
        iterator_s1 = iterator_s1->next_node;
        iterator_s2 = iterator_s2->next_node;
    }
    return true;
}


template <class T>
void set<T>::print_test(){
    nodeptr iterator = head;
    cout << "SET: -> {";
    while( iterator != nullptr ){
        cout << " [" << iterator->value <<"] ";
        iterator = iterator->next_node;
    }
    cout << "}";
}

#endif // SET
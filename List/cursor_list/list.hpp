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

#ifndef LIST
#define LIST

#include <iostream>
#include "../abstract_list.hpp"
using namespace std;

template <class T> class linked_list;
template <class T>
class list_node{
    typedef int position;
    friend class linked_list<T>;
    private:
        const int last_node = -1;
        T value;
        position next_node;
    public:
        //Constructor
        list_node(): value(0), next_node(last_node){}
        list_node( T value_in ): value(value_in), next_node(last_node){}
};

template <class T>
class linked_list: public abstract_list<T, int>{
    public:
        const int default_dimension = 10;
        const int last_node = -1;
        typedef typename abstract_list<T,int>::position position;
        /*** Constructor ***/
        linked_list();
        linked_list(position n_elements_in);
        ~linked_list();
        linked_list(const linked_list&);
        linked_list(linked_list<T>&&) noexcept;

        /*** Abstract Methods Implementation ***/
        int size() const override; //Returns the size of the list.
        T get_value(position) const override;//Returns the value of the node.
        bool empty() const override; //Checks if the list is empty.
        void clear() override; //Clears the elements of the list.
        bool end(position) const override;//Checks if the node is the last of the list.
        position begin() const override; //Returns the first element of the list.
        position last() const override; //Returns the last element of the list.
        position next(position) const override; //Returns the next element of n.
        position previous(position) const override; //Returns the previous element of n.
        void erase(position) override; //Removes an element from the list.
        void insert(const T&) override; //Inserts a new element to the bottom of the list.
        void insert_in_position(const T&, position); //Inserts a a new node in a certain position.
        void write(const T&, position) override; //Set the value of a node of the class.
        T read(position) const override; //Reads an element from the list.
        /*** Methods ***/
        bool find(const T &) const; //Search the value in the list.
        void merge_sort(){ head = merge_sort(head); } //Merge sort algorithm.

        /*** Operators ***/
        linked_list<T>& operator +( const linked_list<T>& ); //Operator + (List concatenation)
        linked_list<T>& operator =( const linked_list<T>& ); //Operator =(Assigment by copy)
        linked_list<T>& operator =( const linked_list<T>&& ); //Operator =(Move assignment)
        void operator =( linked_list<T> &&l );
        //void test_print();
    private:
        void doubling(); //Doubles the length of the array.
        position merge_sort(position);
        position find_mid_node(position);
        position merge_chains(position,position);
        void inizialize(position); //Inizialize the list elements.
        list_node<T> *list;
        position head; //Points to the first element of the list.
        position empty_list; //Points to the first empty position in the list.
        position total_elements;
        position n_elements;
};

/*** Default Constructor ***/
template <class T>
linked_list<T>::linked_list(){
    inizialize(default_dimension);
}

/*** Default Constructor ***/
template <class T>
linked_list<T>::linked_list( position n_elements_in ){
    inizialize(n_elements_in);
}

//Inizialize the list elements.
template <class T>
void linked_list<T>::inizialize( position n_elements_in ){
    total_elements = n_elements_in;
    n_elements = 0;
    head = last_node; //Empty list condition
    empty_list = 0; 
    list = new list_node<T>[total_elements];
    //Inizializing the empty_list
    for( position i = 0; i < total_elements; i++ ){
        list[i].next_node = (i != total_elements-1 )? i+1 : last_node;
    }
}

//Copy Constructor
template <class T>
linked_list<T>::linked_list( const linked_list&l ){
    inizialize( l.total_elements );
    position p = l.begin();
    while( p != last_node ){
        insert(l.list[p].value);
        p = l.list[p].next_node;
    }
}

//Move constructor
template <class T>
linked_list<T>::linked_list( linked_list<T>&& l ) noexcept{
    n_elements = l.n_elements;
    total_elements = l.total_elements;
    list = l.list;
    head = l.head;
    empty_list = l.empty_list;
    l.list = nullptr;
}

/*** Destructor ***/
template <class T>
linked_list<T>::~linked_list(){
    clear();
}

//Clears the elements of the list.
template <class T>
void linked_list<T>::clear(){
    delete []list;
}

//Checks if the list is empty.
template <class T>
bool linked_list<T>::empty() const{
    return (empty_list == last_node);
}

//Checks if the node is the last of the list.
template <class T>
bool linked_list<T>::end(position p) const{
    return(p == last_node);
}   

//Returns the last element of the list
template <class T>
typename linked_list<T>::position linked_list<T>::last() const{
    position i = head;
    while( head != last_node && list[i].next_node != last_node ) i = list[i].next_node;
    return i;
}

//Returns the first element of the list.
template <class T>
typename linked_list<T>::position linked_list<T>::begin() const{
    return head;
}

//Returns the next element of n.
template <class T>
typename linked_list<T>::position linked_list<T>::next( position p ) const{
    if( p == last_node ) return p;
    else return list[p].next_node;
}        

//Returns the previous element of n.
template <class T>
typename linked_list<T>::position linked_list<T>::previous( position p ) const{
    if( head == last_node || p == last_node ) return last_node;
    position i = head;
    while ( list[i].next_node != p )
        i = list[i].next_node;
    return i;
}

//Inserts a new element to the bottom of the list.
template <class T>
void linked_list<T>::insert( const T& value_in ){
    if( n_elements == total_elements ) doubling(); //If the list is full, we doulble the space of the array.
    position i = head;
    //Finding the last node.
    while( head != last_node && list[i].next_node != last_node ) 
        i = list[i].next_node;
    list[empty_list].value = value_in; //Assigning the new value to the node.
    if( head == last_node ) head = empty_list;
    else list[i].next_node = empty_list; //Linking the last node.
    position tmp = list[empty_list].next_node; //Saving the next empty node. 
    list[empty_list].next_node = last_node; //Unlinking the regular list from the empty one.
    empty_list = tmp; //Shifting the empty list pointer.
    n_elements++;
}

//Removes an element from the list.
template <class T>
void linked_list<T>::erase( position p ){
    if( p == head ){
        head = list[p].next_node;
    } 
    else{
        //Removing the in position p from the list
        list[previous(p)].next_node = list[p].next_node;
    }
    //Adding the deleted node to the top of the empty list.
    list[p].next_node = empty_list;
    empty_list = p;
    n_elements--;
}

//Doubles the length of the array.
template <class T>
void linked_list<T>::doubling(){
    linked_list<T> *new_list = new linked_list<T>(total_elements*2);
    position i = head;
    while( i != last_node ){
        new_list->insert(list[i].value);
        i = list[i].next_node;
    }
    clear(); //Deleting the old list.
    list = new_list->list; //Copying the new expanded list into the current one.
    head = new_list->head; //Setting the new head.
    empty_list = new_list->empty_list; //Setting the new head to the empty list.
    n_elements = new_list->n_elements; //Setting the number of elements.
    total_elements *= 2; //Setting the total elements
}

//Returns the size of the list.
template <class T>
int linked_list<T>::size() const{
    return n_elements;
}

//Returns the value of the node.
template <class T>
T linked_list<T>::get_value(position p) const{
    return list[p].value;
}

//Set the value of a node of the class.
template <class T>
void linked_list<T>::write(const T& value_in, position p){
    list[p].value = value_in;
}

//Reads an element from the list.
template <class T>
T linked_list<T>::read(position p) const{
    return list[p].value;
}
//Search the value in the list.
template <class T>
bool linked_list<T>::find(const T &value_in) const{
    position i = head;
    while( i != last_node ){
        if(list[i].value == value_in) return true;
        i = list[i].next_node; 
    }
    return false;
}

//Order the list with Merge Sort alorhitm.
template <class T>
typename linked_list<T>::position linked_list<T>::merge_sort( position top ){
    //End condition: I'm checking the last node.
    if( top == last_node || list[top].next_node == last_node ) return top;
    //Finding the middle point of the list.
    position mid = find_mid_node(top);
    position next_to_middle = list[mid].next_node;
    //Dividing the two halves of the list.
    list[mid].next_node = last_node;
    //Sorting the two halves.
    position left = merge_sort(top);
    position right = merge_sort(next_to_middle);
    return merge_chains(left,right);
}

//Finds the mid node in the list.
template <class T>
typename linked_list<T>::position linked_list<T>::find_mid_node( linked_list<T>::position p ){
    if(p == last_node || list[p].next_node == last_node) return p;
    linked_list<T>::position slow = p;
    linked_list<T>::position fast = list[p].next_node;
    while( fast != last_node && list[fast].next_node != last_node ){
        slow = list[slow].next_node;
        fast = list[list[fast].next_node].next_node;
    }
    return slow;
}

//Merges 2 node chains in crescent order(Used for sorting methods).
template <class T>
typename linked_list<T>::position linked_list<T>::merge_chains( position left, position right ){
    if(left == last_node) return right;
    if(right == last_node) return left;
    if( list[left].value <= list[right].value ){
        list[left].next_node = merge_chains(list[left].next_node,right);
        return left;
    }
    else{
        list[right].next_node = merge_chains(left, list[right].next_node);
        return right;
    }
}

/*** Operators Overload ***/
//Operator + (List concatenation)
template <class T>
linked_list<T>& linked_list<T>::operator +( const linked_list<T>& l1 ){
    linked_list<T> *l3 = new linked_list<T>(total_elements + total_elements);
    position p = this->begin();
    while( !this->end(p) ){
        l3->insert(list[p].value);
        p = list[p].next_node;
    }
    p = l1.begin();
    while( !l1.end(p) ){
        l3->insert(l1.list[p].value);
        p = l1.list[p].next_node;
    }
    return *l3;
}

//Operator =(Assigment by copy)
template <class T>
linked_list<T>& linked_list<T>::operator =( const linked_list<T>&l ){
    if( this == &l ) return *this;
    clear();
    //Starting list conditions.
    inizialize(l.total_elements);
    //Iterating through the l list.
    position p = l.begin();
    while( p != last_node ){
        insert(l.list[p].value);
        p = l.list[p].next_node;
    }
    return *this;
} 

//Operator =(Move equal)
template <class T>
linked_list<T>& linked_list<T>::operator =( const linked_list<T>&& rvalue ){
    clear();
    list = rvalue.list;
    head = rvalue.head;
    empty_list = rvalue.empty_list;
    total_elements = rvalue.total_elements;
    n_elements = rvalue.n_elements;
    return *this;
} 

/* Use this if you want to see the whole list with pointers.
template <class T>
void linked_list<T>::test_print(){
    cout << "Nodes: [";
    for( position i = 0; i < total_elements; i++ ){
        cout << " " << list[i].value;
    }
    cout << " ]" << endl << "Ptrs: [";
    for( position i = 0; i < total_elements; i++ ){
        cout << " " << list[i].next_node;
    }
    cout << " ]" << endl << "Head: " << head << "| Empty Head: " << empty_list << endl;
}*/

#endif // LIST_H
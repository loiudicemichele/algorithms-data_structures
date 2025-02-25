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
    typedef list_node<T>* nodeptr;
    friend class linked_list<T>;
    private:
        T value;
        nodeptr next_node;
        nodeptr prev_node;
    public:
        //Constructor
        list_node(): value(0), next_node(nullptr), prev_node(nullptr){}
        list_node( T value_in ): value(value_in), next_node(nullptr), prev_node(nullptr){}
        //Destructors
        ~list_node(){
            next_node = nullptr;
            prev_node = nullptr;   
        }
};

template <class T>
class linked_list: public abstract_list<T,list_node<T>*>{
   //typedef int position;
    public:
    typedef list_node<T>* nodeptr;
        /*** Default Constructor ***/
        linked_list();
        /*** Destructor ***/
        ~linked_list();
        /*** Copy Constructor ***/
        linked_list( const linked_list<T> &l );
        /*** Move Constructor ***/
        linked_list(linked_list<T>&&) noexcept;
        /*** Abstract Methods Implementation ***/
        int size() const override; //Returns the size of the list.
        T get_value(nodeptr) const override;//Returns the value of the node.
        bool empty() const override; //Checks if the list is empty.
        void clear() override; //Clears the elements of the list.
        bool end(nodeptr) const override;//Checks if the node is the last of the list.
        nodeptr begin() const override; //Returns the first element of the list.
        nodeptr last() const override; //Returns the last element of the list.
        nodeptr next(nodeptr) const override; //Returns the next element of n.
        nodeptr previous(nodeptr) const override; //Returns the previous element of n.
        void erase(nodeptr) override; //Removes an element from the list.
        void insert(const T&) override; //Inserts a new element to the bottom of the list.
        void insert_in_position(const T&, nodeptr); //Inserts a a new node in a certain position.
        void write(const T&, nodeptr) override; //Set the value of a node of the class.
        T read(nodeptr) const override; //Reads an element from the list.
        /*** Methods ***/
        bool find(const T &value) const; //Search the value in the list.
        void merge_sort(); //Sorts the list in crescent order(Merge Sort).
        void natural_merge_sort(); //Sorts the list in crescent order(using Natural Sort).  
        void reverse(); //Reverses the order of the list elements.
        /*** Operators ***/
        linked_list<T> operator +(const linked_list<T>&); //Operator + (List concatenation)
        linked_list<T>& operator =(const linked_list<T>&); //Operator =(Assigment by copy)
        void operator =(linked_list<T> &&);
    private:
        /*** PRIVATE METHODS ***/
        nodeptr merge_chains(nodeptr, nodeptr);//Merges 2 node chains in crescent order(Used for sorting methods).
        /* |Merge Sort| */
        nodeptr find_mid_node(nodeptr);//Find the mid node of the list. (Used in merge sort!).
        nodeptr merge_sort(nodeptr);//The actual sorting method.
        /* |Natural Merge Sort| */
        nodeptr natural_merge_sort(nodeptr);
        nodeptr find_next_chain(nodeptr);
        nodeptr binary_search(const T&);
        nodeptr binary_search(const T&,nodeptr,nodeptr);
        /*** PRIVATE ATTRIBUTES ***/
        int n_elements;
        nodeptr head;
};

//Default constructor
template <class T>
linked_list<T>::linked_list(){
    n_elements = 0;
    head = new list_node<T>;
    head->next_node = head;
    head->prev_node = head;
}

//Destructor
template <class T>
linked_list<T>::~linked_list(){
    clear();
}

//Returns the value of the node..
template <class T>
T linked_list<T>::get_value( linked_list<T>::nodeptr p ) const{
    return p->value;
}

//Copy Constructor
template <class T>
linked_list<T>::linked_list( const linked_list<T> &l ){
    n_elements = 0;
    head = new list_node<T>;
    head->prev_node = head;
    head->next_node = head;
    nodeptr iterator = l.begin();
    while( !l.end(iterator) ){
        insert(iterator->value);
        iterator = iterator->next_node;
    }
}

//Move constructor
template <class T>
linked_list<T>::linked_list( linked_list<T>&& rvalue ) noexcept{
    head = rvalue.head;
    n_elements = rvalue.n_elements;
    rvalue.head = nullptr;
}
//Checks if the list is empty
template <class T>
bool linked_list<T>::empty() const{
    return(head == head->next_node);
}
//Clear the elements of the list
template <class T>
void linked_list<T>::clear(){
    n_elements = 0;
    while( !empty() ){
        erase(begin());
    }
    delete head;
}

//Returns the first element of the list.
template <class T>
typename linked_list<T>::nodeptr linked_list<T>::begin() const{
    return (head->next_node);
}

//Returns the last element of the list.
template <class T>
typename linked_list<T>::nodeptr linked_list<T>::last() const{
    return head->prev_node;
}

//Checks if the node is the last of the list.
template <class T>
bool linked_list<T>::end( linked_list<T>::nodeptr p ) const{
    return( head == p );
}

template <class T>
void linked_list<T>::erase( linked_list<T>::nodeptr n ){   
    if( n == nullptr || empty() ) return;
    n->prev_node->next_node = n->next_node;
    n->next_node->prev_node = n->prev_node;
    delete n;
    n_elements--; 
}

//Returns the next element of n.
template <class T>
typename linked_list<T>::nodeptr linked_list<T>::next( linked_list<T>::nodeptr n ) const{
    return n->next_node;
}

//Returns the previous element of n.
template <class T>
typename linked_list<T>::nodeptr linked_list<T>::previous( linked_list<T>::nodeptr n ) const{
    return n->prev_node;
}

//Inserts a new element to the bottom of the list.
template <class T>
void linked_list<T>::insert( const T &value ){
    nodeptr new_node = new list_node<T>(value);
    nodeptr iterator = begin();
    while( !end(iterator) && iterator->value < value ) iterator = iterator->next_node;
    new_node->next_node = iterator;
    new_node->prev_node = iterator->prev_node;
    iterator->prev_node->next_node = new_node;
    iterator->prev_node = new_node;
    n_elements++;
}

//Returns the numer of elements in the list.
template <class T>
int linked_list<T>::size() const{
    return n_elements;
}


//Set the value of a node of the class.
template <class T>
void linked_list<T>::write(const T &value_in, linked_list<T>::nodeptr p ){
    if(p != nullptr) p->value = value_in;
}

//Reads an element from the list.
template <class T>
T linked_list<T>::read( nodeptr p ) const{
    return p->value;
} 

//Reverses the order of the elements in a list by changing the pointers of each node.
template <class T>
void linked_list<T>::reverse(){
    if(head->next_node == head) return; //The list is empty
    nodeptr prev = head;
    nodeptr current = last();
    head->next_node = current;
    //Scanning the list in reverse order.
    while( current->prev_node != head ){
        //Inverting the direction of previous and next pointers.
        current->next_node = current->prev_node;
        current->prev_node = prev;
        prev = current;
        current = current->next_node;
    }
    //Setting the pointers of the last node, and the sentinel node.
    current->next_node = current->prev_node;
    current->prev_node = prev;
    head->prev_node = current;
}

//Search the value in the list.
template <class T>
bool linked_list<T>::find( const T &value ) const{
    nodeptr p = begin();
    while( !end(p) && value >= p->value ){
        if( p->value == value ) return true;
        p = p->next_node;
    }
    return false;
}

//Merges 2 node chains in crescent order(Used for sorting methods).
template <class T>
typename linked_list<T>::nodeptr linked_list<T>::merge_chains( nodeptr left, nodeptr right ){
    if(left == head) return right; //If left chain is null, the last chain to link is the right one. 
    if(right == head) return left; //If the right chain is null, the last chain to link is the left one.
    //Defining which node to link with the nexts.
    if( left->value <= right->value ){
        //If the left node is less than right one, we attach the left and define the next recursively
        left->next_node = merge_chains(left->next_node,right);
        left->next_node->prev_node = left;
        return left;
    }
    else{
        //If the right node is less than left one, we attach the left and define the next recursively
        right->next_node = merge_chains(left, right->next_node);
        right->next_node->prev_node = right;
        return right;
    }
}

//Finds the next chain start.
template <class T>
typename linked_list<T>::nodeptr linked_list<T>::find_next_chain( nodeptr start_chain ){
    //Checking if the inputted chain is the last one.
    if(start_chain == head || start_chain->next_node == head ) return head;
    nodeptr next_chain = start_chain; 
    //Iterating untill we find a non crescent value in the chain.
    while( next_chain->next_node != head && next_chain->next_node->value >= next_chain->value ){
        next_chain = next_chain->next_node;
    }
    nodeptr unlink_chain = next_chain; 
    next_chain = next_chain->next_node; //Defining the first node of the next chain.
    unlink_chain->next_node = head; //Unlinking the left chain.
    return next_chain;
}  

//Natural sorting.
template <class T>
//Find the next consecutive chain (of the one passed as input) of ordered numbers
typename linked_list<T>::nodeptr linked_list<T>::natural_merge_sort( nodeptr chain_start ){
    //Finding all the series of chains while going down in the recusion tree
    if(chain_start == head || chain_start->next_node == head) return chain_start;
    //Defining the left chain.
    nodeptr left_chain = chain_start;
    //Finding (if it exists) the right chain.
    nodeptr right_chain = find_next_chain(left_chain);
    //If it doesn't exist, we don't have a right chain to merge the left with.
    if( right_chain == head ) return left_chain;
    //Otherwise we recurse obtaining the right chain by merging the other chains
    right_chain = natural_merge_sort(right_chain);
    //We merge the two chains found ordering them.
    return merge_chains(left_chain, right_chain); 
}

//Finds the mid node in the list.
template <class T>
typename linked_list<T>::nodeptr linked_list<T>::find_mid_node( linked_list<T>::nodeptr node ){
    if(node == nullptr || node->next_node == nullptr) return node;
    linked_list<T>::nodeptr slow = node;
    linked_list<T>::nodeptr fast = node->next_node;
    while( fast != head && fast->next_node != head ){
        slow = slow->next_node;
        fast = fast->next_node->next_node;
    }
    return slow;
}

//Order the list with Merge Sort alorhitm.
template <class T>
typename linked_list<T>::nodeptr linked_list<T>::merge_sort( nodeptr top ){
    //End condition: I'm checking the last node.
    if( top == this->head || top->next_node == this->head ) return top;
    //Finding the middle point of the list.
    nodeptr mid = find_mid_node(top);
    nodeptr next_to_middle = mid->next_node;
    //Dividing the two halves of the list.
    mid->next_node = this->head;
    /* X */
    //Sorting the two halves.
    nodeptr left = merge_sort(top);
    nodeptr right = merge_sort(next_to_middle);
    return merge_chains(left,right);
}

//Call of _natural_merge_sort private procedure on the head of the list.
template <class T>
void linked_list<T>::natural_merge_sort(){
    head->next_node = natural_merge_sort(head->next_node);
    nodeptr p = begin();
    for( int i = 0; i < this->n_elements-1; i++ ) p = p->next_node;
    head->prev_node = p; //Reattaching the next pointer of the last node to the head.
    head->next_node->prev_node = head; //Setting the sentinel node to the head previous node pointed.
    p->next_node = head; //Reattaching the head node to the last element that might be changed.
}

//Call of _merge_sort private procedure on the head of the list.
template <class T>
void linked_list<T>::merge_sort(){
    head->next_node = merge_sort(head->next_node);
    nodeptr p = begin();
    for( int i = 0; i < this->n_elements-1; i++ ) p = p->next_node;
    head->prev_node = p; //Reattaching the next pointer of the last node to the head.
    head->next_node->prev_node = head; //Setting the sentinel node to the head previous node pointed.
    p->next_node = head; //Reattaching the head node to the last element that might be changed.
}

/*
template <class T>
typename linked_list<T>::nodeptr linked_list<T>::binary_search(const T& value){
    binary_search(value,head,last());
}

template <class T>
typename linked_list<T>::nodeptr 
linked_list<T>::binary_search(const T& value, nodeptr left_ptr, nodeptr right_ptr ){
    if(left_ptr == right_ptr) return false;
    nodeptr mid = find_mid_node(left_ptr);
    if( value == mid->value ) return true;
    if( value > left_ptr->value ) binary_search(mid, right_ptr);
    else binary_search(left_ptr, mid);
}*/

/*** Operators Overload ***/
//Operator + (List concatenation)
template <class T>
linked_list<T> linked_list<T>::operator +( const linked_list<T> &l1 ){
    linked_list<T> l3;
    typename linked_list<T>::nodeptr p;
    p = this->begin();
    while( !this->end(p) ){
        l3.insert(p->value);
        p = this->next(p);
    }
    p = l1.begin();
    while( !l1.end(p) ){
        l3.insert(p->value);
        p = l1.next(p);
    }
    return l3;
}

//Operator =(Assigment by copy).
template <class T>
linked_list<T>& linked_list<T>::operator =( const linked_list<T> &l ){
    if( this == &l ) return *this;
    clear();
    linked_list();
    linked_list<T>::nodeptr p;
    n_elements = 0;
    p = l.begin();
    while( !l.end(p) ){;
        insert(p->value);
        p = l.next(p);
    }
    insert(p->value);
    return *this;
}

//Operator =(Assign the rvalue to the current obj).
template <class T>
void linked_list<T>::operator =( linked_list<T> &&l ){
    clear();
    head = l.head;
    n_elements = l.n_elements;
    l.head = new list_node<T>;
    l.head->next_node = l.head;
    l.head->prev_node = l.head;
}

#endif // LIST_H
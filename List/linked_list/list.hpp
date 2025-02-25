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
    public:
        //Constructor
        list_node( T value_in ): value(value_in), next_node(nullptr){}
        //Destructors
        ~list_node(){ next_node = nullptr;}
};

template <class T>
class linked_list : public abstract_list<T, list_node<T>*>{
   //typedef int position;
    public:
    typedef list_node<T>* nodeptr;
        /*** Default Constructor ***/
        linked_list();
        /*** Destructor ***/
        ~linked_list();
        /*** Copy Constructor ***/
        linked_list(linked_list<T> &);
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
        void bubble_sort(); //Sorts the list in crescent order(using Bubble Sort).
        void merge_sort(){head = merge_sort(head);} //Sorts the list in crescent order(Merge Sort).
        void natural_merge_sort(){head = natural_merge_sort(head);} //Sorts the list in crescent order(using Natural Sort).  
        void reverselist(); //Reverses the order of the list elements.
        bool find( const T &value ) const; //Search the value in the list.
        /*** Operators ***/
        linked_list<T> operator +( const linked_list<T>& ); //Operator + (List concatenation)
        void operator =( linked_list<T>&& ); //Operator =(Assigment by copy)
        linked_list<T>& operator =( const linked_list<T>& ); //Operator =(Assigment by copy)
        
    private:
        /*** PRIVATE METHODS ***/
        nodeptr merge_chains(nodeptr, nodeptr);//Merges 2 node chains in crescent order(Used for sorting methods).
        /* |Merge Sort| */
        nodeptr find_mid_node(nodeptr);//Find the mid node of the list. (Used in merge sort!).
        nodeptr merge_sort(nodeptr);//The actual sorting method.
        /* |Natural Merge Sort| */
        nodeptr natural_merge_sort(nodeptr);
        nodeptr find_next_chain(nodeptr);
        /*** PRIVATE ATTRIBUTES ***/
        int n_elements;
        nodeptr head;
};

//Default constructor
template <class T>
linked_list<T>::linked_list(){
    n_elements = 0;
    head = nullptr;
}

//Destructor
template <class T>
linked_list<T>::~linked_list(){
    while( !empty() ){
        erase(begin());
    }
}
//Returns the value of the node..
template <class T>
T linked_list<T>::get_value( linked_list<T>::nodeptr p ) const{
    return p->value;
}

//Move Constructor
template <class T>
linked_list<T>::linked_list( linked_list<T> &l ){
    n_elements = l.n_elements;
    nodeptr iterator1 = l.begin();
    head = new list_node<T>(iterator1->value);
    nodeptr iterator2 = head;
    while( !l.end(iterator1) ){
        iterator1 = iterator1->next_node;
        iterator2->next_node = new list_node<T>(iterator1->value);
        iterator2 = iterator2->next_node;
    }
}

//Transport constructor
template <class T>
linked_list<T>::linked_list( linked_list<T>&& rvalue ) noexcept{
    head = rvalue.head;
    n_elements = rvalue.n_elements;
    rvalue.head = nullptr;
}
//Checks if the list is empty
template <class T>
bool linked_list<T>::empty() const{
    return(head==nullptr);
}
//Clear the elements of the list
template <class T>
void linked_list<T>::clear(){
    n_elements = 0;
    while( !empty() ){
        erase(begin());
    }
}

//Returns the first element of the list.
template <class T>
typename linked_list<T>::nodeptr linked_list<T>::begin() const{
    return (head);
}

//Returns the last element of the list.
template <class T>
typename linked_list<T>::nodeptr linked_list<T>::last() const{
    nodeptr tmp;
    tmp = head;
    while( tmp->next_node != nullptr ) tmp = tmp->next_node;
    return tmp;
}

//Checks if the node is the last of the list.
template <class T>
bool linked_list<T>::end( linked_list<T>::nodeptr p ) const{
    return(last() == p );
}

template <class T>
void linked_list<T>::erase( linked_list<T>::nodeptr n ){
    if( n == nullptr || empty() ) return;
    if( n == head ){
        head = head->next_node;
        delete n;
        return;
    }
    nodeptr tmp = head;
    while( tmp->next_node != n && tmp->next_node != nullptr ) tmp = tmp->next_node; 
    if( tmp->next_node != nullptr ){
        tmp->next_node = n->next_node;
        delete n;
    }
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
    if( !empty() && n != head ){
        nodeptr tmp = head;
        while( tmp->next_node != n && tmp->next_node != nullptr ){
            tmp = tmp->next_node;
        }
        return tmp;
    } else if ( n == head ) return head;
    else return nullptr;
}

//Inserts a new element to the bottom of the list.
template <class T>
void linked_list<T>::insert( const T &value ){
    nodeptr n = new list_node<T>(value);
    nodeptr tmp;
    if( head == nullptr ) head = n;
    else{
        tmp = head;
        while( tmp->next_node != nullptr ){
            tmp = tmp->next_node;
        }
        tmp->next_node = n;
    }
    n_elements++;
}

//Inserts a a new node in a certain position.
template <class T>
void linked_list<T>::insert_in_position( const T &value, linked_list<T>::nodeptr n ){
    nodeptr new_node = new list_node<T>(value);
    if ( n == head ){
        new_node->next_node = head;
        head = new_node;
    } else{
        nodeptr tmp = previous(n);
        new_node->next_node = tmp->next_node;
        tmp->next_node = new_node;
    }
    n_elements++;
    return;
}

//Returns the numer of elements in the list.
template <class T>
int linked_list<T>::size() const{
    return n_elements;
}


//Set the value of a node of the class.
template <class T>
void linked_list<T>::write(const T &value_in, linked_list<T>::nodeptr p ){
    p->value = value_in;
}

//Reads an element from the list.
template <class T>
T linked_list<T>::read( nodeptr p ) const{
    return p->value;
} 

//Sorts the list (Bubble sort).
template <class T>
void linked_list<T>::bubble_sort(){
    bool sorted = true;
    while( sorted ){
        linked_list<T>::nodeptr p;
        p = begin();
        while( p != previous(last()) ){
            if( p->value > p->next_node->value ){
                sorted = false;
                T value_tmp = p->value;
                p->value = p->next_node->value;
                p->next_node->value = value_tmp;
            }
            p = p->next_node;
        }
        if(!sorted) sorted = true;
        else sorted = false;
    }
}

//Order the list with Merge Sort alorhitm.
template <class T>
typename linked_list<T>::nodeptr linked_list<T>::merge_sort( nodeptr head ){
    //End condition: I'm checking the last node.
    if( head == nullptr || head->next_node == nullptr ) return head;
    //Finding the middle point of the list.
    nodeptr mid = find_mid_node(head);
    nodeptr next_to_middle = mid->next_node;
    //Dividing the two halves of the list.
    mid->next_node = nullptr;
    //Sorting the two halves.
    nodeptr left = merge_sort(head);
    nodeptr right = merge_sort(next_to_middle);
    return merge_chains(left,right);
}

//Finds the mid node in the list.
template <class T>
typename linked_list<T>::nodeptr linked_list<T>::find_mid_node( linked_list<T>::nodeptr node ){
    if(node == nullptr || node->next_node == nullptr) return node;
    linked_list<T>::nodeptr slow = node;
    linked_list<T>::nodeptr fast = node->next_node;
    while( fast != nullptr && fast->next_node != nullptr ){
        slow = slow->next_node;
        fast = fast->next_node->next_node;
    }
    return slow;
}

//Natural sorting.
template <class T>
typename linked_list<T>::nodeptr linked_list<T>::natural_merge_sort( nodeptr chain_start ){
    if(chain_start == nullptr || chain_start->next_node == nullptr) return chain_start;
    nodeptr left_chain = chain_start;
    nodeptr right_chain = find_next_chain(left_chain);
    if( right_chain == nullptr ) return left_chain;
    right_chain = natural_merge_sort(right_chain);
    return merge_chains(left_chain, right_chain); 
}

//Finds the next chain start.
template <class T>
typename linked_list<T>::nodeptr linked_list<T>::find_next_chain( nodeptr start_chain ){
    if(start_chain == nullptr || start_chain->next_node == nullptr ) return nullptr;
    nodeptr next_chain = start_chain;
    while( next_chain->next_node != nullptr && next_chain->next_node->value >= next_chain->value ){
        next_chain = next_chain->next_node;
    }
    nodeptr unlink_chain = next_chain;
    next_chain = next_chain->next_node;
    unlink_chain->next_node = nullptr;
    return next_chain;
}   

//Merges 2 node chains in crescent order(Used for sorting methods).
template <class T>
typename linked_list<T>::nodeptr linked_list<T>::merge_chains( nodeptr left, nodeptr right ){
    if(left == nullptr) return right;
    if(right == nullptr) return left;
    if( left->value <= right->value ){
        left->next_node = merge_chains(left->next_node,right);
        return left;
    }
    else{
        right->next_node = merge_chains(left, right->next_node);
        return right;
    }
}

//Reverses the order of the elements in a list.
template <class T>
void linked_list<T>::reverselist(){
    linked_list *new_list = new linked_list<T>();
    nodeptr p = last();
    while( p != begin() ){
        new_list->insert(p->value);
        p = previous(p);
    }
    new_list->insert(p->value);
    clear();
    *this = *new_list;
    delete new_list;
}

//Search the value in the list.
template <class T>
bool linked_list<T>::find( const T &value ) const{
    nodeptr p = begin();
    while( !end(p) ){
        if( p->value == value ) return true;
        p = p->next_node;
    }
    return false;
}

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
    l3.insert(p->value);
    p = l1.begin();
    while( !l1.end(p) ){
        l3.insert(p->value);
        p = l1.next(p);
    }
    l3.insert(p->value);
    return l3;
}

//Operator =(Assigment by copy).
template <class T>
linked_list<T>& linked_list<T>::operator =( const linked_list<T> &l ){
    if( this == &l ) return *this;
    //Don't know why I can't use destructor.
    clear();
    linked_list<T>::nodeptr p;
    n_elements = l.get_n_elements();
    p = l.begin();
    while( !l.end(p) ){;
        insert(p->value);
        p = l.next(p);
    }
    insert(p->value);
    return *this;
}

//Equal operator for r-values.
template <class T>
void linked_list<T>::operator =( linked_list<T>&& l ){
    clear();
    head = l.head;
    l.head = nullptr;
}

#endif // LIST_H
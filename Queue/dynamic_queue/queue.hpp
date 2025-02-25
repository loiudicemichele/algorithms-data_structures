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

#ifndef QUEUE
#define QUEUE

#include <iostream>
#include "../abstract_queue.hpp"
using namespace std;

template <class T> class queue;
template <class T>
class stack_node{
    typedef stack_node<T>* nodeptr;
    friend class queue<T>;
    public:
        stack_node(): next_node(nullptr) {}
        stack_node( T value_in ): value(value_in), next_node(nullptr) {}  
        ~stack_node() { next_node = nullptr; }
    private:
        T value;
        nodeptr next_node;
};

template <class T>
class queue : public abstract_queue<T, stack_node<T>*>{
    public:
        typedef typename abstract_queue<T, stack_node<T>*>::position nodeptr;
        /*** Constructors ***/
        queue(){inizialize();}; //Default constructor.
        queue(const queue<T>&); //Copy Constructor.
        queue(const queue<T>&&) noexcept; //Copy Constructor.
        ~queue(); //Destructor.
        /*** Abstract Methods Implementation ***/
        int size() const override; //Returns the size of the queue.
        void enqueue(T) override; //Inserts an element on the queue head.
        void dequeue() override; //Removes the value on the queue's tail..
        T read() const override; //Reads the element on the tail.
        bool empty() const override; //Check if the queue is empty.
        void clear() override; //Removes all the elements from the queue.
        /*** Methods ***/
        void reverse(); //Reverses the queue.
        /*** Operators ***/
        queue<T>& operator =(const queue<T>&); //Operator =
        bool operator ==(const queue<T>&); //Operator ==
        queue<T>& operator +(const queue<T>&); //Operator + (Not commutative!)
        void operator =(queue<T>&&); //Move Operator
    private:
        /*** Private methods ***/
        void inizialize(); //Inizializes the queue.
        /*** Private attributes ***/
        int n_elements;
        nodeptr head;
        nodeptr tail;
};

/*** Constructors ***/
//Copy Constructor.
template <class T>
queue<T>::queue(const queue<T>& q){
    inizialize();
    nodeptr iterator = q.head;
    while( iterator != nullptr ){
        enqueue(iterator->value);
        iterator = iterator->next_node;
    }
}

//Move Constructor.
template <class T>
queue<T>::queue(const queue<T>&& rvalue) noexcept{
    head = rvalue.head;
    tail = rvalue.tail;
    n_elements = rvalue.n_elements;
    rvalue.head = rvalue.tail = nullptr;
}   

//Destructor.
template <class T>
queue<T>::~queue(){
    clear();
}

/*** Methods ***/
template <class T>
int queue<T>::size()const{
    return n_elements;
}

//Inserts an element on the queue head.
template <class T>
void queue<T>::enqueue(T value){
    nodeptr new_node = new stack_node<T>(value);
    if(head == nullptr) head = tail = new_node;
    else{ 
        tail->next_node = new_node;
        tail = tail->next_node;
    }//We're removing from the head, and inserting into the tail.
    n_elements++;
}

//Returns the value on the queue's tail and removes it.
template <class T>
void queue<T>::dequeue(){
    //We assume we can't call dequeue with empty queue.
    //if(head == nullptr) return nullptr;
    nodeptr to_delete;
    to_delete = head; //We're removing from the head, and inserting into the tail.
    //If the queue has one node only, reset the pointers.
    if( head == tail ){
        head = tail = nullptr;
    }else{
        head = head->next_node;
    }
    to_delete->next_node = nullptr;
    delete to_delete;
    n_elements--;
} 

//Reads the element on the tail.
template <class T>
T queue<T>::read() const{
    //We assume we can't call dequeue with empty queue.
    //if(head == nullptr) return nullptr;
    return head->value;
} 

//Check if the queue is empty.
template <class T>
bool queue<T>::empty() const{
    return (head == nullptr);
}

//Inizializes the queue.
template <class T>
void queue<T>::inizialize(){
    head = tail = nullptr;
    n_elements = 0;
}

//Reverses the queue.
template <class T>
void queue<T>::reverse(){
    queue<T> *reversed_queue = new queue<T>;
    nodeptr iterator = head;
    reversed_queue->head = reversed_queue->tail = new stack_node<T>(iterator->value);
    while( iterator->next_node != nullptr ){
        iterator = iterator->next_node;
        nodeptr new_node = new stack_node<T>(iterator->value);
        new_node->next_node = reversed_queue->head;
        reversed_queue->head = new_node;
    }
    clear();
    *this = *reversed_queue;
} 

//Removes all the elements from the queue.
template <class T>
void queue<T>::clear(){
    while(!empty()) dequeue();
}

/*** Operators ***/
//Operator =
template <class T>
queue<T>& queue<T>::operator =(const queue<T>& q){
    clear();
    inizialize();
    nodeptr iterator = q.head;
    while( iterator != nullptr ){
        enqueue(iterator->value);
        iterator = iterator->next_node;
    }
    return *this;
} 

//Operator ==
template <class T>
bool queue<T>::operator ==(const queue<T>& q){
    if( this == &q )return true;
    if( n_elements != q.n_elements ) return false;
    nodeptr iterator_q1 = head;
    nodeptr iterator_q2 = q.head;
    while( head != nullptr ){
        if( iterator_q1->value != iterator_q2 ) return false;
        iterator_q1 = iterator_q1->next_node;
        iterator_q2 = iterator_q2->next_node;
    }
    return true;
} 

//Operator + (Not commutative!)
template <class T>
queue<T>& queue<T>::operator +(const queue<T>& q){
    queue<T> *sum = new queue<T>;
    nodeptr iterator = head;
    while( iterator != nullptr ){
        sum->enqueue(iterator->value);
        iterator = iterator->next_node;
    }
    iterator = q.head;
    while( iterator != nullptr ){
        sum->enqueue(iterator->value);
        iterator = iterator->next_node;
    }
    return *sum;
} 

//Move Operator
template <class T>
void queue<T>::operator =(queue<T>&& rvalue){
    clear();
    head = rvalue.head;
    tail = rvalue.tail;
    n_elements = rvalue.n_elements;
    rvalue.head = rvalue.tail = nullptr;
}

#endif // QUEUE
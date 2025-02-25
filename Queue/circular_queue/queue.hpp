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

template <class T>
class queue : public abstract_queue<T, int>{
    public:
        typedef typename abstract_queue<T, int>::position position;
        const typename abstract_queue<T, int>::position empty_queue = -1;
        const int default_dimension = 10;
        /*** Constructors ***/
        queue(); //Default constructor.
        queue(position); //Default constructor.
        queue(const queue<T>&); //Copy Constructor.
        queue(const queue<T>&&) noexcept; //Copy Constructor.
        ~queue(); //Destructor.
        /*** Methods ***/
        int size() const override; //Returns the size of the queue.
        void enqueue(T) override; //Inserts an element on the queue head.
        void dequeue() override; //Removes the value on the queue's tail.
        T read() const override; //Reads the element on the tail.
        bool empty() const override; //Check if the queue is empty.
        void reverse(); //Reverses the queue.
        /*** Operators ***/
        queue<T>& operator =(const queue<T>&); //Operator =
        void operator =(queue<T>&&); //Move Operator
        bool operator ==(const queue<T>&); //Operator ==
        queue<T>& operator +(const queue<T>&); //Operator + (Not commutative!)
    private:
        /*** Private methods ***/
        void doubling(); //Doubles the length of the array.
        void clear(){delete[] values;}; //Removes all the elements from the queue.
        void inizialize(position); //Inizializes the queue.
        /*** Private attributes ***/
        position n_elements;
        position total_elements;
        position head;
        T *values;
};

/*** Constructors ***/

//Default constructor.
template <class T>
queue<T>::queue(){
    inizialize(default_dimension);
} 


//Default constructor.
template <class T>
queue<T>::queue(position array_dimension){
    inizialize(array_dimension);
} 

//Copy Constructor.
template <class T>
queue<T>::queue(const queue<T>& q){
    inizialize(q.total_elements);
    n_elements = q.n_elements;
    head = 0;
    for(position i = 0; i < q.n_elements; i++){
        values[i] = q.values[(q.head+i)%total_elements]; 
    }
} 

//Copy Constructor.
template <class T>
queue<T>::queue(const queue<T>&& q) noexcept{
    values = q.values;
    total_elements = q.total_elements;
    n_elements = q.n_elements;
    head = q.head;
    q.values = nullptr;
} 

//Destructor.
template <class T>
queue<T>::~queue(){
    clear();
} 

/*** Methods ***/
template <class T>
void queue<T>::inizialize( position array_dimension ){
    total_elements = array_dimension;
    n_elements = 0;
    head = empty_queue;
    values = new T[array_dimension];
}

/*** Methods ***/
template <class T>
int queue<T>::size()const{
    return n_elements;
}

//Inserts an element on the queue head.
template <class T>
void queue<T>::enqueue(T value){
    if( head == empty_queue ){head = 0;} 
    if( n_elements == total_elements-1 ){doubling();}
    values[(head+n_elements)%total_elements] = value;
    n_elements++;
} 

//Returns the value on the queue's tail and removes it.
template <class T>
void queue<T>::dequeue(){
    //We assume we can't call dequeue with empty queue. Or else we implements exception/asserts
    //ERROR: if( head == empty_queue ){} 
    head = (head+1)%total_elements;
    n_elements--;
    if(n_elements == 0) head = empty_queue;
}

//Returns the value on the queue's tail and removes it.
template <class T>
T queue<T>::read() const{
    //We assume we can't call dequeue with empty queue. Or else we implements exception/asserts
    //ERROR: if( head == empty_queue ){} 
    T value = values[head];
    return value;
}

//Check if the queue is empty.
template <class T>
bool queue<T>::empty() const{
    return (head == empty_queue);
}

//Reverses the queue.
template <class T>
void queue<T>::reverse(){
    for(position i = 0; i < n_elements/2; i++ ){
        position left_index = (head + i) % total_elements;
        position right_index = (head + n_elements - 1 - i) % total_elements;
        T tmp = values[left_index];
        values[left_index] = values[right_index];
        values[right_index] = tmp;
    }
}

//Doubles the length of the array.
template <class T>
void queue<T>::doubling(){
    T *new_array = new T[total_elements*2];
    for( position i = 0; i < n_elements; i++ ){
        new_array[i] = values[(head+i)%total_elements];
    }
    head = 0;
    total_elements *= 2;
    delete[] values;
    values = new_array;
}

/*** Operators ***/
//Operator =
template <class T>
queue<T>& queue<T>::operator =(const queue<T>& q){
    if( this == &q )return *this;
    delete[] values;
    n_elements = q.n_elements;
    total_elements = q.total_elements;
    values = new T[total_elements];
    for( position i = 0; i < n_elements; i++ ){
        values[(head+i)%total_elements] = q.values[(q.head+i)%q.total_elements];
    }
    return *this;
} 

//Operator ==
template <class T>
bool queue<T>::operator ==(const queue<T>& q){
    if( this == &q ) return true;
    if( n_elements != q.n_elements ) return false;
    for( position i = 0; i < n_elements; i++ ){
        if( values[(head+i)%total_elements] != q.values[(q.head+i)%q.total_elements] ) return false;
    }
    return true;
} 

//Operator + (Not commutative!)
template <class T>
queue<T>& queue<T>::operator +(const queue<T>& q){
    queue<T> *sum = new queue<T>(total_elements + q.total_elements);
    sum->head = 0;
    sum->n_elements = n_elements + q.n_elements;
    for( position i = 0; i < n_elements; i++ ){
        sum->values[(sum->head+i)%sum->total_elements] = values[(head+i)%total_elements];
    }
    for( position i = 0; i < q.n_elements; i++ ){
        sum->values[(sum->head+i+n_elements)%sum->total_elements] = q.values[(q.head+i)%q.total_elements];
    }
    return *sum;
} 

//Move Operator
template <class T>
void queue<T>::operator =(queue<T>&& rvalue){
    delete []values;
    n_elements = rvalue.n_elements;
    total_elements = rvalue.total_elements;
    values = rvalue.values;
    rvalue.values = nullptr;
} 

//Operator << NB: We use by-value parameters passing method in order to not modify the original queue
template <class T>
ostream& operator <<( ostream &output, queue<T> q ){
    output << "Queue: { HEAD-> ";
    while( !q.empty() ){output << "[" << q.read() <<"] "; q.dequeue();}
    output << "<- TAIL }" << endl;
    return output;
}

#endif // QUEUE
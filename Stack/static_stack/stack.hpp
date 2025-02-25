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

#ifndef STACK
#define STACK

#include <iostream>
#include "../abstract_stack.hpp"
using namespace std;

template <class T>
class stack : public abstract_stack<T, int>{
    public:
        typedef typename abstract_stack<T, int>::position position;
        const position empty_stack = -1; 
        const int default_dimension = 10;
        /*** Default Constructor ***/
        stack();
        stack(position); 
        stack(const stack<T>&); /*** Copy Constructor ***/
        stack(stack<T> &&); /*** Move Constructor ***/
        ~stack(){clear();}; /*** Destructor ***/
        /*** Methods ***/
        int size() const override; //Returns the number of elements of the stack.
        void push(T value) override; //Inserts an element on the stack top.
        T seek() const override; //Returns the value on the stack's top.
        bool empty() const override; //Check if the stack is empty.
        void pop() override; //Removes an element from the stack.
        void reverse(); //Reverses the stack.
        /*** Operators ***/
        stack<T>& operator =(const stack<T>&); //Operator =
        void operator =(stack<T>&&); //Move Operator =
        bool operator ==(const stack<T>&); //Operator ==
        stack<T>& operator +(const stack<T>&); //Operator + (Not commutative!)
        //void test_print();
    private:
        /*** Private methods ***/
        void doubling(); //Doubles the length of the array.
        void clear(){delete []values;} //Clears all the elements from the stack.
        /*** Private attributes ***/
        T *values;
        position top;
        position total_elements;

};

/*** Constructor ***/
template <class T>
stack<T>::stack(){
    total_elements = default_dimension;
    top = empty_stack;
    values = new T[default_dimension];
}


template <class T>
stack<T>::stack( position n_elements ){
    total_elements = n_elements;
    top = empty_stack;
    values = new T[total_elements];
}

/*** Copy Constructor ***/
template <class T>
stack<T>::stack( const stack<T>& s ){
    total_elements = s.total_elements;
    top = s.top;
    values = new T[total_elements];
    for( int i = 0; i <= s.top; i++ ){
        values[i] = s.values[i];
    }
}

/*** Move Constructor ***/
template <class T>
stack<T>::stack( stack<T>&& s ){
    total_elements = s.total_elements;
    top = s.top;
    values = s.values;
    s.values = nullptr;
}

/*** Methods ***/
//Inserts an element on the stack top.
template <class T>
void stack<T>::push(T value){
    if( top == total_elements-1 ) doubling();
    top++;
    values[top] = value;
} 

//Returns the size of the stack.
template <class T>
int stack<T>::size() const{
    return (int)(top+1);
}

//Returns the value on the stack's top.
template <class T>
T stack<T>::seek() const{
    return values[top];
} 

//Clears the stack.
template <class T>
bool stack<T>::empty() const{
    return(top == empty_stack);
} 

//Removes an element from the list.
template <class T>
void stack<T>::pop(){
    if( top > empty_stack )top--;
} 
//Reverses the stack.
template <class T>
void stack<T>::reverse(){
    for(position i = 0; i <= top/2; i++ ){
        T tmp = values[i];
        values[i] = values[top-i];
        values[top-i] = tmp;
    }
} 
//Doubles the length of the array.
template <class T>
void stack<T>::doubling(){
    T *new_array = new T[total_elements*2];
    for( position i = 0; i <= top; i++ ){
        new_array[i] = values[i];
    }
    total_elements *= 2;
    delete[] values;
    values = new_array;
}

/*** Operators ***/

//Operator =
template <class T>
stack<T>& stack<T>::operator =(const stack<T>& s){
    delete[] values;
    values = new T[s.total_elements];
    top = s.top;
    total_elements = s.total_elements;
    for( position i = 0; i <= s.top; i++ ){
        values[i] = s.values[i];
    }
    return *this;
}

//Move Operator =
template <class T>
void stack<T>::operator =( stack<T>&& s ){
    delete[] values; //Deleting 
    values = s.values;
    total_elements = s.total_elements;
    top = s.top;
    //Making sure values doesn't get deleted in the destructor of s.
    s.values = nullptr;
}

//Operator ==
template <class T>
bool stack<T>::operator ==(const stack<T>& s){
    if( this == &s ) return true;
    if( top != s.top ) return false; //The two stacks don't have the same length.
    for( position i = 0; i < top; i++ ){
        if( values[i] != s.values[i] ) return false;
    } 
    return true;
}

//Operator + (Not commutative!)
template <class T>
stack<T>& stack<T>::operator +(const stack<T>& s){
    stack<T> *new_stack = new stack<T>(total_elements + s.total_elements);
    for(position i = 0; i <= top; i++ ){new_stack->values[i] = values[i];}
    for(position i = 0; i <= s.top; i++ ){new_stack->values[top+1+i] = s.values[i];}
    new_stack->top = top + s.top +1;
    return *new_stack;
}

/* Use this if you want to debug the stack.
template <class T>
void stack<T>::test_print(){
    cout << "Stack PROVA: { TOP-> ";
    for( position i = 0; i <= top; i++ ){
        cout << "[" << values[i] << "] ";
    }
    cout << "}" << endl;
} */

#endif // STACK
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

template <class T> class stack;
template <class T>
class stack_node{
    typedef stack_node<T>* nodeptr;
    friend class stack<T>;
    public:
        stack_node(): next_node(nullptr) {}
        stack_node( T value_in ): value(value_in), next_node(nullptr) {}  
        ~stack_node() { next_node = nullptr; }
    private:
        T value;
        nodeptr next_node;
};

template <class T>
class stack : public abstract_stack<T, stack_node<T>*>{
    public:
        typedef typename abstract_stack<T, stack_node<T>*>::position nodeptr; //Nodes of the stack.
        stack(): top(nullptr), n_elements(0){}; //Default constructor.
        stack(const stack<T>&); //Copy Constructor.
        stack(stack<T>&&) noexcept; //Move Constructor.
        ~stack(); //Destructor.
        /*** Methods ***/
        virtual int size() const override; //Returns the size of the stack.
        void push(T value) override; //Inserts an element on the stack top.
        T seek() const override; //Returns the value on the stack's top.
        bool empty() const override; //Check if the stack is empty.
        void pop() override; //Removes an element from the stack.
        void clear() override; //Removes all the elements from the stack.
        void reverse(); //Reverses the stack.
        /*** Operators ***/
        stack<T>& operator =(const stack<T>&); //Operator =
        void operator =(stack<T>&&); //Move Operator
        bool operator ==(const stack<T>&); //Operator ==
        stack<T>& operator +(const stack<T>&); //Operator + (Not commutative!) 
    private:
        int n_elements;
        nodeptr top;
};

//Destructor.
template <class T>
stack<T>::~stack(){
    clear();
}

//Move Constructor.
template <class T>
stack<T>::stack( const stack &s ){
    if(s.empty()){
        n_elements = 0;
        top = nullptr;
        return;
    }
    n_elements = s.n_elements;
    nodeptr p = s.top; //Pointer to input stack nodes
    top = new stack_node<T>(p->value);
    nodeptr t = top; //Pointer to local stack nodes.
    while( p != nullptr && p->next_node != nullptr ){
        p = p->next_node;
        t->next_node = new stack_node<T>(p->value);
        t = t->next_node;
    }
    t->next_node = nullptr;
}

/*** Move Constructor ***/
template <class T>
stack<T>::stack(stack<T>&& rvalue) noexcept{
    top = rvalue.top;
    n_elements = rvalue.n_elements;
    rvalue.top = nullptr;
}

//Clears the stack.
template <class T>
void stack<T>::clear(){
    while(!empty()) pop();
    n_elements = 0;
}

//Check if the list is empty.
template <class T>
bool stack<T>::empty() const{
    return(top == nullptr);
}

//Returns the value on the stack's top.
template <class T>
T stack<T>::seek() const{
    return top->value;
}

//Removes an element from the list.
template <class T>
void stack<T>::pop(){
    if( top == nullptr ) return;
    nodeptr n;
    if( top->next_node == nullptr ){
        n = top;
        top = nullptr;
        delete n;
    }
    else{
        n = top;
        top = top->next_node;
        n->next_node = nullptr;
        delete n;
    }
    n_elements--;
}

//Returns the size of the stack.
template <class T>
int stack<T>::size() const{
    return n_elements;
}

//Inserts a new node on the stack's top.
template <class T>
void stack<T>::push( T value ){
    if( top == nullptr ){
        top = new stack_node<T>(value);
        top->next_node = nullptr;
    } 
    else{
        nodeptr new_top = new stack_node<T>(value);
        new_top->next_node = top;
        top = new_top;
    }
    n_elements++;
}

template <class T>
void stack<T>::reverse(){
    stack<T> *new_stack = new stack<T>();
    nodeptr p = top;
    while( p != nullptr ){
        new_stack->push(p->value);
        p = p->next_node;
    }
    clear();
    *this = *new_stack;
}

/*** Operators ***/
// Operator = | NB: We use value parameters passing method in order to not modify the original stack
template <class T>
stack<T>& stack<T>::operator =( const stack<T> &s ){
    clear();
    if(s.empty()){
        n_elements = 0;
        top = nullptr;
        return *this;
    }
    n_elements = s.n_elements;
    nodeptr p = s.top; //Pointer to s nodes
    top = new stack_node<T>(p->value);
    nodeptr t = top; //Pointer to this nodes.
    while( p != nullptr && p->next_node != nullptr ){
        p = p->next_node;
        t->next_node = new stack_node<T>(p->value);
        t = t->next_node;
    }
    t->next_node = nullptr;
    return *this;
}

//Operator + (Not commutative!)
template <class T>
stack<T>& stack<T>::operator +( const stack<T> &s2 ){
    stack<T> *s3 = new stack<T>();
    s3->n_elements = this->n_elements + s2.n_elements;
    nodeptr p = top; //Pointer to input stack nodes.
    s3->top = new stack_node<T>(p->value); //Declaring the top node for.
    nodeptr t = s3->top; //Pointer to local stack nodes (s3).
    while( p != nullptr && p->next_node != nullptr ){
        p = p->next_node;
        t->next_node = new stack_node<T>(p->value);
        t = t->next_node;
    }
    p = s2.top;
    while( p != nullptr ){
        t->next_node = new stack_node<T>(p->value);
        p = p->next_node;
        t = t->next_node;
    }
    t->next_node = nullptr;
    return *s3;
}

//Move Operator =
template <class T>
void stack<T>::operator =( stack<T> &&rvalue ){
    clear();
    top = rvalue.top;
    n_elements = rvalue.n_elements;
    rvalue.top = nullptr;
}

//Operator ==
//Operator ==(Compares two lists)   
template <class T>
bool stack<T>::operator==( const stack<T> &s ){
    if( this == &s ) return true;
    if( this->n_elements != s.n_elements ) return false;
    nodeptr p = top;
    nodeptr t = s.top;
    while( p != nullptr ){
        if( p->value != t->value )  return false;
        p = p->next_node;
        t = t->next_node;
    }
    return true;
};

#endif // STACK
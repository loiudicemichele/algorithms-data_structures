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

#ifndef ABSTRACT_STACK
#define ABSTRACT_STACK
#include <iostream>
using namespace std;
template <class T, class P>
class abstract_stack{
    public:
        typedef P position; //Position of the stack elements.
        typedef T type_element; //Type of elements of the stack
        /*** Abstract Methods Implementation ***/
        virtual int size() const = 0; //Returns the size of the stack.
        virtual void push(T value) = 0; //Inserts an element on the stack top.
        virtual T seek() const = 0; //Returns the value on the stack's top.
        virtual bool empty() const = 0; //Check if the stack is empty.
        virtual void pop() = 0; //Removes an element from the stack.
        virtual void clear() = 0; //Removes all the elements from the stack.
};

template <class T, class P>
void print_stack( ostream &output, abstract_stack<T, P>&s ){
    if(s.empty()) return;
    T value = s.seek();
    output << "[" << s.seek() <<"] ";
    s.pop();
    print_stack(output,s);
    s.push(value);
}

/*** Operators Overload ***/
//Operator << NB: We use value parameters passing method in order to not modify the original stack
template <class T, class P>
ostream& operator <<( ostream &output, abstract_stack<T, P> &s ){
    output << "Stack: { TOP-> ";
    print_stack(output, s);
    output << "}" << endl;
    return output;
}

#endif //ABSTRACT_STACK
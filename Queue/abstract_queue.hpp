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

#ifndef ABSTRACT_QUEUE
#define ABSTRACT_QUEUE
#include <iostream>
using namespace std;
template <class T, class P>
class abstract_queue{
    public:
        typedef P position; //Position of the list elements.
        typedef T type_element; //Type of elements of the queue
        /*** Abstract Methods Implementation ***/
        virtual int size() const = 0; //Returns the size of the queue.
        virtual void enqueue(T) = 0; //Inserts an element on the queue head.
        virtual void dequeue() = 0; //Removes the value on the queue's tail.
        virtual T read() const = 0; //Reads the element on the tail.
        virtual bool empty() const = 0; //Check if the queue is empty.
        virtual void clear() = 0; //Removes all the elements from the queue.
};

/*** Operators Overload ***/
//Operator << NB: We use by-value parameters passing method in order to not modify the original queue
template <class T, class P>
ostream& operator <<( ostream &output, abstract_queue<T,P> &q ){
    output << "Queue: { HEAD-> ";
    for( int i = 0; i < q.size(); i++ ){
        T value = q.read();
        q.dequeue();
        output << "[" << value <<"] ";
        q.enqueue(value);
    }
    //while( !q.empty() ){output << "[" << q.dequeue() <<"] ";}
    output << "<- TAIL }" << endl;
    return output;
}

#endif //ABSTRACT_QUEUE
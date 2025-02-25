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

#ifndef ABSTRACT_LIST
#define ABSTRACT_LIST
#include <iostream>
using namespace std;
template <class T, class P>
class abstract_list {
    public:
        typedef P position; //Position of the list elements.
        typedef T type_element; //Type of elements of the list
        /*** Methods ***/
        virtual int size() const = 0; //Returns the size of the list.
        virtual T get_value(position) const = 0;//Returns the value of the node.
        virtual bool empty() const = 0; //Checks if the list is empty.
        virtual void clear() = 0; //Clears the elements of the list.
        virtual bool end(position) const = 0;//Checks if the node is the last of the list.
        virtual position begin() const = 0; //Returns the first element of the list.
        virtual position last() const = 0; //Returns the last element of the list.
        virtual position next(position) const = 0; //Returns the next element of n.
        virtual position previous(position) const = 0; //Returns the previous element of n.
        virtual void erase(position) = 0; //Removes an element from the list.
        virtual void insert(const type_element&) = 0; //Inserts a new element to the bottom of the list.
        virtual void write(const type_element&, position) = 0; //Set the value of a node of the class.
        virtual type_element read(position) const = 0; //Reads an element from the list.
        /*** Operators ***/
        bool operator ==(const abstract_list<T,P>&); //Operator ==(Compares two lists.)
};

/*** Operators Overload ***/

//Operator ==(Compares two lists)   
template <class T, class P>
bool abstract_list<T,P>::operator==( const abstract_list<T,P> &l ){
    if( this == &l ) return true;
    if( size() != l.size() ) return false;
    position p = begin();
    position t = l.begin();
    while( !end(p) ){
        if( get_value(p) != l.get_value(t) )return false;
        p = next(p);
        t = l.next(t);
    }
    return true;
}

template <class T, class P>
ostream& operator << ( ostream& output, const abstract_list<T, P> &l ){
    typename abstract_list<T,P>::position p;
    p = l.begin();
    output << "LIST: { ";
    while( !l.end(p) ){
        output << l.get_value(p) << "->";
        p = l.next(p);
    }
    output << "{NULL} }" << std::endl;
    return output;
}

#endif //ABSTRACT_LIST
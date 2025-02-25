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

#ifndef ABSTRACT_SET
#define ABSTRACT_SET
#include <iostream>
using namespace std;
template <class T, class P>
class abstract_set{
    public:
        typedef P position; //Position of the list elements.
        typedef T type_element; //Type of elements of the queue
        /*** Abstract Methods Implementation ***/
        virtual bool empty() const = 0; //Checks if the set is empty.
        virtual void erase(const T&) = 0; //Removes an element from the set.
        virtual void insert(const T&) = 0; //Inserts a new element to the bottom of the set.
        virtual int size() const = 0; //Returns the size of the set.
        virtual bool contains(const T&)const = 0; //Search the value in the set and returns the search result.
    private:
        virtual position find(const T &) const = 0; //Search the value in the set and return his pointer.
        virtual void clear() = 0; //Clears the elements of the set.
};
#endif //ABSTRACT_SET
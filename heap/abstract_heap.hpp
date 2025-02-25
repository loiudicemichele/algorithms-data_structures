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

#ifndef ABSTRACT_HEAP
#define ABSTRACT_HEAP

#include <iostream>
using namespace std;

template <class T, class P>
class abstract_heap{
    public:
        typedef T value;
        typedef P priority;
    
        virtual void insert(const value&, const priority&) = 0; //Inserts an element with his priority.
        virtual value read_min() const = 0; //Reads the element with the lowest priority.
        virtual void delete_min() = 0; //Deletes the element with the lowest priority.
};

#endif
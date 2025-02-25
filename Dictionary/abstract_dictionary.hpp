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

#ifndef ABSTRACT_DICTIONARY
#define ABSTRACT_DICTIONARY
#include <iostream>

template <class K, class V>
class abstract_dictionary{
    public:
        typedef K Key; // Key Type.
        typedef V Value; // Value type.
        typedef pair<K,V> _pair; // Pair type.

        virtual bool empty() const = 0; // Returns true if the dictionary is empty.
        virtual int size() const = 0; // Returns the number of elements of the dictionary.
        virtual void insert(_pair) = 0; // Inserts a pair key-value into the dictionary.
        virtual Value find(Key) const = 0; // Returns the value of a pair with a certain key.
        virtual void erase(Key) = 0; // Removes a pair from the dictionary.
        virtual bool contains(Key) = 0; // Returns true if a key is contained in the dictionary.
};


#endif // ABSTRACT_DICTIONARY

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

#ifndef FUNCTIONS
#define FUNCTIONS
#include <iostream>
#include "../../List/doubly_linked_list/list.hpp"
#include "../dynamic_queue/queue.hpp"
using namespace std;

//Converts a stack to a list
template <class T>
linked_list<T> to_list(queue<T> &q){
    linked_list<T> list;
    while( !q.empty() ){list.insert(q.read()); q.dequeue(); }
    typename linked_list<T>::nodeptr iterator = list.begin();
    while(!list.end(iterator)){
        q.enqueue(list.get_value(iterator));
        iterator = list.next(iterator);
    }
    return list;
};

#endif //FUNCTIONS
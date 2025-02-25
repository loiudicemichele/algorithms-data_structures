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
#include "../dynamic_stack/stack.hpp"
//#include "../../List/doubly_linked_list/list.hpp"
#include "../../List/doubly_linked_list/list.hpp"
using namespace std;

// Converts a stack to a list.
template <class T>
linked_list<T> to_list(stack<T> &stack){
    linked_list<T> list;
    to_list(stack, list);
    return list;
};

// Converts a stack to a list without losing the stack elements.
template <class T>
void to_list(stack<T> &stack, linked_list<T> &list ){
    if(stack.empty()) return;
    T value = stack.seek();
    list.insert(value);
    stack.pop();
    to_list(stack,list);
    stack.push(value);
}


// Converts a list to a stack.
template <class T>
stack<T> to_stack(linked_list<T>& list){
    stack<T> new_stack;
    typename linked_list<T>::nodeptr iterator = list.begin();
    while(!list.end(iterator)){
        new_stack.push(list.get_value(iterator));
        iterator = list.next(iterator);
    }
    return new_stack;
}

// Order the stack in crescent order from the top.
template <class T>
void order_stack(stack<T>& s){
    //The tmp_list is ordered in crescent order.
    linked_list<T>tmp_list = to_list(s);
    tmp_list.reverse();
    s = to_stack(tmp_list);
}

// Deletes all the vlues mutiples of an integer k in the stack.
void delete_multiple(stack<int>& stack, int k){
    if(stack.empty()) return;
    int value = stack.seek();
    stack.pop();
    delete_multiple(stack, k);
    if( (value % k) != 0 ) stack.push(value);
}

// Fibonacci number calculator:

int fibonacci_recursive(int k){
    if(k == 1 || k == 2) return 1;
    return fibonacci_recursive(k-1) + fibonacci_recursive(k-2);
}

int fibonacci_iterative(int k){
    if(k == 1 || k == 2) return 1;
    int i = 3;
    stack<int> s;
    s.push(1);
    s.push(1);
    while(i < k){
        int partial1 = s.seek();
        s.pop();
        int partial2 = s.seek();
        s.pop();
        s.push(partial1);
        s.push(partial1 + partial2);
        i++;
    }
    int result = s.seek();
    s.pop();
    return result + s.seek();
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void _deletes_all_greater(stack<int> &s, int k){
    if(s.empty()) return;
    int value = s.seek();
    s.pop();
    _deletes_all_greater(s,k);
    if(value > k) s.push(value);
}

void deletes_all_greater(stack<int> &s, int k){
    _deletes_all_greater(s,k);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/*
 * Stack reversal. 
 **/
//Reversing using a list.
void reverse(stack<int> &s){
    if(s.empty()) return;
    linked_list<int> tmp;
    while(!s.empty()){
        tmp.insert(s.seek());
        s.pop();
    }
    linked_list<int>::nodeptr iterator = tmp.begin();
    while(!tmp.end(iterator)){
        s.push(tmp.read(iterator));
        iterator = tmp.next(iterator);
    }    
}

//Reversing without other structures.   
void insert_at_bottom(stack<int> &s, int value){
    if(s.empty()){
        s.push(value);
        return;
    }
    int tmp = s.seek();
    s.pop();
    insert_at_bottom(s,value);
    s.push(tmp);
}

void _reverse(stack<int> &s){
    if(s.empty()) return;
    int value = s.seek();
    s.pop();
    _reverse(s);
    insert_at_bottom(s,value);
}



#endif //FUNCTIONS
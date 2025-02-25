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

#include <iostream>
#include "other_functions.hpp"
#include "../static_stack/stack.hpp"
using namespace std;

int main(){
    //cout << fibonacci_iterative(12);
    
    stack<int> l;
    for( int i = 1; i < 15; i++ ) l.push(i);
    cout << l;
    //deletes_all_greater(l,7);
    _reverse(l);
    cout << l;
    /*
    linked_list<int> list = to_list(l);
    cout << "Stack converted do ordered list: " << list;
    cout << l;
    cout << "OPERAZIONE:" <<endl;
    order_stack(l);
    cout << "Modified Set: " << l;
    delete_multiple(l, 2);
    cout << "Deleted Multiples Set: " << l;*/
}
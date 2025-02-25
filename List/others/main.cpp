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
#include "../doubly_linked_list/list.hpp"
using namespace std;

int main(){
    linked_list<int> l,l2,l3;
    for( int i = 1; i < 3; i++ ) l.insert(i);
    l.insert(3);
    for( int i = 3; i >= 1; i-- ) l.insert(i);
    for( int i = 5; i < 10; i++ ) l2.insert(i);
    cout << l2;
    l3 = l + l2;
    cout << l3;
    delete_multiples_of_position(l3);
    cout << l;
    cout << is_palindrome(l);


    
}
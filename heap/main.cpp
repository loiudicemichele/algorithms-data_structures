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
using namespace std;

#include "./heap/heap.hpp"

void initialize(heap<string,int> &p){
    p.insert("a", 9);
    p.insert("b", 13);
    p.insert("c", 11);
    p.insert("d", 16);
    p.insert("e", 18);
    p.insert("f", 22);
    p.insert("g", 20);
    /*
            20
        10      21
    
    */

}

int main(){
    heap<string,int> p;
    initialize(p);
    cout << p.read_min();
    //p.insert(100, 4);
    //cout << p << endl;
    cout << p << endl << endl;
    p.delete_min();
    heap<string,int> f;
    f = p;
    cout << f;

}
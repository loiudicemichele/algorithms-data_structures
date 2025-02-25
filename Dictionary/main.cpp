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

#include "./dictionary.hpp"

void hash_tests(){
    _hash<string> k;
    //cout << k("cane")%3 << endl;
    //cout << k("simone")%3 << endl;
    //cout << k("cane") << endl;
}

int main(){
    hash_tests();

    dictionary<string, int> t;

    pair<string,int> p1("cane", 10);
    pair<string,int> p2("pasta", 20);
    //Generating keys with the same hash value.
    pair<string,int> p3("eanc", 40);
    pair<string,int> p4("aenc", 50);
    pair<string,int> p5("naec", 60);
    //dictionary_pair pair4 = new pair<string,int>("pasta", 70);
    t.insert(p1);
    t.insert(p2);
    t.insert(p3);
    t.insert(p4);
    t.insert(p5);
    cout << t;
    t.erase(p3.first);
    
    cout << t;
    cout << t.find(p5.first);
    t.insert(p3);
    cout << t;
    cout << "Contains test: " << t.contains("eac");
    //cout << "Test: " <<t.find(p1.first);
    
    //t.insert(pair4);
    //t.insert(pair3);
    //t.erase("pasta");
    //t.find("pasta");
}
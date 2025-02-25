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
#include "./knapsack.hpp"

void print_solution(vector<item> items, vector<int> items_picked){
    cout << "| Value | Weight | Fractional " << endl;
    for(int i = 0; i < items.size(); i++ ) 
        cout << i << ": " << items[i].value << " | " << items[i].weight << " | " << items[i].value/items[i].weight << endl;
    cout << "Solution: [" ;
    for(int i = 0; i < items_picked.size(); i++ ) 
        cout << items_picked[i];
    cout << "]" ;
}

int main(){
    //Defining the items of the array
    item t1(10,10, 0);
    item t2(100,20, 1);
    item t3(100,3, 2);
    item t4(50,20, 3);
    item t5(30,40, 4);
    item t6(1,30, 5);
    vector<item> items;
    items.push_back(t1);
    items.push_back(t2);
    items.push_back(t3);
    items.push_back(t4);
    items.push_back(t5);
    items.push_back(t6);
    vector<int> items_picked = backtrack_knapsack(items, 14);
    print_solution(items,items_picked);
};
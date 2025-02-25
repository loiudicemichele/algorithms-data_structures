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
#include "./bst.hpp"
using namespace std;

void inizialize_tree(BST<int> &t){
    typedef BST<int>::nodeptr node;
    node n1 = new tree_node(1);
    node n2 = new tree_node(2);
    node n3 = new tree_node(3);
    node n4 = new tree_node(4);
    node n5 = new tree_node(5);
    node n6 = new tree_node(6);
    node n7 = new tree_node(7);
    node n8 = new tree_node(8);

    t.insert(n4);
    t.insert(n1);
    t.insert(n2);
    t.insert(n7);
    t.insert(n8);
    t.insert(n6);
    t.insert(n3);

    t.delete_node(n2);
    //cout << endl << "Predecessor: " << t.read(t.predecessor(n2)) << endl;
    //cout << "Successor: " << t.read(t.successor(n2)) << endl; 

}

int main(){
    typedef BST<int>::nodeptr node;
    BST<int> t;
    inizialize_tree(t);
    cout << t << endl;
    
    node minimum = t.minimum();
    node maximum = t.maximum();
    cout << endl << "Node with minimum value: " << t.read(minimum) << endl;
    cout << "Node with maximum value: " << t.read(maximum) << endl; 
    cout << "Contains value: " << t.contains(18) <<endl;
}
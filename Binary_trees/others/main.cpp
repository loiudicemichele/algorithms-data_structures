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
#include "../dynamic_binary_trees/binary_tree.hpp"
#include "./other_functions.hpp"
using namespace std;

void inizialize_tree(binary_tree<int> &t){
    /*
    binary_tree<int>::nodeptr n1 = new tree_node(1);
    binary_tree<int>::nodeptr n2 = new tree_node(2);
    binary_tree<int>::nodeptr n3 = new tree_node(3);
    binary_tree<int>::nodeptr n4 = new tree_node(4);
    binary_tree<int>::nodeptr n5 = new tree_node(5);
    binary_tree<int>::nodeptr n6 = new tree_node(6);
    binary_tree<int>::nodeptr n7 = new tree_node(7);
    binary_tree<int>::nodeptr n8 = new tree_node(8);

    t.insert_root(n1);
    t.insert_left_child(n1,n2);
    t.insert_right_child(n1,n3);

    t.insert_left_child(n2,n4);
    t.insert_right_child(n2,n5);

    t.insert_left_child(n3,n6);
    t.insert_right_child(n3,n7);

    t.insert_left_child(n4,n8);

    binary_tree<int>::nodeptr n9 = new tree_node(9);
    t.insert_left_child(n5,n9);*/

    binary_tree<int>::nodeptr n1 = new tree_node(0);
    binary_tree<int>::nodeptr n2 = new tree_node(-6);
    binary_tree<int>::nodeptr n3 = new tree_node(2);
    binary_tree<int>::nodeptr n4 = new tree_node(11);
    binary_tree<int>::nodeptr n5 = new tree_node(-4);
    binary_tree<int>::nodeptr n6 = new tree_node(7);

    t.insert_root(n1);
    t.insert_left_child(n1,n2);
    t.insert_left_child(n2,n4);

    t.insert_right_child(n1,n3);
    t.insert_right_child(n3,n6);
    t.insert_left_child(n3,n5);

}

int main(){
    binary_tree<int> t;
    inizialize_tree(t);
    //cout << t.read(t.get_right_child(t.get_right_child(t.get_root())));
    //cout << t.read(t.get_parent(t.get_right_child(t.get_right_child(t.get_root()))));
    //cout << t.get_level(t.get_right_child(t.get_right_child(t.get_root())));
    //cout << t.get_left_child(t.get_right_child(t.get_right_child(t.get_root())));
    //cout << t.has_left_child(t.get_left_child(t.get_left_child(t.get_root())));
    //t.get_left_child(t.get_left_child(t.get_root()));
    //t.insert_left_child(t.get_right_child(t.get_right_child(t.get_root())),785);
    //cout << t.get_left_child(t.get_right_child(t.get_right_child(t.get_root())));
    //cout << t.read(t.get_left_child(t.get_right_child(t.get_right_child(t.get_root()))));
    //cout << "|" << t.get_height() << endl;
    cout << t << endl << endl;
    
    //multiples(t);
    //cout << "Even tree" << endl << t;
    cout << "Number of Odd nodes in the tree: " << odd(t) << endl;
    cout << "Number of Even leaf nodes in the tree: " << even_leaf(t) << endl;
    cout << "Number of leafs that have an even parent: " << even_leaf(t)<< endl;

    cout << "Number of node divisible by 3: " << divisible_by_3(t)<< endl;

    cout << "Number of leafs that have a parent divisible by 5: " << l2p(t)<< endl;
    
    cout << "Numbers of subtree which sum is equal to k: " << count_subtrees(t,5) << endl;
}
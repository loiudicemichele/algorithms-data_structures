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
#include "../dynamic_trees/tree.hpp"
#include "./other_functions.hpp"
using namespace std;

void inizialize_tree(tree<int> &t){
    
    tree<int>::nodeptr root = new tree_node<int>(5);
    tree<int>::nodeptr node2 = new tree_node<int>(4);
    tree<int>::nodeptr node3 = new tree_node<int>(15);
    tree<int>::nodeptr node4 = new tree_node<int>(6);
    tree<int>::nodeptr node5 = new tree_node<int>(8);
    tree<int>::nodeptr node6 = new tree_node<int>(9);
    tree<int>::nodeptr node7 = new tree_node<int>(21);
    tree<int>::nodeptr node8 = new tree_node<int>(20);
    tree<int>::nodeptr node9 = new tree_node<int>(12);
    tree<int>::nodeptr node10 = new tree_node<int>(11);
    tree<int>::nodeptr node11 = new tree_node<int>(3);
    /*
                       1
                  /         
                2  ->  3  ->  4
               /       |
             5 ->  6   7
    */
    t.insert_root(root);

    t.insert_first_child(root,node2);
    t.insert_next_sibling(node2,node3);
    t.insert_next_sibling(node3,node4);

    t.insert_first_child(node2,node5);
    t.insert_next_sibling(node5,node6);

    t.insert_first_child(node6,node9);
    t.insert_next_sibling(node9,node10);
    t.insert_next_sibling(node10,node11);

    t.insert_first_child(node4,node7);
    t.insert_next_sibling(node7,node8);
};

int main(){
  tree<int> t;
  inizialize_tree(t);
  //cout << t.get_height();
  //cout << find_max_level(t);
  cout << t << endl;
  //sum_of_subtree(t);

  cout << t;
  set_even_parent(t);
  cout << t;
  //in_order_dfs_search(t);
}
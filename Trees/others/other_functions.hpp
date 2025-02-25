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
#include <vector>
#include "../dynamic_trees/tree.hpp"
#include "../../Queue/dynamic_queue/queue.hpp"

using namespace std;

/* ***************************** FIND MAX LEVEL ********************************** */

void find_max_level(tree<int> &t, tree<int>::nodeptr node, int level, vector<int> &v){
    v[level] += t.read(node);
    if(t.has_first_child(node)) find_max_level(t,t.get_first_child(node),level+1,v);
    if(t.has_next_sibling(node)) find_max_level(t,t.get_next_sibling(node),level,v);
}


int find_index_max_value(vector<int> v){
    int max = -1;
    int index = 0;
    for(int i = 0; i < v.size(); i++){
        if(max < v[i]){
            index = i;
            max = v[i];
        } 

    } 
    return index;
}

int find_max_level(tree<int> &t){
    /**
     * I will represent the partial solution with an array, each time i keep track
     * of the level of a node and sum his value to the corrisponding level array position.
     * The solution will be the max of the array value.
     */
    // Inizializing the vector.
    vector<int> sum_count(t.get_height());
    for(int i = 0; i < t.get_height(); i++) sum_count[i] = 0;
    // Calling the solution method
    find_max_level(t,t.get_root(),0,sum_count);
    return find_index_max_value(sum_count);
}

/* *************************************************************** */

void pre_order_dfs_search(tree<int> t, tree<int>::nodeptr node){ 
    cout << "Node: " << t.read(node);
    if(!t.leaf(node)){
        tree<int>::nodeptr first_child = t.get_first_child(node);
        while(!t.last_sibling(first_child)){
            pre_order_dfs_search(t,first_child);
            first_child = t.get_next_sibling(first_child);
        }
        pre_order_dfs_search(t,first_child);
    }
}

void post_order_dfs_search(tree<int> t, tree<int>::nodeptr node){ 
    if(!t.leaf(node)){
        tree<int>::nodeptr first_child = t.get_first_child(node);
        while(!t.last_sibling(first_child)){
            post_order_dfs_search(t,first_child);
            first_child = t.get_next_sibling(first_child);
        }
        post_order_dfs_search(t,first_child);
    }
    cout << "Node: " << t.read(node) << endl;
}

void in_order_dfs_search(tree<int> t, tree<int>::nodeptr node){ 
    if(t.leaf(node)) cout << "Node: " << t.read(node) << endl;
    else{
        tree<int>::nodeptr first_child = t.get_first_child(node);
        in_order_dfs_search(t,first_child);
        cout << "Node: " << t.read(node) << endl;
        while(!t.last_sibling(first_child)){
            first_child = t.get_next_sibling(first_child);
            in_order_dfs_search(t,first_child);
        }
    }
}

void bfs_search(tree<int> &t, tree<int>::nodeptr root){
    queue<tree<int>::nodeptr> bin;
    bin.enqueue(root);
    while(!bin.empty()){
        tree<int>::nodeptr node = bin.read();
        bin.dequeue();
        cout << "Node: " << t.read(node) << endl;
        if(t.has_first_child(node)){
            node = t.get_first_child(node);
            bin.enqueue(node);
            while(!t.last_sibling(node)){
                bin.enqueue(t.get_next_sibling(node));
                node = t.get_next_sibling(node);
            }
        } 
    }
}

void pre_order_dfs_search(tree<int> t){
    if(t.empty()) return;
    cout << "Pre-Order Visit: " << endl;
    pre_order_dfs_search(t,t.get_root());
}

void post_order_dfs_search(tree<int> t){
    if(t.empty()) return;
    cout << "Post-Order Visit: " << endl;
    post_order_dfs_search(t,t.get_root());
}

void in_order_dfs_search(tree<int> t){
    if(t.empty()) return;
    cout << "In-Order Visit: " << endl;
    in_order_dfs_search(t,t.get_root());
}

void bfs_search(tree<int> t){
    if(t.empty()) return;
    cout << "BFS Visit: " << endl;
    bfs_search(t,t.get_root());
}

/* *************************************************************** */
/**
 * The method edit the value of a node, writing the sum of the subtrees.
 */
int _sum_of_subtree(tree<int> &t,tree<int>::nodeptr node){
    int sum = 0;
    if(!t.leaf(node)){
        tree<int>::nodeptr first_child = t.get_first_child(node);
        while(!t.last_sibling(first_child)){
            sum += _sum_of_subtree(t,first_child);
            first_child = t.get_next_sibling(first_child);
        }
        sum += _sum_of_subtree(t,first_child);
    }
    int value = t.read(node);
    t.write(sum,node);
    return (sum+value);
}

void sum_of_subtree(tree<int>&t){
    if(t.empty()) return;
    _sum_of_subtree(t,t.get_root());
}

/* *************************************************************** */
void set_even_parent(tree<int> &t, tree<int>::nodeptr node){
    int value = t.read(node);
    if(t.leaf(node)){
        if(t.has_parent(node) && t.read(t.get_parent(node))%2 == 0) t.write(1,node);
    } else{
        tree<int>::nodeptr first_child = t.get_first_child(node);
        set_even_parent(t,first_child);
        if(t.has_parent(node) && t.read(t.get_parent(node))%2 == 0) t.write(1,node);
        while(!t.last_sibling(first_child)){
            first_child = t.get_next_sibling(first_child);
            set_even_parent(t,first_child);
        }
    }
}

void set_even_parent(tree<int> &t){
    if(t.empty() || t.size() == 1) return;
    set_even_parent(t,t.get_root());
}



#endif //FUNCTIONS
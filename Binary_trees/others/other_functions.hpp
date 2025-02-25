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

#include "../dynamic_binary_trees/binary_tree.hpp"
using namespace std;
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
// Sets as the value node, the number of 
int multiples( binary_tree<int> &t, binary_tree<int>::nodeptr node ){
    int value = t.read(node);
    int left = 0;
    int right = 0;
    if(t.has_left_child(node)){
        left = multiples(t, t.get_left_child(node));
    }   
    if(t.has_right_child(node)){
        right = multiples(t, t.get_right_child(node));
    }
    //Saving the value of the subtrees
    t.write(left + right, node);
    //Return the value based on the even value of the node.
    if(value%2 == 0) return (left + right + 1);
    else return (left + right);
}

void multiples( binary_tree<int> &t ){
    if(t.empty()) return;
    multiples(t, t.get_root());
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void odd(binary_tree<int> &t, binary_tree<int>::nodeptr node, int &odd_result){
    if(t.read(node)%2 == 0) odd_result++;
    if(t.has_left_child(node)) odd(t,t.get_left_child(node),odd_result);
    if(t.has_right_child(node)) odd(t,t.get_right_child(node),odd_result);
}

int odd(binary_tree<int> &t){
    if(t.empty()) return -1;
    int odd_result = 0;
    odd(t,t.get_root(),odd_result);
    return odd_result;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void even_leaf(binary_tree<int> &t, binary_tree<int>::nodeptr node, int &result){
    if((!t.has_left_child(node)) && (!t.has_right_child(node)) && (t.read(node)%2 == 0) ) result++;
    if(t.has_left_child(node)) even_leaf(t,t.get_left_child(node),result);
    if(t.has_right_child(node)) even_leaf(t,t.get_right_child(node),result);
}

int even_leaf(binary_tree<int> &t){
    if(t.empty()) return -1;
    int result = 0;
    even_leaf(t,t.get_root(),result);
    return result;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void leafs_with_even_parent(binary_tree<int> &t, binary_tree<int>::nodeptr node, int &result){
    if((!t.has_left_child(node)) && (!t.has_right_child(node)) //Is a leef
     && t.has_parent(node) && (t.read(t.get_parent(node))%2 == 0) ) result++; //Has an even parent
    if(t.has_left_child(node)) leafs_with_even_parent(t,t.get_left_child(node),result);
    if(t.has_right_child(node)) leafs_with_even_parent(t,t.get_right_child(node),result);
}

int leafs_with_even_parent(binary_tree<int> &t){
    if(t.empty()) return -1;
    int result = 0;
    leafs_with_even_parent(t,t.get_root(),result);
    return result;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
// Calculates the number of nodes that are divisible by 3. 
void divisible_by_3(binary_tree<int> &t,binary_tree<int>::nodeptr node, int &result){
    if(t.read(node)%3 == 0) result++;
    if(t.has_left_child(node)) divisible_by_3(t,t.get_left_child(node),result);
    if(t.has_right_child(node)) divisible_by_3(t,t.get_right_child(node),result);
}

int divisible_by_3(binary_tree<int> &t){
    if(t.empty()) return -1;
    int result = 0;
    divisible_by_3(t,t.get_root(),result);
    return result;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
// Calculates the number of leafs that have a parent divisible by 5
void l2p(binary_tree<int> t, binary_tree<int>::nodeptr node, int &result){
    if((!t.has_left_child(node)) && (!t.has_right_child(node)) 
    && (t.has_parent(node)) && (t.read(t.get_parent(node))%5 == 0) ) result++;
    if(t.has_left_child(node)) l2p(t, t.get_left_child(node),result);
    if(t.has_right_child(node)) l2p(t, t.get_right_child(node),result);
}

int l2p(binary_tree<int> t){
    if(t.empty()) return -1;
    int result = 0;
    l2p(t,t.get_root(),result);
    return result;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/**
 * The method counts the number of subtrees which sum equal to k
 */
int count_subtrees(const binary_tree<int> &t, binary_tree<int>::nodeptr node, const int &k ,int &sum){
    int left = 0, right = 0;
    if(t.has_left_child(node)) left = count_subtrees(t,t.get_left_child(node),k,sum);
    if(t.has_right_child(node)) right = count_subtrees(t,t.get_right_child(node),k,sum);
    
    if(left + t.read(node) == k) sum++;
    if(right + t.read(node) == k) sum++;
    if(!(left==0 || right == 0)) if(left + right + t.read(node) == k) sum++;
    return (left + right + t.read(node));
}

int count_subtrees(const binary_tree<int> &t, const int &k){
    if(t.empty()) return 0;
    int sum = 0;
    count_subtrees(t,t.get_root(),k,sum);
    return sum;
}


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#include <vector>
#include <cmath>
/**
 * The problems requests us to calculate the mean of a binary tree level, for each level of the tree.
 */
void calculate_sum_by_level(binary_tree<double> &tree, binary_tree<double>::position node,  vector<double> &mean_by_level, int level){
    mean_by_level[level] += tree.read(node);
    if(tree.has_left_child(node)) calculate_sum_by_level(tree, tree.get_left_child(node),mean_by_level,level+1);
    if(tree.has_right_child(node)) calculate_sum_by_level(tree, tree.get_right_child(node),mean_by_level,level+1);
}

vector<double> calculate_mean_by_level(binary_tree<double> &tree){
    vector<double> mean_by_level(tree.get_height());
    // If the tree is empty, we do not compute anything.
    if(tree.empty()) return mean_by_level;
    // Otherwise we calculate the sum of the node for each level of the tree.
    calculate_sum_by_level(tree, tree.get_root(),mean_by_level,0);
    /**
     * We calculate the mean of the level knowing that for the k-est level, the number of node is 2^k.
     */
    for(int i = 0; i < mean_by_level.size(); i++){
        mean_by_level[i] /= pow(2,i);
    }
    // Returning the computated value.
    return mean_by_level;
}   

#endif //FUNCTIONS
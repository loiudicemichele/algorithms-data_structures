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
#include "../adjacence_matrix/graphs.hpp"
#include "../support_structure/set.hpp"
using namespace std;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/**
 * Returns true if exists a path in a graph between two nodes which contains colours values.
 * The path must be of the same color of the two nodes.  
 * 
 * Lets visit the graph from node by node, visiting 
 * only path that leads to path_color nodes.
 * We stop when we have not any other path to visit.
 **/ 
bool same_color_path(graph<string> &g, graph<string>::nodeptr node, graph<string>::nodeptr destination, string path_color ){
    if(node == destination) return true;
    list<graph<string>::nodeptr> adjacent = g.adjacent(node);
    list<graph<string>::nodeptr>::nodeptr list_node = adjacent.begin();
    while(!adjacent.end(list_node)){
        graph<string>::nodeptr adjacent_graph_node = adjacent.read(list_node);
        if(g.read(adjacent_graph_node) == path_color && !g.is_marked(adjacent_graph_node)){
            g.mark_node(adjacent_graph_node);
            if(same_color_path(g,adjacent_graph_node,destination,path_color)) return true; 
        }
        list_node = adjacent.next(list_node);  
    }
    return false;
}

bool same_color_path(graph<string> &g, graph<string>::nodeptr n1, graph<string>::nodeptr n2){
    if(g.empty() || !g.exist_node(n1) || !g.exist_node(n2) ) return false;
    string color = g.read(n1);
    if(color != g.read(n2)) return false; // The two nodes does not have the same color.
    g.unmark_all_nodes();
    return same_color_path(g,n1,n2,color);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/**
 * Returns true if exists a path in a graph between two nodes which contains colours values. 
 * The path must not include two adjacent nodes with the same colour
 */

bool _uniform_color_path(graph<string> &g, graph<string>::nodeptr node, graph<string>::nodeptr destination){
    if(node == destination) return true;
    list<graph<string>::nodeptr> adjacent = g.adjacent(node);
    list<graph<string>::nodeptr>::nodeptr iterator = adjacent.begin();
    while(!adjacent.end(iterator)){
        if(g.read(node) != g.read(adjacent.read(iterator)) && !g.is_marked(adjacent.read(iterator))){
            g.mark_node(adjacent.read(iterator));
            if(_uniform_color_path(g,adjacent.read(iterator),destination)) return true;
        }
        iterator = adjacent.next(iterator);
    }
    return false;
}

bool uniform_color_path(graph<string> &g, graph<string>::nodeptr n1, graph<string>::nodeptr n2){
    if(g.empty() || !g.exist_node(n1) || !g.exist_node(n2) ) return false;
    g.unmark_all_nodes();
    g.mark_node(n1);
    return _uniform_color_path(g,n1,n2);
    g.unmark_all_nodes();
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/**
 * Given a directed graph of nodes whoes edges have a weight of 1 or -1  
 * implement a method in C++ that, given two nodes a and b, identifises the number
 * of paths from a to b such that all edges in the corresponding sequence
 * of each path are labled with 1. Additionally, provide the average length of the
 * identifies path.
 *  */

void number_of_paths(graph<int>&g, graph<int>::nodeptr node, graph<int>::nodeptr destination, int &n_paths, int &average, int path_length){
    if(node == destination){
        g.un_mark_node(destination);
        n_paths++;
        average += path_length;
        return;
    }
    list<graph<int>::nodeptr> adjacent_list = g.adjacent(node);
    list<graph<int>::nodeptr>::nodeptr list_node = adjacent_list.begin();
    while(!adjacent_list.end(list_node)){
        if(!g.is_marked(adjacent_list.read(list_node)) && (g.get_weight(node,adjacent_list.read(list_node)) == 1)){
            g.mark_node(adjacent_list.read(list_node));
            number_of_paths(g,adjacent_list.read(list_node),destination,n_paths,average,path_length+1);
        }
        list_node = adjacent_list.next(list_node);
    }
}

// The same method but validate path that only differs by 1 edge.
void number_of_paths_2(graph<int>&g, graph<int>::nodeptr node, graph<int>::nodeptr destination, int &n_paths, int &average, int path_length, set<graph<int>::nodeptr> visited_node){
    if(node == destination){
        n_paths++;
        average += path_length;
        return;
    }
    list<graph<int>::nodeptr> adjacent_list = g.adjacent(node);
    list<graph<int>::nodeptr>::nodeptr list_node = adjacent_list.begin();
    visited_node.insert(node);
    while(!adjacent_list.end(list_node)){
        if(!visited_node.contains(adjacent_list.read(list_node)) && (g.get_weight(node,adjacent_list.read(list_node)) == 1)){
            visited_node.insert(adjacent_list.read(list_node));
            number_of_paths_2(g,adjacent_list.read(list_node),destination,n_paths,average,path_length+1,visited_node);
        }
        list_node = adjacent_list.next(list_node);
    }
}

void number_of_paths(graph<int>&g, graph<int>::nodeptr a, graph<int>::nodeptr b, int &n_paths, int &average){
    n_paths = 0;
    average = 0;
    if(g.empty()) return;
    set<graph<int>::nodeptr> visited_node;
    number_of_paths_2(g,a,b,n_paths,average,0,visited_node);
    if(n_paths != 0) average /= n_paths;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
//Finds the number nodes reachable by node
void count_same(graph<int>&g, graph<int>::nodeptr node, graph<int>::nodeptr comparison, int &n_nodes){
    list<graph<int>::nodeptr> adjacent_list = g.adjacent(node);
    list<graph<int>::nodeptr>::nodeptr iterator = adjacent_list.begin();
    while(!adjacent_list.end(iterator)){
        graph<int>::nodeptr adjacent_node = adjacent_list.read(iterator);
        if(!g.is_marked(adjacent_node)){
            g.mark_node(adjacent_node);
            if(g.read(adjacent_node) == g.read(comparison)) n_nodes++;
            count_same(g,adjacent_node,comparison,n_nodes);
        }
        iterator = adjacent_list.next(iterator);
    }
}

int count_same(graph<int>&g, graph<int>::nodeptr node){
    if(g.empty() || !g.exist_node(node)) return -1;
    int n_nodes = 0;
    if(g.exist_edge(node,node)) n_nodes++;
    g.unmark_all_nodes();
    g.mark_node(node);
    count_same(g,node,node,n_nodes);
    g.unmark_all_nodes();
    return n_nodes;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/**
 * Returns the average of the label values of the nodes reachable from 
 * n1 through paths of length 2.
 *   */

void mean_N2(graph<int> &g, graph<int>::nodeptr node, int &sum,int &n_nodes, int path_length){
    if(path_length == 2){
        sum += g.read(node);
        n_nodes++;
        return;
    }
    list<graph<int>::nodeptr> adjacent_list = g.adjacent(node);
    list<graph<int>::nodeptr>::nodeptr iterator = adjacent_list.begin();
    while(!adjacent_list.end(iterator)){
        graph<int>::nodeptr graph_node = adjacent_list.read(iterator);
        if(!g.is_marked(graph_node) && path_length <= 2){
            g.mark_node(graph_node);
            mean_N2(g,graph_node,sum,n_nodes,path_length+1);
        }
        iterator = adjacent_list.next(iterator);
    }
}

float mean_N2(graph<int> g, graph<int>::nodeptr node){
    if(g.empty() || !g.exist_node(node)) return -1;
    int sum = 0;
    int n_nodes = 0;
    g.unmark_all_nodes();
    mean_N2(g,node,sum,n_nodes,0);
    g.unmark_all_nodes();
    return ((float)sum/(float)n_nodes);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/**
 * Given two nodes of a graph, we need to find a path between those two nodes in which
 * the sum of node's lables is less then a given integer k. 
 **/

bool sum_path(graph<int> &g, graph<int>::nodeptr node, graph<int>::nodeptr destination, int k, int path_sum){
    if(node == destination) return true;
    list<graph<int>::nodeptr> adjacent_list = g.adjacent(node);
    list<graph<int>::nodeptr>::nodeptr iterator = adjacent_list.begin();
    while(!adjacent_list.end(iterator)){
        graph<int>::nodeptr graph_node = adjacent_list.read(iterator);
        if(!g.is_marked(graph_node) && path_sum <= k){
            g.mark_node(graph_node);
            if(sum_path(g,graph_node,destination,k,path_sum + g.read(graph_node))) return true;
        }
        iterator = adjacent_list.next(iterator);
    }
    return false;
}

bool sum_path(graph<int> &g, graph<int>::nodeptr a, graph<int>::nodeptr b, int k){
    //Either the graph is empty or a or b does not belong to the graph.
    if(g.empty() || !g.exist_node(a) || !g.exist_node(b)) return false;
    g.unmark_all_nodes();
    bool result = sum_path(g,a,b,k,0);
    g.unmark_all_nodes();
    return result;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/**
 * The function returns the number of nodes that leave the node. 
 **/
int outDegree(graph<int>&g, graph<int>::nodeptr node){
    return g.adjacent(node).size();
}

/**
 * The function returns the number of nodes that enters the node. 
 **/
void inDegree(graph<int>&g, graph<int>::nodeptr node, graph<int>::nodeptr comparison, int &n_edges){
    if(g.exist_edge(node,comparison))n_edges++;
    list<graph<int>::nodeptr> adjacent_list = g.adjacent(node);
    list<graph<int>::nodeptr>::nodeptr iterator = adjacent_list.begin();
    while(!adjacent_list.end(iterator)){
        graph<int>::nodeptr graph_node = adjacent_list.read(iterator);
        if(!g.is_marked(graph_node)){
            g.mark_node(graph_node);
            inDegree(g,graph_node,comparison,n_edges);
        }
        iterator = adjacent_list.next(iterator);   
    }

}

int inDegree(graph<int>&g, graph<int>::nodeptr node){
    if(g.empty() || !g.exist_node(node)) return -1;
    int n_edges = 0;
    g.unmark_all_nodes();
    inDegree(g,node,node,n_edges);
    g.unmark_all_nodes();
    return n_edges;
}

#endif // FUNCTIONS
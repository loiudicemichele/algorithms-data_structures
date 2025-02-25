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
#include "../adjacence_matrix/graphs.hpp"
#include "./functions.hpp"

int main(){
    
    graph<int> g;
    
    graph<int>::nodeptr n1 = new graph_node(1);
    graph<int>::nodeptr n2 = new graph_node(2);
    graph<int>::nodeptr n3 = new graph_node(3);
    graph<int>::nodeptr n4 = new graph_node(4);
    graph<int>::nodeptr n5 = new graph_node(5);
    graph<int>::nodeptr n6 = new graph_node(6);
    graph<int>::nodeptr n7 = new graph_node(7);
    graph<int>::nodeptr n8 = new graph_node(8);

    graph<int>::nodeptr ntest = new graph_node(9);
    graph<int>::nodeptr n10 = new graph_node(10);
    graph<int>::nodeptr n11 = new graph_node(11);
    //Insertions
    g.insert_node(n1);
    g.insert_node(n2);
    g.insert_node(n3);
    g.insert_node(n4);
    g.insert_node(n5);
    g.insert_node(n6);
    g.insert_node(n7);
    g.insert_node(n8);

    g.insert_edge(n1,n2);
    g.insert_edge(n1,n3);
    g.insert_edge(n1,n4);
    g.insert_edge(n4,n5);
    g.insert_edge(n2,n5);
    g.insert_edge(n5,n6);
    g.insert_edge(n6,n8);
    g.insert_edge(n3,n7);
    g.insert_edge(n7,n8);
    
    g.insert_edge(n7,n3);
    g.insert_edge(n3,n4);
    g.insert_edge(n5,n7);
    cout << "Exist path: " << sum_path(g,n1,n7,3) << endl;
    cout << g;
    cout << "Mean: " << mean_N2(g,n1) << endl;

    cout << "Number of edges leaving the node: " << outDegree(g,n5) << endl;
    cout << "Number of edges entering the node: " << inDegree(g,n5) << endl;
    /*
    cout << "Nodes reachable by n1: " << count_same(g,n1) << endl;

    int n_paths;
    int avg;
    number_of_paths(g,n1,n8,n_paths,avg);
    cout << "Numer of paths to the destination: " << n_paths << endl;
    cout << "Avg path length: " << avg;

    graph<string> g;
    string red = "red";
    string green = "green";
    string white = "white";
    graph<string>::nodeptr n1 = new graph_node(red);
    graph<string>::nodeptr n2 = new graph_node(red);
    graph<string>::nodeptr n3 = new graph_node(red);
    graph<string>::nodeptr n4 = new graph_node(red);
    graph<string>::nodeptr n5 = new graph_node(green);
    graph<string>::nodeptr n6 = new graph_node(green);
    graph<string>::nodeptr n7 = new graph_node(white);
    graph<string>::nodeptr n8 = new graph_node(white);
    g.insert_node(n1);
    g.insert_node(n2);
    g.insert_node(n3);
    g.insert_node(n4);
    g.insert_node(n5);
    g.insert_node(n6);
    g.insert_node(n7);
    g.insert_node(n8);

    g.insert_edge(n1,n2,true);
    g.insert_edge(n1,n5,true);
    g.insert_edge(n2,n4,true);
    g.insert_edge(n2,n7,true);
    g.insert_edge(n5,n7,true);
    g.insert_edge(n7,n6,true);
    g.insert_edge(n4,n3,true);
    g.insert_edge(n4,n6,true);
    g.insert_edge(n3,n8,true);
    //g.insert_edge(n6,n8,true);

    g.test_print();
    //cout << same_color_path(g,n1,n3,red);
    cout << " " << uniform_color_path(g,n1,n3);*/
    
};
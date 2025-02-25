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

#ifndef ABSTRACT_GRAPH
#define ABSTRACT_GRAPH

#include <iostream>
template <class T>
class abstract_graph{
    public:
        typedef T type_element;

        virtual int size() const = 0; // Returns the number of nodes in the graph.
        virtual bool empty() const = 0; // Returns true if the graph is empty.
        /*Inserts an edge between two nodes: If weight is inserted when called it is set, otherwise no weight is considered.
          The same concept is applied for directed that indicates if the edge is in both directions*/
        virtual void insert_edge(type_element,type_element,int weight = 0, bool directed = false) = 0; 
        virtual void insert_edge(type_element,type_element,bool) = 0;
        virtual void insert_node(type_element) = 0; // Inserts a node in the graph.
        virtual void delete_node(type_element) = 0; // Deletes a node in the graph.
        // Deletes nodes between two nodes. If directional is true, it deletes both edges.
        virtual void delete_edge(type_element,type_element,bool directional = false) = 0;  
        virtual bool is_adjacent(type_element,type_element) const = 0; // Returns true if the two nodes are adjacent.
        virtual bool exist_node(type_element) const = 0; // Retunds true if the node exist in the graph.
        virtual bool exist_edge(type_element,type_element) const = 0; // Retruns true if the edge between two nodes exists.
        virtual type_element get_node(int) = 0; // Returns a graph node.

        //Utilities for alorithm
        virtual void mark_node(type_element) = 0; // It sign a node as marked.
        virtual void un_mark_node(type_element) = 0; // It sign a node as un-marked.
        virtual bool is_marked(type_element) = 0; // Retruns true if the node is marked.
        virtual void unmark_all_nodes() = 0; // Unmarks all nodes.

        virtual void un_mark_edge(type_element,type_element) = 0; // It sign an edge as un-marked.
        virtual bool is_marked(type_element,type_element) = 0; // Retruns true if the edge is marked.
        virtual void mark_edge(type_element,type_element) = 0; // It sign an edge as marked.
        virtual void unmark_all_edges() = 0; // Unmarks all edges.

        virtual int get_weight(type_element,type_element) const = 0; //Returns the weight of a the edge between two nodes.
        virtual void set_weight(type_element,type_element, int weight) = 0; // Sets the weight of an edge betweem two nodes.
        virtual int get_n_edges(type_element) const = 0; // Retruns the number of edges of a node.
        virtual type_element get_first_node() const = 0; // Returns the first graph node.
        virtual list<type_element> adjacent(type_element) = 0; // Returns the list of adjacent nodes.

};


#endif // ABSTRACT_GRAPH
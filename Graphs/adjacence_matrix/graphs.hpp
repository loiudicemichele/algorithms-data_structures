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

#ifndef GRAPHS
#define GRAPHS

#include <iostream>
#include "../support_structure/list.hpp"
#include "../abstract_graph.hpp"
using namespace std;
template <class T> class graph;
template <class T>
class graph_node{
        friend class graph<T>;
        typedef int position;
    public:
        graph_node(): value(0), marked(false), edges(0), array_position(not_set){};
        graph_node(const T& value_in): value(value_in), marked(false), edges(0), array_position(not_set){};
        bool is_marked(){ return marked; };
    private:
        const position not_set = -1;

        T value;
        position array_position;
        bool marked;
        int edges;
};

template <class T> class graph;
template <class T>
class matrix_node{
    friend class graph<T>;
    public:
        matrix_node(): weight(0), used(false), marked(false){}
    private:
        int weight;
        bool used;
        bool marked;
};

template <class T>
class graph : public abstract_graph<graph_node<T>*>{
    public:
        typedef int position;
        typedef typename abstract_graph<graph_node<T>*>::type_element nodeptr;
        typedef typename list<nodeptr>::nodeptr list_node_ptr; 
        /*** Default Constructor ***/
        graph();
        graph(int);
        /*** Destructor ***/
        ~graph();
        /*** Copy Constructor ***/
        graph(const graph<T>&);
        /*** Move Constructor ***/
        graph(graph<T>&&) noexcept;
        /*** Methods ***/
        int size() const; // Returns the number of nodes in the graph.
        bool empty() const; // Returns true if the graph is empty.
        /*Inserts an edge between two nodes: If weight is inserted when called it is set, otherwise no weight is considered.
          The same concept is applied for directed that indicates if the edge is in both directions*/
        void insert_edge(nodeptr,nodeptr,int weight = 0, bool directed = false); 
        void insert_edge(nodeptr,nodeptr,bool);
        void insert_node(nodeptr); // Inserts a node in the graph.
        void delete_node(nodeptr); // Deletes a node in the graph.
        // Deletes nodes between two nodes. If directional is true, it deletes both edges.
        void delete_edge(nodeptr,nodeptr,bool directional = false);  
        bool is_adjacent(nodeptr,nodeptr) const; // Returns true if the two nodes are adjacent.
        bool exist_node(nodeptr) const; // Retunds true if the node exist in the graph.
        bool exist_edge(nodeptr,nodeptr) const; // Returns true if the edge between two nodes exists.
        nodeptr get_node(position); // Returns a graph node.
        T read(nodeptr) const; // Reads the value of a node.
        void write(nodeptr,const T&); // Sets the value of a node.

        //Utilities for alorithm
        void mark_node(nodeptr); // It sign a node as marked.
        void un_mark_node(nodeptr); // It sign a node as un-marked.
        bool is_marked(nodeptr); // Returns true if the node is marked.
        void unmark_all_nodes(); // Unmarks all nodes.

        void un_mark_edge(nodeptr,nodeptr); // It sign an edge as un-marked.
        bool is_marked(nodeptr,nodeptr); // Returns true if the edge is marked.
        void mark_edge(nodeptr,nodeptr); // It sign an edge as marked.
        void unmark_all_edges(); // Unmarks all edges.

        int get_weight(nodeptr,nodeptr) const; //Returns the weight of a the edge between two nodes.
        void set_weight(nodeptr,nodeptr, int weight); // Sets the weight of an edge betweem two nodes.
        int get_n_edges(nodeptr) const; // Returns the number of edges of a node.
        nodeptr get_first_node() const; // Returns the first graph node.
        list<nodeptr> adjacent(nodeptr); // Returns the list of adjacent nodes.

        /*** Operators ***/
        graph<T>& operator =(const graph<T>&); // Operator =(Assigment by copy).
        void operator =(graph<T> &&); // Operator =(Move equal).
        bool operator ==(graph<T>&); // Operator ==(Compares two graph.).

        void dfs_search(ostream&,nodeptr);

        /*** Test functions ***/
        void test_print();
    private:
        /*** PRIVATE CONSTANTS ***/
        const int not_set = -1;
        const int default_size = 10; 
        /*** PRIVATE METHODS ***/
        void copy_graph(graph<T>&,const graph<T>&);
        position find_empty_position(); // Finds the first empty spot the in nodes array.
        void inizialize(int);
        void clear();
        position get_position(nodeptr) const; // Returns the position in the nodes and adjacent matrix array.
        void doubling(); // Doubles the length base structure of the graph.
        /*** PRIVATE ATTRIBUTES ***/
        matrix_node<T> **adjacent_matrix;
        nodeptr *nodes;
        int total_elements;
        int n_elements;
};


/*** Default Constructor ***/
template <class T>
graph<T>::graph(){
    inizialize(default_size);
}

template <class T>
graph<T>::graph(int size){
    inizialize(size);
}

//Sets the initial state of adjacent matrix and nodes array.
template <class T>
void graph<T>::inizialize(int size){
    total_elements = size;
    n_elements = 0;
    nodes = new graph_node<T>*[size];
    for(int i = 0; i < total_elements; i++){ nodes[i] = nullptr; }
    adjacent_matrix = new matrix_node<T>*[size];
    for(int i = 0; i < size; i++){
        adjacent_matrix[i] = new matrix_node<T>[size];
    }
}

/*** Destructor ***/
template <class T>
graph<T>::~graph(){
    clear();
}

//Deallocates the memory.
template <class T>
void graph<T>::clear(){
    if(nodes != nullptr){
        for(int i = 0; i < n_elements; i++){
            if(nodes[i] != nullptr) delete nodes[i];
        }
        delete[] nodes;
    }
    if(adjacent_matrix != nullptr ){
        for(int i = 0; i < total_elements; i++){
        delete[] adjacent_matrix[i];
        }
        delete[] adjacent_matrix;
    }
    total_elements = 0;
    n_elements = 0;
}

/*** Copy Constructor ***/
template <class T>
graph<T>::graph(const graph<T>& t){
    inizialize(t.total_elements);
    copy_graph(*this,t);
}

// Copy the second graph into the first one. (Deep copy).
template <class T>
void graph<T>::copy_graph(graph<T>& T1, const graph<T>&T2){
    for(int i = 0; i < T2.size(); i++){
        nodeptr to_copy = T2.nodes[i];
        nodeptr new_node = new graph_node<T>(T2.read(to_copy));
        T1.insert_node(new_node);
    }
    for(int i = 0; i < T2.total_elements; i++){
        for(int j = 0; j < T2.total_elements; j++){
            if(T2.adjacent_matrix[i][j].used){
                T1.insert_edge(T1.get_node(i),T1.get_node(j),T2.adjacent_matrix[i][j].weight);
            }
        }
    }
}

/*** Move Constructor ***/
template <class T>
graph<T>::graph(graph<T>&& g) noexcept{
    total_elements = g.total_elements;
    n_elements = g.n_elements;
    nodes = g.nodes;
    adjacent_matrix = g.adjacent_matrix;
    g.adjacent_matrix = g.nodes = nullptr;
}

/*** Methods ***/

//Returns the number of nodes in the graph.
template <class T>
int graph<T>::size() const{
    return n_elements;
} 

//Returns true if the graph is empty.
template <class T>
bool graph<T>::empty() const{
    return (n_elements == 0);
} 

//Inserts an edge between two nodes. directed = true -> Not oriented nodes
template <class T>
void graph<T>::insert_edge(nodeptr n1, nodeptr n2,int weight, bool directed){
    if(n1 == n2) return;
    position p1 = get_position(n1);
    position p2 = get_position(n2);
    if( !(exist_node(n1) && exist_node(n2)) ) return;
    adjacent_matrix[p1][p2].used = true;
    adjacent_matrix[p1][p2].weight = weight;
    n1->edges++;
    if(directed){
        adjacent_matrix[p2][p1].used = true;
        adjacent_matrix[p2][p1].weight = weight;
        n2->edges++;
    }
}

//Insert edge overloading | directed = true -> Bidirectional nodes
template <class T>
void graph<T>::insert_edge(nodeptr n1, nodeptr n2,bool directed){
    if(n1 == n2) return;
    position p1 = get_position(n1);
    position p2 = get_position(n2);
    if( !(exist_node(n1) && exist_node(n2)) ) return;
    adjacent_matrix[p1][p2].used = true;
    adjacent_matrix[p2][p1].used = true;
    n1->edges++;
    n2->edges++;
}

//Inserts a node in the graph.
template <class T>
void graph<T>::insert_node(nodeptr node){
    position position = find_empty_position();
    nodes[position] = node;
    node->array_position = position;
    n_elements++;
} 

//Finds the first empty spot the in nodes array.
template <class T>
typename graph<T>::position graph<T>::find_empty_position(){
    if(n_elements+1 == total_elements) doubling();
    position position;
    for(position = 0; position < total_elements; position++){
        if(nodes[position] == nullptr) return position;
    }
    return -1;
}

//Doubles the length base structure of the graph. *
template <class T>
void graph<T>::doubling(){ 
    int new_total_dimension = 2*total_elements;
    int new_n_elements = n_elements;
    nodeptr *new_nodes_array = new graph_node<T>*[new_total_dimension];
    matrix_node<T> **new_adjacent_matrix = new matrix_node<T>*[new_total_dimension];
    //Coopying the references of old metrics into the new ones.
    for(int i = 0; i < total_elements; i++){
        new_nodes_array[i] = nodes[i];
        nodes[i] = nullptr;
    }
    for(int i = total_elements; i < new_total_dimension; i++) new_nodes_array[i] = nullptr;
    for(int i = 0; i < new_total_dimension; i++){
        new_adjacent_matrix[i] = new matrix_node<T>[new_total_dimension];
        for(int j = 0; j < new_total_dimension; j++){
            if(i < total_elements && j < total_elements){
                new_adjacent_matrix[i][j].weight = adjacent_matrix[i][j].weight;
                new_adjacent_matrix[i][j].used = adjacent_matrix[i][j].used;
            } 
        }
    }
    clear();
    n_elements = new_n_elements;
    total_elements = new_total_dimension;   
    nodes = new_nodes_array;
    adjacent_matrix = new_adjacent_matrix;
}

//Deletes a node in the graph.
template <class T>
void graph<T>::delete_node(nodeptr node){
    position pos = get_position(node);
    if(pos == not_set) return;
    //We delete all the edges before deleting the node.
    for(int i = 0; i < n_elements; i++){
        if(exist_edge(node,get_node(i))) delete_edge(node,get_node(i));
        if(exist_edge(get_node(i),node)) delete_edge(get_node(i),node);
    }
    if(pos == not_set) return;
    nodes[pos] = nullptr;
    n_elements--;
} 

//Deletes nodes between two nodes. 
template <class T>
void graph<T>::delete_edge(nodeptr n1,nodeptr n2, bool directional){
    if(!(exist_node(n1) && exist_node(n2))) return;
    position p1 = get_position(n1);
    position p2 = get_position(n2);
    adjacent_matrix[p1][p2].used = false;
    n1->edges--;
    if(directional){
        adjacent_matrix[p2][p1].used = false;
        n2->edges--;
    } 
} 

//Returns true if the two nodes are adjacent.
template <class T>
bool graph<T>::is_adjacent(nodeptr n1,nodeptr n2) const{
    return exist_edge(n1,n2);
} 

//Returns the position in the nodes and adjacent matrix array.
template <class T>
typename graph<T>::position graph<T>::get_position(nodeptr node) const{
    if(node == nullptr) return not_set;
    return node->array_position;
} 

//Retunds true if the node exist in the graph.
template <class T>
bool graph<T>::exist_node(nodeptr node) const{
    return (get_position(node) != not_set);
} 

//Returns true if the edge between two nodes exists.
template <class T>
bool graph<T>::exist_edge(nodeptr n1,nodeptr n2) const{
    if(!(exist_node(n1) && exist_node(n2))) return false;
    return adjacent_matrix[get_position(n1)][get_position(n2)].used;
} 

//Returns a graph node.
template <class T>
typename graph<T>::nodeptr graph<T>::get_node(position p){
    return nodes[p];
} 

//Reads the value of a node.
template <class T>
T graph<T>::read(nodeptr node) const{
    return node->value;
} 

//Sets the value of a node.
template <class T>
void graph<T>::write(nodeptr node, const T& value){
    node->value = value;
} 

//It sign a node as marked.
template <class T>
void graph<T>::mark_node(nodeptr node){
    if(!exist_node(node)) return;
    node->marked = true;
} 

//It sign a node as un-marked.
template <class T>
void graph<T>::un_mark_node(nodeptr node){
    if(!exist_node(node)) return;
    node->marked = false;
}

//Returns true if the node is marked.
template <class T>
bool graph<T>::is_marked(nodeptr node){
    return node->is_marked();
}

//Unmarks all nodes.
template <class T>
void graph<T>::unmark_all_nodes(){
    for(int i = 0; i < n_elements; i++ ){
        if(exist_node(nodes[i])) un_mark_node(nodes[i]);
    }
}


// It sign an edge as un-marked.
template <class T>
void graph<T>::un_mark_edge(nodeptr n1,nodeptr n2){
    if(!exist_edge(n1,n2)) return;
    adjacent_matrix[get_position(n1)][get_position(n2)].marked = false;
} 

// Returns true if the edge is marked.
template <class T>
bool graph<T>::is_marked(nodeptr n1,nodeptr n2){
    if(!exist_edge(n1,n2)) return false;
    return (adjacent_matrix[get_position(n1)][get_position(n2)].marked == true);
} 

// It sign an edge as marked.
template <class T>
void graph<T>::mark_edge(nodeptr n1, nodeptr n2){
    if(!exist_edge(n1,n2)) return;
    adjacent_matrix[get_position(n1)][get_position(n2)].marked = true;
} 

// Unmarks all edges.
template <class T>
void graph<T>::unmark_all_edges(){
    for(int i = 0; i < total_elements; i++){
        for(int j = 0; j < total_elements; j++){
            adjacent_matrix[i][j].marked = false;
        }
    }
}   

//Returns the number of edges of a node.
template <class T>
int graph<T>::get_n_edges(nodeptr node) const{
    if(!exist_node(node)) return not_set;
    cout << node->edges;
    return node->edges;
} 

//Returns the first graph node.
template <class T>
typename graph<T>::nodeptr graph<T>::get_first_node() const{
    return nodes[0];
}

//Returns the list of adjacent nodes.
template <class T>
list<typename graph<T>::nodeptr> graph<T>::adjacent(nodeptr node){
    list<nodeptr> _list = list<nodeptr>();
    if(!exist_node(node)) return _list;
    for(int i = 0; i < n_elements; i++){
        if(exist_edge(node,get_node(i))){
            _list.insert(get_node(i));
        } 
    }
    return _list;
} 

//Returns the weight of a the edge between two nodes.
template <class T>
int graph<T>::get_weight(nodeptr n1,nodeptr n2) const{
    if(!exist_edge(n1,n2)) return not_set;
    return adjacent_matrix[get_position(n1)][get_position(n2)].weight;
} 

//Sets the weight of an edge betweem two nodes.
template <class T>
void graph<T>::set_weight(nodeptr n1,nodeptr n2, int weight_in){
    if(!exist_edge(n1,n2)) return;
    adjacent_matrix[get_position(n1)][get_position(n2)].weight = weight_in;
}

//Operator =(Assigment by copy).
template <class T>
graph<T>& graph<T>::operator =(const graph<T>& t){
    clear();
    inizialize(t.total_elements);
    copy_graph(*this,t);
    return *this;
} 

//Operator =(Move equal).
template <class T>
void graph<T>::operator =(graph<T> && t){
    n_elements = t.n_elements;
    total_elements = t.total_elements;
    nodes = t.nodes;
    adjacent_matrix = t.adjacent_matrix;
    t.nodes = nullptr;
    t.adjacent_matrix = nullptr;
} 

// Main function to print the graph 
template <class T>
ostream& operator << (ostream& output, graph<T>& g) {
    if(g.empty()){
        output << "Graph is empty";
        return output;
    }
    //DFS
    output << "DFS Graph Search: " << endl;
    g.dfs_search(output, g.get_first_node());
    g.unmark_all_nodes();
    return output; 
}

//Prints recursively each node at a certain tree level.
template <class T>
void graph<T>::dfs_search(ostream& output,nodeptr node){
    if(exist_node(node)) output << read(node) << endl;
    else return;
    mark_node(node);
    list<nodeptr> adjacent_list = adjacent(node);
    list_node_ptr n = adjacent_list.begin();
    while(!adjacent_list.end(n)){
        if(!adjacent_list.read(n)->is_marked()){
            dfs_search(output,adjacent_list.read(n));
        }
        n = adjacent_list.next(n);
    }
} 

//Operator ==(Compares two trees.).
template <class T>
bool graph<T>::operator ==(graph<T>& t){
    return true;
} 


/*** Test functions ***/
template <class T>
void graph<T>::test_print(){
    cout << "Nodes: [ ";
    for( int i = 0; i < n_elements; i++ ){
        if(nodes[i] == nullptr) continue;
        cout << "{" << nodes[i]->value;
        if(nodes[i]->marked == true) cout << "+" << "} ";
        else cout << "-" << "} ";
    }
    cout << "]" << endl;

    cout << "   ";
    for( int i = 0; i < total_elements; i++ ){
        if(nodes[i] == nullptr) cout << "| - |";
        else cout << "| " << nodes[i]->value << " |";
    }
    cout << endl;
    for( int i = 0; i < total_elements; i++ ){
        if(nodes[i] == nullptr) cout << "|-|";
        else cout << "|" << nodes[i]->value << "|";
        for( int j = 0; j < total_elements; j++ ){
            cout << "{" << adjacent_matrix[i][j].weight << "|" 
            << adjacent_matrix[i][j].used << "|" << adjacent_matrix[i][j].marked << "}";
        }
        cout << endl;
    }
    cout << endl;
}

#endif // GRAPHS
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

#ifndef TREE
#define TREE

#include <iostream>
#include "../abstract_bin_tree.hpp"
using namespace std;

template <class T>
class binary_tree : public abstract_bin_tree<T,int>{
    public:
        typedef typename abstract_bin_tree<T,int>::position position;
        /*** Default Constructor ***/
        binary_tree();
        /*** Destructor ***/
        ~binary_tree();
        /*** Copy Constructor ***/
        binary_tree(const binary_tree<T>&);
        /*** Move Constructor ***/
        binary_tree(binary_tree<T>&&) noexcept;
        /*** Methods ***/
        int size() const; //Returns the number of nodes in the tree.
        bool empty() const; //Returns true if the tree is empty.
        position get_root() const; //Returns the root of the tree.
        position get_left_child(position) const; //Returns the left child of a node.
        position get_right_child(position) const; //Returns the right child of a node.
        position get_parent(position) const; //Returns the parent of a node.
        void erase(position); //Deletes a subtree from the tree.
        void insert_root(T);//Sets the root of the tree.
        void insert_left_child(position,T);//Sets the left child of a parent node.
        void insert_right_child(position,T);//Sets the right child of a parent node.
        void write(const T&, position);//Sets the value of a node.
        T read(position) const; //Reads the value of a node.
        int get_height() const; //Returns the height of the tree.
        int get_level(position) const; //Returns the level of a tree node.
        bool has_left_child(position) const; //Returns true if the node has a left child
        bool has_right_child(position) const; //Returns true if the node has a right child
        bool has_parent(position) const; //Returns true if the node has a parent
        /*** Operators ***/
        binary_tree<T> operator +(const binary_tree<T>&); //Operator + (tree concatenation).
        binary_tree<T>& operator =(const binary_tree<T>&); //Operator =(Assigment by copy).
        void operator =(binary_tree<T> &&); //Operator =(Move equal).
        bool operator ==(binary_tree<T>&); //Operator ==(Compares two trees.).
        //Prints recursively each node at a certain tree level. (Supports the << operator)
        void print_level(ostream&,position,int) const;
        /* Test Functions */
        void inizialize_tree(int,int);
    private:
        /*** PRIVATE CONSTANTS ***/
        const int root = 0;
        const int empty_element = -1;
        const int default_dimension = 10;
        /*** PRIVATE METHODS ***/
        void get_height(position,int,int&) const;
        void copy_tree(binary_tree<T>&,const binary_tree<T>&,position,position);
        //Inizializes the intial state of the array. 
        void inizialize_default(int);
        void clear(); //Clears the elements of the tree.
        void doubling(); //Doubles the lenght of the array.
        /*** PRIVATE ATTRIBUTES ***/
        int n_elements;
        int total_elements;
        T *values;
};

/*** Default Constructor ***/
template <class T>
binary_tree<T>::binary_tree(){
    inizialize_default(default_dimension);
}

/*** Destructor ***/
template <class T>
binary_tree<T>::~binary_tree(){
    clear();
}

//Clears the elements of the tree.
template <class T>
void binary_tree<T>::clear(){
    delete[] values;
    n_elements = 0;
    total_elements = 0;
}

/*** Copy Constructor ***/
template <class T>
binary_tree<T>::binary_tree(const binary_tree<T>& t){
    n_elements = t.n_elements;
    total_elements = t.total_elements;
    values = new T[t.total_elements];
    for(int i = 0; i < t.total_elements; i++) values[i] = t.values[i];
};
/*** Move Constructor ***/
template <class T>
binary_tree<T>::binary_tree(binary_tree<T>&& t) noexcept{
    n_elements = t.n_elements;
    total_elements = t.total_elements;
    values = t.values;
    t.values = nullptr;
};

//Doubles the lenght of the array.
template <class T>
void binary_tree<T>::doubling(){
    T *old_values = values;
    int old_size = total_elements;
    inizialize_default(total_elements*2);
    for(int i = 0; i < old_size; i++ ){
        values[i] = old_values[i];
    }
}

//Inizializes the intial state of the array. 
template <class T>
void binary_tree<T>::inizialize_default(int dimension){
    n_elements = 0;
    total_elements = dimension;
    values = new T[dimension];
    for(int i = 0; i < dimension; i++ ){
        values[i] = empty_element;
    }
}

/*** Methods ***/
//Returns the number of nodes in the tree.
template <class T>
int binary_tree<T>::size() const{
    return n_elements;
}

//Returns true if the tree is empty.
template <class T>
bool binary_tree<T>::empty() const{
    return (values[root] == empty_element);
}

/* ************ */
//Returns the root of the tree.
template <class T>
typename binary_tree<T>::position binary_tree<T>::get_root() const{
    return root;
}

//Returns the left child of a node.
template <class T>
typename binary_tree<T>::position binary_tree<T>::get_left_child(position parent) const{
    if(total_elements <= (2*parent + 1) ) return empty_element;
    return 2*parent + 1;
}

//Returns the right child of a node.
template <class T>
typename binary_tree<T>::position binary_tree<T>::get_right_child(position parent) const{
    if(total_elements <= (2*parent + 2) ) return empty_element;
    return 2*parent + 2;
}

//Returns the parent of a node.
template <class T>
typename binary_tree<T>::position binary_tree<T>::get_parent(position p) const{
    if( p == root ) return empty_element;
    return ((p-1)/2);
}

//Deletes a subtree from the tree.
template <class T>
void binary_tree<T>::erase(position p){
    if(has_left_child(p)) erase(get_left_child(p));
    if(has_right_child(p)) erase(get_right_child(p));
    values[p] = empty_element;
}
//Sets the root of the tree.
template <class T>
void binary_tree<T>::insert_root(T value){
    values[0] = value;
}
//Sets the left child of a parent node.
template <class T>
void binary_tree<T>::insert_left_child(position parent,T value){
    if(total_elements < (2*parent + 1) ) doubling();
    values[2*parent + 1] = value;
}

//Sets the right child of a parent node.
template <class T>
void binary_tree<T>::insert_right_child(position parent,T value){
    if(total_elements <= (2*parent + 2) ) doubling();
    values[2*parent + 2] = value;
}

//Sets the value of a node.
template <class T>
void binary_tree<T>::write(const T& value, position position){
    values[position] = value;
}

//Reads the value of a node.
template <class T>
T binary_tree<T>::read(position p) const{
    return values[p];
}

//Returns the height of the tree.
template <class T>
int binary_tree<T>::get_height() const{
    if(empty()) return 0;
    int height = 0;
    get_height(root,0,height);
    return height;
}

//Calculates the height of the tree.
template <class T>

void binary_tree<T>::get_height(position element, int partial_count, int &height ) const{
    if( has_left_child(element) ) get_height( get_left_child(element), partial_count+1, height );
    if( has_right_child(element) ) get_height( get_right_child(element), partial_count+1, height );
    if( partial_count > height ) height = partial_count;
} 
//Returns the level of a tree node.
template <class T>
int binary_tree<T>::get_level(position p) const{
    int parent = p;
    int level = 0;
    while( parent > 0 ){
        parent = ((parent-1)/2);
        level++;
    } 
    return level;
}

//Returns true if the node has a left child
template <class T>
bool binary_tree<T>::has_left_child(position parent) const{
    if(total_elements <= (2*parent + 1) ) return false;
    return(values[2*parent + 1] != empty_element);

}

//Returns true if the node has a right child
template <class T>
bool binary_tree<T>::has_right_child(position parent) const{
    if(total_elements <= (2*parent + 2) ) return false;
    return(values[2*parent + 2] != empty_element);
}

//Returns true if the node has a parent
template <class T>
bool binary_tree<T>::has_parent(position p) const{
    if( p == root ) return false;
    return(values[(p-1)/2] != empty_element);
}

/* Test Functions */
template <class T>
void binary_tree<T>::inizialize_tree(int start_value,int dimension){
    for(int i = 0; i < dimension; i++){
        values[i] = start_value;
        start_value++;
        n_elements++;
    }
}

//Prints recursively each node at a certain tree level.
template <class T>
void binary_tree<T>::print_level(ostream& output, position node, int level) const {
    //If the node we consider is on the interested level, we print it.
    if (level == 0) {
        output << "[PT:";
        if(get_parent(node) == empty_element) output << "NULL]: ";
        else{
            output << read(get_parent(node)) << "|: ";
            if( get_left_child(get_parent(node)) == node ) output << "SX]: ";
            else output << "DX]: ";
        } 
        output << read(node) << " "; // Print the node's value at this level.
    }
    if( has_left_child(node) ) print_level(output, get_left_child(node), level - 1);
    if( has_right_child(node) ) print_level(output, get_right_child(node), level - 1);
    
} 

template <class T>
void binary_tree<T>::copy_tree(binary_tree<T> &T1, const binary_tree<T> &T2, position n1, position n2){
    if( T2.has_left_child(n2) ){
        T1.insert_left_child(n1,T2.read(T2.get_left_child(n2)));
        copy_tree(T1,T2,T1.get_left_child(n1),T2.get_left_child(n2));
    } 
    if( T2.has_right_child(n2) ){
        T1.insert_right_child(n1,T2.read(T2.get_right_child(n2)));
        copy_tree(T1,T2,T1.get_right_child(n1),T2.get_right_child(n2));
    } 
}

/*** Operators ***/
template <class T>
ostream& operator <<(ostream& output, binary_tree<T>& t){
    if(t.empty()){
        output << "Tree is empty";
        return output;
   }
    int height = t.get_height(); // Get the height of the tree.
    //Printing the tree by levels.
    for (int i = 0; i <= height; ++i) {
        output << "LEVEL: [" <<  i << "]: ";
        t.print_level(output, t.get_root(), i); // Print all nodes at the current level.
       output << endl; // Move to the next level.
    }
    return output;
}


//Operator + (tree concatenation).
template <class T>
binary_tree<T> binary_tree<T>::operator +(const binary_tree<T>&t){
    binary_tree<T> *sum_tree = new binary_tree<T>;
    sum_tree->insert_root(root);//Inserting a Sentinel node as root.
    sum_tree->insert_left_child(sum_tree->get_root(), read(get_root()));
    sum_tree->insert_right_child(sum_tree->get_root(), t.read(t.get_root()));
    copy_tree(*sum_tree, *this, sum_tree->get_left_child(sum_tree->get_root()), get_root());
    copy_tree(*sum_tree, t, sum_tree->get_right_child(sum_tree->get_root()), t.get_root());
    return *sum_tree;
}



//Operator =(Assigment by copy).
template <class T>
binary_tree<T>& binary_tree<T>::operator =(const binary_tree<T>& t){
    clear();
    n_elements = t.n_elements;
    total_elements = t.total_elements;
    values = new T[total_elements];
    for( int i = 0; i < total_elements; i++ ){
        values[i] = t.values[i];
    }
    return *this;
}

//Operator =(Move equal).
template <class T>
void binary_tree<T>::operator =(binary_tree<T> &&t){
    clear();
    values = t.values;
    n_elements = t.n_elements;
    total_elements = t.total_elements;
    t.values = nullptr;
}

//Operator ==(Compares two trees.).
template <class T>
bool binary_tree<T>::operator ==(binary_tree<T>&t){
    if(size() != t.size())return false;
    for(int i = 0; i < size(); i++){
        if(values[i] != t.values[i]) return false;
    }
    return true;
}

#endif // TREE
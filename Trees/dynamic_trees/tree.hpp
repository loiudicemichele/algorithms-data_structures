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
#include "../abstract_tree.hpp"
using namespace std;

template <class T> class tree;
template <class T>
class tree_node{
        friend class tree<T>;
    public:
        typedef tree_node<T>* nodeptr;
        tree_node(): value(0), first_child(nullptr), next_sibling(nullptr), prev_sibling(nullptr), parent(nullptr){}
        tree_node(const T& value_in): value(value_in), first_child(nullptr), next_sibling(nullptr), prev_sibling(nullptr), parent(nullptr){}
        ~tree_node(){first_child = next_sibling = prev_sibling = parent = nullptr;}
    private:
        T value;
        nodeptr first_child;
        nodeptr next_sibling;
        nodeptr prev_sibling;
        nodeptr parent;
};

template <class T>
class tree : public abstract_tree<T,tree_node<T>*>{
    public:
        typedef typename abstract_tree<T,tree_node<T>*>::position nodeptr;
        /*** Default Constructor ***/
        tree();
        /*** Destructor ***/
        ~tree();
        /*** Copy Constructor ***/
        tree(const tree<T>&);
        /*** Move Constructor ***/
        tree(tree<T>&&) noexcept;
        /*** Methods ***/
        int size() const; //Returns the number of nodes in the tree.
        bool empty() const; //Returns true if the tree is empty.
        nodeptr get_root() const; //Returns the root of the tree.
        nodeptr get_first_child(nodeptr) const; //Returns the first child of a node.
        nodeptr get_next_sibling(nodeptr) const; //Returns the next sibling of a node.
        nodeptr get_prev_sibling(nodeptr) const; //Returns the previous sibling of a node.
        nodeptr get_parent(nodeptr) const; //Returns the parent of a node.
        bool has_first_child(nodeptr) const; //Returns true if the node has a first child.
        bool has_next_sibling(nodeptr) const; //Returns true if the node has a next sibling.
        bool has_prev_sibling(nodeptr) const; //Returns true if the node has a previous sibling.
        bool has_parent(nodeptr) const; //Returns true if the node has a parent.
        bool leaf(nodeptr) const; //Returns true if the node is a leef (Has no first child).
        bool last_sibling(nodeptr) const; //Returns true if the node doens't have a next sibling.
        void erase(nodeptr); //Deletes a subtree from the tree.
        void insert_root(nodeptr);//Sets the root of the tree.
        void insert_first_child(nodeptr,nodeptr);//Sets the first child of a parent node.
        void insert_next_sibling(nodeptr,nodeptr);//Sets the next sibling of a node.
        void insert_prev_sibling(nodeptr,nodeptr);//Sets the previous sibling of a node.
        void insert_parent(nodeptr,nodeptr);//Sets the parent of a node.
        void write(const T&, nodeptr);//Sets the value of a node.
        T read(nodeptr) const; //Reads the value of a node.
        int get_height() const; //Returns the height of the tree.
        int get_level(nodeptr) const; //Returns the level of a tree node.
        void delete_subtree(nodeptr); //Deletes a subtree of a node.
        void insert_subtree(const tree<T>&,nodeptr); //Inserts the second tree as a subtree of the first;
        /*** Operators ***/
        tree<T> operator +(const tree<T>&); //Operator + (tree concatenation).
        tree<T>& operator =(const tree<T>&); //Operator =(Assigment by copy).
        void operator =(tree<T> &&); //Operator =(Move equal).
        bool operator ==(tree<T>&); //Operator ==(Compares two trees.).
        //Prints recursively each node at a certain tree level. (Supports the << operator)
        void print_level(ostream&, nodeptr node, int level) const;
    private:
        /*** PRIVATE METHODS ***/
        void copy_tree(tree<T>&,const tree<T>&,nodeptr,nodeptr);
        bool compare_trees(const tree<T> &,const tree<T>&,nodeptr,nodeptr);
        void get_height(nodeptr,int,int&) const;
        void clear(nodeptr);
        /*** PRIVATE ATTRIBUTES ***/
        nodeptr root;   
        int n_elements;
};

/*** Default Constructor ***/
template <class T>
tree<T>::tree(){
    root = nullptr;
    n_elements = 0;
}

/*** Destructor ***/
template <class T>
tree<T>::~tree(){
    clear(root);
}

/*** Copy Constructor ***/
template <class T>
tree<T>::tree(const tree<T>&t){
    n_elements = 0;
    root = nullptr;
    copy_tree(*this,t,root,t.get_root());
}

/*** Move Constructor ***/
template <class T>
tree<T>::tree(tree<T>&&t) noexcept{
    root = t.root;
    n_elements = t.n_elements;
    t.root = nullptr;
}

//Clears the elements of the tree.
template <class T>
void tree<T>::clear(nodeptr node){
    if(node == nullptr) return;
    if(has_next_sibling(node) && has_prev_sibling(node)){
        node->prev_sibling->next_sibling = get_next_sibling(node);
        node->next_sibling->prev_sibling = get_prev_sibling(node);
    }
    if(has_first_child(node)){
        nodeptr child = get_first_child(node);
        while(has_next_sibling(child)){
            nodeptr sibling = get_next_sibling(child);
            if(has_next_sibling(sibling)){
                child->next_sibling = get_next_sibling(sibling);
            }
            else child->next_sibling = nullptr;
            clear(sibling);
        }
        node->first_child = nullptr;
        clear(child);
    }   
    delete node;
}

/*** Methods ***/
//Returns the number of nodes in the tree.
template <class T>
int tree<T>::size() const{
    return n_elements;
}
//Returns true if the tree is empty.
template <class T>
bool tree<T>::empty() const{
    return (root == nullptr);
}
//Returns the root of the tree.
template <class T>
typename tree<T>::nodeptr tree<T>::get_root() const{
    return root;
}


//Returns the left child of a node.
template <class T>
typename tree<T>::nodeptr tree<T>::get_first_child(nodeptr parent) const{
    return parent->first_child;
} 

//Returns the next sibling of a node.
template <class T>
typename tree<T>::nodeptr tree<T>::get_next_sibling(nodeptr sibling) const{
    return sibling->next_sibling;
} 

//Returns the previous sibling of a node.
template <class T>
typename tree<T>::nodeptr tree<T>::get_prev_sibling(nodeptr sibling) const{
    return sibling->prev_sibling;
}

//Returns the parent of a node.
template <class T>
typename tree<T>::nodeptr tree<T>::get_parent(nodeptr node) const{
    return node->parent;
} 

//Returns true if the node has a first child.
template <class T>
bool tree<T>::has_first_child(nodeptr node) const{
    if(node == nullptr) return false;
    return (node->first_child != nullptr);
} 

//Returns true if the node has a next sibling.
template <class T>
bool tree<T>::has_next_sibling(nodeptr node) const{
    if(node == nullptr) return false;
    return (node->next_sibling != nullptr);
} 

//Returns true if the node has a previous sibling.
template <class T>
bool tree<T>::has_prev_sibling(nodeptr node) const{
    return (node->prev_sibling != nullptr);
} 

//Returns true if the node has a parent.
template <class T>
bool tree<T>::has_parent(nodeptr node) const{
    if(node == nullptr) return false;
    return (node->parent != nullptr);
} 

//Returns true if the node is a leef (Has no first child).
template <class T>
bool tree<T>::leaf(nodeptr node) const{
    return !has_first_child(node);
} 

//Returns true if the node doens't have a next sibling.
template <class T>
bool tree<T>::last_sibling(nodeptr node) const{
    return !has_next_sibling(node);
}

//Deletes a subtree from the list.
template <class T>
void tree<T>::erase(nodeptr node){
    if(has_prev_sibling(node) && has_next_sibling(node)){
        node->prev_sibling->next_sibling = node->next_sibling;
        node->next_sibling->prev_sibling = node->prev_sibling;
    }
    else if( has_prev_sibling(node) ){
        node->prev_sibling->next_sibling = nullptr;
    }
    node->prev_sibling = node->next_sibling = node->parent = nullptr;
    clear(node);
}

//Sets the root of the tree.
template <class T>
void tree<T>::insert_root(nodeptr root_in){
    if(root == nullptr) root = root_in;
    n_elements = 1;
}

//Sets the first child of a parent node.
template <class T>
void tree<T>::insert_first_child(nodeptr parent, nodeptr child){
    parent->first_child = child;
    child->parent = parent;
    n_elements++;
}

//Sets the next sibling of a node.
template <class T>
void tree<T>::insert_next_sibling(nodeptr prev_node,nodeptr next_node){
    next_node->next_sibling = prev_node->next_sibling;
    prev_node->next_sibling = next_node;
    next_node->prev_sibling = prev_node;
    next_node->parent = prev_node->parent;
    n_elements++;
}

//Sets the previous sibling of a node.
template <class T>
void tree<T>::insert_prev_sibling(nodeptr next_node,nodeptr prev_node){
    next_node->prev_sibling = prev_node;
    prev_node->next_sibling = next_node;
    prev_node->parent = next_node->parent;
    n_elements++;
}

//Sets the parent of a node.
template <class T>
void tree<T>::insert_parent(nodeptr node,nodeptr parent){
    node->parent = parent;
}

//Sets the value of a node.
template <class T>
void tree<T>::write(const T& value, nodeptr node){
    node->value = value;
}

//Reads the value of a node.
template <class T>
T tree<T>::read(nodeptr node) const{
    return node->value;
}

//Returns the height of the tree.
template <class T>
int tree<T>::get_height() const{
    int height = 0;
    get_height(root,0,height);
    return height;
}

template <class T>
void tree<T>::get_height(nodeptr node, int partial_count, int &height) const{
    if(has_first_child(node)) get_height(get_first_child(node), partial_count+1, height);
    if(has_next_sibling(node)) get_height(get_next_sibling(node), partial_count, height);
    if( partial_count > height ) height = partial_count;
}

 //Returns the level of a tree node.
template <class T>
int tree<T>::get_level(nodeptr node) const{
    int level = 0;
    nodeptr iterator = node;
    while( iterator != get_root() ){
        level++;
        iterator = get_parent(iterator);
    }
    return level;
}

//Deletes a subtree of a node.
template <class T>
void tree<T>::delete_subtree(nodeptr node){
    clear(node);
}

//Inserts the second tree as a subtree of the first;
template <class T>
void tree<T>::insert_subtree(const tree<T>&t, nodeptr node){
    tree<T> *tree = new typename tree<T>::tree<T>;
    copy_tree(*tree,t,tree->get_root(),t.get_root());
    insert_next_sibling(node,tree->get_root());
}

//Prints recursively each node at a certain tree level.
template <class T>
void tree<T>::print_level(ostream& output, nodeptr node, int level) const {
    if (node == nullptr){
        return; // Base case: If the node is null, do nothing.
    }
    //If the node we consider is on the interested level, we print it.
    if (level == 0) {
        output << "[PT:";
        if(get_parent(node) == nullptr) output << "NULL]: ";
        else{
            output << read(get_parent(node)) << "|: ";
            if( get_first_child(get_parent(node)) == node ) output << "FS]: ";
            else output << "NS:" << read(get_prev_sibling(node)) << "]: ";
        } 
        output << read(node) << " "; // Print the node's value at this level.
    }
    print_level(output, get_first_child(node), level - 1);
    print_level(output, get_next_sibling(node), level);

} 

//It copies the second tree into the first tree.
template <class T>
void tree<T>::copy_tree(tree<T> &T1, const tree<T>&T2, nodeptr n1, nodeptr n2){
    if(T1.empty()){
        nodeptr new_node = new tree_node<T>(T2.read(T2.get_root()));
        T1.insert_root(new_node);
        n1 = new_node;
    }
    if(T2.has_first_child(n2)){
        nodeptr first_child = new tree_node<T>(T2.read(T2.get_first_child(n2)));
        T1.insert_first_child(n1,first_child);
        copy_tree(T1,T2,first_child,T2.get_first_child(n2));
    }
    if(T2.get_next_sibling(n2)){
        nodeptr next_sibling = new tree_node<T>(T2.read(T2.get_next_sibling(n2)));
        T1.insert_next_sibling(n1,next_sibling);
        copy_tree(T1,T2,next_sibling,T2.get_next_sibling(n2));
    }
}

/*** Operators ***/
template <class T>
ostream& operator << (ostream& output, tree<T>& t){
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

/*** Operators ***/
//Operator + (tree concatenation).
template <class T>
typename tree<T>::tree<T> tree<T>::operator +(const tree<T>&t){
    tree<T>* sum_tree = new tree<T>;
    nodeptr sum_root = new tree_node<T>(0); //Sentinel node.
    sum_tree->insert_root(sum_root);
    tree<T> first_subtree;
    tree<T> second_subtree;
    first_subtree = *this;
    second_subtree = t;
    sum_tree->insert_first_child(sum_root,first_subtree.get_root());
    sum_tree->insert_next_sibling(first_subtree.get_root(),second_subtree.get_root());
    return *sum_tree;
}

//Operator =(Assigment by copy).
template <class T>
typename tree<T>::tree<T>& tree<T>::operator =(const tree<T>&t){
    clear(root);
    copy_tree(*this,t,get_root(),t.get_root());
    return *this;
}

//Operator =(Move equal).
template <class T>
void tree<T>::operator =(tree<T> &&t){
    clear(root);
    n_elements = t.n_elements;
    root = t.root;
    t.root = nullptr;
}

//Operator ==(Compares two trees.).
template <class T>
bool tree<T>::operator ==(tree<T>&t){
    if(empty() && t.empty()) return true;
    if(size() != t.size()) return false;
    return compare_trees(*this,t,get_root(),t.get_root());
}

template <class T>
bool tree<T>::compare_trees(const tree<T> &T1,const tree<T> &T2, nodeptr n1, nodeptr n2 ){
    if(read(n1) != read(n2)) return false;
    bool layer_result,subtree_result;
    layer_result = subtree_result = true;
    if(has_first_child(n1) && has_first_child(n2)) subtree_result = compare_trees(T1,T2,T1.get_first_child(n1),T2.get_first_child(n2));
    else{
        if(!(has_first_child(n1) && has_first_child(n2))) subtree_result = true;
        else return false;
    } 
    if(has_next_sibling(n1) && has_next_sibling(n2)) layer_result = compare_trees(T1,T2,T1.get_next_sibling(n1),T2.get_next_sibling(n2));
    else{
        if(!(has_next_sibling(n1) && has_next_sibling(n2))) layer_result = true;
        else return false;
    } 
    return (layer_result && subtree_result);
}

#endif // TREE
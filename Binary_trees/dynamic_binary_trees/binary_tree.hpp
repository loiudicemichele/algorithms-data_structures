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

template <class T> class binary_tree;
template <class T>
class tree_node{
        friend class binary_tree<T>;
    public:
        typedef tree_node<T>* nodeptr;
        tree_node(): value(0), left_child(nullptr), right_child(nullptr), parent(nullptr){}
        tree_node(const T& value_in): value(value_in), left_child(nullptr), right_child(nullptr), parent(nullptr){}
        ~tree_node(){left_child = right_child = parent = nullptr;}

    private:
        T value;
        nodeptr left_child;
        nodeptr right_child;
        nodeptr parent;
};

template <class T>
class binary_tree : public abstract_bin_tree<T,tree_node<T>*>{
    public:
        typedef typename abstract_bin_tree<T,tree_node<T>*>::position nodeptr;
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
        nodeptr get_root() const; //Returns the root of the tree.
        nodeptr get_left_child(nodeptr) const; //Returns the left child of a node.
        nodeptr get_right_child(nodeptr) const; //Returns the right child of a node.
        nodeptr get_parent(nodeptr) const; //Returns the parent of a node.
        void erase(nodeptr); //Deletes a subtree from the tree.
        void insert_root(nodeptr);//Sets the root of the tree.
        void insert_left_child(nodeptr,nodeptr);//Sets the left child of a parent node.
        void insert_right_child(nodeptr,nodeptr);//Sets the right child of a parent node.
        void insert_parent(nodeptr,nodeptr);//Sets the parent of a node.
        void write(const T&, nodeptr);//Sets the value of a node.
        T read(nodeptr) const; //Reads the value of a node.
        int get_height() const; //Returns the height of the tree.
        int get_level(nodeptr) const; //Returns the level of a tree node.
        bool has_left_child(nodeptr) const; //Returns true if the node has a left child
        bool has_right_child(nodeptr) const; //Returns true if the node has a right child
        bool has_parent(nodeptr) const; //Returns true if the node has a parent
        

        /*** Operators ***/
        binary_tree<T> operator +(const binary_tree<T>&); //Operator + (tree concatenation).
        binary_tree<T>& operator =(const binary_tree<T>&); //Operator =(Assigment by copy).
        void operator =(binary_tree<T> &&); //Operator =(Move equal).
        bool operator ==(binary_tree<T>&); //Operator ==(Compares two trees.).
        //Prints recursively each node at a certain tree level. (Supports the << operator)
        void print_level(ostream&, nodeptr node, int level) const; 
        /* Test Functions */
        void inizialize_tree(T,T);
    private:
        /*** PRIVATE METHODS ***/
        void copy_tree(binary_tree<T>&,const binary_tree<T>&,nodeptr,nodeptr);
        bool compare_subtree(nodeptr, nodeptr);
        void get_height(nodeptr, int ,int&) const; //Returns the height of a node.
        void clear(nodeptr); //Clears the elements of the tree.
        /*** PRIVATE ATTRIBUTES ***/
        int n_elements;
        nodeptr root;
};

/*** Default Constructor ***/
template <class T>
binary_tree<T>::binary_tree(){
    root = nullptr;
    n_elements = 0;
}
/*** Destructor ***/
template <class T>
binary_tree<T>::~binary_tree(){
    clear(root);
    n_elements = 0;
}
/*** Copy Constructor ***/
template <class T>
binary_tree<T>::binary_tree(const binary_tree<T> &t){
    n_elements = 0;
    insert_root(new tree_node<T>(t.read(t.get_root())));
    copy_tree(*this, t, get_root(), t.get_root());
}
/*** Move Constructor ***/
template <class T>
binary_tree<T>::binary_tree(binary_tree<T>&& tree) noexcept{
    root = tree.root;
    n_elements = tree.n_elements;
    tree.root = nullptr;
}

/*** Methods ***/
template <class T>
void binary_tree<T>::clear(nodeptr node){
    if(node == nullptr) return;
    if(node->left_child != nullptr ) clear(node->left_child);
    if(node->right_child != nullptr ) clear(node->right_child);
    //Deleting the left or right pointer to the parent node is required.
    if(node->parent != nullptr){
        if(node->parent->left_child == node) node->parent->left_child = nullptr;
        else if(node->parent->right_child == node) node->parent->right_child = nullptr;
        node->parent = nullptr;
    }
    n_elements--;
    delete node;
}

//Returns true if the tree is empty.
template <class T>
bool binary_tree<T>::empty() const{
    return (root == nullptr);
} 

//Returns the number of nodes in the tree.
template <class T>
int binary_tree<T>::size() const{
    return n_elements;
}



//Returns the root of the tree.
template <class T>
typename binary_tree<T>::nodeptr binary_tree<T>::get_root() const{
    return root;
} 

//Returns the left child of a node.
template <class T>
typename binary_tree<T>::nodeptr binary_tree<T>::get_left_child(nodeptr n) const{
    if(n == nullptr) return nullptr;
    return n->left_child;
} 

//Returns the right child of a node.
template <class T>
typename binary_tree<T>::nodeptr binary_tree<T>::get_right_child(nodeptr n) const{
    if(n == nullptr) return nullptr;
    return n->right_child;
} 

//Returns the parent of a node.
template <class T>
typename binary_tree<T>::nodeptr binary_tree<T>::get_parent(nodeptr n) const{
    if(n == nullptr) return nullptr;
    return n->parent;
} 

//Deletes a sub-tree from the list.
template <class T>
void binary_tree<T>::erase(nodeptr n){
    //Unlinking the rest of the tree from the sub-tree.
    if(n->parent->left_child == n) n->parent->left_child = nullptr; 
    if(n->parent->right_child == n) n->parent->right_child = nullptr; 
    n->parent = nullptr;
    //Deleting the sub-tree.
    clear(n);
} 

//Sets the root of the tree.
template <class T>
void binary_tree<T>::insert_root(nodeptr root_in){
    if(root_in == nullptr) return;
    root = root_in;
    n_elements++;
}

//Sets the left child of a parent node.
template <class T>
void binary_tree<T>::insert_left_child(nodeptr parent, nodeptr child){
    if(parent == nullptr) return;
    child->parent = parent;
    parent->left_child = child;
    n_elements++;
}

//Sets the right child of a parent node.
template <class T>
void binary_tree<T>::insert_right_child(nodeptr parent, nodeptr child){
    if(parent == nullptr) return;
    child->parent = parent;
    parent->right_child = child;
    n_elements++;
}
  
//Sets the right child of a parent node.
template <class T>
void binary_tree<T>::insert_parent(nodeptr node, nodeptr parent){
    if(parent == nullptr) return;
    //Making sure the parent node has the input node as a child.
    if(parent->left_child != node && parent->right_child != node) return;
    node->parent = parent;
}

//Sets the value of a node.
template <class T>
void binary_tree<T>::write(const T &value, nodeptr n){
    if(n != nullptr) n->value = value;
}

//Reads the value of a node.
template <class T>
T binary_tree<T>::read(nodeptr n) const{
    return n->value;
}

//Returns true if the node has a left child
template <class T>
bool binary_tree<T>::has_left_child(nodeptr n) const{
    return (n->left_child != nullptr);
}

//Returns true if the node has a right child
template <class T>
bool binary_tree<T>::has_right_child(nodeptr n) const{
    return (n->right_child != nullptr);
}

//Returns true if the node has a parent
template <class T>
bool binary_tree<T>::has_parent(nodeptr n) const{
    return (n->parent != nullptr);
}

//Returns the height of the tree.
template <class T>
int binary_tree<T>::get_height() const{
    int count = 0;
    int partial_count = 0;
    get_height(root,partial_count,count);
    return count;
}

//Returns the height of a node.
template <class T>
int binary_tree<T>::get_level(nodeptr node) const{
    if(node == nullptr) return -1;
    if(node == root ) return 0;
    int count = 1;
    while(node->parent != nullptr && node->parent != root ){
        node = node->parent;
        count++;
    } 
    return count;
}

//Caltulates the height of the input node subtree.
template <class T>
void binary_tree<T>::get_height(nodeptr p, int partial_count, int& count) const{
    if(p == nullptr) return;
    if(p->left_child != nullptr) get_height(p->left_child,partial_count+1,count);
    if(p->right_child != nullptr) get_height(p->right_child,partial_count+1,count);
    if(partial_count > count) count = partial_count;
}

//Prints recursively each node at a certain tree level.
template <class T>
void binary_tree<T>::print_level(ostream& output, nodeptr node, int level) const {
    if (node == nullptr) {
        return; // Base case: If the node is null, do nothing.
    }
    //If the node we consider is on the interested level, we print it.
    if (level == 0) {
        output << "[PT:";
        if(node->parent == nullptr) output << "NULL]: ";
        else{
            output << node->parent->value << "|: ";
            if( node->parent->left_child == node ) output << "SX]: ";
            else output << "DX]: ";
        } 
        output << node->value << " "; // Print the node's value at this level.
    } else {
        print_level(output, node->left_child, level - 1);
        print_level(output, node->right_child, level - 1);
    }
} 

// Main function to print the tree by levels
template <class T>
ostream& operator << (ostream& output, binary_tree<T>& t) {
    if(t.empty()){
        output << "Tree is empty";
        return output;
    }
    int height = t.get_height(); // Get the height of the tree.
    //Printing the tree by levels.
    for (int i = 0; i <= height; ++i) {
        output << "LEVEL: [" <<  i << "]: ";
        t.print_level(output, t.get_root(), i); // Print all nodes at the current level.
        output << endl;    // Move to the next level.
    }
    return output; 
}


/*** Operators ***/
//Operator + (tree concatenation).
template <class T>
binary_tree<T> binary_tree<T>::operator +(const binary_tree<T>& t){
    binary_tree<T> *sum_tree = new binary_tree;
    sum_tree->insert_root(new tree_node<T>);  //Inserting a Sentinel node as root.
    sum_tree->insert_left_child(sum_tree->get_root(), new tree_node<T>(read(get_root())));
    sum_tree->insert_right_child(sum_tree->get_root(), new tree_node<T>(t.read(t.get_root())));
    copy_tree(*sum_tree, *this, sum_tree->root->left_child, get_root());
    copy_tree(*sum_tree, t, sum_tree->root->right_child, t.get_root());
    return *sum_tree;
}

//Operator =(Assigment by copy).} template <class T>
template <class T>
binary_tree<T>& binary_tree<T>::operator =(const binary_tree<T>& t){
    if(this == &t)return *this;
    clear(root);
    if(t.empty()) return *this;
    insert_root(new tree_node<T>(t.read(t.get_root())));
    copy_tree(*this, t, get_root(), t.get_root());
    return *this;
}

template <class T>
void binary_tree<T>::copy_tree(binary_tree<T> &T1, const binary_tree<T> &T2, nodeptr n1, nodeptr n2){
    if( T2.has_left_child(n2) ){
        nodeptr new_node = new tree_node<T>(T2.read(T2.get_left_child(n2)));
        T1.insert_left_child(n1,new_node);
        T1.insert_parent(new_node,n1);
        copy_tree(T1,T2,T1.get_left_child(n1),T2.get_left_child(n2));
    } 
    if( T2.has_right_child(n2) ){
        nodeptr new_node = new tree_node<T>(T2.read(T2.get_right_child(n2)));
        T1.insert_right_child(n1,new_node);
        T1.insert_parent(new_node,n1);
        copy_tree(T1,T2,T1.get_right_child(n1),T2.get_right_child(n2));
    } 
}

//Operator =(Move equal).
template <class T>
void binary_tree<T>::operator =(binary_tree<T> && tree){
    clear(root);
    root = tree.root;
    n_elements = tree.n_elements;
    tree.root = nullptr;
}

//Operator ==(Compares two trees.).} template <class T>
template <class T>
bool binary_tree<T>::operator ==(binary_tree<T>& tree){
    if(this == &tree) return true;
    if(this->n_elements != n_elements) return false;
    return compare_subtree(this->root,tree.root);
}

//Compares two sub-tree
template <class T>
bool binary_tree<T>::compare_subtree(nodeptr root_first, nodeptr root_second){
    if(root_first == nullptr || root_second == nullptr){
        if(root_first == nullptr && root_second == nullptr) return true;
        else return false;
    }
    if(root_first->value != root_second->value) return false;
    bool sub_tree_1 = compare_subtree(root_first->left_child,root_second->left_child);
    bool sub_tree_2 = compare_subtree(root_first->right_child,root_second->right_child);
    return (sub_tree_1 && sub_tree_2);
}


/* Test Functions 
* Inserting elements in the following way:
* even (Pari) -> Right Child
* odd (Dispari) -> Left Child
*/
template <class T>
void binary_tree<T>::inizialize_tree(T start_value, T end_value ){
    if( root == nullptr ){ 
        root = new tree_node<T>(start_value);
        n_elements++;
        inizialize_tree(++start_value, end_value);
        return;
    }
    if( start_value >= end_value ) return; //End condition.
    if( start_value%2 == 0 ){
        nodeptr new_node = new tree_node<T>(start_value);
        new_node->left_child = root;
        root->parent = new_node;
        root = new_node;
        n_elements++;
        inizialize_tree(++start_value, end_value);
    } else{
        nodeptr new_node = new tree_node<T>(start_value);
        new_node->right_child = root;
        root->parent = new_node;
        root = new_node;
        n_elements++;
        inizialize_tree(++start_value, end_value);
    }
}

#endif // TREE
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

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <iostream>
#include "abstract_bst.hpp"
using namespace std;

template <class T> class BST;
template <class T>
class tree_node{
        friend class BST<T>;
    public:
        typedef tree_node<T>* nodeptr;
        tree_node(): value(0), left_child(nullptr), right_child(nullptr), parent(nullptr){}
        tree_node(const T& value_in): value(value_in), left_child(nullptr), right_child(nullptr), parent(nullptr){}
        ~tree_node(){left_child = right_child = parent = nullptr;}
        T get_value(){return value;};
    private:
        T value;
        nodeptr left_child;
        nodeptr right_child;
        nodeptr parent;
};

template <class T>
class BST : public abstract_bst_tree<T, tree_node<T>*>{
    public:
        typedef typename abstract_bst_tree<T, tree_node<T>*>::position nodeptr;
        /*** Default Constructor ***/
        BST();
        /*** Destructor ***/
        ~BST();
        /*** Copy Constructor ***/
        BST(const BST<T>&);
        /*** Move Constructor ***/
        BST(BST<T>&&) noexcept;
        
        /*** Methods ***/
        int size() const; //Returns the number of nodes in the tree.
        bool empty() const; //Returns true if the tree is empty.
        nodeptr get_root() const; //Returns the root of the tree.
        nodeptr get_left_child(nodeptr) const; //Returns the left child of a node.
        nodeptr get_right_child(nodeptr) const; //Returns the right child of a node.
        nodeptr get_parent(nodeptr) const; //Returns the parent of a node.
        
        void insert(nodeptr); // Inserts a new node into the tree;
        bool contains(const T&) const; //Searches if a value is contained. 
        void delete_node(nodeptr); //Deleates a node from the tree.
        nodeptr minimum() const; //Returns the minimum value in the tree.
        nodeptr maximum() const; //Returns the maximum value of the tree.
        nodeptr predecessor(nodeptr) const; //Retruns the predecessor of the node. (The previous node in the order).
        nodeptr successor(nodeptr) const; //Retruns the successor of the node. (The next node in the order).
        
        void write(const T&, nodeptr);//Sets the value of a node.
        T read(nodeptr) const; //Reads the value of a node.
        int get_height() const; //Returns the height of the tree.
        int get_level(nodeptr) const; //Returns the level of a tree node.
        bool has_left_child(nodeptr) const; //Returns true if the node has a left child
        bool has_right_child(nodeptr) const; //Returns true if the node has a right child
        bool has_parent(nodeptr) const; //Returns true if the node has a parent
        
        /*** Operators ***/
        BST<T>& operator =(const BST<T>&); //Operator =(Assigment by copy).
        void operator =(BST<T> &&); //Operator =(Move equal).
        bool operator ==(BST<T>&); //Operator ==(Compares two trees.).
        //Prints recursively each node at a certain tree level. (Supports the << operator)
        void print_level(ostream&, nodeptr node, int level) const;
    private:
        /*** PRIVATE METHODS ***/
        nodeptr insert(nodeptr, nodeptr); //Recursive insertion.
        bool contains(const T&, nodeptr) const; //Recursive search.
        void replace_node(nodeptr, nodeptr); //Replace two nodes when deleting a node.
        nodeptr minimum(nodeptr) const; //Recursive search of minimum.
        nodeptr maximum(nodeptr) const; //Recursive search of maximum.
        void erase(nodeptr); //Deletes a subtree from the tree.

        void insert_root(nodeptr);//Sets the root of the tree.
        void insert_left_child(nodeptr,nodeptr);//Sets the left child of a parent node.
        void insert_right_child(nodeptr,nodeptr);//Sets the right child of a parent node.
        void insert_parent(nodeptr,nodeptr);//Sets the parent of a node.
        
        void copy_tree(BST<T>&,const BST<T>&,nodeptr,nodeptr);
        bool compare_subtree(nodeptr, nodeptr);
        void get_height(nodeptr, int ,int&) const; //Returns the height of a node.
        void clear(nodeptr); //Clears the elements of the tree.
        /*** PRIVATE ATTRIBUTES ***/
        int n_elements;
        nodeptr root;
};

/*** Default Constructor ***/
template <class T>
BST<T>::BST(){
    root = nullptr;
    n_elements = 0;
}
/*** Destructor ***/
template <class T>
BST<T>::~BST(){
    clear(root);
    n_elements = 0;
}
/*** Copy Constructor ***/
template <class T>
BST<T>::BST(const BST<T> &t){
    n_elements = 0;
    insert_root(new tree_node<T>(t.read(t.get_root())));
    copy_tree(*this, t, get_root(), t.get_root());
}
/*** Move Constructor ***/
template <class T>
BST<T>::BST(BST<T>&& tree) noexcept{
    root = tree.root;
    n_elements = tree.n_elements;
    tree.root = nullptr;
}

/*** Methods ***/
// Inserts a new node into the tree
template <class T>
void BST<T>::insert(nodeptr node){
    if(node == nullptr) return;
    if(root == nullptr){
        root = node;
        n_elements = 1;
        return;
    }
    n_elements++; 
    insert(root,node);
} 

template <class T>
typename BST<T>::nodeptr BST<T>::insert(nodeptr iterator, nodeptr node){
    if(iterator == nullptr) return node;
    if(read(iterator) > read(node)){
        nodeptr left = insert(get_left_child(iterator),node);
        iterator->left_child = left;
        left->parent = iterator;
        return iterator;
    } else {
        nodeptr right = insert(get_right_child(iterator),node);
        iterator->right_child = right;
        right->parent = iterator;
        return iterator;
    }
} 

//Searches if a value is contained. 
template <class T>
bool BST<T>::contains(const T& value) const{
    if(empty()) return false;
    return contains(value, get_root());
}

//Searches if a value is contained. 
template <class T>
bool BST<T>::contains(const T& value, nodeptr node) const{
    if(value == read(node) ) return true;
    if(has_left_child(node) && (value < read(node))) return contains(value, get_left_child(node));
    if(has_right_child(node) && (value > read(node))) return contains(value, get_right_child(node));
    return false;
}

//Deleates a node from the tree.
template <class T>
void BST<T>::delete_node(nodeptr node){
    //Case 1: The node has no childrens.
    if(!has_left_child(node) && !has_right_child(node)) erase(node);
    else if( has_left_child(node) && has_right_child(node) ){
        //Case 2: has both childrens.
        nodeptr _successor = successor(node);
        write(read(_successor),node);
        if(has_right_child(_successor)) replace_node(_successor, get_right_child(_successor));
        else clear(_successor);
    } else{
        //Case 3: The node has at least one child, replacing the node with his child.
        if(has_left_child(node)) replace_node(node, get_left_child(node));
        else replace_node(node, get_right_child(node));
    }  
} 

//Replace two nodes when deleting a node.
template <class T>
void BST<T>::replace_node(nodeptr node, nodeptr new_node){
    if(!has_parent(node)){ //If the node doesn't have a parent, is the root.
        //Replacing the root.
        if(has_left_child(root)){
            node->left_child = nullptr;
            root = new_node;
        } else{
            node->right_child = nullptr;
            root = new_node;
        }
        //Resetting the parent node.
        root->parent = nullptr;
    } else{
        //If the node is a left child we set the new node as left child of the node's parent.
        if(get_left_child(get_parent(node)) == node){ 
            node->parent->left_child = new_node;
            node->left_child = nullptr;
        } else{
            node->parent->right_child = new_node;
            node->right_child = nullptr;
        }
        new_node->parent = node->parent;
        node->parent = nullptr;
    }
    clear(node);
}

//Returns the minimum value in the tree.
template <class T>
typename BST<T>::nodeptr BST<T>::minimum() const{
    if(empty()) return nullptr;
    else return minimum(get_root());
} 

template <class T>
typename BST<T>::nodeptr BST<T>::minimum(nodeptr node) const{
    if(has_left_child(node)) return minimum(get_left_child(node));
    return node;
} 

//Returns the maximum value of the tree.
template <class T>
typename BST<T>::nodeptr BST<T>::maximum() const{
    if(empty()) return nullptr;
    else return maximum(get_root());
} 

template <class T>
typename BST<T>::nodeptr BST<T>::maximum(nodeptr node) const{
    if(has_right_child(node)) return maximum(get_right_child(node));
    return node;
} 


//Retruns the predecessor of the node. (The previous node in the order).
template <class T>
typename BST<T>::nodeptr BST<T>::predecessor(nodeptr node) const{
    if(has_left_child(node)) return maximum(get_left_child(node));
    else if(has_parent(node) && read(get_parent(node)) < read(node)) return get_parent(node); 
    else return nullptr; //The node has the lowest value
} 

//Retruns the successor of the node. (The next node in the order).
template <class T>
typename BST<T>::nodeptr BST<T>::successor(nodeptr node) const{
    if(has_right_child(node)) return minimum(get_right_child(node));
    else if(has_parent(node) && read(get_parent(node)) > read(node)) return get_parent(node); 
    else return nullptr; //The node has the highest value
} 







template <class T>
void BST<T>::clear(nodeptr node){
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
bool BST<T>::empty() const{
    return (root == nullptr);
} 

//Returns the number of nodes in the tree.
template <class T>
int BST<T>::size() const{
    return n_elements;
}



//Returns the root of the tree.
template <class T>
typename BST<T>::nodeptr BST<T>::get_root() const{
    return root;
} 

//Returns the left child of a node.
template <class T>
typename BST<T>::nodeptr BST<T>::get_left_child(nodeptr n) const{
    if(n == nullptr) return nullptr;
    return n->left_child;
} 

//Returns the right child of a node.
template <class T>
typename BST<T>::nodeptr BST<T>::get_right_child(nodeptr n) const{
    if(n == nullptr) return nullptr;
    return n->right_child;
} 

//Returns the parent of a node.
template <class T>
typename BST<T>::nodeptr BST<T>::get_parent(nodeptr n) const{
    if(n == nullptr) return nullptr;
    return n->parent;
} 

//Deletes a sub-tree from the tree.
template <class T>
void BST<T>::erase(nodeptr n){
    //Unlinking the rest of the tree from the sub-tree.
    if(n->parent->left_child == n) n->parent->left_child = nullptr; 
    if(n->parent->right_child == n) n->parent->right_child = nullptr; 
    n->parent = nullptr;
    //Deleting the sub-tree.
    clear(n);
} 

//Sets the root of the tree.
template <class T>
void BST<T>::insert_root(nodeptr root_in){
    if(root_in == nullptr) return;
    root = root_in;
    n_elements++;
}

//Sets the left child of a parent node.
template <class T>
void BST<T>::insert_left_child(nodeptr parent, nodeptr child){
    if(parent == nullptr) return;
    child->parent = parent;
    parent->left_child = child;
    n_elements++;
}

//Sets the right child of a parent node.
template <class T>
void BST<T>::insert_right_child(nodeptr parent, nodeptr child){
    if(parent == nullptr) return;
    child->parent = parent;
    parent->right_child = child;
    n_elements++;
}
  
//Sets the right child of a parent node.
template <class T>
void BST<T>::insert_parent(nodeptr node, nodeptr parent){
    if(parent == nullptr) return;
    //Making sure the parent node has the input node as a child.
    if(parent->left_child != node && parent->right_child != node) return;
    node->parent = parent;
}

//Sets the value of a node.
template <class T>
void BST<T>::write(const T &value, nodeptr n){
    if(n != nullptr) n->value = value;
}

//Reads the value of a node.
template <class T>
T BST<T>::read(nodeptr n) const{
    return n->value;
}

//Returns true if the node has a left child
template <class T>
bool BST<T>::has_left_child(nodeptr n) const{
    return (n->left_child != nullptr);
}

//Returns true if the node has a right child
template <class T>
bool BST<T>::has_right_child(nodeptr n) const{
    return (n->right_child != nullptr);
}

//Returns true if the node has a parent
template <class T>
bool BST<T>::has_parent(nodeptr n) const{
    return (n->parent != nullptr);
}

//Returns the height of the tree.
template <class T>
int BST<T>::get_height() const{
    int count = 0;
    int partial_count = 0;
    get_height(root,partial_count,count);
    return count;
}

//Returns the height of a node.
template <class T>
int BST<T>::get_level(nodeptr node) const{
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
void BST<T>::get_height(nodeptr p, int partial_count, int& count) const{
    if(p == nullptr) return;
    if(p->left_child != nullptr) get_height(p->left_child,partial_count+1,count);
    if(p->right_child != nullptr) get_height(p->right_child,partial_count+1,count);
    if(partial_count > count) count = partial_count;
}

//Prints recursively each node at a certain tree level.
template <class T>
void BST<T>::print_level(ostream& output, nodeptr node, int level) const {
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
ostream& operator << (ostream& output, BST<T>& t) {
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

//Operator =(Assigment by copy).} template <class T>
template <class T>
BST<T>& BST<T>::operator =(const BST<T>& t){
    if(this == &t)return *this;
    clear(root);
    if(t.empty()) return *this;
    insert_root(new tree_node<T>(t.read(t.get_root())));
    copy_tree(*this, t, get_root(), t.get_root());
    return *this;
}

template <class T>
void BST<T>::copy_tree(BST<T> &T1, const BST<T> &T2, nodeptr n1, nodeptr n2){
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
void BST<T>::operator =(BST<T> && tree){
    clear(root);
    root = tree.root;
    n_elements = tree.n_elements;
    tree.root = nullptr;
}

//Operator ==(Compares two trees.).} template <class T>
template <class T>
bool BST<T>::operator ==(BST<T>& tree){
    if(this == &tree) return true;
    if(this->n_elements != n_elements) return false;
    return compare_subtree(this->root,tree.root);
}

//Compares two sub-tree
template <class T>
bool BST<T>::compare_subtree(nodeptr root_first, nodeptr root_second){
    if(root_first == nullptr || root_second == nullptr){
        if(root_first == nullptr && root_second == nullptr) return true;
        else return false;
    }
    if(root_first->value != root_second->value) return false;
    bool sub_tree_1 = compare_subtree(root_first->left_child,root_second->left_child);
    bool sub_tree_2 = compare_subtree(root_first->right_child,root_second->right_child);
    return (sub_tree_1 && sub_tree_2);
}

#endif // BINARY_SEARCH_TREE
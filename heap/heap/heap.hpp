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

#ifndef heapS
#define heapS

#include <iostream>
using namespace std;

template <class T, class P> class heap;
template <class T, class P>
class tree_node{
        friend class heap<T,P>;
    public:
        typedef tree_node<T, P>* nodeptr;
        tree_node(): value(0), priority(0), left_child(nullptr), right_child(nullptr), parent(nullptr){}
        tree_node(const T& value_in): value(value_in), left_child(nullptr), right_child(nullptr), parent(nullptr){}
        tree_node(const T& value_in,const P& priority_in): value(value_in), priority(priority_in), left_child(nullptr), right_child(nullptr), parent(nullptr){}
        ~tree_node(){left_child = right_child = parent = nullptr;}

    private:
        T value;
        P priority;
        nodeptr left_child;
        nodeptr right_child;
        nodeptr parent;
};

template <class T, class P>
class heap{
    public:
        typedef tree_node<T,P>* nodeptr;
        /*** Default Constructor ***/
        heap();
        /*** Destructor ***/
        ~heap();
        /*** Copy Constructor ***/
        heap(const heap<T,P>&);
        /*** Move Constructor ***/
        heap(heap<T,P>&&) noexcept;
        
        /*** Methods ***/
        void insert(const T&, const P&); //Inserts an element with his priority.
        T read_min() const; //Reads the element with the lowest priority.
        void delete_min(); //Deletes the element with the lowest priority.

        /*** Methods for cout operator ***/
        int get_height() const; //Returns the height of the tree.
        bool empty() const; //Returns true if the tree is empty.
        nodeptr get_root() const; //Returns the root of the tree.
        /*** Operators ***/
        heap<T,P> operator +(const heap<T,P>&); //Operator + (tree concatenation).
        heap<T,P>& operator =(const heap<T,P>&); //Operator =(Assigment by copy).
        void operator =(heap<T,P> &&); //Operator =(Move equal).
        //Prints recursively each node at a certain tree level. (Supports the << operator)
        void print_level(ostream&, nodeptr node, int level) const; 
    private:
        /* Private Methods */
        void bottop_up_balancement(nodeptr); //Balances the tree from a bottom node up to the root node.
        void top_down_balancement(nodeptr); //Balances the tree from the a node untill it is balanced.
        void swap(nodeptr, nodeptr); //Swaps two nodes with different priorities.
        void find_prev_last_inserted();
        /* TREE STRUCTURE FUNCTIONS */
        int size() const; //Returns the number of nodes in the tree.
        nodeptr get_left_child(nodeptr) const; //Returns the left child of a node.
        nodeptr get_right_child(nodeptr) const; //Returns the right child of a node.
        nodeptr get_parent(nodeptr) const; //Returns the parent of a node.
        P get_priority(nodeptr) const; //Returns the priority of a node.
        bool is_left_child(nodeptr) const; //Returns true if the node is a left node.
        bool is_right_child(nodeptr) const; //Returns true if the node is a right node.
        void insert_root(nodeptr);//Sets the root of the tree.
        void insert_left_child(nodeptr,nodeptr);//Sets the left child of a parent node.
        void insert_right_child(nodeptr,nodeptr);//Sets the right child of a parent node.
        void insert_parent(nodeptr,nodeptr);//Sets the parent of a node.
        void write(const T&, nodeptr);//Sets the value of a node.
        T read(nodeptr) const; //Reads the value of a node.
        bool has_left_child(nodeptr) const; //Returns true if the node has a left child
        bool has_right_child(nodeptr) const; //Returns true if the node has a right child
        bool has_parent(nodeptr) const; //Returns true if the node has a parent
        /*** PRIVATE METHODS ***/
        void copy_tree(heap<T,P>&,const heap<T,P>&,nodeptr,nodeptr);
        bool compare_subtree(nodeptr, nodeptr);
        void get_height(nodeptr, int ,int&) const; //Returns the height of a node.
        void clear(nodeptr); //Clears the elements of the tree.
        /*** PRIVATE ATTRIBUTES ***/
        int n_elements;
        nodeptr last_inserted; //Last node inserted in the tree
        nodeptr root;
};

/*** Default Constructor ***/
template <class T, class P>
heap<T,P>::heap(){
    root = last_inserted = nullptr;
    n_elements = 0;
}

/*** Destructor ***/
template <class T, class P>
heap<T,P>::~heap(){
    clear(root);
}

//Destructs the tree.
template <class T, class P>
void heap<T,P>::clear(nodeptr node){
    if(node == nullptr) return;
    if(node->left_child != nullptr ) clear(node->left_child);
    if(node->right_child != nullptr ) clear(node->right_child);
    //Deleting the left or right pointer to the parent node is required.
    if(node->parent != nullptr){
        if(node->parent->left_child == node) node->parent->left_child = nullptr;
        else if(node->parent->right_child == node) node->parent->right_child = nullptr;
    }
    n_elements--;
    delete node;
}

/*** Copy Constructor ***/
template <class T, class P>
heap<T,P>::heap(const heap<T,P>& t){
    n_elements = 0;
    insert_root(new tree_node<T,P>(t.read(t.get_root())));
    copy_tree(*this, t, get_root(), t.get_root());
}

/*** Move Constructor ***/
template <class T, class P>
heap<T,P>::heap(heap<T,P>&& t) noexcept{
    root = t.root;
    last_inserted = t.last_inserted;
    n_elements = t.n_elements;
    t.root = t.last_inserted = nullptr;
}

/*** Methods ***/
//Inserts an element with his priority.
template <class T, class P>
void heap<T,P>::insert(const T& value, const P& priority){
    nodeptr new_node = new tree_node<T,P>(value,priority);
    if(empty()){ //If the tree is empty, we insert the new node as the root of the tree.
        insert_root(new_node);
        return;
    }
    //If the tree has just the root node, we insert his left child.
    if(last_inserted == root) insert_left_child(root, new_node);
    //If the last inserted node is a left node, the right spot is empy, we insert the new node there.
    else if(is_left_child(last_inserted)){ 
        insert_right_child(last_inserted->parent, new_node);
    } else{
        //Otherwise, we iterate in order to find the first node that is not a right node.
        nodeptr iterator = last_inserted;
        while(is_right_child(iterator) && iterator != root ) iterator = get_parent(iterator);
        if(iterator != root) iterator = get_right_child(get_parent(iterator));
        //We insert the new node, as the last left node of the hierarchy.
        while(has_left_child(iterator)) iterator = get_left_child(iterator);    
        insert_left_child(iterator,new_node);
    }
    bottop_up_balancement(last_inserted);
}

//Deletes the element with the lowest priority.
template <class T, class P>
void heap<T,P>::delete_min(){
    if(!has_parent(last_inserted)){
        last_inserted = nullptr;
        delete root;
        return;
    } 
    //Overwriting the root node.
    root->value = read(last_inserted);
    root->priority = get_priority(last_inserted);
    //Deleting the old last_inserted node.
    nodeptr to_delete = last_inserted;
    find_prev_last_inserted();
    clear(to_delete);
    top_down_balancement(root);
}

//Find the previous inserted node.
template <class T, class P>
void heap<T,P>::find_prev_last_inserted(){
    if(empty()) return;
    if(last_inserted == root) {
        last_inserted = nullptr;
        return;
    }
    else if(is_right_child(last_inserted)){
        last_inserted = get_left_child(get_parent(last_inserted));
    } else{
        while(is_left_child(last_inserted) && last_inserted != root ) last_inserted = get_parent(last_inserted);
        if(last_inserted != root) last_inserted = get_left_child(get_parent(last_inserted));
        while(has_right_child(last_inserted)) last_inserted = get_right_child(last_inserted);
    }
}

//Inserts an element with his priority.
template <class T, class P>
void heap<T,P>::top_down_balancement(nodeptr node){
    if(node == nullptr) return;
    if(has_left_child(node) && has_right_child(node)){
        if(get_priority(get_left_child(node)) < get_priority(get_right_child(node))
            && get_priority(node) > get_priority(get_left_child(node)) ){
            swap(node,get_left_child(node));
            top_down_balancement(get_left_child(node));
        } else if ( get_priority(node) > get_priority(get_right_child(node)) ) {
            swap(node,get_right_child(node));
            top_down_balancement(get_right_child(node)); 
        }
    } else if(has_left_child(node) && (get_priority(node) > get_priority(get_left_child(node))) ){
        swap(node,get_left_child(node));
        top_down_balancement(get_left_child(node));
    } else if(has_right_child(node) && (get_priority(node) > get_priority(get_right_child(node)))){
        swap(node,get_right_child(node));
        top_down_balancement(get_right_child(node)); 
    }
}

//Inserts an element with his priority.
template <class T, class P>
void heap<T,P>::bottop_up_balancement(nodeptr node){
    if(node == nullptr || node == root) return;
    nodeptr iterator = node;
    while(has_parent(iterator) && ( get_priority(iterator) < get_priority(get_parent(iterator)) )){
        swap(iterator, get_parent(iterator));
        iterator = get_parent(iterator);
    }
}

//Swaps two nodes with different priorities.
template <class T, class P>
void heap<T,P>::swap(nodeptr node1, nodeptr node2){
    T tmp_value = read(node1); 
    P tmp_priority = get_priority(node1);
    node1->value = read(node2);
    node1->priority = get_priority(node2);
    node2->value = tmp_value;
    node2->priority = tmp_priority;
}

//Reads the element with the lowest priority.
template <class T, class P>
T heap<T,P>::read_min() const{
    return read(root);
} 

/* TREE STRUCTURE FUNCTIONS */
//Returns true if the tree is empty.
template <class T, class P>
bool heap<T,P>::empty() const{
    return (root == nullptr);
} 

//Returns the number of nodes in the tree.
template <class T, class P>
int heap<T,P>::size() const{
    return n_elements;
}

//Returns the root of the tree.
template <class T, class P>
typename heap<T,P>::nodeptr heap<T,P>::get_root() const{
    return root;
} 

//Returns the left child of a node.
template <class T, class P>
typename heap<T,P>::nodeptr heap<T,P>::get_left_child(nodeptr n) const{
    if(n == nullptr) return nullptr;
    return n->left_child;
} 

//Returns the right child of a node.
template <class T, class P>
typename heap<T,P>::nodeptr heap<T,P>::get_right_child(nodeptr n) const{
    if(n == nullptr) return nullptr;
    return n->right_child;
} 

//Returns the parent of a node.
template <class T, class P>
typename heap<T,P>::nodeptr heap<T,P>::get_parent(nodeptr n) const{
    if(n == nullptr) return nullptr;
    return n->parent;
} 

//Returns the priority of a node.
template <class T, class P>
P heap<T,P>::get_priority(nodeptr n) const{
    return n->priority;
} 

//Returns true if the node is a left node.
template <class T,class P>
bool heap<T,P>::is_left_child(nodeptr node) const{
    if(node == nullptr || node->parent == nullptr) return false;
    return(node->parent->left_child == node);
} 

//Returns true if the node is a right node.
template <class T,class P>
bool heap<T,P>::is_right_child(nodeptr node) const{
    if(node == nullptr || node->parent == nullptr) return false;
    return(node->parent->right_child == node);
} 

//Sets the root of the tree.
template <class T, class P>
void heap<T,P>::insert_root(nodeptr root_in){
    if(root_in == nullptr) return;
    root = root_in;
    last_inserted = root;
    n_elements++;
}

//Sets the left child of a parent node.
template <class T, class P>
void heap<T,P>::insert_left_child(nodeptr parent, nodeptr child){
    if(parent == nullptr) return;
    child->parent = parent;
    parent->left_child = child;
    last_inserted = child;
    n_elements++;
}

//Sets the right child of a parent node.
template <class T, class P>
void heap<T,P>::insert_right_child(nodeptr parent, nodeptr child){
    if(parent == nullptr) return;
    child->parent = parent;
    parent->right_child = child;
    last_inserted = child;
    n_elements++;
}
  
//Sets the right child of a parent node.
template <class T, class P>
void heap<T,P>::insert_parent(nodeptr node, nodeptr parent){
    if(parent == nullptr) return;
    //Making sure the parent node has the input node as a child.
    if(parent->left_child != node && parent->right_child != node) return;
    node->parent = parent;
}

//Sets the value of a node.
template <class T, class P>
void heap<T,P>::write(const T &value, nodeptr n){
    if(n != nullptr) n->value = value;
}

//Reads the value of a node.
template <class T, class P>
T heap<T,P>::read(nodeptr n) const{
    return n->value;
}

//Returns true if the node has a left child
template <class T,class P>
bool heap<T,P>::has_left_child(nodeptr n) const{
    return (n->left_child != nullptr);
}

//Returns true if the node has a right child
template <class T,class P>
bool heap<T,P>::has_right_child(nodeptr n) const{
    return (n->right_child != nullptr);
}

//Returns true if the node has a parent
template <class T,class P>
bool heap<T,P>::has_parent(nodeptr n) const{
    return (n->parent != nullptr);
}

//Returns the height of the tree.
template <class T,class P>
int heap<T,P>::get_height() const{
    int count = 0;
    int partial_count = 0;
    get_height(root,partial_count,count);
    return count;
}

//Caltulates the height of the input node subtree.
template <class T,class P>
void heap<T,P>::get_height(nodeptr p, int partial_count, int& count) const{
    if(p == nullptr) return;
    if(p->left_child != nullptr) get_height(p->left_child,partial_count+1,count);
    if(p->right_child != nullptr) get_height(p->right_child,partial_count+1,count);
    if(partial_count > count) count = partial_count;
}

//Prints recursively each node at a certain tree level.
template <class T, class P>
void heap<T,P>::print_level(ostream& output, nodeptr node, int level) const {
    if (node == nullptr) {
        return; // Base case: If the node is null, do nothing.
    }
    //If the node we consider is on the interested level, we print it.
    if (level == 0) {
        output << "[PT:";
        if(get_parent(node) == nullptr) output << "NULL]: ";
        else{
            output << read(get_parent(node)) << "|: ";
            if( node->parent->left_child == node ) output << "SX]: ";
            else output << "DX]: ";
        } 
        output << read(node) << " {PR: " << get_priority(node) << "}"; // Print the node's value at this level.
    } else {
        print_level(output, node->left_child, level - 1);
        print_level(output, node->right_child, level - 1);
    }
} 

// Main function to print the tree by levels
template <class T, class P>
ostream& operator << (ostream& output, heap<T,P>& t) {
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

//Operator =(Assigment by copy).} template <class T>
template <class T,class P>
heap<T,P>& heap<T,P>::operator =(const heap<T,P>& t){
    if(this == &t)return *this;
    clear(root);
    if(t.empty()) return *this;
    insert_root(new tree_node<T,P>(t.read(t.get_root())));
    copy_tree(*this, t, get_root(), t.get_root());
    return *this;
}

template <class T,class P>
void heap<T,P>::copy_tree(heap<T,P> &T1, const heap<T,P> &T2, nodeptr n1, nodeptr n2){
    if( T2.has_left_child(n2) ){
        nodeptr new_node = new tree_node<T,P>(T2.read(T2.get_left_child(n2)),T2.get_priority(T2.get_left_child(n2)));
        T1.insert_left_child(n1,new_node);
        T1.last_inserted = new_node;
        T1.insert_parent(new_node,n1);
        copy_tree(T1,T2,T1.get_left_child(n1),T2.get_left_child(n2));
    } 
    if( T2.has_right_child(n2) ){
        nodeptr new_node = new tree_node<T,P>(T2.read(T2.get_right_child(n2)),T2.get_priority(T2.get_right_child(n2)));
        T1.insert_right_child(n1,new_node);
        T1.last_inserted = new_node;
        T1.insert_parent(new_node,n1);
        copy_tree(T1,T2,T1.get_right_child(n1),T2.get_right_child(n2));
    } 
}


//Operator =(Move equal).
template <class T,class P>
void heap<T,P>::operator =(heap<T,P> && tree){
    clear(root);
    root = tree.root;
    last_inserted = tree.last_inserted;
    n_elements = tree.n_elements;
    tree.root = nullptr;
}

#endif //heap
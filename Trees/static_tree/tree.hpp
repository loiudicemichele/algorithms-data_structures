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
using namespace std;
template <class T> class tree;
template <class T>
class tree_node{
    friend class tree<T>;
    public:
        const int empty = -1;
        tree_node(): value(0), parent(empty), next_sibling(empty), prev_sibling(empty), first_child(empty), used(false) {}
        tree_node(T value_in): value(value_in), parent(empty), next_sibling(empty), prev_sibling(empty), first_child(empty), used(false){}
        ~tree_node(){ 
            used = false;
            first_child = next_sibling = prev_sibling = parent = empty;
        };
    private:
        T value;
        int parent;
        int next_sibling;
        int prev_sibling;
        int first_child;
        bool used;
};

template <class T>
class tree{
        const int default_n_elements = 10;
    public:
        typedef int position;
        /*** Default Constructor ***/
        tree();
        /*** Destructor ***/
        ~tree();
        /*** Copy Constructor ***/
        tree(const tree<T>&);
        /*** Move Constructor ***/
        tree(tree<T>&&);

        /*** Methods ***/
        int size() const; //Returns the number of nodes in the tree.
        bool empty() const; //Returns true if the tree is empty.
        position get_root() const; //Returns the root of the tree.
        position get_first_child(position) const; //Returns the first child of a node.
        position get_next_sibling(position) const; //Returns the next sibling of a node.
        position get_prev_sibling(position) const; //Returns the previous sibling of a node.
        position get_parent(position) const; //Returns the parent of a node.
        bool has_first_child(position) const; //Returns true if the node has a first child.
        bool has_next_sibling(position) const; //Returns true if the node has a next sibling.
        bool has_prev_sibling(position) const; //Returns true if the node has a previous sibling.
        bool has_parent(position) const; //Returns true if the node has a parent.
        bool leaf(position) const; //Returns true if the node is a leef (Has no first child).
        bool last_sibling(position) const; //Returns true if the node doens't have a next sibling.
        void erase(position); //Deletes a subtree from the tree.
        void insert_root(const T&);//Sets the root of the tree.
        void insert_first_child(position,const T&);//Sets the first child of a parent node.
        void insert_next_sibling(position,const T&);//Sets the next sibling of a node.
        void insert_prev_sibling(position,const T&);//Sets the previous sibling of a node.
        void insert_parent(position,position);//Sets the parent of a node.
        void write(position,const T&);//Sets the value of a node.
        T read(position) const; //Reads the value of a node.
        int get_height() const; //Returns the height of the tree.
        int get_level(position) const; //Returns the level of a tree node.
        
        // void delete_subtree(nodeptr); //Deletes a subtree of a node.
        void test_print(); // Use this function to debug node cursors
        void print_level(ostream& output, position node, int level) const; //Prints recursively each node at a certain tree level.
        /*** Operators ***/
        tree<T>& operator =(const tree<T>&); //Operator =(Assigment by copy).
        void operator =(tree<T> &&); //Operator =(Move equal).
        bool operator ==(tree<T>&); //Operator ==(Compares two trees.).
    private:
        /*** PRIVATE METHODS ***/
        void erase_subtree(position); //Sets to un-used the nodes ereased.
        void clear();
        void get_height(position, int, int &) const;
        position get_empty_position(); //Gets the first empty spot in the array.
        void copy_tree(tree<T>&,const tree<T>&); //It copies the second tree into the first tree.
        //Compares the tree nodes and structures recursively.
        bool compare_trees(const tree<T>&,const tree<T>&,position,position);
        void doubling(); //It doubles the length of the values array.
        /*** PRIVATE ATTRIBUTES ***/
        const int empty_v = -1;
        position root;
        tree_node<T> *values;
        int total_elements;
        int n_elements;
};

/*** Default Constructor ***/
template <class T>
tree<T>::tree(){
    values = new tree_node<T>[default_n_elements];
    total_elements = default_n_elements;
    root = empty_v;
    n_elements = 0;
}

/*** Destructor ***/
template <class T>
tree<T>::~tree(){
    clear();
}

template <class T>
void tree<T>::clear(){
    delete[] values;
    n_elements = 0;
    total_elements = 0;
}

/*** Copy Constructor ***/
template <class T>
tree<T>::tree(const tree<T>& t){
    copy_tree(*this,t);
}

//It copies the second tree into the first tree.
template <class T>
void tree<T>::copy_tree(tree<T>& T1,const tree<T>& T2){
    T1.total_elements = T2.total_elements;
    T1.n_elements = T2.n_elements;
    T1.values = new tree_node<T>[T2.total_elements];
    T1.root = 0;
    for(int i = 0; i < T1.total_elements; i++ ){
        T1.values[i].used = T2.values[i].used;
        T1.values[i].value = T2.values[i].value;
        T1.values[i].first_child = T2.values[i].first_child;
        T1.values[i].next_sibling = T2.values[i].next_sibling;
        T1.values[i].parent = T2.values[i].parent;
        T1.values[i].prev_sibling = T2.values[i].prev_sibling;
    }
}

/*** Move Constructor ***/
template <class T>
tree<T>::tree(tree<T>&& t){
    values = t.values;
    n_elements = t.n_elements;
    total_elements = t.total_elements;
    root = 0;
    t.values = nullptr;
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
    return (root == empty_v);
} 

//Returns the root of the tree.
template <class T>
typename tree<T>::position tree<T>::get_root() const{
    return 0; //The root is always placed on values[0].
} 

//Returns the first child of a node.
template <class T>
typename tree<T>::position tree<T>::get_first_child(position p) const{
    return values[p].first_child;
} 

//Returns the next sibling of a node.
template <class T>
typename tree<T>::position tree<T>::get_next_sibling(position p) const{
    return values[p].next_sibling;
} 

//Returns the previous sibling of a node.
template <class T>
typename tree<T>::position tree<T>::get_prev_sibling(position p) const{
    return values[p].prev_sibling;
} 

//Returns the parent of a node.
template <class T>
typename tree<T>::position tree<T>::get_parent(position p) const{
    return values[p].parent;
} 

//Returns true if the node has a first child.
template <class T>
bool tree<T>::has_first_child(position p) const{
    return (values[p].first_child != empty_v);
} 

//Returns true if the node has a next sibling.
template <class T>
bool tree<T>::has_next_sibling(position p) const{
    return (values[p].next_sibling != empty_v);
} 

//Returns true if the node has a previous sibling.
template <class T>
bool tree<T>::has_prev_sibling(position p) const{
    return (values[p].prev_sibling != empty_v);
} 

//Returns true if the node has a parent.
template <class T>
bool tree<T>::has_parent(position p) const{
    return (values[p].parent != empty_v);
} 

//Returns true if the node is a leef (Has no first child).
template <class T>
bool tree<T>::leaf(position p) const{
    return (values[p].first_child == empty_v);
} 

//Returns true if the node doens't have a next sibling.
template <class T>
bool tree<T>::last_sibling(position p) const{
    return (values[p].next_sibling == empty_v);
}

//Deletes a subtree from the tree.
template <class T>
void tree<T>::erase(position node){
    if(node == empty_v) return;
    if(node == root){
        values[root].used = 0;
        root = empty_v;
    } else if(has_prev_sibling(node)){
        //Cheching if the node is a first child or a sibling and unlinking the subtree.
        position sibling = get_prev_sibling(node);
        if(has_next_sibling(node)){
            position next_sibling = get_next_sibling(node);
            values[sibling].next_sibling = next_sibling;
            values[next_sibling].prev_sibling = sibling;
            values[node].next_sibling = empty_v;  
        } else values[sibling].next_sibling = empty_v;
    } else{
        position parent = get_parent(node);
        values[parent].first_child = empty_v;
    }
    erase_subtree(node);
}

//Sets to un-used the nodes ereased.
template <class T>
void tree<T>::erase_subtree(position node){
    if(has_next_sibling(node)) erase_subtree(get_next_sibling(node));
    if(has_first_child(node)) erase_subtree(get_first_child(node));
    values[node].used = false;
    values[node].first_child = values[node].next_sibling = values[node].prev_sibling = values[node].parent = empty_v;
}



//Sets the root of the tree.
template <class T>
void tree<T>::insert_root(const T& value){
    root = 0;        
    values[root].value = value;
    values[root].used = true;
    n_elements = 1;
}

//Gets the first empty spot in the array.
template <class T>
typename tree<T>::position tree<T>::get_empty_position(){
    position p = 1;
    if(n_elements+1 >= total_elements) doubling();
    while(values[p].used == true) p++;
    n_elements++;
    values[p].used = true;
    return p;
}

//It doubles the length of the values array.
template <class T>
void tree<T>::doubling(){
    tree_node<T> *new_values = new tree_node<T>[2*total_elements];
    for(int i = 0; i < total_elements; i++ ){
        new_values[i].used = values[i].used;
        new_values[i].value = values[i].value;
        new_values[i].first_child = values[i].first_child;
        new_values[i].next_sibling = values[i].next_sibling;
        new_values[i].parent = values[i].parent;
        new_values[i].prev_sibling = values[i].prev_sibling;
    }
    total_elements*=2;
    delete[] values;
    values = new_values;
}

//Sets the first child of a parent node.
template <class T>
void tree<T>::insert_first_child(position parent, const T& value){
    if(has_first_child(parent)) erase(get_first_child(parent));
    position new_node = get_empty_position();
    values[new_node].value = value;
    values[new_node].parent = parent;
    values[parent].first_child = new_node;
}

//Sets the next sibling of a node.
template <class T>
void tree<T>::insert_next_sibling(position prev_sibling, const T& value){
    if(has_next_sibling(prev_sibling)) erase(get_next_sibling(prev_sibling));
    position new_node = get_empty_position();
    values[new_node].value = value;
    values[new_node].next_sibling = values[prev_sibling].next_sibling;
    values[new_node].parent = values[prev_sibling].parent;
    values[new_node].prev_sibling = prev_sibling;
    values[prev_sibling].next_sibling = new_node;
}

//Sets the previous sibling of a node.
template <class T>
void tree<T>::insert_prev_sibling(position sibling, const T& value){
    if(has_prev_sibling(sibling)) erase(get_prev_sibling(sibling));
    position new_node = get_empty_position();
    values[new_node] = value;
    values[new_node].parent = values[sibling].parent;
    //values[new_node].prev_sibling = values[sibling].prev_sibling;
    //values[values[sibling].prev_sibling].next_sibling = new_node;
    values[sibling].prev_sibling = new_node;
    values[new_node].next_sibling = sibling;
}

//Sets the parent of a node.
template <class T>
void tree<T>::insert_parent(position parent,position child){
    if(has_parent(child)) return;
    values[child].parent = parent;
}

//Sets the value of a node.
template <class T>
void tree<T>::write(position node,const T& value){
    values[node].value = value;
}

//Reads the value of a node.
template <class T>
T tree<T>::read(position p) const{
    return values[p].value;
}


//Returns the height of the tree.
template <class T>
int tree<T>::get_height() const{
    int height = 0;
    get_height(root,0,height);
    return height;
} 

template <class T>
void tree<T>::get_height(position node, int partial_count, int &height) const{
    if(has_first_child(node)) get_height(get_first_child(node), partial_count+1, height);
    if(has_next_sibling(node)) get_height(get_next_sibling(node), partial_count, height);
    if( partial_count > height ) height = partial_count;
}

//Returns the level of a tree node.
template <class T>
int tree<T>::get_level(position node) const{
    if(node == empty_v) return -1;
    if(node == root) return 0;
    int count = 1;
    while(values[node].parent != root){
        node = values[node].parent;
        count++;
    } 
    return count;
} 
// Use this function to debug node cursors
template <class T>
void tree<T>::test_print(){
    for(int i = 0; i < n_elements; i++ ){
        cout << " VALUE:" <<"{"<< i <<"}"<< "[" << values[i].value << "]";
        cout << " PT: [" << values[i].parent << "]";
        cout << " FC: [" << values[i].first_child << "]";
        cout << " NS: [" << values[i].next_sibling << "]";
        cout << " USED: (" << values[i].used << ")";
        cout << endl;
    }
}

/*** Operators ***/
template <class T>
ostream& operator <<(ostream& output, const tree<T>& t){
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

//Prints recursively each node at a certain tree level.
template <class T>
void tree<T>::print_level(ostream& output, position node, int level) const {
    if (node == empty_v){
        return; // Base case: If the node is null, do nothing.
    }
    //If the node we consider is on the interested level, we print it.
    if (level == 0) {
        output << "[PT:";
        if(get_parent(node) == empty_v) output << "NULL]: ";
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

//Operator =(Assigment by copy).
template <class T>
tree<T>& tree<T>::operator =(const tree<T>&t){
    clear();
    copy_tree(*this,t);
    return *this;
} 

//Operator =(Move equal).
template <class T>
void tree<T>::operator =(tree<T> && t){
    clear();
    root = t.root;
    n_elements = t.n_elements;
    total_elements = t.total_elements;
    values = t.values;
    t.values = nullptr;
} 

//Operator ==(Compares two trees.).
template <class T>
bool tree<T>::operator ==(tree<T>&t){
    if(empty() && t.empty()) return true;
    if(t.size() != size()) return false;
    return compare_trees(*this,t,get_root(),t.get_root());
} 

//Compares the tree nodes and structures recursively.
template <class T>
bool tree<T>::compare_trees(const tree<T>& T1,const tree<T>& T2,position n1,position n2){
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

#endif //TREE
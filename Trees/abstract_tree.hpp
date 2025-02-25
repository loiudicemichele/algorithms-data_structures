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

#ifndef ABSTRACT_TREE
#define ABSTRACT_TREE
#include <iostream>
using namespace std;
template <class T, class P>
class abstract_tree{
    public:
        typedef P position; //Position of the tree elements.
        typedef T type_element; //Type of elements of the tree
        /*** Methods ***/
        virtual int size() const = 0; //Returns the number of nodes in the tree.
        virtual bool empty() const = 0; //Returns true if the tree is empty.
        virtual position get_root() const = 0; //Returns the root of the tree.
        virtual position get_first_child(position) const = 0; //Returns the first child of a node.
        virtual position get_next_sibling(position) const = 0; //Returns the next sibling of a node.
        virtual position get_prev_sibling(position) const = 0; //Returns the previous sibling of a node.
        virtual position get_parent(position) const = 0; //Returns the parent of a node.
        virtual bool has_first_child(position) const = 0; //Returns true if the node has a first child.
        virtual bool has_next_sibling(position) const = 0; //Returns true if the node has a next sibling.
        virtual bool has_prev_sibling(position) const = 0; //Returns true if the node has a previous sibling.
        virtual bool has_parent(position) const = 0; //Returns true if the node has a parent.
        virtual bool leaf(position) const = 0; //Returns true if the node is a leef (Has no first child).
        virtual bool last_sibling(position) const = 0; //Returns true if the node doens't have a next sibling.
        virtual void erase(position) = 0; //Deletes a subtree from the tree.
        virtual void insert_root(position) = 0;//Sets the root of the tree.
        virtual void insert_first_child(position,position) = 0;//Sets the first child of a parent node.
        virtual void insert_next_sibling(position,position) = 0;//Sets the next sibling of a node.
        virtual void insert_prev_sibling(position,position) = 0;//Sets the previous sibling of a node.
        virtual void insert_parent(position,position) = 0;//Sets the parent of a node.
        virtual void write(const T&, position) = 0;//Sets the value of a node.
        virtual type_element read(position) const = 0; //Reads the value of a node.
        virtual int get_height() const = 0; //Returns the height of the tree.
        virtual int get_level(position) const = 0; //Returns the level of a tree node.
        virtual void delete_subtree(position) = 0; //Deletes a subtree of a node.
};

#endif //ABSTRACT_TREE
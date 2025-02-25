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

#ifndef ABSTRACT_BIN_TREE
#define ABSTRACT_BIN_TREE
#include <iostream>
using namespace std;
template <class T, class P>
class abstract_bin_tree{
    public:
        typedef P position; //Position of the tree elements.
        typedef T type_element; //Type of elements of the tree
        /*** Methods ***/
        virtual int size() const = 0; //Returns the number of nodes in the tree.
        virtual bool empty() const = 0; //Returns true if the tree is empty.
        virtual position get_root() const = 0; //Returns the root of the tree.
        virtual position get_left_child(position) const = 0; //Returns the left child of a node.
        virtual position get_right_child(position) const = 0; //Returns the right child of a node.
        virtual position get_parent(position) const = 0; //Returns the parent of a node.
        virtual void erase(position) = 0; //Deletes a subtree from the list.
        virtual void insert_root(position) = 0;//Sets the root of the tree.
        virtual void insert_left_child(position,position) = 0;//Sets the left child of a parent node.
        virtual void insert_right_child(position,position) = 0;//Sets the right child of a parent node.
        virtual void write(const T&, position) = 0;//Sets the value of a node.
        virtual type_element read(position) const = 0; //Reads the value of a node.
        virtual int get_height() const = 0; //Returns the height of the tree.
        virtual int get_level(position) const = 0; //Returns the level of a tree node.
        virtual bool has_left_child(position) const = 0; //Returns true if the node has a left child
        virtual bool has_right_child(position) const = 0; //Returns true if the node has a right child
        virtual bool has_parent(position) const = 0; //Returns true if the node has a parent
};

#endif //ABSTRACT_BIN_TREE
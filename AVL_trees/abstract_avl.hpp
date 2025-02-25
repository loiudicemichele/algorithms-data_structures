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

 #ifndef ABSTRACT_AVL_TREE
 #define ABSTRACT_AVL_TREE
 #include <iostream>
 using namespace std;
 template <class T, class P>
 class abstract_avl_tree{
     public:
        typedef P position; //Position of the tree elements.
        typedef T type_element; //Type of elements of the tree
        /*** Methods ***/
        virtual void insert(position) = 0; // Inserts a new node into the tree = 0
        virtual void delete_node(position) = 0; //Deleates a node from the tree.
        virtual bool contains(const T&) const = 0; //Searches if a value is contained.
        virtual position minimum() const = 0; //Returns the minimum value in the tree.
        virtual position maximum() const = 0; //Returns the maximum value of the tree.
        virtual position predecessor(position) const = 0; //Returns the predecessor of the node. (The previous node in the order).
        virtual position successor(position) const = 0; //Returns the successor of the node. (The next node in the order).
 };
 
 #endif //ABSTRACT_AVL_TREE
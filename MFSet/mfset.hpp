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

#ifndef MFSET
#define MFSET

#include <iostream>
#include <set>
#include <unordered_map>
using namespace std;

template <class T> class mfset;
template <class T>
class mfset_node {
    friend class mfset<T>;
    public:
        typedef mfset_node<T>* nodeptr;
        mfset_node(const T& value_in) : value(value_in), rank(0), parent(this) {}
        // Find with path compression
        nodeptr find() {
            if (parent != this) {
                parent = parent->find();
            }
            return parent;
        }
        T getValue() const { return value; }

    private:
        T value;
        int rank;
        nodeptr parent;

};

template <class T>
class mfset {
public:
    
    void create(const set<T>&); // Create an MFSET from a set of elements
    ~mfset(); // Destructor to free memory
    T find(const T& x); // Find the representative of the set containing x
    void merge(const T& x, const T& y); // Merge operation: merge sets containing x and y
private:
    unordered_map<T, mfset_node<T>*> nodes;
};


template <class T>
void mfset<T>::create(const set<T>& elements) {
    for (const auto& elem : elements) {
        nodes[elem] = new mfset_node<T>(elem);
    }
}

template <class T>
mfset<T>::~mfset() {
    for (auto& pair : nodes) {
        delete pair.second;
    }
}

template <class T>
T mfset<T>::find(const T& x) {
    if (nodes.find(x) == nodes.end()) {
        throw runtime_error("Element not found in MFSET.");
    }
    return nodes[x]->find()->getValue();
}

// Merge operation: merge sets containing x and y
template <class T>
void mfset<T>::merge(const T& x, const T& y) {
    if (nodes.find(x) == nodes.end() || nodes.find(y) == nodes.end()) {
        throw std::runtime_error("One or both elements not found in MFSET.");
    }
    auto rootX = nodes[x]->find();
    auto rootY = nodes[y]->find();
    if (rootX != rootY) {
        // Union by rank
        if (rootX->rank > rootY->rank) {
            rootY->parent = rootX;
        } else if (rootX->rank < rootY->rank) {
            rootX->parent = rootY;
        } else {
            rootY->parent = rootX;
            rootX->rank++;
        }
    }
}

#endif // MFSET
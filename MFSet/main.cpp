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

#include <iostream>
using namespace std;
#include "./mfset.hpp"

// Example usage
int main() {
    mfset<int> ds;
    set<int> elements;
    elements.insert(1);
    elements.insert(2);
    elements.insert(3);
    elements.insert(4);
    elements.insert(5);
    ds.create(elements);

    ds.merge(1, 2);
    ds.merge(3, 4);
    ds.merge(2, 3);

    cout << "Find(1) = " << ds.find(1) << endl;
    cout << "Find(2) = " << ds.find(2) << endl;
    cout << "Find(3) = " << ds.find(3) << endl;
    cout << "Find(4) = " << ds.find(4) << endl;
    cout << "Find(5) = " << ds.find(5) << endl;

    return 0;
}
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
#include <vector>
#include "./quicksort.hpp"
#include "./merge_sort.hpp"

using namespace std;
 
int main() {
    vector<int> values = {3, 1, 9, 2, 7, 5, 8, 4, 6};
    //quicksort(values);
    merge_sort(values);
    for(int i = 0; i < values.size(); i++) cout << " " << values[i];
    /**
     *  {3, 1, 9, 2, 7, 5, 8, 4, 6}
     *         2  9               p
     *         i  7  9
     *            i  5  9 
     *               i  4  8  9 
     * 
     */
}
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

#ifndef QUICKSORT
#define QUICKSORT

#include <iostream>
#include <vector>
using namespace std;

void swap(vector<int> &v, int i, int j){
    int tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

int partition(vector<int> &v, int start, int end){
    int pivot = end;
    int i = start-1;
    for(int j = start; j < end; j++){
        if(v[j] < v[pivot]){
            i++;
            swap(v,j,i);
        }
    }
    swap(v,i+1,end);
    return i+1;
}

void quicksort(vector<int> &v, int start, int end){
    if( end <= start ) return;
    int pivot_position = partition(v,start,end);
    quicksort(v,start, pivot_position-1);
    quicksort(v,pivot_position+1,end);
}


void quicksort(vector<int> &v){
    if(v.size() == 0 || v.size() == 1 ) return;
    quicksort(v,0,v.size()-1);
}

#endif
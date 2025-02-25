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

#ifndef MERGE_SORT
#define MERGE_SORT
 
#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int> &v, int start, int mid, int end){

    vector<int> left(mid-start+1),right(end-mid);
    for (int i = 0; i < left.size(); i++) left[i] = v[start + i];
    for (int j = 0; j < right.size(); j++) right[j] = v[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = start;

    while (i < (mid-start+1) && j < (end-mid)) {
        if (left[i] <= right[j]) {
            v[k] = left[i];
            i++;
        } else {
            v[k] = right[j];
            j++;
        }
        k++;
    }   
    while (i < (mid-start+1)) {
        v[k] = left[i];
        i++;
        k++;
    } 
    while (j < (end-mid)) {
        v[k] = right[j];
        j++;
        k++;
    }
}

void merge_sort(vector<int> &v, int start, int end){
    if(end <= start) return;
    int mid = (start+end)/2;
    merge_sort(v,start,mid);
    merge_sort(v,mid+1,end);
    merge(v,start,mid,end);
}


void merge_sort(vector<int> &v){
    if(v.size() == 0 || v.size() == 1) return;
    merge_sort(v,0,v.size()-1);
}

#endif
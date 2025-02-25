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

#ifndef MIN_MAX
#define MIN_MAX

#include <iostream>
#include <vector>
using namespace std;




void min_max(vector<int> &values, int &min, int &max, int start, int end){
    if(start == end){
        min = values[start];
        max = values[start];
        return;
    } 
    if(start + 1 == end){
        if(values[start] > values[end]){
           min = values[end];
           max = values[start]; 
        } else{
            min = values[start];
            max = values[end];     
        }
        return;
    }
    
    //Divide
    int mid = (start+end)/2;
    int local_min_1 = INT_MAX;
    int local_min_2 = INT_MAX;
    int local_max_1 = INT_MIN;
    int local_max_2 = INT_MIN;

    min_max(values,local_min_1,local_max_1,start,mid);
    min_max(values,local_min_2,local_max_2,mid+1,end);

    //Impera
    min = (local_min_1 < local_min_2) ? local_min_1 : local_min_2;
    max = (local_max_1 > local_max_2) ? local_max_1 : local_max_2;
}

void min_max_calculator(vector<int> &values, int &min, int &max){
    if(values.size() == 0) return;
    min_max(values,min,max,0,values.size()-1);
}

#endif
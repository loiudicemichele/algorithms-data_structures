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

#ifndef PARTITION
#define PARTITION

#include <iostream>
#include <vector>
using namespace std;

void represent_solution(vector<int> &set, vector<int> &partition){
    for(int i = 0; i < set.size(); i++){
        cout << "Value: [" << set[i] << "] | [" << partition[i] << "] :Taken" << endl;
    }
}

int valid_solution(vector<int> &set, vector<int> &partition){
    int first_set_sum = 0, second_set_sum = 0;
    for(int i = 0; i < partition.size(); i++){
        if(partition[i] == 1) first_set_sum+=set[i];
        else second_set_sum+=set[i];
    }
    if (first_set_sum == second_set_sum) return 1; // The solution is the one searched.
    else if (first_set_sum < second_set_sum) return 0; // The partial solution is valid still.
    else return -1; // The partial solution cannot lead us to the solution.
}

bool partition(vector<int> &set, vector<int> &_partition, int i){
    if(valid_solution(set,_partition) == -1) return false;
    else if(valid_solution(set,_partition) == 1) return true;
    else{
        if(i >= set.size()) return false; // The istance has no solution
        _partition[i] = 1;
        if(partition(set,_partition,i+1)) return true;
        else{
            _partition[i] = 0;
            return partition(set,_partition,i+1);
        }
    }
}

bool partition(vector<int> &set, vector<int> &_partition){
    if(set.size() == 0) _partition;
    return partition(set,_partition,0);
}

#endif // Partition
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

#ifndef QUEEN
#define QUEEN

#include <iostream>
#include <vector>
using namespace std;

void represent_solution(vector<int> solution){
    for(int i = 0; i < solution.size(); i++ ){
        for(int j = 0; j < solution.size(); j++ ){
            if(j == solution[i]) cout << " " << solution[i] << " ";
            else cout << " x ";    
        }
        cout << endl;
    }
}

bool verify(vector<int> queens, int n){
    for( int i = 0; i < n; i++ ){
       // cout << queens[n] << "|" << queens[i] << " * " << abs(queens[n]-queens[i]) << " | " << abs(n-i) << endl;
        if( queens[n] == queens[i] || abs(queens[n]-queens[i]) == abs(n-i) ) return false;
    }
    return true;
}

//N is the numbers of queen to display
vector<int> n_queens(int n){
    //Solving the problem using backtracking algorithm.
    //We initially suppose we haven't found a solution
    vector<int> v(n);
    
    int k = 0;
    bool solution = false;
    v[0] = -1; 
    while(!solution){
        bool found = false;
        while(!found && v[k] < n-1){
            v[k]++;
            found = verify(v, k);
        }
        if(!found){
            v[k] = -1;
            k--;
        }
        else{
            if( k == n-1 ) solution = true;
            k++;
            v[k] = -1;
        }
    }
    return v;
}


#endif

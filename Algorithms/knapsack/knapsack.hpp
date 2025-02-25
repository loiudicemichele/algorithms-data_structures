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

#ifndef KNAPSACK
#define KNAPSACK

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class item{
    public:
        int cost;
        int profit;
        int index;
        item(int profit_in, int cost_in, int index_in): profit(profit_in), cost(cost_in), index(index_in){}
};

// Greedy solution to knapsack
vector<int> knapsack(vector<item> items, int budget){
    sort(items.begin(),items.end(), [](const item &i1, const item &i2){
        return ( ( i1.profit/i1.cost ) >= (i2.profit/i2.cost) );
    });
    vector<int> solution(items.size());
    for(int i = 0; i < solution.size(); i++ ) solution[i] = 0;
    int j = 0;
    while(budget > 0 && j < items.size()){
        if( budget - items[j].cost > 0 ){
            solution[items[j].index]++;
            budget -= items[j].cost;
        } 
        j++;
    }
    return solution;
}

// Backtrack solution to knapsack
bool better_solution(vector<item> items,vector<int> partial_solution, vector<int> optimal_solution){
    int value_partial = 0;
    int value_optimal = 0;
    for(int i = 0; i < items.size(); i++){
        if(partial_solution[i] == 1) value_partial += items[i].value;
        if(optimal_solution[i] == 1) value_optimal += items[i].value;
    }
    return (value_optimal < value_partial);
}

bool valid_solution(vector<item> items,int budget, vector<int> partial_solution){
    int cost = 0;
    for(int i = 0; i < items.size(); i++){
        if(partial_solution[i] == 1) cost += items[i].weight;
    }
    return(cost <= budget);
}

void backtrack_knapsack(vector<item> &items, int budget, vector<int> &partial_solution,vector<int> &optimal_solution, int index){
    if(index < items.size()){
        partial_solution[index] = 1;
        if(valid_solution(items,budget,partial_solution)){
            if(better_solution(items,partial_solution,optimal_solution)){
                optimal_solution = partial_solution;
            }
        }
        else partial_solution[index] = 0;
        backtrack_knapsack(items,budget,partial_solution,optimal_solution,index+1);
    } else return;
}

vector<int> backtrack_knapsack(vector<item> &items, int budget){
    vector<int> partial_solution(items.size());
    vector<int> optimal_solution(items.size());
    backtrack_knapsack(items,budget,partial_solution, optimal_solution,0);
    return optimal_solution;
}



#endif // KNAPSACK
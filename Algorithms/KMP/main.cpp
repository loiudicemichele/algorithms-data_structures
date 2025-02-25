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
#include "kmp.hpp"

void run_kmp(){
    /*
    vector<int> k = calculate_lms("abaabcabaabafaba");
    for(int i = 0; i < k.size(); i++){
        cout << "I: "<<  i << " VAL: " << k[i];
    }*/
    string s = "aaabaaabababbabaaabbbaaa";
    string sub = "babab";
    cout << kmp(s,sub);
}

int main(){
    run_kmp();
}
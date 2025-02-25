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

#ifndef ALGORIGHTM
#define ALGORITHM

#include <iostream>
using namespace std;
#include <vector>
// Calculates the Longest Proper Prefix
/*
 * A proper prefix is prefix that is both prefix and suffix of a word. 
 */
vector<int> calculate_lps(string s){
    vector<int> lms(s.length());
    lms[0] = 0;
    int j = 0;
    int i = 1;
    while ( i < s.length() ){
        if(s[i] == s[j]) { j++; lms[i] = j; i++; }
        else if(j > 0) {j = lms[j-1];}
        else { lms[j] = 0; i++; }
    }
    return lms;
}

// sub is the string im verifying  
int kmp(string s, string sub){
    vector<int> lms = calculate_lps(sub);
    int n = s.length();
    int m = sub.length();
    int i = 0, j = 0;
    while( i < n && j < m ){
        if(s[i] == sub[j] ){ i++; j++; }
        else if ( j > 0 ) j = lms[j-1];
        else { i++; }
    }
    if(j < m) return -1;
    else return i-j;
}

#endif // Algorithm

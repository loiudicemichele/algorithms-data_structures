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

#ifndef FUNCTIONS
#define FUNCTIONS
#include <iostream>
#include "../doubly_linked_list/list.hpp"
using namespace std;

//Retuns the frequencies of a multiple element of the list.
int frequency_of_multiple(linked_list<int>&list, int k){
    linked_list<int>::nodeptr iterator = list.begin();
    int count = 0;
    while(!list.end(iterator)){
        if( (list.read(iterator)%k) == 0 ) count++;
        iterator = list.next(iterator);
    }
    return count;
}

//Retuns the frequencies of an element of the list.
int frequency(linked_list<int>&list, int k){
    linked_list<int>::nodeptr iterator = list.begin();
    int count = 0;
    while(!list.end(iterator)){
        if( list.read(iterator) == k ) count++;
        iterator = list.next(iterator);
    }
    return count;
}


//Prints all the frequencies for each element of the list.
void hist(linked_list<int>&list){
    linked_list<int>::nodeptr iterator = list.begin();
    while(!list.end(iterator)){
        cout << "[" << list.get_value(iterator) << "]: " 
        << "[" << frequency(list, list.get_value(iterator)) << "]" << endl; 
        iterator = list.next(iterator);
    }
}

//Removes all the elements of the list followed by an odd number.
void remp(linked_list<int> &list){
    linked_list<int>::nodeptr iterator = list.begin();
    if(list.end(iterator)) return; //Ther's one node only.
    while( !list.end( list.next(iterator) )){
        linked_list<int>::nodeptr to_delete = iterator;
        iterator = list.next(iterator);
        if( (list.get_value(iterator) % 2) != 0 ) list.erase(to_delete);
    }
}

//Deletes all the elements which value is a multiple of the position they are in.
void delete_multiples_of_position(linked_list<int> &list){
    int k = list.size();
    typename linked_list<int>::nodeptr iterator = list.last();
    while(!list.end(iterator)){
        typename linked_list<int>::nodeptr comparison = iterator;
        iterator = list.previous(iterator);
        if( (list.get_value(comparison) % k) == 0 ) list.erase(comparison);
        k--;
    }
}

//Returns true if the elements of the list are palindrome
bool is_palindrome(const linked_list<int> &list){
    if(list.empty() || list.size() == 1) return true;
    typename linked_list<int>::nodeptr iterator_begin = list.begin();
    typename linked_list<int>::nodeptr iterator_end = list.last();
    while(iterator_begin != iterator_end && list.next(iterator_end) != iterator_end){
        if( list.get_value(iterator_begin) != list.get_value(iterator_end) ) return false;
        iterator_begin = list.next(iterator_begin);
        iterator_end = list.previous(iterator_end);
    }
    return true;
}

#endif //FUNCTIONS
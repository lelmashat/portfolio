#ifndef RECCHECK
#include <iostream>
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Helper function to generate all possible combinations of words
void generateCombinations(const string& in, const string& floating, set<string>& combinations, string current, int index, const set<string>& dict) {
    // base case for if we have filled the word
    if (index == current.length()) {
        if(dict.find(current) != dict.end() && floating.length() == 0){ // is the word valid?
          combinations.insert(current);
        }
        return;
    }
    
    if (current[index] != '-') {
        // If the character at the current index is not a placeholder '-'
        // Add the current character to the current string and move to the next index
        generateCombinations(in, floating, combinations, current, index + 1, dict);
        return;
    }
    // count the number of blanks in the current word
    int blankCount = 0;
    for(int k = index; k < current.length(); k++){
      blankCount += (int)(current[k] == '-');
    }
    // if floating is smaller than the number of blanks
    if(floating.length() < blankCount){
      for(char c = 'a'; c <= 'z'; ++c){ // looping through to try each letter in word
        current[index] = c;
        generateCombinations(in, floating, combinations, current, index+1, dict);
      }
    }
    // fill in the word with a floating character
    for(int j = 0; j < floating.length(); j++){
      string newFloating = floating.substr(0,j) + floating.substr(j+1);
      current[index] = floating[j];
      generateCombinations(in, newFloating, combinations, current, index+1, dict);
    }
}

// Primary wordle function
set<string> wordle(const string& in, const string& floating, const set<string>& dict) {
    // Initialize a set to store all possible combinations of words
    set<string> combinations;
    string currWord = in;
    string currFloating = floating;
    generateCombinations(in, currFloating, combinations, currWord,0,dict);
    return combinations;
}

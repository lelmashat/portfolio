#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Convert a string containing a rawWord
    to a set of words **/
std::set<std::string> parseStringToWords(string rawWords)
{   // create return set
    std::set<std::string> words;
    // create an iss stream and a string to help parse words
    std::istringstream iss(rawWords);
    std::string word;

    while (iss >> word) {
        // Remove punctuation from the word
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());

        // Check if the modified word is at least 2 characters long
        if (word.size() >= 2) {
            words.insert(word); // insert into return set
        }
    }

    return words;



}


// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

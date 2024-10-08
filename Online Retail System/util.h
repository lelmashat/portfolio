#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>



template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
  // create return set
  std::set<T> result;
  // Perform set intersection using std::set_intersection, where the result is inserted into the 'result'
  std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(result, result.begin()));
  return result;

}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
  // create a return set
  std::set<T> result;
  // Perform set intersection using std::set_intersection, where the result is inserted into the 'result'.
  std::set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(result, result.begin()));
  return result;

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif

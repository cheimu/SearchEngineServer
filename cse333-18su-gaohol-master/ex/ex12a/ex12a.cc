/*
 * Copyright ©2018 Gaohong Liu.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C++ program reads and counts the individual words in the file.
 * After reading the entire file, it should print a sorted list of the words
 * and the number of times each word appears in the file.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <cstdlib>

using namespace std;
// declaration of print function
void print(const pair<string, int>& mapPair);
int main(int argc, char** argv) {
  // check if number of input is 2
  if (argc != 2) {
    cerr << "ERROR: Invalid Input" << endl;
    return EXIT_FAILURE;  // return failure
  }
  string filename = argv[1];
  string word;
  map<string, int> wordMap;
  // open the file
  ifstream fd(filename);
  // check if open successfully
  if (fd.is_open()) {
    // read by words
    while (fd >> word) {
      // check current word is inside of map
      if (wordMap.count(word) > 0) {
        wordMap[word]++;
      } else {
        // if not, insert it into map
        wordMap.insert(pair<string, int>(word, 1));
      }
    }
  } else {
    cerr << "ERROR: Unable to open file" << endl;
    return EXIT_FAILURE;  // return failure
  }
  for_each(wordMap.begin(), wordMap.end(), print);  // print each element out
  // close the file
  fd.close();
  return EXIT_SUCCESS;  // return success
}

// print the word and the number of occurrence of the corresponding word
void print(const pair<string, int>& mapPair) {
  cout << mapPair.first << " " << mapPair.second << endl;
}

/**
 * C++ File Autocomplete
 * Authors: Alan Chen
 *	    Arman Ghazi
 */
 
#include "util.hpp"
#include "DictionaryBST.hpp"

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST() { std::set<string> bst; }

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word) {
  if (word == "") {
    return false;
  } else {
    if (!bst.insert(word).second) return false;
    return true;
  }
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const {
  std::set<std::string>::iterator found = bst.find(word);
  return found == bst.end() ? false : true;
}

/* Destructor */
DictionaryBST::~DictionaryBST() { bst.clear(); }

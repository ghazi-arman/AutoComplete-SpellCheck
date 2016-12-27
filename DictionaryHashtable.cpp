/**
 * C++ File Autocomplete
 * Authors: Alan Chen
 *	    Arman Ghazi
 */
 
#include "util.hpp"
#include "DictionaryHashtable.hpp"

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable() {
  std::unordered_set<std::string> hashed;
}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word) {
  if (word == "") {
    return false;
  } else {
    if (!hashed.insert(word).second) return false;
    return true;
  }
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const {
  std::unordered_set<std::string>::const_iterator found = hashed.find(word);
  return found == hashed.end() ? false : true;
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable() {
  hashed.clear();
  // delete hashed;
}

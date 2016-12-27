/**
 * C++ File Autocomplete
 * Authors: Alan Chen
 *	    Arman Ghazi
 */

#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP
#define ALPHABET_SIZE 27
#include <vector>
#include <string>
#include <queue>

using namespace std;

/**
 * A class for making a TrieNode, which will be able to append the word,
 * find the word, and set contents.
 *
 */
class TrieNode {
 public:
  // unordered_map<char, TrieNode*> children;
  vector<TrieNode*> children = vector<TrieNode*>(ALPHABET_SIZE, (TrieNode*)0);
  bool isWord;
  string text;
  unsigned int freq;
  // public:
  TrieNode(string t) {
    isWord = false;
    freq = 0;
    text = t;
  }
  // Destructor for the TrieNode
  ~TrieNode();

};

class TrieNodePtrComp {
 public:
  bool operator()(TrieNode* lhs, TrieNode* rhs) const {
    return lhs->freq < rhs->freq;
  }
};

/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie {
 public:
  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  void deleteAll(TrieNode* t);

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Return up to num_completions of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the num_completions most frequent completions
   * of the prefix)
   */
  std::vector<std::string> predictCompletions(std::string prefix,
                                              unsigned int num_completions);

  void loadQueue(
      std::priority_queue<TrieNode*, vector<TrieNode*>, TrieNodePtrComp>& pq,
      TrieNode* curr);

  /* Destructor */
  ~DictionaryTrie();

  TrieNode* search(std::string word);

 private:
  // Add your own data members and methods here
  TrieNode* root;
};

#endif  // DICTIONARY_TRIE_HPP

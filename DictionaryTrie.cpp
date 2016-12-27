/**
 * C++ File Autocomplete
 * Authors: Alan Chen
 *	    Arman Ghazi
 */
 
#include "util.hpp"
#include <stack>
#include "DictionaryTrie.hpp"
#include <deque>
#include <queue>

TrieNode::~TrieNode() {}

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie() { root = new TrieNode(""); }

DictionaryTrie::~DictionaryTrie() { deleteAll(root); }

void DictionaryTrie::deleteAll(TrieNode* t) {
  if (t == NULL) return;
  for (unsigned int i = 0; i < t->children.size(); i++) {
    deleteAll(t->children[i]);
  }
  delete t;
  t = NULL;
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq) {
  TrieNode* curr = root;
  if (curr == NULL) return false;
  string text = curr->text;
  curr->freq = freq;
  for (unsigned int i = 0; i < word.length(); i++) {
    int letter = 0;
    if (word[i] == ' ')
      letter = 26;
    else
      letter = (int)word[i] - 'a';
    if (curr->children[letter] == NULL) {
      text = curr->text + word[i];
      curr->children[letter] = new TrieNode(text);
    }
    curr = curr->children[letter];
    if (i == word.length() - 1) {
      if (curr->isWord) return false;
      curr->freq = freq;
    }
  }

  curr->isWord = true;
  return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const {
  TrieNode* curr = root;
  for (unsigned int i = 0; i < word.length(); ++i) {
    if (word[i] == ' ') {
      if (curr->children[26] == NULL) return false;
      curr = curr->children[26];
    } else {
      if (curr->children[(int)word[i] - 'a'] == NULL) return false;
      curr = curr->children[(int)word[i] - 'a'];
    }
  }
  cout << curr->freq << endl;
  return curr->isWord;
}

TrieNode* DictionaryTrie::search(std::string word) {
  TrieNode* curr = root;

  for (unsigned int i = 0; i < word.length(); ++i) {
    if (curr->children[(int)word[i] - 'a'] == NULL) return NULL;

    curr = curr->children[(int)word[i] - 'a'];
  }

  return curr;
}

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
std::vector<std::string> DictionaryTrie::predictCompletions(
    std::string prefix, unsigned int num_completions) {
  vector<string> words;  

  string output = "";
  
  // if word in not in library return vector of size 0
  if (!find(prefix)) {
    return words;
  }
  
  // get first node with prefix
  TrieNode* curr = root;
  TrieNode* next = NULL;
  char c = ' ';
  if (!curr) return words;

  for (unsigned int i = 0; i < prefix.length(); ++i) {
    c = prefix[i];
    next = curr->children[(int)c - 'a'];
    output += prefix[i];
    if (next == NULL) return words;

  }

  priority_queue<TrieNode*, vector<TrieNode*>, TrieNodePtrComp> pq;
  unsigned int idx = 0;
  string w = "";
  pq.push(next);
  loadQueue(pq, next);

  while (!pq.empty() && idx < num_completions) {
    w = pq.top()->text;
    pq.pop();
    words.push_back(w);
    idx++;
  }

  return words;
}

void DictionaryTrie::loadQueue(
    priority_queue<TrieNode*, vector<TrieNode*>, TrieNodePtrComp>& pq,
    TrieNode* curr) {
    
  for (unsigned int i = 0; i < ALPHABET_SIZE; i++) {
    if (curr->children[i] != NULL) {
      loadQueue(pq, curr->children[i]);
      if (curr->children[i]->isWord) {
        pq.push(curr->children[i]);
      }
    }
  }
}

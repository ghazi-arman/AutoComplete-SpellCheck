/**
 * C++ File Autocomplete
 * Authors: Alan Chen
 *	    Arman Ghazi
 */

#include "util.hpp"
#include "DictionaryTrie.hpp"
#include "DictionaryBST.hpp"
#include "DictionaryHashtable.hpp"
#include <fstream>
#include <sstream>

/*
 * Arguments
 * min_size: The minimum size of the dictionary you want to test
 * step_size: How much to increase the dict size each iteration
 * num_iterations: How many times do you want to increase your dictionary size
 * dict_filename: Name of file that has the dictionary
 */
void testStudent(std::string min_size, std::string step_size,
                 std::string num_iterations, std::string dict_filename) {
  const char* toread = dict_filename.c_str();
  unsigned int minSize = atoi(min_size.c_str());
  unsigned int stepSize = atoi(step_size.c_str());
  unsigned int numIters = atoi(num_iterations.c_str());

  Timer T;
  const int RUN = 20;
  long long avg_time_duration;
  unsigned int number_of_lines = 0;

  FILE* infile = fopen(toread, "r");

  int ch;
  while (EOF != (ch = getc(infile))) {
    if ('\n' == ch) {
      ++number_of_lines;
    }
  }
  ++number_of_lines;

  fclose(infile);

  std::ifstream in;
  in.open(dict_filename, std::ios::binary);

  // Test DictionaryTrie
  DictionaryTrie* dict_trie = new DictionaryTrie();
  Utils::load_dict(*dict_trie, in);

  // Compute the worst case time to find ten words
  std::cout << "DictionaryTrie" << std::endl;

  for (unsigned int i = 0; i < numIters; i++) {
    unsigned int toLoad = minSize + i * stepSize;

    if (toLoad > number_of_lines) {
      std::cout << "Warning: load size > file size \n" << std::endl;
    }

    Utils::load_dict(*dict_trie, in, toLoad);

    T.begin_timer();

    // try looking for 10 words not in the dictionary
    for (int j = 0; j < RUN; j++) {
      dict_trie->predictCompletions("abcde", 10);
      dict_trie->predictCompletions("bcdea", 10);
      dict_trie->predictCompletions("cdeab", 10);
      dict_trie->predictCompletions("deabc", 10);
      dict_trie->predictCompletions("eabcd", 10);
      dict_trie->predictCompletions("fghij", 10);
      dict_trie->predictCompletions("ghijf", 10);
      dict_trie->predictCompletions("hijfg", 10);
      dict_trie->predictCompletions("ijfgh", 10);
      dict_trie->predictCompletions("jfghi", 10);
    }

    avg_time_duration = T.end_timer() / RUN;

    std::cout << toLoad << "\t" << avg_time_duration << std::endl;
  }
  delete dict_trie;

  std::cout << "\n" << std::endl;

  // Test DictionaryBST
  DictionaryBST* dict_bst = new DictionaryBST();
  Utils::load_dict(*dict_bst, in);

  // Compute the worst case time to find ten words
  std::cout << "DictionaryBST" << std::endl;

  for (unsigned int i = 0; i < numIters; i++) {
    unsigned int toLoad = minSize + i * stepSize;

    if (toLoad > number_of_lines) {
      std::cout << "Warning: load size > file size" << std::endl;
    }

    Utils::load_dict(*dict_bst, in, toLoad);

    T.begin_timer();

    // try looking for 10 words not in the dictionary
    for (int j = 0; j < RUN; j++) {
      dict_bst->find("abcde");
      dict_bst->find("bcdea");
      dict_bst->find("cdeab");
      dict_bst->find("deabc");
      dict_bst->find("eabcd");
      dict_bst->find("fghij");
      dict_bst->find("ghijf");
      dict_bst->find("hijfg");
      dict_bst->find("ijfgh");
      dict_bst->find("jfghi");
    }

    avg_time_duration = T.end_timer() / RUN;

    std::cout << toLoad << "\t" << avg_time_duration << std::endl;
  }
  delete dict_bst;

  std::cout << "\n" << std::endl;

  // Test DictionaryHashtable
  DictionaryHashtable* dict_hash = new DictionaryHashtable();
  Utils::load_dict(*dict_hash, in);

  // Compute the worst case time to find ten words
  std::cout << "DictionaryHashtable" << std::endl;

  for (unsigned int i = 0; i < numIters; i++) {
    unsigned int toLoad = minSize + i * stepSize;

    if (toLoad > number_of_lines) {
      std::cout << "Warning: load size > file size" << std::endl;
    }

    Utils::load_dict(*dict_hash, in, toLoad);

    T.begin_timer();

    // try looking for 10 words not in the dictionary
    for (int j = 0; j < RUN; j++) {
      dict_hash->find("abcde");
      dict_hash->find("bcdea");
      dict_hash->find("cdeab");
      dict_hash->find("deabc");
      dict_hash->find("eabcd");
      dict_hash->find("fghij");
      dict_hash->find("ghijf");
      dict_hash->find("hijfg");
      dict_hash->find("ijfgh");
      dict_hash->find("jfghi");
    }

    avg_time_duration = T.end_timer() / RUN;

    std::cout << toLoad << "\t" << avg_time_duration << std::endl;
  }
  delete dict_hash;

  // clean up
  in.close();
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Incorrect number of arguments." << std::endl;
    std::cout << "\t First argument: name of dictionary file." << std::endl;
    std::cout << std::endl;
    exit(-1);
  }

  
  testStudent(argv[1], argv[2], argv[3], argv[4]);
}

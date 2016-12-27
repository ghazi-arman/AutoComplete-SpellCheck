/**
 * C++ File Autocomplete
 * Authors: Alan Chen
 *	    Arman Ghazi
 */
 
#include <fstream>
#include "util.hpp"
#include "DictionaryBST.hpp"
#include "DictionaryHashtable.hpp"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
  long runTime = 0;

  /*cout << "Test DictionaryBST Insert" << "\n";

  // get dictionary
  ifstream testDict;
  testDict.open(argv[1], ios::binary);

  DictionaryBST* testTree = new DictionaryBST();
  clock_t t = clock();
  Utils::load_dict(*testTree, testDict);
  runTime = clock() - t;

  cout << "BST Insert Runtime: " << runTime << "\n";

  // ------------------------------------------------------- //

  cout << "Test DictionaryBST Find" << "\n";

  bool status = testTree->find("balanced");

  cout << "Found Status: " << status << "\n";
  testDict.close();
  delete testTree;
  // ------------------------------------------------------- //

  ifstream testDict2;
  testDict2.open(argv[1], ios::binary);

  cout << "Test DictionaryHashtable Insert" << "\n";

  DictionaryHashtable* testTable = new DictionaryHashtable();

  clock_t t2 = clock();
  Utils::load_dict(*testTable, testDict2);
  runTime = clock() - t2;

  cout << "Hashtable Insert Runtime: " << runTime << "\n";

  // ------------------------------------------------------- //

  cout << "Test DictionaryHashtable Find" << "\n";

  status = testTable->find("balanced");

  cout << "Found Status: " << status << "\n";
  testDict2.close();
  delete testTable;*/
  // ------------------------------------------------------- //

  ifstream testDict1;
  testDict1.open(argv[1], ios::binary);

  cout << "Test DictionaryTrie Insert"
       << "\n";

  DictionaryTrie* testTrie = new DictionaryTrie();
  cerr << "blah" << endl;
  // testTrie->insert("as i was walking", 4);
  clock_t t1 = clock();
  Utils::load_dict(*testTrie, testDict1);
  runTime = clock() - t1;

  cout << "Trie Insert Runtime: " << runTime << "\n";

  // ------------------------------------------------------- //

  cout << "Test DictionaryTrie Find"
       << "\n";

  bool status = testTrie->find("assume");

  cout << "Found Status: " << status << "\n";

  // ------------------------------------------------------- //

  testDict1.close();
  cerr << "blah" << endl;
  vector<string> tmp = testTrie->predictCompletions("as", 4);
  cerr << "check" << endl;
  cerr << tmp.size() << endl;
  for (unsigned int i = 0; i < tmp.size(); i++) {
    cout << tmp[i] << endl;
  }
  delete testTrie;
}

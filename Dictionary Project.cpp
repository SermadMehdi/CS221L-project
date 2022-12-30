#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <iomanip>

using namespace std;

const int ALPHABET_SIZE = 26;

// Trie node
struct TrieNode {
  TrieNode* children[ALPHABET_SIZE];
  bool isEndOfWord;
  int frequency;

  TrieNode() {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
      children[i] = nullptr;
    }
    isEndOfWord = false;
    frequency = 0;
  }
};

// Trie class
class Trie {
 public:
  TrieNode* root;
  Trie() {
    root = new TrieNode();
  }

  // Insert a word into the trie
  void insert(const std::string& word) {
  TrieNode* current = root;
  for (char ch : word) {
    int index = ch - 'a';
    if (current->children[index] == nullptr) {
      current->children[index] = new TrieNode();
    }
    current = current->children[index];
  }
  current->isEndOfWord = true;
  current->frequency++;
}


  // Check if a word is present in the trie
  bool search(const string& word) {
    TrieNode* current = root;
    for (char ch : word) {
      int index = ch - 'a';
      if (current->children[index] == nullptr) {
        return false;
      }
      current = current->children[index];
    }
    return current->isEndOfWord;
  }

  // Suggest words based on a given prefix
 void suggestWords(const string& prefix) {
  TrieNode* current = root;
  for (char ch : prefix) {
    int index = ch - 'a';
    if (current->children[index] == nullptr) {
      cout << "No suggestions" << endl;
      return;
    }
    current = current->children[index];
  }

  // Use a priority queue to store the suggestions in order of frequency
  priority_queue<pair<int, string>> pq;
  string word = prefix;
  suggestWordsUtil(current, pq, word);

 std::cout << std::left << std::setw(15) << "Word" << std::setw(15) << "Frequency" << std::endl;
while (!pq.empty()) {
  std::pair<int, std::string> top = pq.top();
  pq.pop();
  std::cout << std::left << std::setw(15) << top.second << std::setw(15) << top.first << std::endl;
}
 }


 private:
  // Recursive function to suggest words
  void suggestWordsUtil(TrieNode* node, priority_queue<pair<int, string>>& pq, string& word) {
    if (node->isEndOfWord) {
pq.push({node->frequency, word});
}
for (int i = 0; i < ALPHABET_SIZE; i++) {
if (node->children[i] != nullptr) {
word.push_back(i + 'a');
suggestWordsUtil(node->children[i], pq, word);
word.pop_back();
}
}
}
};

int main() {
  // Read the words from the text file and insert them into the trie
  Trie trie;
  ifstream infile("dictionary.txt");
  string word;
  while (infile >> word) {
    trie.insert(word);
  }

  int choice;
  do {
    cout << "Menu:" << endl;
    cout << "1. Spell check a word" << endl;
    cout << "2. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
      // Spell check a given word and suggest words
      string input;
      cout << "Enter a word to spell check: ";
      cin >> input;
      if (trie.search(input)) {
        cout << "Correct spelling" << endl;
      } else {
        cout << "Incorrect spelling" << endl;
      }
      trie.suggestWords(input);
    }
  } while (choice != 2);

  return 0;
}


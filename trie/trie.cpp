// Структура данных "бор"

#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <algorithm>
#include <vector>

#include <curses.h>

using namespace std;

struct trie_node {
  trie_node *parent;
  char c;
  map<char, trie_node*> children;

  int frequency;

  string gather_string() {
    trie_node *a = this;
    vector<char> result;
    while (a->parent != NULL) {
      result.push_back(a->c);
      a = a->parent;
    }
    return string(result.rbegin(), result.rend());
  }

  struct compare_frequencies {
    bool operator()(trie_node* const &a, trie_node* const &b) const {
      if (a->frequency != b->frequency) {
        return a->frequency > b->frequency;
      } else {
        return a->gather_string() < b->gather_string();
      }
    }
  };

  set<trie_node*, compare_frequencies> top10;

  void delete_node() {
    for (auto child : children) {
      child.second->delete_node();
      delete child.second;
    }
  }
};

struct trie {
  trie_node *head = new trie_node{NULL, '\0', {}, 0, {}};

  void delete_trie() {
    head->delete_node();
    delete head;
  }

  void add_word(string const &word, int frequency) {
    trie_node *a = head;
    size_t i = 0;
    while (i < word.size() && a->children.count(word[i]) != 0) {
      a = a->children[word[i]];
      ++i;
    }
    while (i < word.size()) {
      a = new trie_node{a, word[i], {}, 0, {}};
      a->parent->children[word[i]] = a;
      ++i;
    }
    a->frequency += frequency;
    trie_node *new_node = a;
    while (a != NULL && a->parent != NULL) {
      a->top10.insert(new_node);
      if (a->top10.size() > 10) {
        a->top10.erase(prev(a->top10.end()));
      }
      a = a->parent;
    }
  }

  int search(string const &word) {
    trie_node *a = head;
    size_t i = 0;
    while (i < word.size() && a->children.count(word[i]) != 0) {
      a = a->children[word[i]];
      ++i;
    }
    if (i == word.size()) {
      return a->frequency;
    } else {
      return 0;
    }
  }

  vector<string> top10(string const &word) {
    trie_node *a = head;
    size_t i = 0;
    while (i < word.size() && a->children.count(word[i]) != 0) {
      a = a->children[word[i]];
      ++i;
    }
    if (i != word.size()) {
      return {};
    }
    vector<string> result;
    for (trie_node *top_word : a->top10) {
      result.push_back(top_word->gather_string());
    }
    return result;
  }
};

int main(int argc, char **argv) {
  /*int word_n;
  cin >> word_n;

  string word;
  int frequency;
  for (int i = 0; i < word_n; ++i) {
    cin >> word >> frequency;
    words.add_word(word, frequency);
  }

  int request_n;
  cin >> request_n;

  string request;
  for (int i = 0; i < request_n; ++i) {
    cin >> request;
    vector<string> suggestions = words.top10(request);
    for (string const &suggestion : suggestions) {
      cout << suggestion << "\n";
    }
    if (i != request_n - 1) {
      cout << "\n";
    }
  }
  */

  if (argc < 2) {
    cout << "Usage: ./trie words.txt\n";
    return 0;
  }

  trie my_trie;

  ifstream words((char*) argv[1]);
  string word;
  int frequency;
  int word_n = 0;
  while (words >> word >> frequency) {
    for (size_t i = 0; i < word.size(); ++i) {
      word[i] = tolower(word[i]);
    }
    my_trie.add_word(word, frequency);
    ++word_n;
    if (word_n % 50000 == 0) {
      cout << "read " << word_n << " words\n";
    }
  }

  initscr();
  cbreak();
  noecho();

  char c = ' ';
  string s;
  string s_lower;

  while (c != '*') {
    clear();

    auto suggestions = my_trie.top10(s_lower);
    for (size_t i = 0; i < suggestions.size(); ++i) {
      mvprintw(i + 2, 0, "%s", suggestions[i].c_str());
    }
    mvprintw(0, 0, "%s", s.c_str());
    c = getch();
    if ((int) c == 127) {
      if (!s.empty()) {
        s.pop_back();
        s_lower.pop_back();
      }
    } else {
      s += c;
      s_lower += tolower(c);
    }
  }

  refresh();
  endwin();

  my_trie.delete_trie();
  return 0;
}

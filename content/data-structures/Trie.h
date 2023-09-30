/**
 *  Tested:
 *  - ...
**/

#pragma once

struct Trie {
  struct Node {
    int exist, cnt;
    Node* child[26];
    Node() {
      exist = cnt = 0;
      for (int i = 0; i < 26; i++) child[i] = NULL;
    }
  };
  int cur;
  Node* root;
  Trie() : cur(0) { root = new Node(); };
 
  void add_string(string& s) {
    Node* p = root;
    for (char f : s) {
      int c = f - 'a';
      if (p->child[c] == NULL) p->child[c] = new Node();
      p = p->child[c];
      p->cnt++;
    }
    p->exist++;
  }
  bool delete_string_recursive(Node* p, string& s, int i) {
    if (i != (int) s.size()) {
      int c = s[i] - 'a';
      bool isChildDeleted = delete_string_recursive(p->child[c], s, i + 1);
      if (isChildDeleted) p->child[c] = NULL;
    }
    else p->exist--;

    if (p != root) {
      p->cnt--;
      if (p->cnt == 0) {
        delete p;
        return true;
      }
    }
    return false;
  }
  void delete_string(string s) {
    if (find_string(s) == false) return;
    delete_string_recursive(root, s, 0);
  }
  bool find_string(string s) {
    Node* p = root;
    for (auto f : s) {
      int c = f - 'a';
      if (p->child[c] == NULL) return false;
      p = p->child[c];
    }
    return (p->exist != 0);
  }
};
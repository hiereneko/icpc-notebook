/**
 *  Tested:
 *  - https://judge.yosupo.jp/problem/staticrmq
**/

#pragma once

template <class T>
struct SparseTable { // 0-indexed
  int n{};
  vector<vector<T>> table{};
  inline T op(T a, T b) { return min(a, b); }
  inline int highest_one(int n) { return n == 0 ? -1 : 31 - __builtin_clz(n); }

  template <class U>
  void build(const vector<U>& A) {
    assert(!A.empty());
    n = A.size();
    int lv = highest_one(n) + 1;
    table.resize(lv);
    table[0] = A;
    for (int i = 0; i < lv; i++) {
      table[i].resize(n - (1 << i) + 1);
    }
    for (int i = 1; i < lv; i++) {
      for (int j = 0; j <= n - (1 << i); j++) {
        table[i][j] = op(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
      }
    }
  }
  SparseTable() {}
  template <class U>
  SparseTable(const vector<U>& A) { build(A); }
  T query(int l, int r) {
    if (l == r) { return table[0][l]; }
    assert(0 <= l && l < r && r < n);
    int lv = highest_one(r - l + 1);
    return op(table[lv][l], table[lv][r - (1 << lv) + 1]);
  }
};
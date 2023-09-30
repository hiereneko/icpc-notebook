/**
 *  Tested:
 *  - https://judge.yosupo.jp/problem/point_add_range_sum
**/

#pragma once

template <class T>
struct FenwickTree { // 1-indexed
  int n{};
  vector<T> tree{};

  template <class U>
  void build(const vector<U>& A) { // A is 0-indexed
    n = A.size();
    tree.assign(n + 1, T());

    for (int i = 1; i <= n; i++) {
      tree[i] += A[i - 1];
      int p = i + (i & -i); // parent node
      // faster than if, lol
      p <= n ? tree[p] += tree[i] : 0;
    }
  }
  FenwickTree() {}
  FenwickTree(int N) : n(N), tree(N + 1) {}
  template <class U>
  FenwickTree(const vector<U>& A) { build(A); }
  void add(int i, T v) {
    assert(1 <= i && i <= n);
    for (; i <= n; i += i & -i) { tree[i] += v; }
  }
  void add(int l, int r, T v) {
    add(l, v);
    add(r + 1, v);
  }
  T rsq(int i) {
    assert(i <= n);
    T res{};
    for (; i >= 1; i -= i & -i) { res += tree[i]; }
    return res;
  }
  T rsq(int l, int r) { // inclusive
    return rsq(r) - rsq(l - 1);
  }
  int lower_bound(T v) { // O(log^2(n))
    int lo = 1, hi = n;
    for (int i = 0; i < 30; i++) { // 2^30 > 10^9
      int mi = lo + (hi - lo) / 2;
      rsq(1, mi) < v ? lo = mi : hi = mi;
    }
    return hi;
  }
};
/**
 *  Tested:
 *  - https://cses.fi/problemset/task/1649
**/

#pragma once

template <class T>
struct SegmentTree { // 1-indexed
  int n{};
  vector<T> tree{};
  const T NIL = numeric_limits<T>::max(); // = T() for RSQ
  inline T op(T a, T b) { return min(a, b); }
  #define L(i) (i << 1)
  #define R(i) (i << 1 | 1)

  // a is 0-indexed, query ranges are inclusive and 0-indexed
  template <class U>
  void build(const vector<U>& a, int i, int l, int r) {
    if (l == r) return tree[i] = a[l], void();
    int m = (l + r) >> 1;
    build(a, L(i), l, m);
    build(a, R(i), m + 1, r);
    tree[i] = op(tree[L(i)], tree[R(i)]);
  }
  SegmentTree(int N) : n(N), tree(N << 2) {}
  template <class U>
  SegmentTree(const vector<U>& a) {
    n = a.size();
    tree.assign(n << 2, T());
    build(a, 1, 0, n - 1);
  }

  T query(int i, int l, int r, int ql, int qr) { // inclusive
    if (qr < l || ql > r || l > r) return NIL;
    if (ql == l && r == qr) return tree[i];
    int m = (l + r) >> 1;
    return op(query(L(i), l, m, ql, min(qr, m)),
              query(R(i), m + 1, r, max(ql, m + 1), qr));
  }
  T query(int ql, int qr) {
    return query(1, 0, n - 1, ql, qr);
  }
  void update(int i, int l, int r, int qi, T v) {
    if (l == r) return tree[i] = v, void();
    int m = (l + r) >> 1;
    if (qi <= m) update(L(i), l, m, qi, v);
    else         update(R(i), m + 1, r, qi, v);
    tree[i] = op(tree[L(i)], tree[R(i)]);
  }
  void update(int qi, T v) {
    update(1, 0, n - 1, qi, v);
  }
};

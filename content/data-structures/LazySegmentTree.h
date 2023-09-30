/**
 * Description: range add query, range replace query, RSQ
**/

#pragma once

#include "../various/BumpAllocator.h"

namespace LazySegmentTree {

#define L(i) (i << 1)
#define R(i) (i << 1 | 1)
 
struct Node {
  lint sum{};
  lint lazy_a{}; // add
  lint lazy_r{}; // replace
};
 
constexpr int N = 2e5 + 5;
int n, q;
int a[N];
Node seg[N << 2];
 
void build(int i, int l, int r) {
  if (l == r) { return seg[i].sum = a[l], void(); }
  int m = (l + r) >> 1;
  build(L(i), l, m);
  build(R(i), m + 1, r);
  seg[i].sum = seg[L(i)].sum + seg[R(i)].sum;
}
 
void push(int i, int l, int r) {
  int m = (l + r) >> 1;
 
  if (seg[i].lazy_r) {
    lint v = seg[i].lazy_r;
    seg[L(i)].sum = 1ll * (m - l + 1) * v;
    seg[R(i)].sum = 1ll * (r - m) * v;
    seg[L(i)].lazy_a = seg[R(i)].lazy_a = 0;
    seg[L(i)].lazy_r = seg[R(i)].lazy_r = v;
    seg[i].lazy_r = 0;
  }
 
  if (seg[i].lazy_a) {
    lint v = seg[i].lazy_a;
    seg[L(i)].sum += 1ll * (m - l + 1) * v;
    seg[R(i)].sum += 1ll * (r - m) * v;
    seg[L(i)].lazy_a += v;
    seg[R(i)].lazy_a += v;
    seg[i].lazy_a = 0;
  }
}
 
void add(int i, int l, int r, int ql, int qr, lint v) {
  if (ql > r || qr < l) { return; }
  if (ql <= l && r <= qr) {
    seg[i].sum += 1ll * (r - l + 1) * v;
    seg[i].lazy_a += v;
    return;
  }
 
  push(i, l, r);
  int m = (l + r) >> 1;
  add(L(i), l, m, ql, qr, v);
  add(R(i), m + 1, r, ql, qr, v);
  seg[i].sum = seg[L(i)].sum + seg[R(i)].sum;
}
 
void update(int i, int l, int r, int ql, int qr, lint v) {
  if (ql > r || qr < l) { return; }
  if (ql <= l && r <= qr) {
    seg[i].sum = 1ll * (r - l + 1) * v;
    seg[i].lazy_a = 0;
    seg[i].lazy_r = v;
    return;
  }
 
  push(i, l, r);
  int m = (l + r) >> 1;
  update(L(i), l, m, ql, qr, v);
  update(R(i), m + 1, r, ql, qr, v);
  seg[i].sum = seg[L(i)].sum + seg[R(i)].sum;
}
 
lint query(int i, int l, int r, int ql, int qr) { // RSQ
  if (ql > r || qr < l) { return 0; }
  if (ql <= l && r <= qr) { return seg[i].sum; }
 
  push(i, l, r);
  int m = (l + r) >> 1;
  lint res = query(L(i), l, m, ql, qr) +
             query(R(i), m + 1, r, ql, qr);
  return res;
}

} /// LazySegmentTree
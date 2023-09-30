/**
 *  Tested:
 *  - https://judge.yosupo.jp/problem/associative_array
**/

#pragma once

struct custom_hash {
  // any random-ish large odd number will do
  const size_t C = size_t(2e18 * acos(-1.0)) + 71;
  // random 32-bit number
  const size_t RANDOM = chrono::steady_clock::now().time_since_epoch().count();
  size_t operator()(size_t x) const {
    // see https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
    return __builtin_bswap64((x ^ RANDOM) * C);
  }
};

// same API as unordered_map
template <class K, class V>
using hash_table = gp_hash_table<K, V, custom_hash>;

/**
 * Description: Count number of integers $X$ such that $A \leq X \leq B$ and sum of all digits in X equals to an integer $K$, where ($0 \leq A \leq B \leq 10^{18}$).
**/

#pragma once

// Use different sum range strategy for bottom-up and top-down
ll dp_bottom_up(vector<int>& digits, int sum) {
  for (int i = 0; i <= digits[0] && i <= sum; ++i) {
    f[0][i == digits[0]][sum - i] = 1;
  }
  
  int n = digits.size();
  for (int id = 0; id < n; ++id) {
    for (int tight = 0; tight < 2; tight++) { 
      for (int remain = 0; remain <= sum; ++remain) {
        if (f[id][tight][remain] == 0) { continue; }
        int linmit = tight ? digits[id + 1] : 9;
        for (int d = 0; d <= limit; ++d) {
          if (d > remain) break;
          f[id + 1][tight && d == limit][remain - d] += f[id][tight][remain];
        }
      }
    }
  }
  return f[n - 1][0][0] + f[n - 1][1][0];
}
ll dp_top_down(int id, int tight, int remain, vector<int>& digits) {
  if (remain < 0) { return 0; }
  if (id < 0) { return remain == 0 ? 1 : 0; }
  if (f[id][tight][remain] != -1) { return f[id][tight][remain]; }

  ll& res = f[id][tight][remain];
  res = 0;
  int limit = tight ? digits[id] : 9;
  for (int i = 0; i <= limit; ++i) {
    int newTight = tight && i == digits[id];
    res += dp(id - 1, newTight, remain - i, digits);
  }
  return res;
}
/**
 * Description: Find all numbers in $[L, R]$ containing exactly $k$ $d$ digits: dfs(R) - dfs(L - 1)
**/

#pragma once

const int max_num_digits = 100;
int dp[max_num_digits][max_num_digits][2];
int n, m, k, d;

void reset() {
  for (int i = 0; i < max_num_digits; i++){
    for (int j = 0; j < max_num_digits; j++){
      dp[i][j][0] = -1;
      dp[i][j][1] = -1;
    }
  }
}
// range [0, c] with state [x][y][z]
int dfs(int c, int x = 0, int y = 0, bool z = 0) {
  if (dp[x][y][z] != -1) { return dp[x][y][z]; }
  dp[x][y][z] = (y == k);
  if (x == to_string(c).length()) { return dp[x][y][z]; }
  int limit = 9;
  if (!z) { // if the number being formed CAN exceed c
    limit = to_string(c)[x] - '0'; // the x-th digit of c
  }
  // now setting the x-th digit of the number we're building
  dp[x][y][z] = 0; // going to permanently set dp[x][y][z] now
  for (int xth_digit = 0; xth_digit <= limit; xth_digit++){
    if (z) {
      dp[x][y][z] += dfs(c, x + 1, y + (xth_digit == d), 1);
    }
    else {
      dp[x][y][z] += dfs(c, x + 1, y + (xth_digit == d), xth_digit < limit);
    }
  }
  return dp[x][y][z];
}
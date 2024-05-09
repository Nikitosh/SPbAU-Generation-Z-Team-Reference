int dp[(1 << MASK)][MASK];

void calcDP(int n) {
  forn(mask, 1 << n) {
    dp[mask][n] = 1;
    fornr(i, n) {
      dp[mask][i] = dp[mask][i + 1];
      if ((1 << i) & mask) {
        dp[mask][i] += dp[mask ^ (1 << i)][i + 1];
      }
    }
  }
}

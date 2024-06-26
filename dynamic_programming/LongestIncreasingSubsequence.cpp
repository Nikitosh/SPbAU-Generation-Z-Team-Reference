int longestIncreasingSubsequence(vi a) {
  int n = sz(a);
  vi d(n + 1, INF);
  d[0] = -INF;
  forn (i, n) *upper_bound(all(d), a[i]) = a[i];
  fornr (i, n + 1) if (d[i] != INF) return i;
  return 0;
}
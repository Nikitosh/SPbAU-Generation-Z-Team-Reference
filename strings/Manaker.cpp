void manaker(const string& s, int *z0, int *z1) {
  int n = sz(s);
  forn (t, 2) {
    int *z = t ? z1 : z0, l = -1, r = -1; // [l..r]
    forn (i, n - t) {
      int k = 0;
      if (r > i + t) {
        int j = l + (r - i - t);
        k = min(z[j], j - l);
      }
      while (i - k >= 0 && i + k + t < n && s[i - k] == s[i + k + t]) k++;
      z[i] = k;
      if (k && i + k + t > r) {
        l = i - k + 1, r = i + k + t - 1;
      }
    }
  }
}

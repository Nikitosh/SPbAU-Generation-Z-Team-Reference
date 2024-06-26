vi crt(vi a, vi mod) {
  int n = sz(a);
  vi x(n);
  forn (i, n) {
    x[i] = a[i];
    forn (j, i) {
      x[i] = inverse(mod[j], mod[i]) * (x[i] - x[j]) % mod[i];
      if (x[i] < 0) x[i] += mod[i];
    }
  }
  return x;
}

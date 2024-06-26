int primitiveRoot(int mod) { // Returns -1 if no primitive root exists
  vi fact;
  int ph = phi(mod);
  int n = mod;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      fact.pb(i);
      while (n % i == 0) n /= i;
    }
  }
  if (n > 1) fact.pb(n);
  forab (i, 2, mod + 1) {
    bool ok = 1;
    for (int j = 0; j < sz(fact) && ok; j++) {
      ok &= power(i, ph / fact[j], mod) != 1;
    }
    if (ok) return i;
  }
  return -1;
}

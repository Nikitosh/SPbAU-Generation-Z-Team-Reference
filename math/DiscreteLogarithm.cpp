// Returns x: a^x = b (mod mod) or -1, if no such x exists
int discreteLogarithm(int a, int b, int mod) { 
  int sq = (int) sqrt(mod);
  int sq2 = mod / sq + (mod % sq ? 1 : 0);
  vector<pii> powers(sq2);
  forn (i, sq2) {
    powers[i] = mp(power(a, (i + 1) * sq, mod), i + 1);
  }
  sort(all(powers));
  forn (i, sq + 1) {
    int cur = power(a, i, mod);
    cur = mul(cur, b, mod);
    auto it = lower_bound(all(powers), mp(cur, 0));
    if (it != powers.end() && it->fst == cur) return it->snd * sq - i;
  }
  return -1;
}

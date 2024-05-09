using vpnt = vector<Pnt>;

inline bool byAngle(const Pnt& a, const Pnt& b) {
  dbl x = a % b;
  return eq(x, 0) ? a.len2() < b.len2() : x < 0;
}

vpnt convexHull(vpnt p) {
  int n = sz(p);
  assert(n > 0);
  swap(p[0], *min_element(all(p)));
  forab(i, 1, n)
  p[i] = p[i] - p[0];
  sort(p.begin() + 1, p.end(), byAngle);

  /*
  To keep 180 angles (1) и (2)
  (1):
  int k = p.size() - 1;
  while(k > 0 && eq((p[k - 1] - p.back()) % p.back(), 0))
    --k;
  reverse(pi.begin() + k, pi.end());
  */

  int rn = 0;
  vpnt r(n);
  r[rn++] = p[0];
  forab (i, 1, n){
    Pnt q = p[i] + p[0];
    while(rn >= 2 && geq((r[rn - 1] - r[rn - 2]) % (q - r[rn - 2]), 0)) { // (2) ge
      --rn;
  }
    r[rn++] = q;
  }
  r.resize(rn);
  return r;
}

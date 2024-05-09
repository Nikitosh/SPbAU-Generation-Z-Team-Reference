using T = int;
using poly = vector<int>;

void remz(poly& p) { while (sz(p) && p.back() == T(0)) p.pop_back(); }

poly operator*(const poly& l, const poly& r) {
  if (!min(sz(l), sz(r))) return {};
  poly x(sz(l) + sz(r) - 1); 
  forn (i, sz(l)) forn(j, sz(r)) x[i + j] += l[i] * r[j];
  return x;
}
pair<poly,poly> quoRem(poly a, poly b) { 
  remz(a); remz(b); assert(sz(b));
  T lst = b.back(), B = T(1) / lst; 
  for (auto &t : a) t *= B; 
  for (auto &t : b) t *= B;
  poly q(max(sz(a) - sz(b) + 1, 0));
  for (int dif; (dif = sz(a) - sz(b)) >= 0; remz(a)) {
    q[dif] = a.back(); 
    forn(i, sz(b)) a[i + dif] -= q[dif] * b[i]; 
  }
  for(auto &t : a) t *= lst;
  return {q, a}; // quotient, remainder
}
poly operator%(const poly& a, const poly& b) { 
  return quoRem(a, b).snd; 
}

struct LinRec {
  poly s, C, rC; 
  void BM() { // find smallest C such that C[0]=1 and 
    // for all i >= sz(C)-1, sum_{j=0}^{sz(C)-1}C[j]*s[i-j]=0
    // If we treat C and s as polynomials in D, then
    // for all i >= sz(C)-1, [D^i]C*s=0
    int x = 0; T b = 1;
    poly B; B = C = {1}; // B is fail vector
    /// for all sz(B)+x-1 <= j < i, [D^j](B<<x)*s=0
    /// but [D^i](B<<x)*s=b
    /// invariant: sz(B)+x = M
    forn(i, sz(s)) { // update C after adding a term of s
      ++x; 
      int L = sz(C), M = i + 3 - L;
      T d = 0; 
      forn(j, L) d += C[j] * s[i - j]; // [D^i]C*s
      if (d == 0) continue; // [D^i]C*s=0
      poly _C = C; T coef = d / b; /// d-coef*b = 0
      /// set C := C-coef*(B<<x) to satisfy condition
      C.resize(max(L, M)); 
      forn(j, sz(B)) C[j + x] -= coef * B[j];
      if (L < M) B = _C, b = d, x = 0;
    } /// replace B<<x with C<<0
  }
  void init(const poly& _s) { 
    s = _s; BM();
    rC = C; 
    reverse(all(rC)); // poly for getPow
    C.erase(begin(C)); 
    for(auto &t : C) t *= -1;
  } // now s[i]=sum_{j=0}^{sz(C)-1}C[j]*s[i-j-1]
  poly getPow(ll p) { // get x^p mod rC
    if (p == 0) return {1};
    poly r = getPow(p / 2); r = (r * r) % rC;
    return p & 1 ? (r * poly{0, 1}) % rC : r;
  }
  T dot(poly v) { // dot product with seq
    T ans = 0; 
    forn(i, sz(v)) ans += v[i] * s[i];
    return ans; 
  } // get p-th term of rec
  T eval(ll p) { assert(p >= 0); return dot(getPow(p)); } 
};

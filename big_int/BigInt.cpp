const int BASE_LEN = 9;
const int NUM_LEN = 50000 / BASE_LEN + 2; // LEN <= NUM_LEN * BASE_LEN
const int BASE = pow(10, BASE_LEN);
const ll INF = 8e18, ADD = INF / BASE;

struct num {
  ll a[NUM_LEN];
  int len; // always > 0

  inline const ll& operator [] ( int i ) const { return a[i]; }
  inline ll& operator [] ( int i ) { return a[i]; }

  num& operator = ( const num &x ) { // copy
    len = x.len;
    memcpy(a, x.a, sizeof(a[0]) * len);
    return *this;
  }

  num( const num &x ) { *this = x; } // copy

  num() { len = 1, a[0] = 0; } // 0
  num( ll x ) { // x
    len = 0;
    while (!len || x) {
      assert(len < NUM_LEN); // to catch overflow
      a[len++] = x % BASE, x /= BASE;
    }
  }

  num& cor() {
    while (a[len - 1] >= BASE) {
      assert(len < NUM_LEN); // to catch overflow
      if (a[len - 1] >= 2 * BASE) 
        a[len] = a[len - 1] / BASE, a[len - 1] %= BASE;
      else 
        a[len] = 1, a[len - 1] -= BASE;
      len++;
    }
    while (len > 1 && !a[len - 1])
      len--;
    return *this;
  }

  int length() {
    if (!len)
      return 0;
    int x = a[len - 1], res = 0;
    assert(x);
    while (x || !res)
      x /= 10, res++;
    return res + (len - 1) * BASE_LEN;
  }

  void out() const {
    int i = len - 1;
    printf("%d", (int)a[i--]);
    while (i >= 0)
      printf("%0*d", BASE_LEN, (int)a[i--]);
    puts("");
  }

  void init( const char *s ) {
    int sn = strlen(s);
    while (sn && s[sn - 1] <= 32)
      sn--;
    len = (sn + BASE_LEN - 1) / BASE_LEN;
    memset(a, 0, sizeof(a[0]) * len);
    forn(i, sn) {
      ll &r = a[(sn - i - 1) / BASE_LEN];
      r = r * 10 + (s[i] - '0');
    }
  }

  bool read() {
    static const int L = NUM_LEN * BASE_LEN + 1;
    static char s[L];
    if (!fgets(s, L, stdin))
      return 0;
    assert(!s[L - 2]);
    init(s);
    return 1;
  }

  void mul2() {
    forn(i, len)
      a[i] <<= 1;
    forn(i, len - 1)
      if (a[i] >= BASE)
        a[i + 1]++, a[i] -= BASE;
    cor();
  }

  void div2() {
    for (int i = len - 1; i >= 0; i--) {
      if (i && (a[i] & 1))
        a[i - 1] += BASE;
      a[i] >>= 1;
    }
    cor();
  }

  static ll cmp( ll *a, ll *b, int n ) {
    while (n--)
      if (a[n] != b[n])
        return a[n] - b[n];
    return 0;
  }

  int cmp( const num &b ) const {
    if (len != b.len)
      return len - b.len;
    for (int i = len - 1; i >= 0; i--)
      if (a[i] != b[i])
        return a[i] - b[i];
    return 0;
  }

  bool zero() {
    return len == 1 && !a[0];
  }

  /** c = this/b, this %= b */
  num &div( num b, num &c ) {
    c.len = len - b.len;
    for (int i = c.len; i >= 0; i--) {
      int k = (1.0L * a[len - 1] * BASE + (len >= 2 ? a[len - 2] : 0)) / (1.0L * b[b.len - 1] * BASE + (b.len >= 2 ? b[b.len - 2] + 1 : 0));
      c[i] = 0;
      if (k > 0) {
        c[i] += k;
        forn(j, b.len)
          a[i + j] -= (ll)b[j] * k;
        forn(j, b.len)
          if (a[i + j] < 0) {
            ll k = (-a[i + j] + BASE - 1) / BASE;
            a[i + j] += k * BASE, a[i + j + 1] -= k;
          }
      }
      if (i)
        len--, a[len - 1] += a[len] * BASE, a[len] = 0;
      else if (cmp(a, b.a, b.len) >= 0) {
        c[0]++;
        forn(j, b.len)
          if ((a[j] -= b[j]) < 0)
            a[j] += BASE, a[j + 1]--;
      }
    }
    if (c.len < 0)
      c[c.len = 0] = 0;
    forn(i, c.len)
      if (c[i] >= BASE)
        c[i + 1] += c[i] / BASE, c[i] %= BASE;
    c.len += (!c.len || c[c.len]);
    return cor();
  }
};

num& operator += ( num &a, const num &b ) {
  while (a.len < b.len)
    a[a.len++] = 0;
  forn(i, b.len)
    a[i] += b[i];
  forn(i, a.len - 1)
    if (a[i] >= BASE)
      a[i] -= BASE, a[i + 1]++;
  return a.cor();
}

num& operator -= ( num &a, const num &b ) {
  while (a.len < b.len)
    a[a.len++] = 0;
  forn(i, b.len)
    a[i] -= b[i];
  forn(i, a.len - 1)
    if (a[i] < 0)
      a[i] += BASE, a[i + 1]--;
  assert(a[a.len - 1] >= 0); // a >= b
  return a.cor();
}

num& operator *= ( num &a, int k ) {
  if (k == 1)
    return a;
  if (k == 0) {
    a.len = 0;
    return a;
  }
  forn(i, a.len)
    a[i] *= k;
  forn(i, a.len - 1)
    if (a[i] >= BASE)
      a[i + 1] += a[i] / BASE, a[i] %= BASE;
  return a.cor();
}

num& operator /= ( num &a, int k ) {
  if (k == 1)
    return a;
  assert(k != 0);
  for (int i = a.len - 1; i > 0; i--)
    a[i - 1] += (ll)(a[i] % k) * BASE, a[i] /= k;
  a[0] /= k;
  return a.cor();
}

num& mul( const num &a, const num &b, num &x ) {
  assert(a.len + b.len - 1 <= NUM_LEN);
  memset(x.a, 0, sizeof(x[0]) * (a.len + b.len - 1));
  forn(i, a.len)
    forn(j, b.len)
      if ((x[i + j] += a[i] * b[j]) >= INF)
        x[i + j + 1] += ADD, x[i + j] -= INF;
  x.len = a.len + b.len - 1;
  forn(i, x.len - 1)
    if (x[i] >= BASE)
      x[i + 1] += x[i] / BASE, x[i] %= BASE;
  return x.cor();
}

bool operator == ( const num &a, const num &b ) { return a.cmp(b) == 0; }
bool operator != ( const num &a, const num &b ) { return a.cmp(b) != 0; }
bool operator < ( const num &a, const num &b )  { return a.cmp(b) < 0; }
bool operator > ( const num &a, const num &b )  { return a.cmp(b) > 0; }
bool operator <= ( const num &a, const num &b ) { return a.cmp(b) <= 0; }
bool operator >= ( const num &a, const num &b ) { return a.cmp(b) >= 0; }

num& add( const num &a, const num &b, num &c ) { c = a; c += b; return c; }
num& sub( const num &a, const num &b, num &c ) { c = a; c -= b; return c; }
num& mul( const num &a, int k, num &c )        { c = a; c *= k; return c; }
num& div( const num &a, int k, num &c )        { c = a; c /= k; return c; }

num& operator *= ( num &a, const num &b ) {
  static num tmp;
  mul(a, b, tmp);
  return a = tmp;
}

num operator ^ ( const num &a, int k ) {
  num res(1);
  forn(i, k)
    res *= a;
  return res;
}

num& gcd_binary( num &a, num &b ) {
  int cnt = 0;
  while (!a.zero() && !b.zero()) {
    while (!(b[0] & 1) && !(a[0] & 1))
      cnt++, a.div2(), b.div2();
    while (!(b[0] & 1))
      b.div2();
    while (!(a[0] & 1))
      a.div2();
    if (a.cmp(b) < 0)
      b -= a;
    else
      a -= b;
  }
  if (a.zero())
    std::swap(a, b);
  while (cnt)
    a.mul2(), cnt--;
  return a;
}

num& gcd( num &a, num &b ) {
  static num tmp;
  return b.zero() ? a : gcd(b, a.div(b, tmp));
}

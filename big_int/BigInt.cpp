constexpr int BASE = 1000000000;
constexpr int BASE_DIGITS = 9;

struct BigInt {
  // value == 0 is represented by empty z
  vi z; // digits
  // sign == 1/-1 <==> value >=/< 0
  int sign;
  BigInt(): sign(1) {}
  BigInt(ll v) { *this = v; }
  BigInt& operator=(ll v) {
    sign = v < 0 ? -1 : 1; v *= sign;
    z.clear(); for (; v > 0; v = v / BASE) z.pb((int) (v % BASE));
    return *this;
  }
  BigInt& operator+=(const BigInt& other) {
    if (sign == other.sign) {
      for (int i = 0, carry = 0; i < sz(other.z) || carry; ++i) {
        if (i == sz(z)) z.pb(0);
        z[i] += carry + (i < sz(other.z) ? other.z[i] : 0);
        carry = z[i] >= BASE;
        if (carry) z[i] -= BASE;
      }
    } else if (other != 0 /* prevent infinite loop */) {
      *this -= -other;
    }
    return *this;
  }
  friend BigInt operator+(BigInt a, const BigInt& b) { return a += b; }
  BigInt& operator-=(const BigInt& other) {
    if (sign == other.sign) {
      if ((sign == 1 && *this >= other) || (sign == -1 && *this <= other)) {
        for (int i = 0, carry = 0; i < sz(other.z) || carry; ++i) {
          z[i] -= carry + (i < sz(other.z) ? other.z[i] : 0);
          carry = z[i] < 0;
          if (carry) z[i] += BASE;
        }
        trim();
      } else {
        *this = other - *this;
        this->sign = -this->sign;
      }
    } else { *this += -other; }
    return *this;
  }
  friend BigInt operator-(BigInt a, const BigInt& b) { return a -= b; }
  BigInt& operator*=(int v) {
    if (v < 0) sign = -sign, v = -v;
    for (int i = 0, carry = 0; i < sz(z) || carry; ++i) {
      if (i == sz(z)) z.pb(0);
      ll cur = (ll) z[i] * v + carry;
      carry = (int) (cur / BASE);
      z[i] = (int) (cur % BASE);
    }
    trim();
    return *this;
  }
  BigInt operator*(int v) const { return BigInt(*this) *= v; }
  friend pair<BigInt, BigInt> divmod(const BigInt& a1, const BigInt& b1) {
    int norm = BASE / (b1.z.back() + 1);
    BigInt a = a1.abs() * norm;
    BigInt b = b1.abs() * norm;
    BigInt q, r;
    q.z.resize(sz(a.z));
    fornr (i, sz(a.z)) {
      r *= BASE, r += a.z[i];
      int s1 = sz(b.z) < sz(r.z) ? r.z[sz(b.z)] : 0;
      int s2 = sz(b.z) - 1 < sz(r.z) ? r.z[sz(b.z) - 1] : 0;
      int d = (int) (((ll) s1 * BASE + s2) / b.z.back());
      r -= b * d;
      while (r < 0) r += b, --d;
      q.z[i] = d;
    }
    q.sign = a1.sign * b1.sign, r.sign = a1.sign;
    q.trim(), r.trim();
    return {q, r / norm};
  }
  BigInt operator/(const BigInt& v) const { return divmod(*this, v).fst; }
  BigInt operator%(const BigInt& v) const { return divmod(*this, v).snd; }
  BigInt& operator/=(int v) {
    if (v < 0) sign = -sign, v = -v;
    int rem = 0;
    fornr (i, sz(z)) {
      ll cur = z[i] + rem * (ll) BASE;
      z[i] = (int) (cur / v);
      rem = (int) (cur % v);
    }
    trim();
    return *this;
  }
  BigInt operator/(int v) const { return BigInt(*this) /= v; }
    int operator%(int v) const {
    if (v < 0) v = -v;
    int m = 0;
    fornr (i, sz(z))
      m = (int) ((z[i] + m * (ll) BASE) % v);
    return m * sign;
  }
  BigInt& operator*=(const BigInt& v) { return *this = *this * v; }
  BigInt& operator/=(const BigInt& v) { return *this = *this / v; }
    bool operator<(const BigInt& v) const {
    if (sign != v.sign) return sign < v.sign;
    if (sz(z) != sz(v.z)) return sz(z) * sign < sz(v.z) * v.sign;
    fornr (i, sz(z)) {
      if (z[i] != v.z[i]) return z[i] * sign < v.z[i] * sign;
    }
    return false;
  }
  bool operator>(const BigInt& v) const { return v < *this; }
  bool operator<=(const BigInt& v) const { return !(v < *this); }
  bool operator>=(const BigInt& v) const { return !(*this < v); }
  bool operator==(const BigInt& v) const { return !(*this < v) && !(v < *this); }
  bool operator!=(const BigInt& v) const { return *this < v || v < *this; }
  void trim() {
    while (!z.empty() && z.back() == 0) z.pop_back();
    if (z.empty()) sign = 1;
  }
  bool isZero() const { return z.empty(); }
  friend BigInt operator-(BigInt v) {
    if (!v.z.empty()) v.sign = -v.sign;
    return v;
  }
  BigInt abs() const { return sign == 1 ? *this : -*this; }
  void read(const string& s) {
    sign = 1, z.clear();
    int pos = 0;
    while (pos < sz(s) && (s[pos] == '-' || s[pos] == '+')) {
      if (s[pos] == '-') sign = -sign;
      ++pos;
    }
    for (int i = sz(s) - 1; i >= pos; i -= BASE_DIGITS) {
      int x = 0;
      forab (j, max(pos, i - BASE_DIGITS + 1), i) x = x * 10 + s[j] - '0';
      z.pb(x);
    }
    trim();
  }
  friend ostream &operator<<(ostream& stream, const BigInt& v) {
    if (v.sign == -1) stream << '-';
    stream << (v.z.empty() ? 0 : v.z.back());
    fornr (i, sz(v.z) - 1) {
      stream << setw(BASE_DIGITS) << setfill('0') << v.z[i];
    }
    return stream;
  }
  static vi convertBase(const vi& a, int oldDigits, int newDigits) {
    vector<ll> p(max(oldDigits, newDigits) + 1);
    p[0] = 1;
    for (int i = 1; i < sz(p); i++) p[i] = p[i - 1] * 10;
    vi res;
    ll cur = 0;
    int curDigits = 0;
    for (int v : a) {
      cur += v * p[curDigits];
      curDigits += oldDigits;
      while (curDigits >= newDigits) {
        res.pb(int(cur % p[newDigits]));
        cur /= p[newDigits];
        curDigits -= newDigits;
      }
    }
    res.pb((int) cur);
    while (!res.empty() && res.back() == 0) res.pop_back();
    return res;
  }
  static vll karatsubaMultiply(const vll& a, const vll& b) {
    int n = sz(a);
    vll res(n + n);
    if (n <= 32) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) res[i + j] += a[i] * b[j];
      }
      return res;
    }

    int k = n >> 1;
    vll a1(a.begin(), a.begin() + k), a2(a.begin() + k, a.end());
    vll b1(b.begin(), b.begin() + k), b2(b.begin() + k, b.end());
    vll a1b1 = karatsubaMultiply(a1, b1);
    vll a2b2 = karatsubaMultiply(a2, b2);
    forn (i, k) a2[i] += a1[i];
    forn (i, k) b2[i] += b1[i];

    vll r = karatsubaMultiply(a2, b2);
    forn (i, sz(a1b1)) r[i] -= a1b1[i];
    forn (i, sz(a2b2)) r[i] -= a2b2[i];
    forn (i, sz(r)) res[i + k] += r[i];
    forn (i, sz(a1b1)) res[i] += a1b1[i];
    forn (i, sz(a2b2)) res[i + n] += a2b2[i];
    return res;
  }
  BigInt operator*(const BigInt& v) const {
    vi a6 = convertBase(this->z, BASE_DIGITS, 6);
    vi b6 = convertBase(v.z, BASE_DIGITS, 6);
    vll a(all(a6)), b(all(b6));
    while (sz(a) < sz(b)) a.pb(0);
    while (sz(b) < sz(a)) b.pb(0);
    while (sz(a) & (sz(a) - 1)) a.pb(0), b.pb(0);
    vll c = karatsubaMultiply(a, b);
    BigInt res;
    res.sign = sign * v.sign;
    int carry = 0;
    forn (i, sz(c)) {
      ll cur = c[i] + carry;
      res.z.push_back((int) (cur % 1000000));
      carry = (int) (cur / 1000000);
    }
    res.z = convertBase(res.z, 6, BASE_DIGITS);
    res.trim();
    return res;
  }
};

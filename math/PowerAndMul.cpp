template <typename T>
inline T add(T a, T b, T mod) {
  a += b;
  return a >= mod ? a - mod : a;
}

template <typename T>
inline T sub(T a, T b, T mod) {
  a -= b;
  return a < 0 ? a + mod : a;
}

template <typename T>
T mul(T a, T b, T mod) {
  return T((a * 1ll * b) % mod);
}

template <>
ll mul<ll>(ll a, ll b, ll mod) {
  ll q = ll((ld) a * b / mod);
  ll r = a * b - mod * q;
  while (r < 0) r += mod;
  while (r >= mod) r -= mod;
  return r;
}

template <typename T>
T power(T a, T n, T mod) {
  if (!n) return 1;
  T b = power(a, n / 2, mod);
  b = mul(b, b, mod);
  return n & 1 ? mul<T>(a, b, mod) : b; 
}

int powerFast(int a, int n, int mod) {
  int res = 1;
  while (n) {
    if (n & 1) res = mul(res, a, mod);
    a = mul(a, a, mod);
    n /= 2;
  }
  return res;
}

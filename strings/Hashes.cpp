const int P = 239017, MOD_X = 1e9 + 7, MOD_Y = 1e9 + 9;

inline int add(int a, int b, int m) {
	a += b;
	return a >= m ? a - m : a;
}

inline int sub(int a, int b, int m) {
	a -= b;
	return a < 0 ? a + m : a;
}

inline int mul(int a, int b, int m) {
	return (a * 1ll * b) % m;
}

// using H = unsigned long long;
struct H {
	int x, y;
	H() = default;
	H(int _x): x(_x), y(_x) {}
	H(int _x, int _y): x(_x), y(_y) {}
	inline H operator+(const H& h) const { return H(add(x, h.x, MOD_X), add(y, h.y, MOD_Y)); }
	inline H operator-(const H& h) const { return H(sub(x, h.x, MOD_X), sub(y, h.y, MOD_Y)); }
	inline H operator*(const H& h) const { return H(mul(x, h.x, MOD_X), mul(y, h.y, MOD_Y)); }
	inline bool operator==(const H& h) const { return x == h.x && y == h.y; }
};

H p[N], h[N];

inline H get(int l, int r) { return h[r] - h[l] * p[r - l]; }

void init(const string& s) {
	int n = sz(s);
	deg[0] = 1;
	forn (i, n)
		h[i + 1] = h[i] * P + s[i], p[i + 1] = p[i] * P;
}

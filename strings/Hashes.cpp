const int P = 239017;

inline int add(int a, int b, int m) {
	a += b;
	return a >= m ? a - m : a;
}

inline int sub(int a, int b, int m) {
	a -= b;
	return a < 0 ? a + m : a;
}
         
const int MOD_X = 1e9 + 9, MOD_Y = 1e9 + 7;

// using H = unsigned long long;
struct H {
	int x, y;
	H(): x(0), y(0) {}
	H(int _x): x(_x), y(_x) {}
	H(int _x, int _y): x(_x), y(_y) {}
	inline H operator+(const H& h) const { return H(add(x, h.x, MOD_X), add(y, h.y, MOD_Y)); }
	inline H operator-(const H& h) const { return H(sub(x, h.x, MOD_X), sub(y, h.y, MOD_Y)); }
	inline H operator*(ll k) const { return H(int((x * k) % MOD_X), int((y * k) % MOD_Y)); }
	inline H operator*(const H& h) const{ return H(int((ll(x) * h.x) % MOD_X), int((ll(y) * h.y) % MOD_Y)); }
	inline bool operator==(const H& h) const { return x == h.x && y == h.y; }
	inline bool operator!=(const H& h) const { return x != h.x || y != h.y; }
	inline bool operator<(const H& h) const { return x < h.x || (x == h.x && y < h.y); }
	explicit inline operator ll() const { return ll(x) * MOD_Y + y + 1; } // > 0
};

H deg[MAX_N], h[MAX_N];

inline H get(int l, int r) { return h[r] - h[l] * deg[r - l]; }

void init(const string& s) {
	int n = sz(s);
	deg[0] = 1;
	forn (i, n)
		h[i + 1] = h[i] * P + s[i], deg[i + 1] = deg[i] * P;
}
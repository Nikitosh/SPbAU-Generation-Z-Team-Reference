ll a[4][MAX_N][MAX_N];
int n, m;

inline int f(int x) { return x & ~(x - 1); }

inline void add(int k, int x, int y, ll val) {
	for (; x <= n; x += f(x))
		for (int j = y; j <= m; j += f(j))
			a[k][x][j] += val;
}

inline ll get(int k, int x, int y) {
	ll s = 0;
	for (; x > 0; x -= f(x))
		for (int j = y; j > 0; j -= f(j))
			s += a[k][x][j];
	return s;
}

inline ll get(int x, int y) {
	return ll(x + 1) * (y + 1) * get(0, x, y) - (y + 1) * get(1, x, y) 
	    - (x + 1) * get(2, x, y) + get(3, x, y);
}

inline void add(int x, int y, ll val) {
	add(0, x, y, val);
	add(1, x, y, val * x);
	add(2, x, y, val * y);
	add(3, x, y, val * x * y);
}

inline ll get(int x_1, int y_1, int x_2, int y_2) {
	return get(x_2, y_2) - get(x_1 - 1, y_2) - get(x_2, y_1 - 1) + get(x_1 - 1, y_1 - 1);
}

// Adds val to corresponding rectangle
inline void add(int x_1, int y_1, int x_2, int y_2, ll val) {
	add(x_1, y_1, val);
	if (y_2 < m) add(x_1, y_2 + 1, -val);
	if (x_2 < n) add(x_2 + 1, y_1, -val);
	if (x_2 < n && y_2 < m) add(x_2 + 1, y_2 + 1, val);
}

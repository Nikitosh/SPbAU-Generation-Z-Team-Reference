struct Line {
	int k, b;
	Line() {}
	Line(int _k, int _b): k(_k), b(_b) {}
	ll get(int x) { return b + k * 1ll * x; }
	bool operator<(const Line &l) const { return k < l.k; } // change to > in case of different order
};

// Checks if intersection of (a, b) is on the left from (a, c).
inline bool check(Line a, Line b, Line c) { 
	return (a.b - b.b) * 1ll * (c.k - a.k) < (a.b - c.b) * 1ll * (b.k - a.k);
}

struct Convex {
	vector<Line> st;
	inline void add(Line l) {
		while (sz(st) >= 2 && !check(st[sz(st) - 2], st[sz(st) - 1], l))
			st.pop_back();
		st.pb(l);
	}
	int get(int x) {
		int l = 0, r = sz(st);
		while (r - l > 1) {
			int m = (l + r) / 2; // change to > in case of different order
			if (st[m - 1].get(x) < st[m].get(x))
				l = m;
			else
				r = m;
		}
		return l;
	}
	Convex() {}
	Convex(vector<Line> &lines) {
		st.clear();
		for(Line &l : lines)
			add(l);
	}
	Convex(Line line) { st.pb(line); }
	Convex(const Convex &a, const Convex &b) {
		vector<Line> lines;
		lines.resize(sz(a.st) + sz(b.st));
		merge(all(a.st), all(b.st), lines.begin());
		st.clear();
		for(Line &l : lines)
			add(l);
	}
};

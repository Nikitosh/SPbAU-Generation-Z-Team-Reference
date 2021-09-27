struct Vertex {
	int suf, len, next[ALPHA];
	Vertex() { fill(next, next + ALPHA, 0); }
};

int vn, v;
Vertex t[N + 2];
int n, s[N];

int get(int i) { return i < 0 ? -1 : s[i]; }

void init() {
	t[0].len = -1, vn = 2, v = 0, n = 0;
}

void add(int ch) {
	s[n++] = ch;
	while (v != 0 && ch != get(n - t[v].len - 2)) 
		v = t[v].suf;
	int& r = t[v].next[ch];
	if (!r) {
		t[vn].len = t[v].len + 2;
		if (!v) t[vn].suf = 1;
		else {
			v = t[v].suf;
			while (v != 0 && ch != get(n - t[v].len - 2)) 
				v = t[v].suf;
			t[vn].suf = t[v].next[ch];
		}
		r = vn++;
	}
	v = r;
}

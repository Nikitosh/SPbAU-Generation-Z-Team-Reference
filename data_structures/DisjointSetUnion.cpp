int pr[N]; 	

int get(int v) {
	return v == pr[v] ? v : pr[v] = get(pr[v]);
}

bool unite(int v, int u) {
	v = get(v), u = get(u);
	if (v == u) return 0;
	pr[u] = v;
	return 1;
}

void init(int n) {
	forn (i, n) pr[i] = i;
}

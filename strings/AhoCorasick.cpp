const int ALPHA = 26;
const int MAX_N = 1e5;

struct Node {
	int next[ALPHA], term; // Бор
	int go[ALPHA], suf, p, pCh; // Автомат
	Node(): term(0), suf(-1), p(-1) {
		fill(next, next + ALPHA, -1);
		fill(go, go + ALPHA, -1);
	}
};

Node g[MAX_N];
int last;

void add(const string &s) {
	int now = 0;
	for(char x : s) { 
		if (g[now].next[x - 'a'] == -1) {
			g[now].next[x - 'a'] = ++last;
			g[last].p = now, g[last].pCh = x;
		} 
		now = g[now].next[x - 'a'];
	}
	g[now].term = 1;
}

int go(int v, int c);

int getLink(int v) {
	if (g[v].suf == -1) { 
		if (!v || !g[v].p) g[v].suf = 0;
		else g[v].suf = go(getLink(g[v].p), g[v].pCh);
	}
	return g[v].suf;
}

int go(int v, int c) {
	if (g[v].go[c] == -1) {
		if (g[v].next[c] != -1) g[v].go[c] = g[v].next[c];
		else g[v].go[c] = !v ? 0 : go(getLink(v), c);
	}
	return g[v].go[c];
}

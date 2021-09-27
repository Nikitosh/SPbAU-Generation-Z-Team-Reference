int used[N];

struct Edge {
 	ll l;
 	Edge() {}
 	Edge(int _l): l(_l) {}
};

vector<pair<int, Edge>> g[N], rev[N], path;
pair<int, Edge> pr[N];

void dfsInit(int v, int p, Edge prE) {
	used[v] = 1;
	pr[v] = mp(p, prE);
	for (auto e : g[v]) {
		int u = e.fst;
		if (u == p)
			continue;
		if (used[u] == 1)
			rev[u].pb(mp(v, e.snd));
		else if (used[u] != 2)
			dfsInit(u, v, e.snd);
	}
	used[v] = 2;
}

void calc(int v) {
	used[v] = 1;
	for (auto e : rev[v]) {
 		path.clear();
 		int u = e.fst;
 	 	while (u != v) {
 	 	 	calc(u);
 	 	 	path.pb(mp(u, pr[u].snd));
 	 	 	u = pr[u].fst;
 	 	}
 	 	// Calculate answer for cycle -- path and vertex v
 	}
 	for (auto e : g[v])
 		if (!used[e.fst] && e.fst != pr[v].fst) {
 			calc(e.fst);
 			// Update answer for tree edges
 		}
}

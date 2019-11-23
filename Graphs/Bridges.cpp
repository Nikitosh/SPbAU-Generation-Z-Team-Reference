int up[MAX_N], tIn[MAX_N], timer;
vector<vi> comps;
vi st;

struct Edge {
	int to, id;
	Edge(int _to, int _id) : to(_to), id(_id) {}
};

vector<Edge> g[MAX_N];

void newComp(int size = 0) {
	comps.emplace_back(); // новая пустая
	while (sz(st) > size) {
		comps.back().pb(st.back());
		st.pop_back();
	}
}

void findBridges(int v, int parentEdge = -1) {
	if (up[v]) // уже были
		return;
	up[v] = tIn[v] = ++timer;
	st.pb(v);
	for (Edge e : g[v]) {
		if (e.id == parentEdge)
			continue;
		int u = e.to;
		if (!tIn[u]) {
			int size = sz(st);
			findBridges(u, e.id);
			if (up[u] > tIn[v])
				newComp(size);
		}
		up[v] = min(up[v], up[u]);
	}
}

// после вызова find_bridges newComp() для корня
void run(int n) {
	forn (i, n) 
		if (!up[i]) {
			findBridges(i);
			newComp();
		}	
}

//for directed unweighted graph
struct Edge {
    int v, u, c, f;
    Edge() {}
    Edge(int v, int u, int c): v(v), u(u), c(c), f(0) {}
};

vector <Edge> edges;

inline void addFlow(int e, int flow) {
 	edges[e].f += flow;
 	edges[e ^ 1].f -= flow;
}

inline void addEdge(int v, int u, int c) {
    g[v].pb(sz(edges));
    edges.pb(Edge(v, u, c));
    g[u].pb(sz(edges));
    edges.pb(Edge(u, v, 0)); //for undirected 0 should be c
}

void read(int m) {
 	forn (i, m) {
 	 	int v, u, c;
 	 	scanf("%d%d%d", &v, &u, &c);
 	 	addEdge(v - 1, u - 1, c);
 	}
}
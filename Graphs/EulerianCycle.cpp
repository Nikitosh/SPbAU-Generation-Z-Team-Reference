struct Edge {
	int to, used;
	Edge(): to(-1), used(0) {}	
	Edge(int v): to(v), used(0) {}
};

vector <Edge> edges; 
vector <int>  g[MAX_N], res, ptr;
//не забывать чистить ptr

void dfs(int v) {
	for(; ptr[v] < sz(g[v]);) {
		int id = g[v][ptr[v]++];
		if (!edges[id].used) {
			edges[id].used = edges[id ^ 1].used = 1;
			dfs(edges[id].to); 
//			res.pb(id); // для ребер
		}
	}
	res.pb(v); // в res вершины
}

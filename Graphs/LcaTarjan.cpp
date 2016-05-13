namespace LcaTarjan {
    vi g[MAX_N], q[MAX_N];
    int pr[MAX_N], rank[MAX_N], ancestor[MAX_N], used[MAX_N];

    int get(int v) {
     	return v == pr[v] ? v : pr[v] = get(pr[v]);
    }

    void unite(int v, int u, int anc) {
		v = get(v), u = get(u);
		if (rank[v] < rank[u])
			swap(v, u);
		if (rank[v] == rank[u])
			rank[v]++;
		pr[u] = v;
		ancestor[v] = anc; 	
    }

    void dfs(int v) {
    	used[v] = 1;
     	for (int u : g[v])
     		if (!used[u])
     			dfs(u), unite(v, u, v);
		for (int u : q[v])
			if (used[u])
				ancestor[get(u)]; //handle answer somehow
    }

  	void init(int n) {
		forn (i, n)
			pr[i] = i, ancestor[i] = i, rank[i] = 0;			
		dfs(0);
  	}
};
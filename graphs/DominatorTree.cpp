// clean: forn(i, n+1)!!!
vi adj[N], ans[N]; // input edges, edges of dominator tree
vi radj[N], child[N], sdomChild[N];
int label[N], rlabel[N], sdom[N], dom[N], co = 0;
int par[N], bes[N]; 
int get(int x) { // DSU with path compression
	// get vertex with smallest sdom on path to root
	if (par[x] != x) {
		int t = get(par[x]); par[x] = par[par[x]];
		if (sdom[t] < sdom[bes[x]]) bes[x] = t;
	}
	return bes[x];
} 
void dfs(int x) { // create DFS tree
	label[x] = ++co; rlabel[co] = x; 
	sdom[co] = par[co] = bes[co] = co;
	for(auto y : adj[x]) {
		if (!label[y]) {
			dfs(y); child[label[x]].pb(label[y]); }
		radj[label[y]].pb(label[x]);
	}
}
void init(int root) {
	dfs(root);
	for(int i = co; i >= 1; i--) {
		for(auto j : radj[i]) sdom[i] = min(sdom[i], sdom[get(j)]);
		if (i > 1) sdomChild[sdom[i]].pb(i);
		for(auto j : sdomChild[i]) {
			int k = get(j);
			if (sdom[j] == sdom[k]) dom[j] = sdom[j];
			else dom[j] = k;
		}
		for(auto j : child[i]) par[j] = i;
	}
	forab(i,2,co+1) {
		if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
		ans[rlabel[dom[i]]].pb(rlabel[i]);
	}
}

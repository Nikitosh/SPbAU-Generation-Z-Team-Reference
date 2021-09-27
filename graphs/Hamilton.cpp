// DP in O(n*2^n) for Ham cycle
vi g[MASK];
int adj[MASK], dp[1 << MASK];

vi hamiltonCycle(int n) {
	fill(dp, dp + (1 << n), 0);
	forn (v, n) {
		adj[v] = 0;
		for (int to : g[v])
			adj[v] |= (1 << to);
	}
	dp[1] = 1;
	forn (mask, (1 << n)) 
		forn(v, n)
			if (mask & (1 << v) && dp[mask ^ (1 << v)] & adj[v])
				dp[mask] |= (1 << v);
	vi ans;
	int mask = (1 << n) - 1, v; 
	if (dp[mask] & adj[0]) {
		forab (i, 1, n)
			if ((1 << i) & (mask & adj[0]))
				v = i;
		ans.pb(v);
		mask ^= (1 << v);
		while(v) {
			forn(i, n)
				if ((dp[mask] & (1 << i)) && (adj[i] & (1 << v))) {
					v = i;
					break;
				} 
			mask ^= (1 << v);
			ans.pb(v);
		}
	}
	return ans;
}

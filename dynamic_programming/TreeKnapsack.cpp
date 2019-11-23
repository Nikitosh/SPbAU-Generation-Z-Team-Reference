int dp[MAX_N][MAX_N], a[MAX_N];
vi g[MAX_N];

int dfs(int v, int n) {
	forn (i, n + 1)
		dp[v][i] = -INF;
	dp[v][1] = a[v];
	int curSz = 1;
	for (int to : g[v]) {
		int toSz = dfs(to, n);
		for (int i = curSz; i >= 1; i--)
			fornr (j, toSz + 1)
				dp[v][i + j] = max(dp[v][i + j], dp[v][i] + dp[to][j]);
		curSz += toSz;
	}
	return curSz;
}

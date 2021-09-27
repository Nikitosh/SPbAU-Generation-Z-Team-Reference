int pr[N], d[N], q[N], first[N];

int dfs(int v, int can, int toPush, int t) {
	if (v == t) return can;
	int sum = 0;
	for (; first[v] < (int) g[v].size(); first[v]++) {
		auto &e = edges[g[v][first[v]]];
		if (d[e.u] != d[v] + 1 || e.c - e.f < toPush) continue;
		int flow = dfs(e.u, min(can, e.c - e.f), toPush, t);
		addFlow(g[v][first[v]], flow);
		can -= flow, sum += flow;
		if (!can)
		return sum;
	}
	return sum;
}

bool bfs(int n, int s, int t, int curPush) {
	forn (i, n) d[i] = INF, first[i] = 0;
	int head = 0, tail = 0;
	q[tail++] = s;
	d[s] = 0;
	while (tail - head > 0) {
		int v = q[head++];
		for (int edge : g[v]) {
			auto &e = edges[edge];
			if (d[e.u] > d[v] + 1 && e.c - e.f >= curPush)
				d[e.u] = d[v] + 1, q[tail++] = e.u;		
		}
	}
	return d[t] != INF;
}
				  
int dinic(int n, int s, int t) {
	int ansFlow = 0;
	// Without scaling
	while (bfs(n, s, t, 1))
		ansFlow += dfs(s, INF, 1, t);
	// With scaling
	fornr (j, INF_LOG)
		while (bfs(n, s, t, 1 << j))
			ansFlow += dfs(s, INF, 1 << j, t);
	return ansFlow;
}

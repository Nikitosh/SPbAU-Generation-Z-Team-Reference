namespace EdmondsKarp {
	int used[MAX_N], pr[MAX_N], d[MAX_N], q[MAX_N], maxFlow[MAX_N];
	vi g[MAX_N];

	#include "Utilities.cpp"

	int edmondsKarp(int n, int m, int s, int t) {
		read(m);
		int ansFlow = 0;
		while(1) {
			for (int i = 0; i < n; i++)
				d[i] = INF, maxFlow[i] = 0;
			int head = 0, tail = 0;
			q[tail++] = s;
			d[s] = 0;
			maxFlow[s] = INF;
			while (tail - head > 0) {
				int v = q[head++];
				for (int edge : g[v]) {
					auto &e = edges[edge];
					if (d[e.u] > d[v] + 1 && e.c - e.f > 0) {
						d[e.u] = d[v] + 1;
						maxFlow[e.u] = min(maxFlow[e.v], e.c - e.f);
						q[tail++] = e.u;
						pr[e.u] = edge;
					}
				}
			}
			if (d[t] == INF)
				break;
			for (int u = t; u != s; u = edges[pr[u]].v)
				addFlow(pr[u], maxFlow[t]);
			ansFlow += maxFlow[t];
		}
		return ansFlow;
	}
}
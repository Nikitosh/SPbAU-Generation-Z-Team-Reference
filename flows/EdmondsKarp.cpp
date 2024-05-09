int used[N], pr[N], d[N], q[N], maxFlow[N];

int edmondsKarp(int n, int s, int t) {
  int ansFlow = 0;
  while (1) {
    forn (i, n) d[i] = INF, maxFlow[i] = 0;
    int head = 0, tail = 0;
    q[tail++] = s;
    d[s] = 0;
    maxFlow[s] = INF;
    while (tail - head > 0) {
      int v = q[head++];
      for (int edge : g[v]) {
        auto &e = edges[edge];
        if (d[e.u] > d[v] + 1 && e.c - e.f > 0) {
          d[e.u] = d[v] + 1, q[tail++] = e.u, pr[e.u] = edge;
          maxFlow[e.u] = min(maxFlow[e.v], e.c - e.f);
        }
      }
    }
    if (d[t] == INF) break;
    for (int u = t; u != s; u = edges[pr[u]].v) {
      addFlow(pr[u], maxFlow[t]);
    }
    ansFlow += maxFlow[t];
  }
  return ansFlow;
}

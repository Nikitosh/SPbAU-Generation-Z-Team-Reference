int used[N], pr[N];
int curTime = 1;

int dfs(int v, int can, int toPush, int t) {
  if (v == t) return can;
  used[v] = curTime;
  for (int edge : g[v]) {
    auto &e = edges[edge];
    if (used[e.u] != curTime && e.c - e.f >= toPush) {
      int flow = dfs(e.u, min(can, e.c - e.f), toPush, t);
      if (flow > 0) {
        addFlow(edge, flow), pr[e.u] = edge;
        return flow;
      }
    }
  }
  return 0;
}

int fordFulkerson(int s, int t) {
  int ansFlow = 0, flow = 0;
  // Without scaling
  while ((flow = dfs(s, INF, 1, t)) > 0) {
    ansFlow += flow, curTime++;
  }
  // With scaling
  fornr (i, INF_LOG) {
    for (curTime++; (flow = dfs(s, INF, (1 << i), t)) > 0; curTime++) {
      ansFlow += flow;
    }
  }
  return ansFlow;
}

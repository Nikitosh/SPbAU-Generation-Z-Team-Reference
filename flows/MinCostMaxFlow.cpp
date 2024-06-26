int pr[N], in[N], q[N * M], used[N], d[N], pot[N];
vi g[N];

struct Edge {
  int v, u, c, f, w;
  Edge() {}
  Edge(int _v, int _u, int _c, int _w): v(_v), u(_u), c(_c), f(0), w(_w) {}
};

vector<Edge> edges;

inline void addFlow(int e, int flow) {
  edges[e].f += flow, edges[e ^ 1].f -= flow;
}

inline void addEdge(int v, int u, int c, int w) {
  g[v].pb(sz(edges)), edges.pb(Edge(v, u, c, w));
  g[u].pb(sz(edges)), edges.pb(Edge(u, v, 0, -w));
}

int dijkstra(int n, int s, int t) {
  forn (i, n) used[i] = 0, d[i] = INF;
  d[s] = 0;
  while (1) {
    int v = -1;
    forn (i, n) {
      if (!used[i] && (v == -1 || d[v] > d[i])) {
        v = i;
      }
    }
    if (v == -1 || d[v] == INF) break;
    used[v] = 1;
    for (int edge : g[v]) {
      auto &e = edges[edge];
      int w = e.w + pot[v] - pot[e.u];
      if (e.c > e.f && d[e.u] > d[v] + w) {
        d[e.u] = d[v] + w, pr[e.u] = edge;
      }
    }
  }
  if (d[t] == INF) return d[t];
  forn (i, n) pot[i] += d[i];
  return pot[t];
}

int fordBellman(int n, int s, int t) {
  forn (i, n) d[i] = INF;
  int head = 0, tail = 0;
  d[s] = 0, q[tail++] = s, in[s] = 1;
  while (tail - head > 0) {
    int v = q[head++];
    in[v] = 0;
    for (int edge : g[v]) {
      auto &e = edges[edge];
      if (e.c > e.f && d[e.u] > d[v] + e.w) {
        d[e.u] = d[v] + e.w;
        pr[e.u] = edge;
        if (!in[e.u]) {
          in[e.u] = 1, q[tail++] = e.u;
        }
      } 
    }
  }
  return d[t];
}

int minCostMaxFlow(int n, int s, int t) {
  int ansFlow = 0, ansCost = 0, dist;
  while ((dist = dijkstra(n, s, t)) != INF) {
    int curFlow = INF;
    for (int cur = t; cur != s; cur = edges[pr[cur]].v) {
      curFlow = min(curFlow, edges[pr[cur]].c - edges[pr[cur]].f); 
    }
    for (int cur = t; cur != s; cur = edges[pr[cur]].v) {
      addFlow(pr[cur], curFlow);
    }
    ansFlow += curFlow;
    ansCost += curFlow * dist;
  }
  return ansCost;
}

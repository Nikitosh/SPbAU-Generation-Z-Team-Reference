int d[N][N], p[N][N];
vi g[N], ans;

struct Edge {
  int a, b, w;
  Edge(int _a, int _b, int _w): a(_a), b(_b), w(_w) {}
};

vector<Edge> edges;

void fordBellman(int s, int n) {
  forn (i, n + 1) {
    forn (j, n + 1) {
      d[i][j] = INF;
    }
  }
  d[0][s] = 0;
  forab (i, 1, n + 1) {
    for (auto &e : edges) {
      if (d[i - 1][e.a] < INF && d[i][e.b] > d[i - 1][e.a] + e.w) {
        d[i][e.b] = d[i - 1][e.a] + e.w, p[i][e.b] = e.a;
      }
    }
  }
}

ld karp(int n) {
  int s = n++;
  forn (i, n - 1) {
    g[s].pb(sz(edges)), edges.pb(Edge(s, i, 0));
  }
  fordBellman(s, n);
  ld ansValue = INF;
  int curV = -1, dist = -1;
  forn (v, n - 1) {
    if (d[n][v] != INF) {
      ld curAns = -INF;
      int curPos = -1;
      forn(k, n) {
        if (curAns <= (d[n][v] - d[k][v]) * (ld) (1) / (n - k)) {
          curAns = (d[n][v] - d[k][v]) * (ld) (1) / (n - k), curPos = k;
        }
      }
      if (ansValue > curAns) {
        ansValue = curAns, dist = curPos, curV = v;
      }
    }
  }
  if (curV == -1) return ansValue;
  for (int iter = n; iter != dist; iter--) {
    ans.pb(curV), curV = p[iter][curV];
  }
  reverse(all(ans));
  return ansValue;
}

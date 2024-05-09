int tin[N], tout[N], up[N][LOG], curTime = 0;;
vi g[N];

void dfs(int v, int p) {
  up[v][0] = p;
  forn (i, LOG - 1) up[v][i + 1] = up[up[v][i]][i];
  tin[v] = curTime++;
  for (int u : g[v]) if (u != p) dfs(u, v);
  tout[v] = curTime++;
}

int isUpper(int v, int u) {
  return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int lca(int v, int u) {
  if (isUpper(u, v)) return u;
  fornr (i, LOG) {
    if (!isUpper(up[u][i], v)) u = up[u][i];
  }
  return up[u][0];
}

void init() {
  dfs(0, 0);
}

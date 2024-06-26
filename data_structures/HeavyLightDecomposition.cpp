vi g[N];
int size[N], comp[N], num[N], top[N], pr[N], tin[N], tout[N];
vi t[N], toPush[N], lst[N];
int curPath = 0, curTime = 0;

void pushST(int path, int v, int vl, int vr) {
  if (toPush[path][v] != -1) {
    if (vl != vr - 1) {
      forn (j, 2) toPush[path][2 * v + j] = toPush[path][v];
    } else { 
      t[path][v] = toPush[path][v]; 
    }
    toPush[path][v] = -1;
  }
}

int getST(int path, int v, int vl, int vr, int ind) {
  pushST(path, v, vl, vr);
  if (vl == vr - 1) return t[path][v];
  int vm = (vl + vr) / 2;
  if (ind >= vm) return getST(path, 2 * v + 1, vm, vr, ind);
  return getST(path, 2 * v, vl, vm, ind);
}

void setST(int path, int v, int vl, int vr, int l, int r, int val) {
  if (vl >= l && vr <= r) {
    toPush[path][v] = val;
    pushST(path, v, vl, vr);
    return;
  }
  pushST(path, v, vl, vr);
  if (vl >= r || l >= vr) return;
  int vm = (vl + vr) / 2;
  setST(path, 2 * v, vl, vm, l, r, val);
  setST(path, 2 * v + 1, vm, vr, l, r, val);
  t[path][v] = min(t[path][2 * v], t[path][2 * v + 1]);
}

bool isUpper(int v, int u) {
  return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int getHLD(int v) { 
  return getST(comp[v], 1, 0, sz(t[comp[v]]) / 2, num[v]);
}

int setHLD(int v, int u, int val) {
  int ans = 0, w = 0;
  forn (i, 2) {
    while (!isUpper(w = top[comp[v]], u)) {
      setST(comp[v], 1, 0, sz(t[comp[v]]) / 2, 0, num[v] + 1, val), v = pr[w];
    }
    swap(v, u);
  }
  setST(comp[v], 1, 0, sz(t[comp[v]]) / 2, min(num[v], num[u]), max(num[v], num[u]) + 1, val);
  return ans;
}

void dfs(int v, int p) {
  tin[v] = curTime++;
  size[v] = 1;
  pr[v] = p;
  for (int u : g[v]) {
    if (u != p) {
      dfs(u, v);
      size[v] += size[u];
    }
  }
  tout[v] = curTime++;
}

void build(int v) {
  if (v == 0 || size[v] * 2 < size[pr[v]]) { 
    top[curPath] = v, comp[v] = curPath, num[v] = 0, curPath++;
  } else {
    comp[v] = comp[pr[v]], num[v] = num[pr[v]] + 1;
  }
  lst[comp[v]].pb(v);
  for (int u : g[v]) {
    if (u != pr[v]) build(u);
  }
}

void initHLD() {
  dfs(0, 0);
  build(0);
  forn (i, curPath) {
    int curSize = 1;
    while (curSize < sz(lst[i])) curSize *= 2;
    t[i].resize(curSize * 2);
    toPush[i] = vi(curSize * 2, -1);
    //initialize t[i]
  }
}

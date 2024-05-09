mt19937 rng(239017);
template<int SZ> struct UnweightedMatch {
  int match[SZ], N; 
  vi adj[SZ];

  void ae(int u, int v) { 
    adj[u].pb(v);
    adj[v].pb(u); 
  }
 
  queue<int> q;
  int par[SZ], vis[SZ], orig[SZ], aux[SZ];
 
  void augment(int u, int v) { // toggle edges on u-v path
    while (1) { // one more matched pair
      int pv = par[v], nv = match[pv];
      match[v] = pv; match[pv] = v;
      v = nv; if (u == pv) return;
    }
  }
 
  int lca(int u, int v) { // find LCA of supernodes in O(dist)
    static int t = 0;
    for (++t;; swap(u, v)) {
      if (!u) continue;
      if (aux[u] == t) return u; // found LCA
      aux[u] = t; u = orig[par[match[u]]];
    }
  }
 
  void blossom(int u, int v, int a) { // go other way
    for (; orig[u] != a; u = par[v]) { // around cycle
      par[u] = v; v = match[u]; // treat u as if vis[u] = 1
      if (vis[v] == 1) vis[v] = 0, q.push(v);
      orig[u] = orig[v] = a; // merge into supernode
    }
  }
 
  bool bfs(int u) { // u is initially unmatched
    forn (i, N + 1) {
      par[i] = 0, vis[i] = -1, orig[i] = i;
    }
    q = queue<int>(); 
    vis[u] = 0;
    q.push(u);
    while (sz(q)) { // each node is pushed to q at most once
      int v = q.front(); q.pop(); // 0 -> unmatched vertex
      for (int x : adj[v]) {
        if (vis[x] == -1) { // neither of x, match[x] visited
          vis[x] = 1; par[x] = v;
          if (!match[x]) return augment(u, x), 1;
          vis[match[x]] = 0;
          q.push(match[x]);
        } else if (vis[x] == 0 && orig[v] != orig[x]) {
          int a = lca(orig[v], orig[x]); // odd cycle
          blossom(x, v, a), blossom(v, x, a); 
        } // contract O(n) times
      }
    }
    return 0;
  }
 
  int calc(int _N) { // rand matching -> constant improvement
    N = _N; 
    forn (i, N + 1) match[i] = aux[i] = 0; 
    int ans = 0; vi V(N); iota(all(V),1); shuffle(all(V),rng); // find rand matching
    for (int x : V) {
      if (!match[x]) { 
        for (int y : adj[x]) {
          if (!match[y]) { 
            match[x] = y, match[y] = x; ++ans; 
            break; 
          }
        }
      }
    }
    forab (i, 1, N + 1) {
      if (!match[i] && bfs(i)) ans++;
    }
    return ans;
  }
};

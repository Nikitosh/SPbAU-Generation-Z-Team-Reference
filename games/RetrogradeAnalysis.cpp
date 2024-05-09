int win[N], lose[N], outDeg[N];
vi rg[N];

void retro(int n) {
  queue<int> q;
  forn (i, n) {
    if (!outDeg[i]) {
      lose[i] = 1, q.push(i);
    }
  }
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int to : rg[v]) {
      if (lose[v]) {
        if (!win[to]) win[to] = 1, q.push(to);
      } else {
        outDeg[to]--;
        if (!outDeg[to]) lose[to] = 1, q.push(to);
      }
    }
  }
}

struct Edge {
    int fr, to, w, id;
    bool operator < (const Edge& o) const { return w < o.w; }
};

// find oriented mst (tree)
// there are no edge --> root (root is 0)
// 0 .. n - 1, weights and vertices will be changed, but ids are ok
vector<Edge> work(const vector<vector<Edge>>& graph) {
    int n = (int) graph.size();
    vector<int> color(n), used(n, -1);
    for (int i = 0; i < n; i++)
        color[i] = i;
    vector<Edge> e(n);
    for (int i = 0; i < n; i++) {
        if (graph[i].empty()) {
            e[i] = {-1, -1, -1, -1};
        } else {
            e[i] = *min_element(graph[i].begin(), graph[i].end());
        }
    }
    vector<vector<int>> cycles;
    used[0] = -2;
    for (int s = 0; s < n; s++) {
        if (used[s] != -1)
            continue;
        int x = s;
        while (used[x] == -1) {
            used[x] = s;
            x = e[x].fr;
        }
        if (used[x] != s)
            continue;
        vector<int> cycle = {x};
        for (int y = e[x].fr; y != x; y = e[y].fr)
            cycle.push_back(y), color[y] = x;
        cycles.push_back(cycle);
    }
    if (cycles.empty())
        return e;
    vector<vector<Edge>> next_graph(n);
    for (int s = 0; s < n; s++) {
        for (const Edge& edge : graph[s]) {
            if (color[edge.fr] != color[s])
                next_graph[color[s]].push_back({
                    color[edge.fr], color[s], edge.w - e[s].w, edge.id
                });
        }
    }
    vector<Edge> tree = work(next_graph);
    for (const auto& cycle : cycles) {
        int cl = color[cycle[0]];
        Edge next_out = tree[cl], out{};
        int from = -1;
        for (int v : cycle) {
            tree[v] = e[v];
            for (const Edge& edge : graph[v])
                if (edge.id == next_out.id)
                    from = v, out = edge;
        }
        tree[from] = out;
    }
    return tree;
}

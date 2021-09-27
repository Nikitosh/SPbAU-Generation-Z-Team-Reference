bool used[M];
int tIn[N], timer, isCut[N], color[M], compCnt;
vi st;

struct Edge {
	int to, id;
	Edge(int _to, int _id) : to(_to), id(_id) {}
};

vector<Edge> g[N];

int dfs(int v, int parent = -1) {
	tIn[v] = ++timer;
	int up = tIn[v], x = 0, y = (parent != -1);
	for (Edge p : g[v]) {
		int u = p.to, id = p.id;
		if (id != parent) {
			int t, size = sz(st);
			if (!used[id])
				used[id] = 1, st.push_back(id);
			if (!tIn[u]) { // not visited yet
				t = dfs(u, id);
				if (t >= tIn[v]) {
					++x, ++compCnt;
					while (sz(st) != size) {
						color[st.back()] = compCnt;
						st.pop_back();
					}
				}
			} else
				t = tIn[u];
			up = min(up, t);
		}
	}
	if (x + y >= 2)
		isCut[v] = 1; // v is cut vertex
	return up;
}

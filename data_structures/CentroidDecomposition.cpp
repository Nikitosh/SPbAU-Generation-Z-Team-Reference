vi g[N];
int d[N], par[N], centroid; 
//d and par - in centroid tree

int find(int v, int p, int total) {
	int size = 1, ok = 1;
	for (int to : g[v]) 
		if (d[to] == -1 && to != p) {
			int s = find(to, v, total);
			if (s > total / 2) ok = 0;
			size += s;
		}
	if (ok && size > total / 2) centroid = v;
	return size;
}

void calcInComponent(int v, int p, int level) {
	// do something
	for (int to : g[v])
		if (d[to] == -1 && to != p)
			calcInComponent(to, v, level);
}

//fill(d, d + n, -1)
//decompose(0, -1, 0)
void decompose(int root, int parent, int level) {  
	find(root, -1, find(root, -1, INF));
	int c = centroid;
	par[c] = parent, d[c] = level;
	calcInComponent(centroid, -1, level);
	for (int to : g[c])
		if (d[to] == -1)
			decompose(to, c, level + 1);
}

// sz(LEFT) = n, sz(RIGHT) = m
// numbered consequently
int n, m, paired[2 * N], used[2 * N];
vi g[N];

bool dfs(int v) {
	if (used[v]) return false;
	used[v] = 1;
	for (int to : g[v]) 
		if (paired[to] == -1 || dfs(paired[to])) {
			paired[to] = v, paired[v] = to;
			return true;
		}
	return false;
}

int kuhn() {
	int ans = 0;
	forn (i, n + m) paired[i] = -1;
	for (int run = 1; run;) { 
		run = 0;
		fill(used, used + n + m, 0);
		forn(i, n) 
			if (!used[i] && paired[i] == -1 && dfs(i))
				ans++, run = 1;
	}
	return ans;
}

// Start from unpaired vertex in Left part, go from Left anywhere, from Right only to pair
// Max Independent -- A+, B-
// Min Cover       -- A-, B+ 

vi minCover, maxIndependent;

void dfsCoverIndependent(int v) {
	if (used[v]) return;
	used[v] = 1;
	for (int to : g[v]) 
		if (!used[to])
			used[to] = 1, dfsCoverIndependent(paired[to]);
}

// Kuhn first!
void findCoverIndependent() {
	fill(used, used + n + m, 0);
	forn (i, n)
		if (paired[i] == -1)
			dfsCoverIndependent(i);
	forn (i, n)
		if (used[i]) maxIndependent.pb(i);
		else minCover.pb(i);
	forab (i, n, n + m)
		if (used[i]) minCover.pb(i);
		else maxIndependent.pb(i);
}

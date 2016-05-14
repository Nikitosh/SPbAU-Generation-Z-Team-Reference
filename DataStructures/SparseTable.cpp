namespace SparseTable {
	int st[MAX_N][MAX_LOG];
	int lg[MAX_N];

	int get(int l, int r) { //[l, r)
		int curLog = lg[r - l];
		return min(st[l][curLog], st[r - (1 << curLog)][curLog]);
	}

	void initSparseTable(int *a, int n) {
		lg[1] = 0;
		forab (i, 2, n + 1)
			lg[i] = lg[i / 2] + 1;
		forn (i, n)
			st[i][0] = a[i];
		forn (i, lg[n])
			forn (j, n - (1 << (i + 1)) + 1)
				st[j][i + 1] = min(st[j][i], st[j + (1 << i)][i]);
	}
}
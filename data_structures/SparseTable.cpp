int st[N][LOG];
int lg[N];

int get(int l, int r) { // [l, r)
	int curLog = lg[r - l];
	return min(st[l][curLog], st[r - (1 << curLog)][curLog]);
}

void initSparseTable(int *a, int n) {
	lg[1] = 0;
	forab (i, 2, n + 1) lg[i] = lg[i / 2] + 1;
	forn (i, n) st[i][0] = a[i];
	forn (j, lg[n])
		forn (i, n - (1 << (j + 1)) + 1)
			st[i][j + 1] = min(st[i][j], st[i + (1 << j)][j]);
}

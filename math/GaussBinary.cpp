const int MAX = 1024;

int gaussBinary(vector<bitset<MAX>> a, int n, int m) {
	int row = 0, col = 0;
	vi par(m, -1);
	for (col = 0; col < m && row < n; col++) {
		int best = row;
		for (int i = row; i < n; i++)
			if (a[i][col] > a[best][col])
				best = i;
		if (a[best][col] == 0)
			continue;
		par[col] = row;
		swap(a[row], a[best]);
		forn (i, n)
			if (i != row && a[i][col])
					a[i] ^= a[row];
		row++;
	}
	vi ans(m, 0);
	forn (i, m)
		if (par[i] != -1)
			ans[i] = a[par[i]][n] / a[par[i]][i];
	bool ok = 1;
	forn (i, n) {
		int cur = 0;
		forn (j, m) cur ^= (ans[j] & a[i][j]);
		if (cur != a[i][n]) ok = 0;
	}
	return ok;
}

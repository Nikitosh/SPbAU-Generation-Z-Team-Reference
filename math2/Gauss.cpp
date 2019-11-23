const double EPS = 1e-9;

int gauss(double **a, int n, int m) { // n is number of equations, m is number of variables
	int row = 0, col = 0;
	vi par(m, -1);
	vector<double> ans(m, 0);
	for (col = 0; col < m && row < n; col++) {
		int best = row;
		for (int i = row; i < n; i++)
			if (abs(a[i][col]) > abs(a[best][col]))
				best = i;
		if (abs(a[best][col]) < EPS)
			continue;
		par[col] = row;
		forn (i, m + 1)
			swap(a[row][i], a[best][i]);
		forn (i, n)
			if (i != row) {
				double k = a[i][col] / a[row][col];
				for (int j = col; j <= m; j++)
					a[i][j] -= k * a[row][j];
			}
		row++;
	}
	int single = 1;
	forn (i, m)
		if (par[i] != -1)
			ans[i] = a[par[i]][m] / a[par[i]][i];
		else
			single = 0;
	forn (i, n) {
		double cur = 0;
		for (int j = 0; j < m; j++)
			cur += ans[j] * a[i][j];
		if (abs(cur - a[i][m]) > EPS)
			return 0;
	}
	if (!single)
		return 2;
	return 1;
}
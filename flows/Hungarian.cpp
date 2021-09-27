const int INF = 1e9;
int a[N][N];

// min = sum of a[pa[i],i]
// you may optimize speed by about 15%, just change all vectors to static arrays
vi Hungarian(int n) {
	vi pa(n + 1, -1), row(n + 1, 0), col(n + 1, 0), la(n + 1);
	forn (k, n) {
		vi u(n + 1, 0), d(n + 1, INF);
		pa[n] = k;
		int l = n, x;
		while ((x = pa[l]) != -1) {
			u[l] = 1;
			int minn = INF, tmp, l0 = l;
			forn (j, n)
				if (!u[j]) {
					if ((tmp = a[x][j] + row[x] + col[j]) < d[j])
						d[j] = tmp, la[j] = l0;
					if (d[j] < minn)
						minn = d[j], l = j;
				}
			forn (j, n + 1)
				if (u[j])
					col[j] += minn, row[pa[j]] -= minn;
				else
					d[j] -= minn;
		}
		while (l != n)
			pa[l] = pa[la[l]], l = la[l];
	}
	return pa;
}

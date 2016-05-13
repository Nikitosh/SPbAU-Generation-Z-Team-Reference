namespace Math {
    const int MAX = 1024;

    int gaussMod2(vector<bitset<MAX>> a, int n, int m) {
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
            for (int i = 0; i < n; i++)
                if (i != row) {
                    if (a[i][col])
                        a[i] ^= a[row];
                }
            row++;
        }
        vi ans(m, 0);
        for (int i = 0; i < m; i++)
            if (par[i] != -1)
                ans[i] = a[par[i]][n] / a[par[i]][i];
        bool ok = 1;
        for (int i = 0; i < n; i++) {
            int cur = 0;
            for (int j = 0; j < m; j++)
                cur ^= (ans[j] & a[i][j]);
            if (cur != a[i][n])
                ok = 0;
        }
    	return ok;
    }
}            
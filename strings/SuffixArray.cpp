int sLen, num[MAX_N + 1];
char s[MAX_N + 1];
int p[MAX_N], col[MAX_N], inv[MAX_N], lcp[MAX_N];

inline int mod(int x) {
	return (x + sLen) % sLen;
}

void buildArray(int n) {
	sLen = n;
	int ma = max(n, 256);
	forn (i, n)
		col[i] = s[i], p[i] = i;

	for (int k2 = 1; k2 / 2 < n; k2 *= 2) {
		int k = k2 / 2;
		memset(num, 0, sizeof(num));
		forn (i, n)
			num[col[i] + 1]++;
		forn (i, ma) 
			num[i + 1] += num[i];
		forn (i, n) 
			inv[num[col[mod(p[i] - k)]]++] = mod(p[i] - k);
		int cc = 0;
		forn (i, n) {
			bool add = col[inv[i]] != col[inv[i - 1]];
			add |= col[mod(inv[i] + k)] != col[mod(inv[i - 1] + k)];
			if (i && add) 
				cc++;
			num[inv[i]] = cc;
		}
		forn (i, n) 
			p[i] = inv[i], col[i] = num[i];
	}
 
	memset(num, 0, sizeof(num));
	forn (i, n)
		num[col[i] + 1]++;
	forn (i, ma)
		num[i + 1] += num[i];
	forn (i, n)
		inv[num[col[i]]++] = i;
	forn (i, n)
		p[i] = inv[i];
	forn (i, n) 
		inv[p[i]] = i;
}

void buildLCP(int n) {
	int len = 0;
	forn (ind, n){
		int i = inv[ind];
		len = max(0, len - 1);
		if (i != n - 1)
			while (len < n && s[mod(p[i] + len)] == s[mod(p[i + 1] + len)]) 
				len++;
		lcp[i] = len;
		if (i != n - 1 && p[i + 1] == n - 1) 
			len = 0;
	}
}

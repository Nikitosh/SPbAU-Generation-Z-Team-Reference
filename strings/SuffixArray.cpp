const int MAX_N = 250000;

int n, num[MAX_N + 1];
char s[MAX_N + 1];
int p[MAX_N], col[MAX_N], p2[MAX_N], len[MAX_N];

void BuildArray(){
	int ma = max(n, 256);
	forn(i, n)
		col[i] = s[i], p[i] = i;

	for (int k2 = 1; k2 / 2 < n; k2 *= 2){
		int k = k2 / 2;
		memset(num, 0, sizeof(num));
		forn(i, n)
			num[col[i] + 1]++;
		forn(i, ma)
			num[i + 1] += num[i];
		forn(i, n)
			p2[num[col[(p[i] - k + n) % n]]++] = (p[i] - k + n) % n;

		int cc = 0;
		forn(i, n){
			if (i && (col[p2[i]] != col[p2[i - 1]] ||
			col[(p2[i] + k) % n] != col[(p2[i - 1] + k) % n]))
				cc++;
			num[p2[i]] = cc;
		}
		forn(i, n)
			p[i] = p2[i], col[i] = num[i];
	}
 
	// make it stable
	memset(num, 0, sizeof(num));
	forn(i, n)
		num[col[i] + 1]++;
	forn(i, ma)
		num[i + 1] += num[i];
	forn(i, n)
		p2[num[col[i]]++] = i;
	forn(i, n)
		p[i] = p2[i];

	// calc inverse permutation
	forn(i, n)
		p2[p[i]] = i;
}

void BuildLCP(){
	int lcp = 0;
	forn(i, n){
		int j = p2[i];
		lcp = max(0, lcp - 1);
		if (j != n - 1)
			while (lcp < n && s[(p[j] + lcp) % n] == s[(p[j + 1] + lcp) % n])
				lcp++;
		len[j] = lcp;
		if (j != n - 1 && p[j + 1] == n - 1)
			lcp = 0;
	}
}

int main()
{
	scanf("%d%s", &n, s);

	BuildArray();
	BuildLCP();

	// res = sum of all LCP[i,i+1]
	LL res = 0;
	forn(i, n)
		res += len[i];
	printf("%.3f\n", (double)res / (n - 1));
	return 0;
}

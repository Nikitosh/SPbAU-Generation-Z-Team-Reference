Num ta[MAX_N], tb[MAX_N], tf[MAX_N], tg[MAX_N];

const int HALF = 15;

void mult(int *a, int *b, int *r, int n, int mod) {
	int tw = (1 << HALF) - 1;
	forn (i, n) {
		int x = int(a[i] % mod);
		ta[i] = Num(x & tw, x >> HALF);
	}
	forn (i, n) {
		int x = int(b[i] % mod);
		tb[i] = Num(x & tw, x >> HALF);
	}
	fft(ta, n);
	fft(tb, n);

	forn (i, n) {
		int j = (n - i) & (n - 1);
		Num a1 = (ta[i] + conj(ta[j])) * Num(0.5, 0);
		Num a2 = (ta[i] - conj(ta[j])) * Num(0, -0.5);
		Num b1 = (tb[i] + conj(tb[j])) * Num(0.5 / n, 0);
		Num b2 = (tb[i] - conj(tb[j])) * Num(0, -0.5 / n);
		tf[j] = a1 * b1 + a2 * b2 * Num(0, 1);
		tg[j] = a1 * b2 + a2 * b1;
	}
	
	fft(tf, n);
	fft(tg, n);

	forn (i, n) {
		ll aa = ll(tf[i].x + 0.5);
		ll bb = ll(tg[i].x + 0.5);
		ll cc = ll(tf[i].y + 0.5);
		r[i] = int((aa + ((bb % mod) << HALF) + ((cc % mod) << (2 * HALF))) % mod);
	}
}

int tc[MAX_N], td[MAX_N];

const int MOD1 = 1.5e9, MOD2 = MOD1 + 1;
void multLL(int *a, int *b, ll *r, int n){
	mult(a, b, tc, n, MOD1);
	mult(a, b, td, n, MOD2);

	forn(i, n)
		r[i] = tc[i] + (td[i] - tc[i] + (ll)MOD2) * MOD1 % MOD2 * MOD1;
}
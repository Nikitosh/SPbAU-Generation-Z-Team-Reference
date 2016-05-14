#include "fft.cpp"
typedef long long LL;

namespace FFT{
	Num ta[MAX_N], tb[MAX_N], tf[MAX_N], tg[MAX_N];

	const int HALF = 15;

	void mult(int *a, int *b, int *r, int N, int mod){
		int tw = (1 << HALF) - 1;
		forn(i, N){
			int x = int(a[i] % mod);
			ta[i] = Num(x & tw, x >> HALF);
		}
		forn(i, N){
			int x = int(b[i] % mod);
			tb[i] = Num(x & tw, x >> HALF);
		}
		fft(ta, N);
		fft(tb, N);

		forn(i, N){
			int j = (N - i) & (N - 1);
			Num a1 = (ta[i] + conj(ta[j])) * Num(0.5, 0);
			Num a2 = (ta[i] - conj(ta[j])) * Num(0, -0.5);
			Num b1 = (tb[i] + conj(tb[j])) * Num(0.5 / N, 0);
			Num b2 = (tb[i] - conj(tb[j])) * Num(0, -0.5 / N);
			tf[j] = a1 * b1 + a2 * b2 * Num(0, 1);
			tg[j] = a1 * b2 + a2 * b1;
		}
		
		fft(tf, N);
		fft(tg, N);

		forn(i, N){
			LL aa = LL(tf[i].x + 0.5);
			LL bb = LL(tg[i].x + 0.5);
			LL cc = LL(tf[i].y + 0.5);
			r[i] = int((aa + ((bb % mod) << 15) + ((cc % mod) << 30)) % mod);
		}
	}

	int tc[MAX_N], td[MAX_N];

	const int MOD1 = 1.5e9, MOD2 = MOD1 + 1;
	void multLL(int *a, int *b, LL *r, int N){
		mult(a, b, tc, N, MOD1);
		mult(a, b, td, N, MOD2);

		forn(i, N)
			r[i] = tc[i] + (td[i] - tc[i] + (LL)MOD2) * MOD1 % MOD2 * MOD1;
	}
}
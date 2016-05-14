#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

void manaker( int n, char *s, int *z0, int *z1 ) {
	forn(t, 2) {
		int *z = t ? z1 : z0, l = -1, r = -1; // [l..r]
		forn(i, n - t) {
			int k = 0;
			if (r > i + t) {
				int j = l + (r - i - t);
				k = min(z[j], j - l);
			}
			while (i - k >= 0 && i + k + t < n && s[i - k] == s[i + k + t])
				k++;
			z[i] = k;
			if (k && i + k + t > r)
				l = i - k + 1, r = i + k + t - 1;
		}
	}
}

const int N = 1e5;

int n, r0[N], r1[N];
char s[N + 1];

int main() {
	assert(freopen("palindrome.in", "rt", stdin));
	assert(freopen("palindrome.out", "wt", stdout));

	gets(s);
	n = strlen(s);
	manaker(n, s, r0, r1);
	cout << accumulate(r0, r0 + n, 0LL) + accumulate(r1, r1 + n, 0LL) - n << endl;
	return 0;
}

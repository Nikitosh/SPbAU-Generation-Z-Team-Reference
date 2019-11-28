/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <iostream>

using namespace std;

// finds min x: 
//		a+k*x mod m \in [l..r]
// 		+k costs pk, -m costs pm
//		l <= r < a, first tries -m then +k 
int go(int a, int k, int m, int pk, int pm, int l, int r) {
	int ans = 0, steps;
	while (1) {
		steps = (a - r + m - 1) / m;
		ans += steps * pm, a -= steps * m;
		if (l <= a) return ans;
		if (!k) return -1;
		steps = (l - a + k - 1) / k;
		ans += steps * pk, a += steps * k;
		if (a <= r) return ans;
		int m1 = m % k, pm1 = (m / k) * pk + pm;
		if (!m1) return -1;
		int k1 = k % m1, pk1 = (k / m1) * pm1 + pk;
		k = k1, m = m1, pk = pk1, pm = pm1; // recursion =)
	}
}

int go(int a, int k, int m, int l, int r) {
	if (a < r)
		a += ((r - a) / m + 1) * m;
	return go(a, k, m, 1, 0, l, r);
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);

	int a, k, m, l, r;
	while (cin >> a >> k >> m >> l >> r)
		cout << go(a, k, m, l, r) << '\n';
}

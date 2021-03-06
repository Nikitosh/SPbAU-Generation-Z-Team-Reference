vector <int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23};

bool isPrimeMillerRabin(ll n) {
	int k = 0;
	ll t = n - 1;
	while (t % 2 == 0) k++, t /= 2;
	for (auto p : primes) {
		ll g = __gcd(n, (ll) p);
		if (g > 1 && g < n) return 0;
		if (g == n) return 1;
		ll b = powerLL(p, t, n), last = n - 1;
		bool was = 0;
		forn (i, k + 1) {
			if (b == 1 && last != n - 1)
				return 0;
			if (b == 1) {
				was = 1;
				break;	
			}
			last = b, b = mul(b, b, n);
		}
		if (!was) return 0;
	}
	return 1;
}

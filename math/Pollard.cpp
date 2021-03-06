inline void pollardFoo(ll& x, ll mod) {
	x = (mul(x, x, mod) + 1) % mod;
}

vector<pair<ll, int>> factorize(ll n) {
	if (n == 1) return {};
	if (isPrimeMillerRabin(n)) return {mp(n, 1)};
	if (n <= 100) {
		vector<pair<ll, int>> ans;
		for (int i = 2; i * i <= n; i++)
			if (n % i == 0) {
				int cnt = 0;
				while (n % i == 0) n /= i, cnt++;
				ans.pb(mp(i, cnt));	
			}
		if (n != 1) ans.pb(mp(n, 1));
		sort(all(ans));
		return ans;
	}
	while (1) {
		ll a = rand() % n, b = a;
		while (1) {
			pollardFoo(a, n), pollardFoo(b, n), pollardFoo(b, n);
			ll g = __gcd(abs(a-b), n);
			if (g != 1) {
				if (g == n)
					break;
				auto ans1 = factorize(g);
				auto ans2 = factorize(n / g);
				vector<pair<ll, int>> ans;
				ans1.insert(ans1.end(), all(ans2));
				sort(all(ans1));
				for (auto np : ans1)
					if (sz(ans) == 0 || np.fst != ans.back().fst)
						ans.pb(np);
					else
						ans.back().snd += np.snd;
				return ans;
			}
		}
	}
	assert(0);
}

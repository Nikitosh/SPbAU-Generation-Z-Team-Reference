ull pollard(ull n) { // return some nontrivial factor of n
	auto f = [n](ull x) { return mul(x, x, n) + 1; };
	ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	while (t++ % 40 || __gcd(prd, n) == 1) { /// speedup: don't take gcd every it
		if (x == y) x = ++i, y = f(x);
		if ((q = mul(prd, max(x, y) - min(x, y), n))) prd = q;
		x = f(x), y = f(f(y));
	}
	return __gcd(prd, n);
}

void factorize(ull n, map<ull,int>& cnt) {
	if (n == 1) return;
	if (isPrimeMillerRabin(n)) { 
		++cnt[n]; 
		return; 
	}
	ull u = pollard(n);
	factorize(u, cnt), factorize(n / u, cnt);
}
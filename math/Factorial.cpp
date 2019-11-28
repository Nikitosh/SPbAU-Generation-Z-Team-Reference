// Returns pair (rem, deg), where rem = n! % mod, 
// deg = k: mod^k | n!, mod is prime, O(mod log mod)
pii fact(int n, int mod) { 
	int rem = 1, deg = 0, nCopy = n;
	while (nCopy) nCopy /= mod, deg += nCopy;
	while (n > 1) {
		rem = (rem * ((n / mod) % 2 ? -1 : 1) + mod) % mod;
		for (int i = 2; i <= n % mod; i++)
			rem = (rem * 1ll * i) % mod;
		n /= mod;
	}
	return mp(rem % mod, deg);
}
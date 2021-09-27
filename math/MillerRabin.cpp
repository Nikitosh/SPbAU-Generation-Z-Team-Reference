bool isPrimeMillerRabin(ull n) { // not ll!
	if (n < 2 || n % 6 % 4 != 1) 
		return n - 2 < 2;
	ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
	ull s = __builtin_ctzll(n - 1), d = n >> s;
	for (ull a : A) {   // ^ count trailing zeroes
		ull p = power(a, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--) 
			p = mul(p, p, n);
		if (p != n - 1 && i != s) return 0;
	}
	return 1;
}
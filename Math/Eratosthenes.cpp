vi eratosthenes(int n) {
	vi minDiv(n + 1, 0);
	minDiv[1] = 1;
	forab (i, 2, n + 1)
		if (minDiv[i] == 0) 
			for (int j = i; j <= n; j += i)
				if (minDiv[j] == 0)
					minDiv[j] = i; 
	return minDiv;
}

vi eratosthenesLinear(int n) {
	vi minDiv(n + 1, 0);
	vi primes;
	minDiv[1] = 1;
	forab (i, 2, n + 1) {
		if (minDiv[i] == 0) {
			minDiv[i] = i;
			primes.pb(i);
		}
		for (int j = 0; j < sz(primes) && primes[j] <= minDiv[i] && i * primes[j] <= n; j++)
			minDiv[i * primes[j]] = primes[j];
	}	
	return minDiv;
}
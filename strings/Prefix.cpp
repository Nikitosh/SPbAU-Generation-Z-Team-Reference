vi prefix(const string &s) {
	int n = sz(s);
	vi pr(n);
	forab (i, 1, n + 1) {
		int j = pr[i - 1];
		while (j > 0 && s[i] != s[j]) j = pr[j - 1];
		if (s[i] == s[j]) j++;
		pr[i] = j;	
	}
	return pr;
}

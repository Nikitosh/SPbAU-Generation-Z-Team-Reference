int t[N];

int get(int ind) {
	int res = 0;
	for (; ind >= 0; ind &= (ind + 1), ind--)
		res += t[ind];
	return res;
}

void add(int ind, int n, int val) {
	for (; ind < n; ind |= (ind + 1))	
		t[ind] += val;
}

int sum(int l, int r) { // [l, r)
	return get(r - 1) - get(l - 1);
}

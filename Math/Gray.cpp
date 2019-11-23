int gray(int n) {
	return n ^ (n >> 1); 					
}

int revGray(int n) {
	int k = 0;
	for (; n; n >>= 1)
		k ^= n;
	return k;
}
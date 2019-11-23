inline ll fix(ll a, ll mod) { // a in [0, 2 * mod)
	if (a >= mod)
		a -= mod;
	return a;
}

// Returns (a * b) % mod, 0 <= a < mod, 0 <= b < mod
ll mulSlow(ll a, ll b, ll mod) { 
	if (!b)
		return 0;
	ll c = fix(mulSlow(a, b / 2, mod) * 2, mod);
	return b & 1 ? fix(c + a, mod) : c;
}

ll mul(ll a, ll b, ll mod) {
	ll q = (ld) a * b / mod;
	ll r = a * b - mod * q;
	while (r < 0)
		r += mod;
	while (r >= mod)
		r -= mod;
	return r;
}

int power(int a, int n, int mod) {
	if (!n) 
		return 1;
	int b = power(a, n / 2, mod);
	b = (b * 1ll * b) % mod;
	return n & 1 ? (a * 1ll * b) % mod : b; 
}

ll powerLL(ll a, ll n, ll mod) {
	if (!n) 
		return 1;
	ll b = power(a, n / 2, mod);
	b = mul(b, b, mod);
	return n & 1 ? mul(a, b, mod) : b; 
}

int powerFast(int a, int n, int mod) {
	int res = 1;
	while (n) {
		if (n & 1)
		res = (res * 1ll * a) % mod;
		a = (a * 1ll * a) % mod;
		n /= 2;
	}
	return res;
}
   

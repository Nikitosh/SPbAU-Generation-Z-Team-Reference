//typedef complex<dbl> Num;
struct Num{
	dbl x, y;
	Num(){}
	Num(dbl _x, dbl _y):x(_x),y(_y){}

	inline dbl real() const{ return x; }
	inline dbl imag() const{ return y; }

	inline Num operator +(const Num &B) const{
		return Num(x+B.x, y+B.y);
	}
	inline Num operator -(const Num &B) const{
		return Num(x-B.x, y-B.y);
	}
	inline Num operator *(dbl k) const{
		return Num(x*k, y*k);
	}
	inline Num operator *(const Num &B) const{
		return Num(x*B.x - y*B.y, x*B.y + y*B.x);
	}

	inline void operator +=(const Num &B){
		x+=B.x, y+=B.y;
	}
	inline void operator /=(dbl k){
		x/=k, y/=k;
	}
	inline void operator *=(const Num &B){
		*this = *this * B;
	}
};

inline Num sqr(const Num &x){ return x * x; }
inline Num conj(const Num &x){ return Num(x.real(), -x.imag()); }

inline int getN(int n){
	int k = 1;
	while(k < n)
		k <<= 1;
	return k;
}

namespace FFT{
	const int LOG = 18;
	const int MAX_N = 1 << LOG;

	Num rt[MAX_N];
	int rev[MAX_N];

	void fft(Num *a, int n){
		assert(rev[1]); // don't forget to init
		int q = MAX_N / n;
		forn(i, n)
			if(i < rev[i] / q)
				swap(a[i], a[rev[i] / q]);
		for(int k = 1; k < n; k <<= 1)
			for(int i = 0; i < n; i += 2 * k)
				forn(j, k){
					const Num z = a[i + j + k] * rt[j + k];
					a[i + j + k] = a[i + j] - z;
					a[i + j] += z;
				}
	}

	void fft_inv(Num *a, int n){
		fft(a, n);
		reverse(a + 1, a + n);
		forn(i, n)
			a[i] /= n;
	}

	void double_fft(Num *a, Num *fa, Num *fb, int n){ // only if you need it
		fft(a, n);
		const int n1 = n - 1;
		forn(i, n){
			const Num &z0 = a[i], &z1 = a[(n - i) & n1];
			fa[i] = Num(z0.real() + z1.real(), z0.imag() - z1.imag()) * 0.5;
			fb[i] = Num(z0.imag() + z1.imag(), z1.real() - z0.real()) * 0.5;
		}
	}

	Num tmp[MAX_N];
	template<class T>
	void mult(T *a, T *b, T *r, int n){ // n = 2^k
		forn(i, n)
			tmp[i] = Num((dbl)a[i], (dbl)b[i]);
		fft(tmp, n);
		const int n1 = n - 1;
		const Num c = Num(0, -0.25 / n);
		fornr(i, n / 2 + 1){
			const int j = (n - i) & n1;
			const Num z0 = sqr(tmp[i]), z1 = sqr(tmp[j]);
			tmp[i] = (z1 - conj(z0)) * c;
			tmp[j] = (z0 - conj(z1)) * c;
		}
		fft(tmp, n);
		forn(i, n)
			r[i] = (T)round(tmp[i].real());
	}

	void init(){ // don't forget to init
		forn(i, MAX_N)
			rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (LOG - 1));

		rt[1] = Num(1, 0);
		for(int k = 1, p = 2; k < LOG; ++k, p *= 2){
			const Num x(cos(M_PI / p), sin(M_PI / p));
			for(int i = p / 2; i < p; ++i)
				rt[2 * i] = rt[i], rt[2 * i + 1] = rt[i] * x;
		}
	}
}
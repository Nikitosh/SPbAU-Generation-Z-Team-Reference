namespace Math {
	double f(double x) {
		return x;
	}	

	double simpson(double a, double b, int iterNumber) {
		double res = 0, h = (b - a) / iterNumber;
		forn (i, iterNumber + 1)
			res += f(a + h * i) * ((i == 0) || (i == iterNumber) ? 1 : ((i & 1) == 0) ? 2 : 4);
		return res * h / 3;
	}
}
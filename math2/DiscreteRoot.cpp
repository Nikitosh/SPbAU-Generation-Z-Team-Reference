// Returns x: x^k = a mod mod, mod is prime
int discreteRoot(int a, int k, int mod) { 
	if (a == 0)
		return 0;
	int g = primitiveRoot(mod);
	int y = discreteLogarithm(power(g, k, mod), a, mod);
	return power(g, y, mod);	
}
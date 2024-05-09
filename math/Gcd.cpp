int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}
    
int gcd(int a, int b, int &x, int &y) {
  if (b == 0) {
    x = 1, y = 0; 
    return a;
  }
  int g = gcd(b, a % b, x, y), newX = y;
  y = x - a / b * y;
  x = newX;
  return g;
}

void diophant(int a, int b, int c, int &x, int &y) {
  int g = gcd(a, b, x, y);
  if (c % g != 0) return;
  x *= c / g, y *= c / g;
  // next solutions: x += b / g, y -= a / g
}

int inverse(int a, int mod) { // Returns -1, if a and mod are not coprime
  int x, y;
  int g = gcd(a, mod, x, y);
  return g == 1 ? (x % mod + mod) % mod : -1;
}

vi inverseForAll(int mod) {
  vi r(mod, 0);
  r[1] = 1;
  for (int i = 2; i < mod; i++) {
    r[i] = (mod - r[mod % i]) * (mod / i) % mod;
  }
  return r;
}

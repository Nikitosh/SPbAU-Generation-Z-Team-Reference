// Returns pair (rem, power), where rem = n! % mod, 
// power = k: mod^k | n!, mod is prime, O(mod log mod)
pii fact(int n, int mod) { 
  int rem = 1, power = 0, nCopy = n;
  while (nCopy) nCopy /= mod, power += nCopy;
  while (n > 1) {
    rem = (rem * ((n / mod) % 2 ? -1 : 1) + mod) % mod;
    for (int i = 2; i <= n % mod; i++) rem = mul(rem, i, mod);
    n /= mod;
  }
  return mp(rem % mod, power);
}

/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <iostream>

using namespace std;

// finds x: 
//    a+k*x mod m --> min, 0 <= x <= r (0 <= a, k < m, 0 <= r)
//    +k costs pk, -m costs pm
//    return r-x
int go(int a, int k, int m, int pk, int pm, int r) {
  if (!k) return r;
  if (a >= k) { // make a: 0 <= a < k
    int add = (m - a + k - 1) / k;
    if ((int64_t) add * pk + pm > r) return r;
    a += (int64_t) add * k - m, r -= add * pk + pm;
  }
  int m1 = m % k, pm1 = (m / k) * pk + pm;
  if (!m1) return r;
  int k1 = k % m1, pk1 = (k / m1) * pm1 + pk;
  if (pm1 * (a / m1) > r) return r % pm1;
  return go(a % m1, k1, m1, pk1, pm1, r - (a / m1) * pm1);
}

// finds x: a+k*x mod m --> min, 0 <= a, k < m, 0 <= r
int go(int a, int k, int m, int r) {
  return r - go(a, k, m, 1, 0, r);
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(0);

  int a, k, m, r;
  while (cin >> a >> k >> m >> r) {
    int x = go(a, k, m, r);
    cout << ((int64_t)x * k + a) % m << ' ' << x << '\n';
  }
}

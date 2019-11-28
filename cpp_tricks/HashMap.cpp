#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

struct chash { // To use most bits rather than just the lowest ones:
	const uint64_t C = ll(2e18 * PI) + 71; // large odd number
	const int RANDOM = 912387491;
	ll operator()(ll x) const { return __builtin_bswap64((x ^ RANDOM) * C); }
};
template<class K, class V> using ht = gp_hash_table<K, V, chash>;
template<class K, class V> V get(ht<K, V>& u, K x) {
	return u.find(x) == end(u) ? 0 : u[x]; 
}

ht<ll, int> h({}, {}, {}, {}, {1<<20});

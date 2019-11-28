#include "header.h"

const int N = 2e5;

struct Pnt {
	int x, y, i;
	bool operator <(const Pnt &p) const { return mp(y, i) < mp(p.y, p.i); }
};

ll d2 = 8e18, d = (ll) sqrt(d2) + 1;
Pnt p[N];

inline ll sqr(int x){
	return (LL)x * x;
}

inline void relax(const Pnt &a, const Pnt &b){
	ll tmp = sqr(a.x - b.x) + sqr(a.y - b.y);
	if (tmp < d2)
		d2 = tmp, d = (LL)(sqrt(d2) + 1 - 1e-9); // round up
}

inline bool xless(const Pnt &a, const Pnt &b){
	return a.x < b.x;
}

int main() {
	int n;
	scanf("%d", &n);
	forn(i, n)
		scanf("%d%d", &p[i].x, &p[i].y), p[i].i = i;
	sort(p, p + n, xless);

	set <Pnt> s;
	int l = 0;
	forn(r, n){
		set<Pnt>::iterator it_r = s.lower_bound(p[r]), it_l = it_r;
		for (; it_r != s.end() && it_r->y - p[r].y < d; ++it_r)
			relax(*it_r, p[r]);
		while (it_l != s.begin() && p[r].y - (--it_l)->y < d)
			relax(*it_l, p[r]);
		s.insert(p[r]);
		while (l <= r && p[r].x - p[l].x >= d)
			s.erase(p[l++]);
	}
	printf("%.9f\n", sqrt(d2));
	return 0;
}

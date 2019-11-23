int sign(dbl a){ return (a > EPS) - (a < -EPS); }

// Checks, if point is inside the segment
inline bool inSeg(const Pnt &p, const Pnt &a, const Pnt &b) {
    return eq((p - a) % (p - b), 0) && leq((p - a) * (p - b), 0);
}

// Checks, if two intervals (segments without ends) intersect AND do not lie on the same line
inline bool subIntr(const Pnt &a, const Pnt &b, const Pnt &c, const Pnt &d){
    return
            sign((b - a) % (c - a)) * sign((b - a) % (d - a)) == -1 &&
            sign((d - c) % (a - c)) * sign((d - c) % (b - c)) == -1;
}

// Checks, if two segments (ends are included) has an intersection
inline bool checkSegInter(const Pnt &a, const Pnt &b, const Pnt &c, const Pnt &d){
    return inSeg(c, a, b) || inSeg(d, a, b) || inSeg(a, c, d) || inSeg(b, c, d) || subIntr(a, b, c, d);
}

inline dbl area(vector<Pnt> p){
    dbl s = 0;
    int n = sz(p);
    p.pb(p[0]);
    forn(i, n)
        s += p[i + 1] % p[i];
    p.pop_back();
    return abs(s) / 2;
}

// Check if point p is inside polygon <n, q[]>
int contains_slow(Pnt p, Pnt *z, int n){
    int cnt = 0;
    forn(j, n){
        Pnt a = z[j], b = z[(j + 1) % n];
        if (inSeg(p, a, b))
            return -1; // border
        if (min(a.y, b.y) - EPS <= p.y && p.y < max(a.y, b.y) - EPS)
            cnt += (p.x < a.x + (p.y - a.y) * (b.x - a.x) / (b.y - a.y));
    }
    return cnt & 1; // 0 = outside, 1 = inside
}


//for convex polygon
//assume polygon is counterclockwise-ordered
bool contains_fast(Pnt p, Pnt *z, int n) {
    Pnt o = z[0];
    if(gr((p - o) % (z[1] - o), 0) || ls((p - o) % (z[n - 1] - o), 0))
        return 0;
    int l = 0, r = n - 1;
    while(r - l > 1){
        int m = (l + r) / 2;
        if(gr((p - o) % (z[m] - o), 0))
            r = m;
        else
            l = m;
    }
    return leq((p - z[l]) % (z[r] - z[l]), 0);
}

// Checks, if point "i" is in the triangle "abc" IFF triangle in CCW order
inline int isInTr(int i, int a, int b, int c){
    return
            gr((p[b] - p[a]) % (p[i] - p[a]), 0) &&
            gr((p[c] - p[b]) % (p[i] - p[b]), 0) &&
            gr((p[a] - p[c]) % (p[i] - p[c]), 0);
}

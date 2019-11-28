inline dbl sqr(dbl x) { return x * x; }

void buildTangent(Pnt p1, dbl r1, Pnt p2, dbl r2, Line &l) { // r1, r2 = radius with sign
    Pnt p = p2 - p1;
    l.c = r1;
    dbl c2 = p.len2(), c1 = sqrt(c2 - sqr(r2));
    l.a = (-p.x * (r1 - r2) + p.y * c1) / c2;
    l.b = (-p.y * (r1 - r2) - p.x * c1) / c2;
    l.c -= l.no() * p1;
    assert(eq(l.d(p1), r1));
    assert(eq(l.d(p2), r2));
}


struct Circle {
    Pnt p;
    dbl r;
};

vector<Pnt> v; // to store intersection

// Intersection of two lines
int line_line(const Line &l, const Line &m){
    dbl z = m.a * l.b - l.a * m.b;
	dbl x = m.c * l.b - l.c * m.b;
	dbl y = m.c * l.a - l.c * m.a;
    if(fabs(z) > EPS){
        v.pb(Pnt(-x/z, y/z));
        return 1;
    }else if(fabs(x) > EPS || fabs(y) > EPS)
        return 0; // parallel lines
    else
        return 2; // same lines
}

// Intersection of Circle and line
int circle_line(const Circle &c, const Line &l){
    dbl d = l.d(c.p);
    if(fabs(d) > c.r + EPS)
        return 0;
    if(fabs(fabs(d) / c.r - 1) < EPS) {
        v.pb(c.p - l.no() * d);
        return 1;
    } else {
        dbl s = sqrt(fabs(sqr(c.r) - sqr(d)));
        v.pb(c.p - l.no() * d + l.no().getRot90() * s);
        v.pb(c.p - l.no() * d - l.no().getRot90() * s);
        return 2;
    }
}

// Intersection of two circles, 3 = inf
int circle_circle(const Circle &a, const Circle &b) {
	if (a.p == b.p && eq(a.r, b.r)) 
		return 3;
	Pnt diff = b.p - a.p;
	dbl dist = diff.len();
	if (ls(a.r + dist, b.r) || ls(b.r + dist, a.r))
		return 0;
	Line line(diff.x * 2, diff.y * 2, a.p.len2() - b.p.len2() + sqr(b.r) - sqr(a.r));
	return circle_line(a, line);
}

// Squared distance between point p and segment [a..b]
dbl dist2(Pnt p, Pnt a, Pnt b){
    if ((p - a) * (b - a) < 0) return (p - a).len2();
    if ((p - b) * (a - b) < 0) return (p - b).len2();
    dbl d = fabs((p - a) % (b - a));
    return d * d / (b - a).len2();
}

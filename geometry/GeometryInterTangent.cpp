inline dbl sqr(dbl x) { return x * x; }

struct Circle {
  Pnt p;
  dbl r;
};

Pnt tangent(Pnt x, Circle y, int t = 0) {
  y.r = abs(y.r); // abs needed because internal calls y.s < 0
  if (y.r == 0) return y.p;
  dbl d = (x - y.p).len();
  Pnt a = (x - y.p) * pow(y.r / d, 2)  + y.p;
  Pnt b = ((x - y.p).getNorm() * sqrt(d * d - y.r * y.r) / d * y.r).bmul(Pnt(0, 1)); 
  return t == 0 ? a+b : a-b;
}

vector<pair<Pnt,Pnt>> external(const Circle &x, const Circle &y) { 
  vector<pair<Pnt,Pnt>> v; 
  if (x.r == y.r) {
    Pnt tmp = ((x.p-y.p).getNorm()*x.r).bmul(Pnt(0,1));
    v.pb(mp(x.p+tmp,y.p+tmp));
    v.pb(mp(x.p-tmp,y.p-tmp));
  } else {
    Pnt p = (x.p*y.r-y.p*x.r)/(y.r-x.r);
    forn(i,2) v.pb(mp(tangent(p,x,i),tangent(p,y,i)));
  }
  return v;
}
vector<pair<Pnt,Pnt>> internal(const Circle &x, const Circle &y) { 
  return external({x.p,-x.r},y); 
}

vector<Pnt> line_line(const Line &l, const Line &m){
  dbl z = m.a * l.b - l.a * m.b;
  dbl x = m.c * l.b - l.c * m.b;
  dbl y = m.c * l.a - l.c * m.a;
  if (fabs(z) > EPS) return {Pnt(-x / z, y / z)};
  else if (fabs(x) > EPS || fabs(y) > EPS) return {}; // parallel lines
  return {Pnt(0, 0), Pnt(0, 0)}; // same lines
}

vector<Pnt> circle_line(const Circle &c, const Line &l){
  dbl d = l.d(c.p);
  if (fabs(d) > c.r + EPS) return {};
  if (fabs(fabs(d) / c.r - 1) < EPS) return {c.p - l.no() * d};
  dbl s = sqrt(fabs(sqr(c.r) - sqr(d)));
  return {c.p - l.no() * d + l.no().getRot90() * s, 
    c.p - l.no() * d - l.no().getRot90() * s};
}

vector<Pnt> circle_circle(const Circle &x, const Circle &y) {
  dbl d = (x.p - y.p).len(), a = x.r, b = y.r; 
  if (eq(d, 0)) { assert(a != b); return {}; }
  dbl C = (a * a + d * d - b * b) / (2 * a * d); 
  if (abs(C) > 1+EPS) return {};
  dbl S = sqrt(max(1 - C * C, 0.)); 
  Pnt tmp = (y.p - x.p) / d * x.r;
  if (eq(S, 0)) return {x.p + tmp.bmul(Pnt(C, 0))};
  return {x.p + tmp.bmul(Pnt(C, S)),x.p + tmp.bmul(Pnt(C, -S))};
}

dbl circle_isect_area(const Circle &x, const Circle &y) {
  dbl d = (x.p - y.p).len(), a = x.r, b = y.r; if (a < b) swap(a, b);
  if (geq(d, a + b)) return 0;
  if (leq(d, a - b)) return PI * b * b;
  dbl ca = acos((a * a + d * d - b * b) / (2 * a * d)), cb = acos((b * b + d * d - a * a) / (2 * b * d));
  return (ca * a * a - 0.5 * a * a * sin(ca * 2)) + (cb * b * b - 0.5 * b * b * sin(cb * 2));
}

// Squared distance between point p and segment [a..b]
dbl dist2(Pnt p, Pnt a, Pnt b){
  if ((p - a) * (b - a) < 0) return (p - a).len2();
  if ((p - b) * (a - b) < 0) return (p - b).len2();
  dbl d = fabs((p - a) % (b - a));
  return d * d / (b - a).len2();
}

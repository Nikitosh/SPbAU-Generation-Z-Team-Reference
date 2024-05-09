const dbl EPS = 1e-9;
const int PREC = 20;
inline bool eq(dbl a, dbl b) { return abs(a-b)<=EPS; }
inline bool gr(dbl a, dbl b) { return a>b+EPS; }
inline bool geq(dbl a, dbl b) { return a>=b-EPS; }
inline bool ls(dbl a, dbl b) { return a<b-EPS; }
inline bool leq(dbl a, dbl b) { return a<=b+EPS; }

struct Pnt {
  dbl x,y;
  Pnt(): x(0), y(0) {}
  Pnt(dbl xx, dbl yy): x(xx), y(yy) {}

  inline Pnt operator +(const Pnt &p) const { return Pnt(x + p.x, y + p.y); }
  inline Pnt operator -(const Pnt &p) const { return Pnt(x - p.x, y - p.y); }
  inline dbl operator *(const Pnt &p) const { return x * p.x + y * p.y; } // ll
  inline dbl operator %(const Pnt &p) const { return x * p.y - y * p.x; } // ll

  inline Pnt operator *(dbl k) const { return Pnt(x * k, y * k); }
  inline Pnt operator /(dbl k) const { return Pnt(x / k, y / k); }
  inline Pnt operator -() const { return Pnt(-x, -y); }

  inline void operator +=(const Pnt &p) { x += p.x, y += p.y; }
  inline void operator -=(const Pnt &p) { x -= p.x, y -= p.y; }
  inline void operator *=(dbl k) { x*=k, y*=k; }

  inline bool operator ==(const Pnt &p) const { return abs(x-p.x)<=EPS && abs(y-p.y)<=EPS; }
  inline bool operator !=(const Pnt &p) const { return abs(x-p.x)>EPS || abs(y-p.y)>EPS; }
  inline bool operator <(const Pnt &p) const { return abs(x-p.x)<=EPS ? y<p.y-EPS : x<p.x; }

  inline dbl angle() const { return atan2(y, x); } // ld
  inline dbl len2() const { return x*x+y*y; } // ll
  inline dbl len() const { return sqrt(x*x+y*y); } // ll, ld
  inline Pnt getNorm() const {
    auto l = len();
    return Pnt(x/l, y/l);
  }
  inline void normalize() {
    auto l = len();
    x /= l, y /= l;
  }

  inline Pnt getRot90() const { // counter-clockwise
    return Pnt(-y, x);
  }
  inline Pnt getRot(dbl a) const { // ld
    dbl si = sin(a), co = cos(a);
    return Pnt(x*co - y*si, x*si + y*co);
  }

  inline void read() {
    int xx, yy;
    cin >> xx >> yy;
    x = xx, y = yy;
  }
  inline void write() const{
    cout << fixed << (double)x << " " << (double)y << '\n';
  }
  Pnt bmul(const Pnt& r) const { 
    return Pnt(x*r.x - y*r.y, y*r.x + x*r.y); 
  }
};

struct Line{
  dbl a, b, c;
  Line(): a(0), b(0), c(0) {}
  // normalizes
  Line(dbl aa, dbl bb, dbl cc) {
    dbl norm = sqrt(aa * aa + bb * bb);
    aa /= norm, bb /= norm, cc /= norm;
    a = aa, b = bb, c = cc;
  }

  Line(const Pnt &A, const Pnt &p){ // it normalizes (a,b), important in d(), normalToP()
    Pnt n = (p-A).getRot90().getNorm();
    a = n.x, b = n.y, c = -(a * A.x + b * A.y);
  }

  inline dbl d(const Pnt &p) const { return a*p.x + b*p.y + c; }
  inline Pnt no() const { return Pnt(a, b); }
  inline Pnt normalToP(const Pnt &p) const { return Pnt(a,b) * (a*p.x + b*p.y + c); }

  inline void write() const{
    cout << fixed << (double) a << " " << (double) b << " " << (double) c << '\n';
  }
};

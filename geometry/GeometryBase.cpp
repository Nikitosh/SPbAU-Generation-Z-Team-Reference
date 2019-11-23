#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef long double LD;
typedef double dbl;

const dbl EPS = 1e-9;
const int PREC = 20;
inline bool eq(dbl a, dbl b){ return abs(a-b)<=EPS; }
inline bool gr(dbl a, dbl b){ return a>b+EPS; }
inline bool geq(dbl a, dbl b){ return a>=b-EPS; }
inline bool ls(dbl a, dbl b){ return a<b-EPS; }
inline bool leq(dbl a, dbl b){ return a<=b+EPS; }

struct Pnt{
    dbl x,y;
    Pnt():x(0),y(0){}
    Pnt(dbl _x,dbl _y):x(_x),y(_y){}

    inline Pnt operator +(const Pnt &B) const{ return Pnt(x+B.x, y+B.y); }
    inline Pnt operator -(const Pnt &B) const{ return Pnt(x-B.x, y-B.y); }
    inline dbl operator *(const Pnt &B) const{ return x*B.x + y*B.y; } // LL
    inline dbl operator %(const Pnt &B) const{ return x*B.y - y*B.x; } // LL

    inline Pnt operator *(dbl k) const{ return Pnt(x*k, y*k); }
    inline Pnt operator /(dbl k) const{ return Pnt(x/k, y/k); }
    inline Pnt operator -() const{ return Pnt(-x, -y); }

    inline void operator +=(const Pnt &B){ x+=B.x, y+=B.y; }
    inline void operator -=(const Pnt &B){ x-=B.x, y-=B.y; }
    inline void operator *=(dbl k){ x*=k, y*=k; }

    inline bool operator ==(const Pnt &B){ return abs(x-B.x)<=EPS && abs(y-B.y)<=EPS; }
    inline bool operator !=(const Pnt &B){ return abs(x-B.x)>EPS || abs(y-B.y)>EPS; }
    inline bool operator <(const Pnt &B){ return abs(x-B.x)<=EPS ? y<B.y-EPS : x<B.x; }

    inline dbl angle() const{ return atan2(y, x); } // LD
    inline dbl len2() const{ return x*x+y*y; } // LL
    inline dbl len() const{ return sqrt(x*x+y*y); } // LL, LD
    inline Pnt getNorm() const{
        auto l = len();
        return Pnt(x/l, y/l);
    }
    inline void normalize(){
        auto l = len();
        x/=l, y/=l;
    }

    inline Pnt getRot90() const{ //counter-clockwise
        return Pnt(-y, x);
    }
    inline Pnt getRot(dbl a) const{ // LD
        dbl si = sin(a), co = cos(a);
        return Pnt(x*co - y*si, x*si + y*co);
    }

    inline void read(){
        int _x,_y;
        scanf("%d%d",&_x,&_y);
        x=_x, y=_y;
    }
    inline void write() const{
        printf("%.*f %.*f ", PREC, (double)x, PREC, (double)y);
    }
};

struct Line{
    dbl a, b, c;
    Line():a(0),b(0),c(0){}
    Line(dbl _a, dbl _b, dbl _c):a(_a),b(_b),c(_c){}

    Line(const Pnt &A, const Pnt &B){ // it normalizes (a,b), important in d(), normalToP()
        Pnt n = (B-A).getRot90().getNorm();
        a = n.x, b = n.y, c = -(a*A.x + b*A.y);
    }

    inline dbl d(const Pnt &p) const{ return a*p.x + b*p.y + c; }
    inline Pnt no() const {return Pnt(a, b);}
    inline Pnt normalToP(const Pnt &p) const{ return Pnt(a,b) * (a*p.x + b*p.y + c); }

    inline void write() const{
        printf("%.*f %.*f %.*f ", PREC, (double)a, PREC, (double)b, PREC, (double)c);
    }
};

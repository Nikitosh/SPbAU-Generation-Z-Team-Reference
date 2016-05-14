#include<bits/stdc++.h>

typedef long long LL;

inline int byMod(int a, int m){
    return a >= m ? a - m : a;
}

const int MX = 1e9 + 9, MY = 1e9 + 7;

//typedef unsigned long long H;
struct H{
    int x, y;
    H(): x(0), y(0){}
    H(int _x): x(_x), y(_x){}
    H(int _x, int _y): x(_x), y(_y){}
    inline H operator +(const H &B) const{return H(byMod(x + B.x, MX), byMod(y + B.y, MY));}
    inline H operator -(const H &B) const{return H(byMod(x + MX - B.x, MX), byMod(y + MY - B.y, MY));}
    inline H operator *(LL k) const{return H(int((x * k) % MX), int((y * k) % MY));}
    inline H operator *(const H &B) const{return H(int((LL(x) * B.x) % MX), int((LL(y) * B.y) % MY));}
    inline bool operator ==(const H &B) const{return x == B.x && y == B.y;}
    inline bool operator !=(const H &B) const{return x != B.x || y != B.y;}
    inline bool operator <(const H &B) const{return x < B.x || (x == B.x && y < B.y);}
    explicit inline operator LL() const{return (LL)x * MY + y + 1;} // > 0
};

const int P = 239017, MAX_N = 1e6 + 10;
H deg[MAX_N], h[MAX_N];
char s[MAX_N];

inline H Get(int a, int l){
    return h[a + l] - h[a] * deg[l];
}

int main(){
#ifdef LOCAL
    assert(freopen("test.in", "r", stdin));
    assert(freopen("test.out", "w", stdout));
#endif

    gets(s);
    int L = strlen(s);
    deg[0] = 1;
    for(int i = 0; i < L; ++i)
        h[i + 1] = h[i] * P + s[i], deg[i + 1] = deg[i] * P;

    return 0;
}

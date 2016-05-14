#define fill(a, x) memset(a, x, sizeof(a))

template<const int N>
struct PalindromeTree {
  struct Vertex {
    int suf, len, next[26];
  };

  int vn, v;
  Vertex t[N + 2];
  int n, s[N];

  int get( int i ) { return i < 0 ? -1 : s[i]; }

  void init() {
    fill(t, 0);
    t[0].len = -1, vn = 2, v = 0, n = 0;
  }

  void add( int ch ) {
    s[n++] = ch;
    while (v != 0 && ch != get(n - t[v].len - 2)) 
      v = t[v].suf;
    int &r = t[v].next[ch];
    if (!r) {
      t[vn].len = t[v].len + 2;
      if (!v)
        t[vn].suf = 1;
      else {
        v = t[v].suf;
        while (v != 0 && ch != get(n - t[v].len - 2)) 
          v = t[v].suf;
        t[vn].suf = t[v].next[ch];
      }
      r = vn++;
    }
    v = r;
  }
};

const int N = 1e5;

PalindromeTree<N> pt;

char s[N + 1];

int main() {
  gets(s);
  int n = strlen(s);
  pt.init();
  forn(i, n) {
    pt.add(s[i] - 'a');
    printf("%d ", pt.vn - 2);
  }
  return 0;
}

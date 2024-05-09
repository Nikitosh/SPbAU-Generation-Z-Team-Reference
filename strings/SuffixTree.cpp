char S[N];
int L;

struct Node;
struct Pos;
typedef Node *pNode;
typedef map<char,pNode> mapt;

struct Node{
  pNode P, link;
  int L, R;
  mapt next;

  Node(): P(NULL), link(this), L(0), R(0) {}
  Node(pNode P_, int L_, int R_): P(P_), link(NULL), L(L_), R(R_) {}

  inline int elen() const { return R - L; }
  inline pNode addEdge(int L_, int R_) { return next[S[L_]] = new Node(this, L_, R_); }
};

struct Pos{
  pNode V;
  int up;
  Pos(): V(NULL), up(0) {}
  Pos(pNode V_, int up_): V(V_), up(up_) {}

  pNode splitEdge() const {
    if (!up) return V;
    int L_ = V->L, M = V->R - up;
    pNode P = V->P, n = new Node(P, L_, M);
    P->next[S[L_]] = n;
    n->next[S[M]] = V;
    V->P = n, V->L = M;
    return n;
  }
  Pos nextChar(char c) const {
    if (up) {
      return S[V->R - up] == c ? Pos(V, up - 1) : Pos();
    } else {
      mapt::iterator it = V->next.find(c);
      return it == V->next.end() ? Pos() : Pos(it->snd, it->snd->elen() - 1);
    }
  }
};

Pos goDown(pNode V, int L_, int R_) {
  if (L_ == R_) return Pos(V, 0);
  while (1) {
    V = V->next[S[L_]];
    L_ += V->elen();
    if (L_ >= R_) return Pos(V, L_ - R_);
  }
}

inline pNode calcLink(pNode &V) {
  if (!V->link) {
    V->link = goDown(V->P->link, V->L + !V->P->P, V->R).splitEdge();
  }
  return V->link;
}

Pos addChar(Pos P, int k) {
  while (1) {
    Pos p = P.nextChar(S[k]);
    if (p.V) return p;
    pNode n = P.splitEdge();
    n->addEdge(k, LEN);
    if (!n->P) return Pos(n, 0);
    P = Pos(calcLink(n), 0);
  }
}

pNode Root;
void make_tree() {
  Root = new Node();
  Pos P(Root, 0);
  forn (i, L) P = addChar(P, i);
}

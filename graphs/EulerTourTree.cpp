mt19937 rng(239);

struct Edge {
 	int v, u;
 	Edge(int _v, int _u): v(_v), u(_u) {}
};

struct Node {
	Node *l, *r, *p;
	Edge e;
	int y, size;
	Node(Edge _e): l(nullptr), r(nullptr), p(this), e(_e), y(rng()), size(1) {}
};

inline int getSize(Node* root) { return root ? root->size : 0; }

inline void recalc(Node* root) { root->size = getSize(root->l) + getSize(root->r) + 1; }

set<pair<int, Node*>> edges[MAX_N];

Node* merge(Node *a, Node *b) {
	if (!a) return b;
	if (!b) return a;
	if (a->y < b->y) {
		a->r = merge(a->r, b);
		if (a->r) a->r->p = a;
		recalc(a);
		return a;
	}
	b->l = merge(a, b->l);
	if (b->l) b->l->p = b;
	recalc(b);
	return b;
}

void split(Node *root, Node *&a, Node *&b, int size) {
	if (!root) {
		a = b = nullptr;
		return;
	}
	int lSize = getSize(root->l);
	if (lSize >= size) {
		split(root->l, a, root->l, size);
		if (root->l) root->l->p = root;
		b = root, b->p = b;
	} else {
		split(root->r, root->r, b, size - lSize - 1);
		if (root->r) root->r->p = root;
		a = root, a->p = a;
		a->p = a;
	}
	recalc(root);
}

inline Node* rotate(Node* root, int k) {
	if (k == 0) return root;
	Node *l, *r;
	split(root, l, r, k);
	return merge(r, l);
}

inline pair<Node*, int> goUp(Node* root) {
	int pos = getSize(root->l);
	while (root->p != root) 
		pos += (root->p->r == root ? getSize(root->p->l) + 1 : 0), root = root->p;
	return mp(root, pos);
}

inline Node* deleteFirst(Node* root) {
	Node* a;
	split(root, a, root, 1);
	edges[a->e.v].erase(mp(a->e.u, a));
	return root;
}

inline Node* getNode(int v, int u) {
	return edges[v].lower_bound(mp(u, nullptr))->snd;
}

inline void cut(int v, int u) {
	auto pV = goUp(getNode(v, u));
	auto pU = goUp(getNode(u, v));
	int l = min(pV.snd, pU.snd), r = max(pV.snd, pU.snd);
	Node *a, *b, *c;
	split(pV.fst, a, b, l); 
	split(b, b, c, r - l);
	deleteFirst(b);
	merge(a, deleteFirst(c));
}

inline pair<Node*, int> getRoot(int v) {
	return !sz(edges[v]) ? mp(nullptr, 0) : goUp(edges[v].begin()->snd);
}

inline Node* makeRoot(int v) {
	auto root = getRoot(v);
	return rotate(root.fst, root.snd);
}

inline Node* makeEdge(int v, int u) {
	Node* e = new Node(Edge(v, u));
	edges[v].insert(mp(u, e));
	return e;
}

inline void link(int v, int u) {
	Node *vN = makeRoot(v), *uN = makeRoot(u);
	merge(merge(merge(vN, makeEdge(v, u)), uN), makeEdge(u, v));
}

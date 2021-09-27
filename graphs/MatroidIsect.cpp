struct Gmat { // graphic matroid
	int V = 0; vector<pii> ed; vi par;
	Gmat(vector<pii> _ed):ed(_ed) {
		map<int,int> m; 
		for(auto &t : ed) m[t.fst] = m[t.snd] = 0;
		for(auto &t : m) t.snd = V++; 
		for(auto &t : ed) t.fst = m[t.fst], t.snd = m[t.snd];
	}
	int p(int v) {
		return par[v] == v ? v : par[v] = p(par[v]);
	}
	bool unite(int v, int u) {
		v = p(v), u = p(u);
		if (v != u) { par[v] = u; return true; }
		return false;
	}
	void clear() { 
		par.resize(V);
		forn(i,V) par[i] = i; 
	}
	void ins(int i) { assert(unite(ed[i].fst,ed[i].snd)); }
	bool indep(int i) { return p(ed[i].fst) != p(ed[i].snd); }
};
struct Cmat { // colorful matroid
	int C = 0; vi col; vi used;
	Cmat(vi _col):col(_col) {for(auto t : col) C = max(C, t+1);}
	void clear() { used.assign(C,0); }
	void ins(int i) { used[col[i]] = 1; }
	bool indep(int i) { return !used[col[i]]; }
};
template<class M1, class M2> struct MatroidIsect {
	int n; vi iset; M1 m1; M2 m2;
	bool augment() {
		vi pre(n+1,-1); queue<int> q({n});
		while (sz(q)) {
			int x = q.front(); q.pop();
			if (iset[x]) {
				m1.clear(); forn(i,n) if (iset[i] && i != x) m1.ins(i);
				forn(i,n) if (!iset[i] && pre[i] == -1 && m1.indep(i))
					pre[i] = x, q.push(i);
			} else {
				auto backE = [&]() { // back edge
					m2.clear(); 
					forn(c,2)forn(i,n) if((x==i||iset[i])&&(pre[i]==-1)==c){
						if (!m2.indep(i))return c?pre[i]=x,q.push(i),i:-1;
						m2.ins(i); }
					return n; 
				};
				for (int y; (y = backE()) != -1;) if (y == n) { 
					for(; x != n; x = pre[x]) iset[x] = !iset[x];
					return 1; }
			}
		}
		return 0;
	}
	MatroidIsect(int _n, M1 _m1, M2 _m2):n(_n), m1(_m1), m2(_m2) {
		iset.assign(n+1,0); iset[n] = 1;
		m1.clear(); m2.clear(); // greedily add to basis
		fornr(i,n) if (m1.indep(i) && m2.indep(i)) 
			iset[i] = 1, m1.ins(i), m2.ins(i); 
		while (augment());
	}
};

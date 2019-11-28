// MAXVAR - 2 * vars
int cntVar = 0, val[MAXVAR], usedSat[MAXVAR], comp[MAXVAR];
vector<int> topsortSat;
 
vector<int> g[MAXVAR], rg[MAXVAR];
 
inline int newVar() {
	cntVar++;
	return (cntVar - 1) * 2;
}
 
inline int Not(int v) {
	return v ^ 1;
}
 
inline void Implies(int v1, int v2) {
	g[v1].pb(v2);
	rg[v2].pb(v1);
}
 
inline void Or(int v1, int v2) {
	Implies(Not(v1), v2);
	Implies(Not(v2), v1);
}
 
inline void Nand(int v1, int v2) {
	Or(Not(v1), Not(v2));
}

inline void setTrue(int v) {
	Implies(Not(v), v);
}
 
void dfs1(int v) {
	usedSat[v] = 1;
	for (int to : g[v]) {
		if (!usedSat[to]) dfs1(to);
	}
	topsortSat.pb(v);
}
 
void dfs2(int v, int c) {
	comp[v] = c;
	for (int to : rg[v]) {
		if (!comp[to]) {
			dfs2(to, c);
		}
	}
}
 
int getVal(int v) {
	return val[v];
}
//cntVar сам следит за числом переменных
bool solveSat() {
	forn(i, 2 * cntVar) usedSat[i] = 0;
	forn(i, 2 * cntVar) {
		if (!usedSat[i]) {
			dfs1(i);
		}
	}
	reverse(all(topsortSat));
	int c = 0;
	for (int v : topsortSat) {
		if (!comp[v]) {
			dfs2(v, ++c);
		}
	}
	forn(i, cntVar) {
		if (comp[2 * i] == comp[2 * i + 1]) return false;
		if (comp[2 * i] < comp[2 * i + 1]) val[2 * i + 1] = 1;
		else val[2 * i] = 1;
	}
	return true;
}


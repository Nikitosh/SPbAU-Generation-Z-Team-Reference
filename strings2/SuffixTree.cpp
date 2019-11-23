const int MAX_L=1e5+10;
char S[MAX_L];
int L;

struct Node;
struct Pos;
typedef Node *pNode;
typedef map<char,pNode> mapt;

struct Node{
	pNode P,link;
	int L,R;
	mapt next;

	Node():P(NULL),link(this),L(0),R(0){}
	Node(pNode P,int L,int R):P(P),link(NULL),L(L),R(R){}

	inline int elen() const{return R-L;}
	inline pNode add_edge(int L,int R){return next[S[L]]=new Node(this,L,R);}
};

struct Pos{
	pNode V;
	int up;
	Pos():V(NULL),up(0){}
	Pos(pNode V,int up):V(V),up(up){}

	pNode split_edge() const{
		if(!up)
			return V;
		int L=V->L, M=V->R-up;
		pNode P=V->P, n=new Node(P,L,M);
		P->next[S[L]]=n;
		n->next[S[M]]=V;
		V->P=n, V->L=M;
		return n;
	}
	Pos next_char(char c) const{
		if(up)
			return S[V->R-up]==c ? Pos(V,up-1) : Pos();
		else{
			mapt::iterator it=V->next.find(c);
			return it==V->next.end() ? Pos() : Pos(it->snd,it->snd->elen()-1);
		}
	}
};

Pos go_down(pNode V,int L,int R){
	if(L==R)
		return Pos(V,0);
	while(1){
		V=V->next[S[L]];
		L+=V->elen();
		if(L>=R)
			return Pos(V,L-R);
	}
}

inline pNode calc_link(pNode &V){
	if(!V->link)
		V->link=go_down(V->P->link,V->L+!V->P->P,V->R).split_edge();
	return V->link;
}

Pos add_char(Pos P,int k){
	while(1){
		Pos p=P.next_char(S[k]);
		if(p.V)
			return p;
		pNode n=P.split_edge();
		n->add_edge(k,MAX_L);
		if(!n->P)
			return Pos(n,0);
		P=Pos(calc_link(n),0);
	}
}

pNode Root;
void make_tree(){
	Root=new Node();
	Pos P(Root,0);
	forn(i,L)
		P=add_char(P,i);
}
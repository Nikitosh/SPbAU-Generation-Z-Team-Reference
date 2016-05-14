const int MAX_N=1002;
LL F[4][MAX_N][MAX_N];
int N,M;

inline int Z(int a){
	return a&~(a-1);
}

inline void add(int k,int x,int y,LL a){
	for(;x<=N;x+=Z(x))
		for(int j=y;j<=M;j+=Z(j))
			F[k][x][j]+=a;
}
inline LL get(int k,int x,int y){
	LL s=0;
	for(;x>0;x-=Z(x))
		for(int j=y;j>0;j-=Z(j))
			s+=F[k][x][j];
	return s;
}

inline LL Get(int a,int b){
	return LL(a+1)*(b+1)*get(0,a,b)-(b+1)*get(1,a,b)
			-(a+1)*get(2,a,b)+get(3,a,b);
}

inline void Add(int a,int b,LL w){
	add(0,a,b,w);
	add(1,a,b,w*a);
	add(2,a,b,w*b);
	add(3,a,b,w*a*b);
}

inline LL Get(int a,int b,int c,int d){
	return Get(c,d)-Get(a-1,d)-Get(c,b-1)+Get(a-1,b-1);
}

inline void Add(int a,int b,int c,int d,LL w){
	Add(a,b,w);
	if(d<M)
		Add(a,d+1,-w);
	if(c<N)
		Add(c+1,b,-w);
	if(c<N && d<M)
		Add(c+1,d+1,w);
}

int main(){
	int Q;
	scanf("%d%d%d",&N,&M,&Q);
	forn(i,Q){
		int type,a,b,c,d;
		scanf("%d%d%d%d%d",&type,&a,&b,&c,&d);
		if(type==1){
			int w;
			scanf("%d",&w);
			Add(a,b,c,d,w);
		}else
			printf(lld"\n",Get(a,b,c,d));
	}
}

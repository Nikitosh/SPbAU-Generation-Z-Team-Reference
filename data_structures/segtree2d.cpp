const int ST_SZ=1<<10, ST_SZ2=2*ST_SZ;

struct Node_1d{
	Node_1d *l,*r;
	LL val,need;
	Node_1d():l(NULL),r(NULL),val(0),need(0){}
	inline void norm(){
		if(l==NULL)
			l=new Node_1d();
		if(r==NULL)
			r=new Node_1d();
	}
	LL Get(int L0,int R0,int L=0,int R=ST_SZ){
		if(L0>=R || L>=R0)
			return 0;
		if(L0<=L && R<=R0)
			return val;
		int a=max(L0,L), b=min(R0,R), M=(L+R)>>1;
		norm();
		return l->Get(L0,R0,L,M)+r->Get(L0,R0,M,R)+need*LL(b-a);
	}
	void Add(int L0,int R0,int x,int L=0,int R=ST_SZ){
		if(L0>=R || L>=R0)
			return;
		if(L0<=L && R<=R0){
			need+=x;
			val+=x*LL(R-L);
			return;
		}
		int M=(L+R)>>1;
		norm();
		l->Add(L0,R0,x,L,M), r->Add(L0,R0,x,M,R);
		val=l->val+r->val+need*(R-L);
	}
};

struct Node_2d{
	Node_2d *l,*r;
	Node_1d *val,*need;
	Node_2d():l(NULL),r(NULL),val(new Node_1d()),need(new Node_1d()){}
	inline void norm(){
		if(l==NULL)
			l=new Node_2d();
		if(r==NULL)
			r=new Node_2d();
	}
	LL Get(int L0,int R0,int L1,int R1,int L=0,int R=ST_SZ){
		if(L0>=R || L>=R0)
			return 0;
		if(L0<=L && R<=R0)
			return val->Get(L1,R1);
		int a=max(L0,L), b=min(R0,R), M=(L+R)>>1;
		norm();
		return l->Get(L0,R0,L1,R1,L,M)+r->Get(L0,R0,L1,R1,M,R)+need->Get(L1,R1)*LL(b-a);
	}
	void Add(int L0,int R0,int L1,int R1,int x,int L=0,int R=ST_SZ){
		if(L0>=R || L>=R0)
			return;
		if(L0<=L && R<=R0){
			need->Add(L1,R1,x);
			val->Add(L1,R1,x*LL(R-L));
			return;
		}
		int a=max(L0,L), b=min(R0,R), M=(L+R)>>1;
		norm();
		l->Add(L0,R0,L1,R1,x,L,M), r->Add(L0,R0,L1,R1,x,M,R);
		val->Add(L1,R1,x*LL(b-a));
	}
};


int main(){
	Node_2d *Z=new Node_2d();

	int x,y,Q;
	scanf("%d%d%d",&x,&y,&Q);
	forn(i,Q){
		int type,a,b,c,d;
		scanf("%d%d%d%d%d",&type,&a,&b,&c,&d);
		--a, --b;
		if(type==1){
			int w;
			scanf("%d",&w);
			Z->Add(a,c,b,d,w);
		}else
			printf(lld"\n",Z->Get(a,c,b,d));
	}
}

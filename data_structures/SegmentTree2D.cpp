int tSize = (1 << 10);

struct Node1D {
	Node1D *l, *r;
	ll val, need;
	Node1D(): l(nullptr), r(nullptr), val(0), need(0) {}
	inline void norm() {
		if(!l) l = new Node1D();
		if(!r) r = new Node1D();
	}
	ll get(int ql, int qr, int vl = 0, int vr = tSize) {
		if(vl >= qr || ql >= vr)
			return 0;
		if(ql <= vl && vr <= qr)
			return val;
		int a = max(vl, ql), b = min(vr, qr), vm = (vl + vr) / 2;
		norm();
		return l->get(ql, qr, vl, vm) + r->get(ql, qr, vm, vr) + need * ll(b - a);
	}
	void add(int ql, int qr, int x, int vl = 0, int vr = tSize) {
		if (ql >= vr || vl >= qr)
			return;
		if (ql <= vl && vr <= qr){
			need += x;
			val += x * ll(vr - vl);
			return;
		}
		int vm = (vl + vr) / 2;
		norm();
		l->add(ql, qr, x, vl, vm), r->add(ql, qr, x, vm, vr);
		val = l->val + r->val + need * (vr - vl);
	}
};

struct Node2D {
	Node2D *l, *r;
	Node1D *val, *need;
	Node2D(): l(nullptr), r(nullptr), val(new Node1D()), need(new Node1D()) {}
	inline void norm() {
		if(!l) l = new Node2D();
		if(!r) r = new Node2D();
	}
	ll get(int ql0, int qr0, int ql1, int qr1, int vl = 0, int vr = tSize) {
		if(vl >= qr0 || ql0 >= vr)
			return 0;
		if(ql0 <= vl && vr <= qr0)
			return val->get(ql1, qr1);
		int a = max(vl, ql0), b = min(vr, qr0), vm = (vl + vr) / 2;
		norm();
		return l->get(ql0, qr0, ql1, qr1, vl, vm) + r->get(ql0, qr0, ql1, qr1, vm, vr) + need->get(ql1, qr1) * ll(b - a);
	}
	void add(int ql0, int qr0, int ql1, int qr1, int x, int vl = 0, int vr = tSize) {
		if (ql0 >= vr || vl >= qr0)
			return;
		if (ql0 <= vl && vr <= qr0){
			need->add(ql1, qr1, x);
			val->add(ql1, qr1, x * ll(vr - vl));
			return;
		}
		int a = max(ql0, vl), b = min(qr0, vr), vm = (vl + vr) / 2;
		norm();
		l->add(ql0, qr0, ql1, qr1, x, vl, vm), r->add(ql0, qr0, ql1, qr1, x, vm, vr);
		val->add(ql1, qr1, x * ll(b - a));
	}
};

#include<bits/stdc++.h>
const int INF=1e9;
using namespace std;

struct Node;
typedef Node *pNode;

struct Node{
    static pNode null;
    pNode l, r;
    int y, val, size, m;

    Node(): l(this), r(this), y(-1), val(INF), size(0), m(INF){}
    Node(int v): l(null), r(null), y(rand()), val(v), size(1), m(v){}

    void calc(){
        size = 1 + l->size + r->size;
        m = min(val, min(l->m, r->m));
    }
};

pNode Node::null = new Node();

void merge(pNode &t, pNode l, pNode r){
    if(l == Node::null)
        t = r;
    else if(r == Node::null)
        t = l;
    else if(l->y < r->y)
        merge(l->r, l->r, r), (t = l)->calc();
    else
        merge(r->l, l, r->l), (t = r)->calc();
}

void split(pNode t, pNode &l, pNode &r, int k){
    if(t == Node::null)
        l = r = t;
    else if(t->l->size >= k)
        split(t->l, l, t->l, k), (r = t)->calc();
    else
        split(t->r, t->r, r, k - t->l->size - 1), (l = t)->calc();
}

void insert(pNode &root, int k, int x){
	pNode r, n = new Node(x);
	split(root, root, r, k);
	merge(root, root, n);
	merge(root, root, r);
}

void erase(pNode &root, int k){
	pNode l, n;
	split(root, l, root, k);
	split(root, n, root, 1);
	merge(root, l, root);
}

pNode build(int k){
    if(k == 1)
        return new Node(0);
    pNode root;
    merge(root, build(k / 2), build((k + 1) / 2));
    return root;
}

void print(pNode t, bool root = 1){
    if(t != Node::null){
        print(t->l, 0);
        printf("%d ", t->val);
        print(t->r ,0);
    }
    if(root)
    	puts("");
}

int main(){
	pNode r=Node::null; // r is an empty tree
	// work with r
}

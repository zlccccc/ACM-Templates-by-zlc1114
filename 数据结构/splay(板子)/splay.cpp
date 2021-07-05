#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=a*a%M) ret=1ll*ret*a%M; return ret;}

int A[maxn];
struct splay_tree {
    struct node {
        int val,min,max,add,size,son[2];//add=lazy
        bool rev;
        void init(int _val) { //开始时T[i].val==a[i-1](线性的);
            val=min=max=_val; size=1;
            if (_val==INF) max=-INF;
            add=son[0]=son[1]=0; rev=0;
        }
    } T[maxn*2]; //内存池
    int fa[maxn*2],root,tot;
    void pushup(int x) {
        T[x].min=T[x].max=T[x].val; T[x].size=1;
        if (T[x].val==INF) T[x].max=-INF;
        if (T[x].son[0]) {
            T[x].min=min(T[x].min,T[T[x].son[0]].min);
            T[x].max=max(T[x].max,T[T[x].son[0]].max);
            T[x].size+=T[T[x].son[0]].size;
        }
        if (T[x].son[1]) {
            T[x].min=min(T[x].min,T[T[x].son[1]].min);
            T[x].max=max(T[x].max,T[T[x].son[1]].max);
            T[x].size+=T[T[x].son[1]].size;
        }
    }
    void pushdown(int x) {
        if (x==0) return;
        if (T[x].add) {
            if (T[x].son[0]) {
                T[T[x].son[0]].val+=T[x].add;
                T[T[x].son[0]].min+=T[x].add;
                T[T[x].son[0]].max+=T[x].add;
                T[T[x].son[0]].add+=T[x].add;
            }
            if (T[x].son[1]) {
                T[T[x].son[1]].val+=T[x].add;
                T[T[x].son[1]].min+=T[x].add;
                T[T[x].son[1]].max+=T[x].add;
                T[T[x].son[1]].add+=T[x].add;
            }
            T[x].add=0;
        }
        if (T[x].rev) {
            if (T[x].son[0]) T[T[x].son[0]].rev^=1;
            if (T[x].son[1]) T[T[x].son[1]].rev^=1;
            swap(T[x].son[0],T[x].son[1]);
            T[x].rev=0;
        }
    }
    void rotate(int x,int kind) { //zig(1->) zag(0<-)都行
        int y=fa[x],z=fa[y];
        T[y].son[!kind]=T[x].son[kind],fa[T[x].son[kind]]=y;
        T[x].son[kind]=y,fa[y]=x;
        T[z].son[T[z].son[1]==y]=x,fa[x]=z;
        pushup(y);
    }
    void splay(int x,int goal) { //node x->goal's son
        if (x==goal) return;
        while (fa[x]!=goal) {
            int y=fa[x],z=fa[y];
            pushdown(z),pushdown(y),pushdown(x);
            int rx=T[y].son[0]==x,ry=T[z].son[0]==y;
            if (z==goal) rotate(x,rx);
            else {
                if (rx==ry) rotate(y,ry);
                else rotate(x,rx);
                rotate(x,ry);
            }
        } pushup(x);
        if (goal==0) root=x;
    }
    int select(int pos) { //getnode
        int u=root;
        pushdown(u);
        while (T[T[u].son[0]].size!=pos) { //这里由于头节点有个-INF 所以不-1
            if (pos<T[T[u].son[0]].size) u=T[u].son[0];
            else {
                pos-=T[T[u].son[0]].size+1;
                u=T[u].son[1];
            } pushdown(u);
        } return u;
    }
//下面是自己写的一点常用?函数
    void update(int l,int r,int val) {
        int u=select(l-1),v=select(r+1);
        splay(u,0); splay(v,u);
        T[T[v].son[0]].min+=val;
        T[T[v].son[0]].max+=val;
        T[T[v].son[0]].val+=val;
        T[T[v].son[0]].add+=val;//lazy
    }
    void reverse(int l,int r) {
        int u=select(l-1),v=select(r+1);
        splay(u,0); splay(v,u);
        T[T[v].son[0]].rev^=1;
    }
    void revolve(int l,int r,int x) { //l~r->循环往后x位
        int u=select(r-x),v=select(r+1);
        splay(u,0); splay(v,u);
        int tmp=T[v].son[0]; T[v].son[0]=0;
        pushup(v); pushup(u);
        u=select(l-1),v=select(l);
        splay(u,0); splay(v,u);
        fa[tmp]=v; T[v].son[0]=tmp;
        pushup(v); pushup(u);
    }
    void cut(int l,int r,int x) { //l~r->去掉的x位置后 //HDU3487
        int u=select(l-1),v=select(r+1);
        splay(u,0); splay(v,u);
        int tmp=T[v].son[0];
        T[v].son[0]=0;
        pushup(v); pushup(u);
        u=select(x); v=select(x+1);
        splay(u,0); splay(v,u);
        fa[tmp]=v; T[v].son[0]=tmp;
        pushup(v); pushup(u);
    }
    int query_min(int l,int r) {
        int u=select(l-1),v=select(r+1);
        splay(u,0); splay(v,u);
        return T[T[v].son[0]].min;
    }

    void insert(int x,int val) {
        int u=select(x),v=select(x+1);
        splay(u,0); splay(v,u);
        ++tot; if (tot==maxn) tot=1;
        T[tot].init(val); fa[tot]=v;
        T[v].son[0]=tot;
        pushup(v); pushup(u);
    }
    void delfree(int x) {//buffer
        if (x==0) return;
        bufs++; if (bufs==maxn) bufs=1;
        nodebuff[bufs]=x;
        delfree(T[x].son[0]);
        delfree(T[x].son[1]);
    }
    void erase(int l,int r) {
        int u=select(l-1),v=select(r+1);
        splay(u,0); splay(v,u);
        delfree(T[v].son[0]);
        T[v].son[0]=0;
        pushup(v); pushup(u);
    }
    void exchange(int l1,int r1,int l2,int r2) { //r1-l1+1?=r2-l2+1  OK
        if (l1>l2) {swap(l1,l2); swap(r1,r2);}
        int u=select(l1-1),v=select(r1+1);
        splay(u,0); splay(v,u);
        int tmp=T[v].son[0]; T[v].son[0]=0;
        pushup(v); pushup(u);
        l2-=T[tmp].size; r2-=T[tmp].size;
        int _u=select(l2-1),_v=select(r2+1);
        splay(_u,0); splay(_v,_u);
        fa[tmp]=_v;
        swap(T[_v].son[0],tmp);
        pushup(_v); pushup(_u);
        u=select(l1-1),v=select(l1);
        splay(u,0); splay(v,u);
        fa[tmp]=v;
        T[v].son[0]=tmp;
        pushup(v); pushup(u);
    }

    int nodebuff[maxn],bufs;//bufs:position
    int build(int l,int r) { //add_list
        if (l>r) return 0;
        ++tot; if (tot==maxn) tot=1;
        int ret=nodebuff[tot];
        int mid=(l+r)/2;
        T[ret].init(A[mid]);
        if (l==r) return ret;
        int ls=build(l,mid-1);
        int rs=build(mid+1,r);
        if (ls) fa[ls]=ret,T[ret].son[0]=ls;
        if (rs) fa[rs]=ret,T[ret].son[1]=rs;
        pushup(ret);
        return ret;
    }
    void init(int n) {
        int i; tot=0;
        REP(i,maxn) nodebuff[i]=i;
        rFOR(i,1,n) A[i+1]=A[i];
        A[1]=A[n+2]=-INF;
        root=build(1,n+2);
        fa[root]=0; T[0].init(-INF);
        fa[0]=0; T[0].son[1]=root; T[0].size=0;
    }
} T;
int n,m,i;
char s[50];
int main() {
}
/*
*/

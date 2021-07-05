

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
#include <cassert>
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
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

const double alpha=0.75;
const int DIM=2;
//树套树
namespace KDT{
    struct point{
        int A[DIM],max[DIM],min[DIM];
        int l,r;int size;
        void init(){
            l=r=0;initval();
        }
        void initval(){
            int i;size=1;
            REP(i,DIM) min[i]=max[i]=A[i];
        }
    }T[maxn*30];int TOT;
    int Cur;
    bool cmp(int x,int y){
        return T[x].A[Cur]<T[y].A[Cur];
    }
    void update(int x){
        int i;T[x].initval();
        int l=T[x].l,r=T[x].r;
        if (l) T[x].size+=T[l].size;
        if (r) T[x].size+=T[r].size;
        REP(i,DIM) {
            if (l){
                T[x].max[i]=max(T[x].max[i],T[l].max[i]);
                T[x].min[i]=min(T[x].min[i],T[l].min[i]);
            }
            if (r){
                T[x].max[i]=max(T[x].max[i],T[r].max[i]);
                T[x].min[i]=min(T[x].min[i],T[r].min[i]);
            }
        }
    }
    int id[maxn],tot;
    void build(int &x,int l,int r,int cur){//should have id
        x=0;if (l>r) return;
        int m=(l+r)/2;Cur=cur;
        nth_element(id+l,id+m,id+r+1,cmp);
        x=id[m];
        build(T[x].l,l,m-1,cur^1);
        build(T[x].r,m+1,r,cur^1);
        update(x);
    }
    void getid(int x){//没有顺序=_=
        id[++tot]=x;
        if (T[x].l) getid(T[x].l);
        if (T[x].r) getid(T[x].r);
    }
    void rebuild(int &x,int cur){
        tot=0;getid(x);
        build(x,1,tot,cur);
    }
    void insert(int &x,int now,int cur){
        if (!x) {x=now;return;}
        Cur=cur;
        if (cmp(now,x)) insert(T[x].l,now,cur^1);
        else insert(T[x].r,now,cur^1);
        update(x);
        if (T[x].size*alpha<max(T[T[x].l].size,T[T[x].r].size)) rebuild(x,cur);
    }
    void addnode(int &x,int px,int py){
        TOT++;T[TOT].A[0]=px;T[TOT].A[1]=py;
        T[TOT].init();insert(x,TOT,0);
    }
    int x0,y0,x1,y1;//check两个=_=
    int check(int x,int y){
        return x0<=x&&x<=x1&&y0<=y&&y<=y1;
    }
    int ok(point &A){
        return check(A.A[0],A.A[1]);
    }
    int allin(point &A){
        return  x0<=A.min[0]&&A.max[0]<=x1&&
                y0<=A.min[1]&&A.max[1]<=y1;
    }
    int allout(point &A){
        return  A.max[0]<x0||x1<A.min[0]||
                A.max[1]<y0||y1<A.min[1];
    }
    int query(int x){
        if (!x) return 0;
        if (allin(T[x])) return T[x].size;
        if (allout(T[x])) return 0;
        int ret=0;
        if (ok(T[x])) ret++;
        if (T[x].size==1) return ret;
        ret+=query(T[x].l);
        ret+=query(T[x].r);
        return ret;
    }
}
const int MAX=1e9+7;
struct Tnode{
    int l,r,KD_root;
    Tnode(){l=r=KD_root=0;}
}T[maxn*30];int cnt;
void update(int &x,int px,int py,int pos,int L,int R){
    if (!x) x=++cnt;
    KDT::addnode(T[x].KD_root,px,py);
    if (L==R) return;
    int mid=(L+R)/2;
    if (pos<=mid) update(T[x].l,px,py,pos,L,mid);
    else update(T[x].r,px,py,pos,mid+1,R);
}
int query(int x,int k,int L,int R){
//    printf("q:%d: %d %d-%d\n",x,k,L,R);
    if (!x) return 0;
    if (L==R) return L;
    int mid=(L+R)/2;
    if (T[x].r){
        int rk=KDT::query(T[T[x].r].KD_root);
        if (rk<k) return query(T[x].l,k-rk,L,mid);
        return query(T[x].r,k,mid+1,R);
    }return query(T[x].l,k,L,mid);
}
char buffer[36000000],*buf=buffer;
void read(int &x){
    for(x=0;*buf<48;++buf);
    while(*buf>=48)x=x*10+*buf-48,++buf;
}
int n,q;
int i,j,k;
int root,lastans;
int main(){
    fread(buffer,1,36000000,stdin);
    read(n);read(q);KDT::TOT=0;
    FOR(i,1,q){
        int op;
        read(op);
        if (op==1){
            int x,y,v;
            read(x);read(y);read(v);
            x^=lastans;y^=lastans;v^=lastans;
            update(root,x,y,v,0,MAX);
//            printf(" A: 1    %d %d %d\n",x,y,v);
        }else{
            int x1,y1,x2,y2,k;
            read(x1);read(y1);read(x2);read(y2);read(k);
            x1^=lastans;y1^=lastans;
            x2^=lastans;y2^=lastans;
            k^=lastans;
            KDT::x0=x1;KDT::y0=y1;
            KDT::x1=x2;KDT::y1=y2;
//            printf(" Q: 1    %d %d %d %d;  k=%d ",x1,y1,x2,y2,k);
//            printf("query_root=%d\n",KDT::query(T[root].KD_root));
            lastans=query(root,k,0,MAX);
            if (!lastans) puts("NAIVE!ORZzyz.");
            else printf("%d\n",lastans);
        }
    }
}
/*
*/

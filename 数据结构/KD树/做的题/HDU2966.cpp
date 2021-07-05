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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

const double alpha=0.8;
struct point{
    int A[2],max[2],min[2];
    int l,r;int size;
}T[maxn];
int Cur;
bool cmp(int x,int y){
    return T[x].A[Cur]<T[y].A[Cur];
}
void update(int x){
    T[x].size=1;int i;
    int l=T[x].l,r=T[x].r;
    if (l) T[x].size+=T[l].size;
    if (r) T[x].size+=T[r].size;
    REP(i,2) {
        T[x].max[i]=T[x].min[i]=T[x].A[i];
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
LL distance(point &x,point &y){
    LL ret=0;int i;
    REP(i,2) ret+=(LL)(x.A[i]-y.A[i])*(x.A[i]-y.A[i]);
    return ret;
}
LL mindis(point &x,point &q){//注意q在后
    int i;LL ret=0;
    REP(i,2){
        if (q.A[i]<x.min[i]) ret+=(LL)(q.A[i]-x.min[i])*(q.A[i]-x.min[i]);
        if (q.A[i]>x.max[i]) ret+=(LL)(q.A[i]-x.max[i])*(q.A[i]-x.max[i]);
    }
    return ret;
}
LL ans;
void query(int x,point &A){
//    printf("query:[%-3d,%-3d] %2d;  d=%-2lld\n",A.A[0],A.A[1],x,mindis(T[x],A));
    if (!x) return;
    LL d0=distance(T[x],A);
    if (d0) ans=min(ans,d0);
    if (T[x].size==1) return;
    LL dl,dr;dl=dr=INFF;
    if (T[x].l) dl=mindis(T[T[x].l],A);
    if (T[x].r) dr=mindis(T[T[x].r],A);
    if (dl<dr){
        if (dl<ans) query(T[x].l,A);
        if (dr<ans) query(T[x].r,A);
    }else{
        if (dr<ans) query(T[x].r,A);
        if (dl<ans) query(T[x].l,A);
    }
}
int n,m;
int i,j,k;
int root;
int main(){
    static int C;
    scanf("%d",&C);
    while (C--){
        scanf("%d",&n);
        FOR(i,1,n) scanf("%d%d",&T[i].A[0],&T[i].A[1]);
        FOR(i,1,n) id[i]=i;
        build(root,1,n,0);
//        FOR(i,1,n) {
//            printf("%-2d  l,r= %-2d %-2d; size=%-2d  ",i,T[i].l,T[i].r,T[i].size);
//            REP(j,2) printf("%-2d-%-2d  ",T[i].min[j],T[i].max[j]);puts("");
//        }
        FOR(i,1,n) ans=INFF,query(root,T[i]),printf("%lld\n",ans);
    }
}
/*
*/

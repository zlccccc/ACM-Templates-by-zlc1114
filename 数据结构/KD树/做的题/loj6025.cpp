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
const int DIM=2;
struct point{
    int A[DIM],max[DIM],min[DIM];
    int l,r;int size;
    LL sum,val;
    void init(){
        l=r=0;initval();
    }
    void initval(){
        int i;size=1;sum=val;
        REP(i,DIM) min[i]=max[i]=A[i];
    }
}T[maxn];
int Cur;
bool cmp(int x,int y){
    return T[x].A[Cur]<T[y].A[Cur];
}
void update(int x){
    int i;T[x].initval();
    int l=T[x].l,r=T[x].r;
    if (l) T[x].size+=T[l].size,T[x].sum+=T[l].sum;
    if (r) T[x].size+=T[r].size,T[x].sum+=T[r].sum;
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

LL A,B,C;
inline int check(int x,int y){
    return A*x+B*y<C;
}
inline int ok(point &A){
    return check(A.A[0],A.A[1]);
}
inline int queryall(point &A){
    return  check(A.min[0],A.min[1])+
            check(A.min[0],A.max[1])+
            check(A.max[0],A.min[1])+
            check(A.max[0],A.max[1]);
}
LL query(int x){
    if (!x) return 0;
    int mark=queryall(T[x]);
    if (mark==4) return T[x].sum;
    if (mark==0) return 0;
    LL ret=0;
    if (ok(T[x])) ret+=T[x].val;
    ret+=query(T[x].l);
    ret+=query(T[x].r);
    return ret;
}
char buffer[36000000],*buf=buffer;
template<typename T>
void read(T &x){
    for(x=0;(*buf<'0'||*buf>'9')&&*buf!='-';++buf);
    int flag=0;if (*buf=='-') flag=1,buf++;
    while('0'<=*buf&&*buf<='9')x=x*10+*buf-48,++buf;
    if (flag) x=-x;
}
int n,m;
int i,j,k;
int root;
int main(){
    fread(buffer,1,36000000,stdin);
//    static int C;
//    scanf("%d",&C);
//    while (C--){
        read(n);read(m);
        FOR(i,1,n) read(T[i].A[0]),read(T[i].A[1]),read(T[i].val),T[i].init();
        FOR(i,1,n) id[i]=i;
        build(root,1,n,0);
//        FOR(i,1,n) {
//            printf("%-2d  l,r= %-2d %-2d; size=%-2d  ",i,T[i].l,T[i].r,T[i].size);
//            REP(j,2) printf("%-2d-%-2d  ",T[i].min[j],T[i].max[j]);puts("");
//        }
        FOR(i,1,m){
            read(A),read(B),read(C);
            printf("%lld\n",query(root));
        }
//    }
}
/*
*/

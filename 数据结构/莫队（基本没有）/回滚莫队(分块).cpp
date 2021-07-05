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
const LL M=998244353;
const LL maxn=200000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M; return ret;}

//北京区域赛,题意是l->r的所有内部边的并查集啥的
//回滚分块(然而我没回滚,记录了一下)
//queries按照左端点排序(有边的要按照我这种方式来排,否则菊花图会卡死)
//cmpu的时候v要倒着,因为要让块外的不受左边影响(same_l and small_r)
//然后对于左端点在block内部的所有query,按右端点往右走,走到头即可
//这个做法就是按照左分块,然后把右边有效的加进去,再把左边的加进去就行了
int SIZE;
struct node {
    int u,v,id,o;
    node() {};
    node(int _u,int _v,int _id=0):u(_u),v(_v),id(_id) {};
} to[maxn],re[maxn],queries[maxn];
int BID[maxn],L[maxn];
bool cmpu(node A,node B) {
    if (A.u!=B.u) return A.u<B.u;
    //区间为了避免漏掉r小的
    if (A.v!=B.v) return A.v>B.v;
    return A.id>B.id;
}
bool cmpv(node A,node B) {
    if (A.v!=B.v) return A.v<B.v;
    if (A.u!=B.u) return A.u<B.u;
    return A.id<B.id;
}
bool cmpQ(node A,node B) {
    if (A.o!=B.o) return A.o<B.o;
    if (A.v!=B.v) return A.v<B.v;
    if (A.u!=B.u) return A.u<B.u;
    return A.id<B.id;
}
int fa[maxn],size[maxn];
LL Ans[maxn];
inline int getfa(int x) {
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
}
int FA[maxn],SZ[maxn],PID[maxn];
inline int getFA(int x) {
    if (FA[x]==x) return x;
    return FA[x]=getFA(FA[x]);
}
inline void update(int u,int pid) {
    if (PID[u]!=pid) {
        int f=getfa(u);
        if (PID[f]!=pid) {
            FA[f]=f;
            PID[f]=pid;
            SZ[f]=size[f];
        } PID[u]=pid; FA[u]=f;
    }
} int tot=0;
LL now;
int main() {
    int T;
    scanf("%d",&T);
    while (T--) {
        int n,m,q,i,j,k;
        scanf("%d%d%d",&n,&m,&q);
        if (q==0) SIZE=m; else SIZE=m/sqrt(q)*2;
        if (!SIZE) SIZE++;
        FOR(i,0,(m+1)/SIZE) L[i]=0;
        FOR(i,1,m+1) {BID[i]=i/SIZE; if (!L[i/SIZE]) L[i/SIZE]=i;}
        FOR(i,1,m) {
            int u,v;
            scanf("%d%d",&u,&v);
            if (u>v) swap(u,v);
            to[i]=node(u,v);
            re[i]=node(u,v);
        } sort(to+1,to+m+1,cmpv);
        sort(re+1,re+m+1,cmpu);
        FOR(i,1,m) {
            to[i].o=BID[lower_bound(re+1,re+1+m,to[i],cmpu)-re];
            re[i].o=BID[i];
        }
        FOR(i,1,q) {
            int u,v;
            scanf("%d%d",&u,&v);
            if (u>v) swap(u,v);
            queries[i]=node(u,v,i);
            queries[i].o=BID[lower_bound(re+1,re+1+m,queries[i],cmpu)-re];
        } sort(queries+1,queries+q+1,cmpQ);
        FOR(i,1,q) {
            if (i==1||queries[i].o!=queries[i-1].o) { //initialize
                FOR(j,1,n) fa[j]=j,size[j]=1;
                j=1; now=0;
            }
            for (; j<=m&&to[j].v<=queries[i].v; j++) {
                if (to[j].o>queries[i].o) {//sorted by l
                    node &e=to[j];
                    int x=getfa(e.u),y=getfa(e.v);
                    if (x==y) continue; fa[x]=y;
                    now+=(LL)size[x]*size[y];
                    size[y]+=size[x];
                }
            }
            LL ans=now; tot++;
            for (k=L[queries[i].o]; k<=m&&BID[k]==queries[i].o; k++) {
                if (queries[i].u<=re[k].u&&re[k].v<=queries[i].v) {
                    node &e=re[k];
                    update(e.u,tot); update(e.v,tot);
                    int x=getFA(e.u),y=getFA(e.v);
                    if (x==y) continue; FA[x]=y;
                    ans+=(LL)SZ[x]*SZ[y];
                    SZ[y]+=SZ[x];
                }
            }
            Ans[queries[i].id]=ans;
        }
        FOR(i,1,q) printf("%lld\n",Ans[i]);
    }
}
/*
*/

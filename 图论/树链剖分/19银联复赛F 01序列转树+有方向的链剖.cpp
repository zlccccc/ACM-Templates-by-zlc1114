#include <sstream>
#include <fstream>
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
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

pii val[maxn],T[maxn*4];//position
pii merge(const pii &x,const pii &y) {
    return make_pair(max(x.first,y.first),max(x.second,y.second));
}
void build(int x,int l,int r) {
    if (l==r) {
        T[x]=val[l];
        return;
    } int mid=(l+r)/2;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
    T[x]=merge(T[x<<1],T[x<<1|1]);
}
void update(int x,int pos,int L,int R) {
    if (L==R) {
        T[x]=val[L];
        return;
    } int mid=(L+R)/2;
    if (pos<=mid) update(x<<1,pos,L,mid);
    if (mid<pos) update(x<<1|1,pos,mid+1,R);
    T[x]=merge(T[x<<1],T[x<<1|1]);
}
pii query(int x,int l,int r,int L,int R) {
    if (l<=L&&R<=r) return T[x];
    int mid=(L+R)/2; pii ret(0,0);
    if (l<=mid) ret=merge(ret,query(x<<1,l,r,L,mid));
    if (mid<r) ret=merge(ret,query(x<<1|1,l,r,mid+1,R));
    return ret;
}
vector<int> edge[maxn];
int son[maxn],sz[maxn],fa[maxn];//changes
int top[maxn],id[maxn],dep[maxn],tot;
void dfs1(int u,int depth){
    int mx=-1;
    sz[u]=1; dep[u]=depth; son[u]=0;
    for (int v:edge[u]) {
        dfs1(v,depth+1);
        sz[u]+=sz[v];
        if (sz[v]>mx) mx=sz[v],son[u]=v;
    }
}
void dfs2(int u,int x){
    top[u]=x; id[u]=++tot;
    if (son[u]) dfs2(son[u],x);
    for (int v:edge[u]){
        if (v==son[u]) continue;
        dfs2(v,v);
    }
}
//线段树merge应为merge(query,nowans)(从上往下);
//up:1; down:0
inline int Query(int x,int y){
    int o=1,ret=0; // o: up(x)
    while (top[x]!=top[y]){//up(1)的更新应该是倒着的
        if (dep[top[x]]<dep[top[y]]) swap(x,y),o^=1;
        pii now=query(1,id[top[x]],id[x],1,tot);//x_up
        if (!o) ret=max(ret,now.first);
        else ret=max(ret,now.second);
        x=fa[top[x]];
    }
    if (dep[x]>dep[y]) swap(x,y),o^=1; o^=1;
    if (son[x]) {
        pii now=query(1,id[son[x]],id[y],1,tot);//y_up
        if (!o) ret=max(ret,now.first);
        else ret=max(ret,now.second);
    } return ret;
}
int tot_id;
int root,now;
int b[maxn],c[maxn];
int pid[maxn];
int main() {
    int n,i,q;
    scanf("%d%d",&n,&q); root=now=tot_id=1;
    FOR(i,1,n) {
        scanf("%d",&b[i]);
        if (b[i]) {//up
            pid[i]=now;
            if (!fa[now]) {
                root=++tot_id; fa[now]=tot_id;
                edge[tot_id].push_back(now);
            } now=fa[now];
        } else {//down
            fa[++tot_id]=now;
            edge[now].push_back(tot_id);
            now=tot_id; pid[i]=now; 
        }
    } dfs1(root,0); dfs2(root,0);
    FOR(i,1,n) {
        scanf("%d",&c[i]);
        if (b[i]) val[id[pid[i]]].second=c[i];//up(1)
        else val[id[pid[i]]].first=c[i];//down(0)
    } 
    build(1,1,tot);
    FOR(i,1,q) {
        int op; scanf("%d",&op);
        if (op==1) {
            int x,y; scanf("%d%d",&x,&y);
            if (b[x]) val[id[pid[x]]].second=y;//up
            else val[id[pid[x]]].first=y;//down
            update(1,id[pid[x]],1,tot);
        } else if (op==2) {
            int l,r; scanf("%d%d",&l,&r);
            int u,v; u=pid[l]; v=pid[r];
            if (!b[l]) u=fa[u];
            if (b[r]) v=fa[v];
            printf("%d\n",Query(u,v));
        }
    }
}
/*
*/
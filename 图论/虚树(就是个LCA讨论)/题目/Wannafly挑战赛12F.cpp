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
#include <cstdlib>
#include <iomanip>
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
const double pi=acos(-1.0);
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M; return ret;}

struct Edges {
    int to; LL len; int next;
    Edges(int _to=0,LL _len=0,int _next=0):to(_to),len(_len),next(_next) {}
} edge[maxn*2]; int etot;
int head[maxn];
int fa[maxn];
LL uplen[maxn];
int id[maxn],dfn[maxn],idtot;
inline void addedge(int u,int v,LL len) {
    edge[++etot]=Edges(v,len,head[u]); head[u]=etot;
}
namespace LCA {//内部和外部dfn不同...
    int dep[maxn]; LL len[maxn];
    int st_dfn[maxn],tot;
    int ST[maxn*2][20];//only L
    void dfs(int x,int f,int d,LL l) {
        int i; dep[x]=d; len[x]=l;
        st_dfn[x]=++tot; ST[tot][0]=x;
        ::id[++idtot]=x; ::dfn[x]=idtot;
        for (i=head[x]; ~i; i=edge[i].next) if (edge[i].to!=f) {
                int v=edge[i].to;
                ::fa[v]=x; ::uplen[v]=edge[i].len;
                dfs(v,x,d+1,l+edge[i].len);
                ST[++tot][0]=x;
            }
    }
    int t_t[maxn*2];
    inline void initST(int n) {
        int i,j;
        FOR(i,1,n*2) t_t[i]=t_t[i>>1]+1;
        FOR(i,1,n*2) {
            rep(j,1,t_t[i]) {
                int u=ST[i][j-1],v=ST[i-(1<<(j-1))][j-1];
                ST[i][j]=dep[u]<dep[v]?u:v;
            }
        }
    }
    inline int lca(int x,int y) {
        x=st_dfn[x]; y=st_dfn[y];
        if (x>y) swap(x,y);
        int t=t_t[y-x+1]-1;
        x=ST[x+(1<<t)-1][t]; y=ST[y][t];
        return dep[x]<dep[y]?x:y;
    }
    inline LL dis(int x,int y) {
        return len[x]+len[y]-2*len[lca(x,y)];
    }
}

namespace vtree{
    int S[maxn],top;
    int pid[maxn],mark[maxn];
    int vid[maxn],vfa[maxn];
    LL vlen[maxn];
    int cmp(int x,int y) {
        return dfn[x]<dfn[y];
    }
    void addedge(int u,int v) {
        vfa[v]=u; vlen[v]=LCA::dis(u,v);
    }
    int m;
    void vbuild(int n) {
        int i;m=0;
        S[top=1]=pid[1];
        mark[pid[1]]=1;
        FOR(i,2,n) {
            int f=LCA::lca(pid[i-1],pid[i]);
            while (top&&LCA::dep[S[top]]>LCA::dep[f]) {
                int v; vid[++m]=v=S[top--];
                if (top&&LCA::dep[S[top]]>LCA::dep[f]) addedge(S[top],v);
                else addedge(f,v);
            } if (!top||S[top]!=f) S[++top]=f;
            S[++top]=pid[i]; mark[pid[i]]=1;
        } while (top-1) addedge(S[top-1],S[top]),vid[++m]=S[top--];
        vid[++m]=S[1];
        reverse(vid+1,vid+m+1);
    }
    void vclear() {
        int i;
        FOR(i,1,m) mark[vid[i]]=0;
    }
}

int T;
int w[maxn];
LL down[maxn],nowans[maxn],sz[maxn];//down->upper,ans
void solve(int id[],int fa[],LL len[],int n) {
    int i;
    FOR(i,1,n) nowans[w[id[i]]]=down[id[i]]=0;
    rFOR(i,2,n) {
        int x=id[i];
        sz[fa[x]]+=sz[x];
        down[fa[x]]+=down[x]+sz[x]*len[x];
    } nowans[w[id[1]]]+=down[id[1]];
    LL k=sz[id[1]];
    FOR(i,2,n) {
        int x=id[i];
        down[x]=down[fa[x]]+(k-2*sz[x])*len[x];
        nowans[w[x]]+=down[x];
    }
}
void solve_big(int x,int n) {
    int i;
    FOR(i,1,n) sz[i]=(w[i]==x);
    solve(id,fa,uplen,n);
}
vector<int> pos[maxn];
void solve_small(int u,int v) {
    int i;
    int n=merge(pos[u].begin(),pos[u].end(),
                pos[v].begin(),pos[v].end(),vtree::pid+1)-vtree::pid-1;
    n=unique(vtree::pid+1,vtree::pid+n+1)-vtree::pid-1;
    FOR(i,1,n) vtree::pid[i]=id[vtree::pid[i]];
    vtree::vbuild(n);
    FOR(i,1,vtree::m) sz[vtree::vid[i]]=(w[vtree::vid[i]]==u);
    solve(vtree::vid,vtree::vfa,vtree::vlen,vtree::m);
    vtree::vclear();
}
char buffer[36000000],*buf=buffer;
char write[7000000],*ed=write;
void read(int &x) {
    for (x=0; *buf<48; ++buf);
    while (*buf>=48)x=x*10+*buf-48,++buf;
}
int pp[20];
void print(LL x){
    if (!x) *ed++='0';
    else {
        int now=0,i;
        while (x) pp[now++]=x%10,x/=10;
        while (now) *ed++=pp[--now]+48;
    }*ed++='\n';
}
LL smallcnt[maxn];
vector<pair<int,int> > Q[maxn];
LL ans[maxn];
int main() {
    int n,i;
    fread(buffer,1,36000000,stdin);
    read(n);
    FOR(i,1,n) head[i]=-1;
    FOR(i,1,n) read(w[i]);
    FOR(i,1,n-1) {
        int u,v,l;
        read(u); read(v); read(l);
        addedge(u,v,l);
        addedge(v,u,l);
    } LCA::dfs(1,0,0,0);
    LCA::initST(n);
    FOR(i,1,n) pos[w[i]].push_back(dfn[i]);
    FOR(i,1,n) sort(pos[i].begin(),pos[i].end());
    int q;
    read(q);
    FOR(i,1,q) {
        int u,v;
        read(u); read(v);
        if (pos[u].size()<pos[v].size()) swap(u,v);
        Q[u].push_back(make_pair(v,i));
        smallcnt[u]+=pos[u].size()+pos[v].size();
    }
    FOR(i,1,n) {
        if (!Q[i].size()) continue;
        if (smallcnt[i]<n){
            for (auto now:Q[i]){
                int v=now.first;
                solve_small(i,v);
                ans[now.second]=nowans[v];
                if (i==v) ans[now.second]/=2;
            }
        }else{
            solve_big(i,n);
            for (auto now:Q[i]){
                int v=now.first;
                ans[now.second]=nowans[v];
                if (i==v) ans[now.second]/=2;
            }
        }
    }FOR(i,1,q) print(ans[i]);
    fwrite(write,1,ed-write,stdout);
}
/*
*/

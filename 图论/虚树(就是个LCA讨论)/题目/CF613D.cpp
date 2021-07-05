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
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+9;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}


// 题意:问最少去掉几个未标记点可以把所有的标记点全分开
// 做法:建虚树然后树上DP

struct Edges {
    int to; LL len; int next;
    Edges(int _to=0,LL _len=0,int _next=0):to(_to),len(_len),next(_next) {}
} edge[maxn]; int etot;
int head[maxn];
inline void addedge(int u,int v,LL len) {
    edge[++etot]=Edges(v,len,head[u]); head[u]=etot;
}
int fa[maxn][20];
int dep[maxn]; LL len[maxn];
int id[maxn],tot;
void dfs(int x,int f,int d,LL l) {
    int i; dep[x]=d; id[x]=++tot; len[x]=l;
    fa[x][0]=f; rep(i,1,20) fa[x][i]=fa[fa[x][i-1]][i-1];
    for (i=head[x]; ~i; i=edge[i].next)
        if (edge[i].to!=f) dfs(edge[i].to,x,d+1,l+edge[i].len);
}
inline int lca(int x,int y) {
    int i;
    if (dep[x]<dep[y]) swap(x,y);
    rREP(i,20) if (dep[x]-dep[y]>=1<<i) x=fa[x][i];
    if (x==y) return x;
    rREP(i,20) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
inline int dis(int x,int y) {
    return len[x]+len[y]-2*len[lca(x,y)];
}

Edges vedge[maxn]; int vtot;
int S[maxn],top;
int pid[maxn],mark[maxn];
int vhead[maxn],vid[maxn];
int cmp(int x,int y) {
    return id[x]<id[y];
}
void addedge(int u,int v) {
    LL len=dis(u,v);
    vedge[++vtot]=Edges(v,len,vhead[u]); vhead[u]=vtot;
}
void vbuild(int n) {
    int i,m=0;
    sort(pid+1,pid+1+n,cmp);
    S[top=1]=pid[1]; vid[++m]=pid[1];
    mark[pid[1]]=1;
    FOR(i,2,n) {
        int f=lca(pid[i-1],pid[i]);
        while (top&&dep[S[top]]>dep[f]) {
            int v=S[top--];
            if (top&&dep[S[top]]>dep[f]) addedge(S[top],v);
            else addedge(f,v);
        } if (!top||S[top]!=f) S[++top]=f;
        S[++top]=pid[i]; mark[pid[i]]=1;
        vid[++m]=f; vid[++m]=pid[i];
    } while (top-1) addedge(S[top-1],S[top]),top--;
}
void vclear(int n) {
    int i; vtot=0;
    FOR(i,1,n*2) vhead[vid[i]]=-1,mark[vid[i]]=0;
}

int ans;
int cnt[maxn];
void vdfs(int x) {
    int i;
    cnt[x]=0;
    for (i=vhead[x]; ~i; i=vedge[i].next) {
        vdfs(vedge[i].to);
        cnt[x]+=cnt[vedge[i].to];
    }
    if (mark[x]) ans+=cnt[x],cnt[x]=1;
    else if (cnt[x]>1) ans++,cnt[x]=0;
}
int vis[maxn];
int main() {
    int i;
    int n,q;
    scanf("%d",&n);
    FOR(i,1,n) head[i]=vhead[i]=-1;
    FOR(i,1,n-1) {
        int u,v;
        scanf("%d%d",&u,&v);
        addedge(u,v,1); addedge(v,u,1);
    } dfs(1,0,0,0);
    scanf("%d",&q);
    while (q--) {
        int m,mark=0;
        scanf("%d",&m);
        FOR(i,1,m) scanf("%d",&pid[i]);
        FOR(i,1,m) vis[pid[i]]=1;
        FOR(i,1,m) if (vis[fa[pid[i]][0]]) mark=1;
        FOR(i,1,m) vis[pid[i]]=0;
        if (mark) {puts("-1"); continue;}
        vbuild(m);
        ans=0; vdfs(S[1]);
        printf("%d\n",ans);
        vclear(m);
    }
    return 0;
}
/*
*/
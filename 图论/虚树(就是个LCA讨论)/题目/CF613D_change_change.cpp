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
const LL maxn=1e5+7;
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
} edge[maxn*2]; int etot;
int head[maxn];
int fa[maxn],uplen[maxn];
int id[maxn];
inline void addedge(int u,int v,LL len) {
    edge[++etot]=Edges(v,len,head[u]); head[u]=etot;
}
namespace LCA{
    int dep[maxn]; LL len[maxn];
    int dfn[maxn],tot;
    int ST[maxn*2][20];//only L
    void dfs(int x,int f,int d,LL l) {
        int i; dep[x]=d; len[x]=l;
        dfn[x]=++tot; id[tot]=ST[tot][0]=x;
        for (i=head[x]; ~i; i=edge[i].next) if (edge[i].to!=f){
            int v=edge[i].to;
            ::fa[v]=x; ::uplen[v]=edge[i].len;
            dfs(v,x,d+1,l+edge[i].len);
            ST[++tot][0]=x;
        }
    }
    int t_t[maxn*2];
    inline void initST(int n){
        int i,j;
        FOR(i,1,n*2) t_t[i]=t_t[i>>1]+1;
        FOR(i,1,n*2){
            rep(j,1,t_t[i]){
                int u=ST[i][j-1],v=ST[i-(1<<(j-1))][j-1];
                ST[i][j]=dep[u]<dep[v]?u:v;
            }
        }
    }
    inline int lca(int x,int y) {
        x=dfn[x];y=dfn[y];
        if (x>y) swap(x,y);
        int t=t_t[y-x+1]-1;
        x=ST[x+(1<<t)-1][t];y=ST[y][t];
        return dep[x]<dep[y]?x:y;
    }
    inline int dis(int x,int y) {
        return len[x]+len[y]-2*len[lca(x,y)];
    }
}

namespace vtree{
//    Edges vedge[maxn]; int vtot;
//    int vhead[maxn];
    int S[maxn],top;
    int pid[maxn],mark[maxn];
    int vid[maxn],vfa[maxn],vlen[maxn];
    int cmp(int x,int y) {
        return LCA::dfn[x]<LCA::dfn[y];
    }
    void addedge(int u,int v) {
//        LL len=LCA::dis(u,v);
//        vedge[++vtot]=Edges(v,len,vhead[u]); vhead[u]=vtot;
        vfa[v]=u; vlen[v]=LCA::dis(u,v);
    }
    int m;
    void vbuild(int n) {
        int i;m=0;
        sort(pid+1,pid+1+n,cmp);
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
int ans;
int cnt[maxn];
//void vdfs(int x) {
//    int i;
//    cnt[x]=0;
//    for (i=vtree::vhead[x]; ~i; i=vtree::vedge[i].next) {
//        vdfs(vtree::vedge[i].to);
//        cnt[x]+=cnt[vtree::vedge[i].to];
//    }
//    if (vtree::mark[x]) ans+=cnt[x],cnt[x]=1;
//    else if (cnt[x]>1) ans++,cnt[x]=0;
//}
void solve(){
    int i;
//    FOR(i,1,vtree::m) printf("%d ",vtree::vid[i]);puts("");
    FOR(i,1,vtree::m) cnt[vtree::vid[i]]=0;
    rFOR(i,1,vtree::m){
        int x=vtree::vid[i];
        if (vtree::mark[x]) ans+=cnt[x],cnt[x]=1;
        else if (cnt[x]>1) ans++,cnt[x]=0;
        if (i>1) cnt[vtree::vfa[x]]+=cnt[x];
    }
}
int vis[maxn];
int main() {
    int i;
    int n,q;
    scanf("%d",&n);
    FOR(i,1,n) head[i]=-1;
    FOR(i,1,n-1) {
        int u,v;
        scanf("%d%d",&u,&v);
        addedge(u,v,1); addedge(v,u,1);
    } LCA::dfs(1,0,0,0);
    LCA::initST(n);
    scanf("%d",&q);
    while (q--) {
        int m,mark=0;
        scanf("%d",&m);
        FOR(i,1,m) scanf("%d",&vtree::pid[i]);
        FOR(i,1,m) vis[vtree::pid[i]]=1;
        FOR(i,1,m) if (vis[fa[vtree::pid[i]]]) mark=1;
        FOR(i,1,m) vis[vtree::pid[i]]=0;
        if (mark) {puts("-1"); continue;}
        vtree::vbuild(m);
        ans=0;
        solve();
//        vdfs(vtree::S[1]);
        vtree::vclear();
        printf("%d\n",ans);
    }
    return 0;
}
/*
*/

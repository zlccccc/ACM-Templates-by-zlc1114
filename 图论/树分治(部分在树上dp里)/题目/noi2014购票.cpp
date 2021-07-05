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

#define DEBUG1
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=3e5+7;
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

//len:length to 1
int fa[maxn];
LL len[maxn],p[maxn],q[maxn],l[maxn];
int dep[maxn];
vector<int> edge[maxn];
void _dfs(int x){
    dep[x]=dep[fa[x]]+1; len[x]+=len[fa[x]];
    for (int v:edge[x]){
        if (v==fa[x]) continue;
        _dfs(v);
    }
}
int sz[maxn];
bool mark[maxn];
int minweight,root;
void dfs1(int x,int fa,int n){
    int weight=0; sz[x]=1;
    for (int v:edge[x]){
        if (v==fa||mark[v]) continue;
        dfs1(v,x,n); sz[x]+=sz[v];
        weight=max(weight,sz[v]);
    }weight=max(weight,n-sz[x]);
    if (weight<minweight) root=x,minweight=weight;
}
vector<pair<LL,int> > now;
vector<pair<LL,int> > ancient[maxn],subtree[maxn];
void dfs2(int x,int fa,int nowroot){
    LL length=len[x]-len[nowroot];
    if (l[x]-length>=0)
        subtree[nowroot].push_back(make_pair(l[x]-length,x));
//    debug("%d %lld %lld\n",x,l[x],length);
    for (int v:edge[x]){
        if (v==fa||mark[v]) continue;
        dfs2(v,x,nowroot);
    }
}
void calc(int x){
    for (int _x=x;_x&&!mark[_x];_x=fa[_x])
        ancient[x].push_back(make_pair(len[x]-len[_x],_x));
    for (int v:edge[x]) if (v!=fa[x]) dfs2(v,x,x);
    sort(ancient[x].begin(),ancient[x].end());
    sort(subtree[x].begin(),subtree[x].end());
}
void dfs3(int x){
    debug("dfs3: %d\n",x);
    calc(x); mark[x]=1;
    for (int v:edge[x]){
        if (mark[v]) continue;
        minweight=sz[v]; dfs1(v,0,sz[v]);
        dfs3(root);
    }
}

bool Q;
struct Line {
    mutable LL a,b,k;
    bool operator<(const Line &o)const {
        return Q?k<o.k:a<o.a;
    }
};
struct convexHull:public multiset<Line> {
    LL div(LL a,LL b) {
        return a/b-((a^b)<0&&a%b);
    }
    bool getK(iterator x,iterator y) {
        if (y==end()) {x->k=INFF; return 0;}
        if (x->a==y->a) x->k=x->b>y->b?INFF:-INFF;
        else x->k=div(y->b-x->b,x->a-y->a);
        return x->k>=y->k;
    }
    void insPos(LL a,LL b) {
        auto z=insert({a,b,0}); auto y=z++,x=y;
        while (getK(y,z)) z=erase(z);
        if (y!=begin()&&getK(--x,y)) getK(x,erase(y));
        while ((y=x)!=begin()&&(--x)->k>=y->k)
            getK(x,erase(y));
    }
    LL query(LL x) {
        assert(size());
        Q=1; auto now=lower_bound({0,0,x}); Q=0;
        return now->a*x+now->b;
    }
}C;

LL ans[maxn];
void solve(int x){
    debug("solve %d\n",x);
    C.clear();
    for (auto now:ancient[x]) {
        int v=now.second; if (len[x]-len[v]>l[x]) break;
        ans[x]=min(ans[x],p[x]*(len[x]-len[v])+ans[v]+q[x]);
    }int i=0;
    for (auto now:subtree[x]){
        for (;i!=ancient[x].size()&&ancient[x][i].first<=now.first;i++){
            int v=ancient[x][i].second;
            C.insPos(len[v],-ans[v]);
            debug("que anc %lld %d\n",ancient[x][i].first,ancient[x][i].second);
//            debug("inspos: %lld %lld\n",len[v],-ans[v]);
        }if (!C.size()) continue;
        int y=now.second;
        ans[y]=min(ans[y],-C.query(p[y])+p[y]*len[y]+q[y]);
        debug("que sub %lld %d\n",now.first,now.second);
//        debug("query : %lld %lld\n",len[y],-C.query(p[y])+p[y]*len[y]+q[y]);
    }
    for (auto now:ancient[x]) debug("anc %d (%lld) (%lld)\n",now.second,now.first,ans[now.second]);
    for (auto now:subtree[x]) debug("sub %d |%lld| (%lld)\n",now.second,now.first,ans[now.second]);
}
int id[maxn];
int main() {
    int n,m,i;
    int T;
    scanf("%d%*d",&n);
    FOR(i,2,n){
        scanf("%d%lld%lld%lld%lld",&fa[i],&len[i],&p[i],&q[i],&l[i]);
        edge[fa[i]].push_back(i);
        edge[i].push_back(fa[i]);
    } _dfs(1); minweight=n; dfs1(1,0,n); dfs3(root);
    FOR(i,1,n) id[i]=i;
    sort(id+1,id+1+n,[](int i,int j){
        return dep[i]<dep[j];
    });
    FOR(i,1,n) ans[i]=INFF; ans[1]=0;
    FOR(i,1,n) solve(id[i]);
    FOR(i,2,n) printf("%lld\n",ans[i]);
}
/*
7 3
1 2 20 0 3
1 5 10 100 5
2 4 10 10 10
2 9 1 100 10
3 5 20 100 10
4 4 20 0 10
*/

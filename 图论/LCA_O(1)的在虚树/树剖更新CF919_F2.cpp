// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define REP_(I,N) for (int I=0,END=(N);I<END;I++)
#define rREP_(I,N) for (int I=(N)-1;I>=0;I--)
#define rep_(I,S,N) for (int I=(S),END=(N);I<END;I++)
#define rrep_(I,S,N) for (int I=(N)-1,START=(S);I>=START;I--)
#define FOR_(I,S,N) for (int I=(S),END=(N);I<=END;I++)
#define rFOR_(I,S,N) for (int I=(N),START=(S);I>=START;I--)

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
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=1e-10;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
inline ll fastgcd(ll a, ll b) {  // __gcd()
    if (!a) return b;
    ll az=__builtin_ctzll(a),bz=__builtin_ctzll(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctzll(diff);
        (b>a)&&(b=a); a=abs(diff);
    }
    return b<<z;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

struct LCA {
    vector<vector<int>> edge;
    vector<int> sz, fa, son, top, dep, id;
    LCA(int n) : edge(n + 1), sz(n + 1), fa(n + 1), son(n + 1), top(n + 1), dep(n + 1), id(n + 1) {}
    int tot=0;
    void addedge(int x,int y) {
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    void dfs1(int u,int f,int depth) {
        // printf("dfs1 %d %d %d\n",u,f,depth);
        int mx=-1; fa[u]=f;
        sz[u]=1; dep[u]=depth; son[u]=0;
        for(int v:edge[u]){
            if (v==f) continue;
            dfs1(v,u,depth+1);
            sz[u]+=sz[v];
            if (sz[v]>mx) mx=sz[v],son[u]=v;
        }
    }
    void dfs2(int u,int f,int x) {
        // printf("dfs2 %d %d %d\n",u,f,x);
        top[u]=x; id[u]=++tot;
        if (son[u]) dfs2(son[u],u,x);
        for (int v:edge[u]){
            if (v==son[u]||v==f) continue;
            dfs2(v,u,v);
        }
    }
    int lca(int x,int y){
        // printf("lca %d %d\n",x,y);
        while (top[x]!=top[y]){
            if (dep[top[x]]<dep[top[y]]) swap(x,y);
            x=fa[top[x]];
        }
        if (dep[x]>dep[y]) swap(x,y);
        return x;
    }
    void solve(int root) {
        dfs1(root,0,0);
        dfs2(root,0,root);
    }
};

// https://codeforces.com/contest/1920/problem/F2
// 题意是给你一个图, 里面有个连通块
// 问你从某个点出发绕着走一圈是否能把连通块包住
// 然后给了个限制, 距离'v'的方块<=mindis的都不能走
// 问mindis最大是多少
// 做法就很简单; 先bfs然后求最小生成树
// 最小生成树merge的时候搞边权; 查询的时候直接看lca就行了; lca留个板子
int ax[4]={0,1,0,-1};
int ay[4]={1,0,-1,0};
int solve() {
    int n,m,q;
    cin>>n>>m>>q;
    vector<string> s(n);
    REP_(i,n) cin>>s[i];
    vector<vector<char>> vec(n+2,vector<char>(m+2));
    FOR_(i,1,n) FOR_(j,1,m) vec[i][j]=s[i-1][j-1];
    vector<vector<int>> dist(n+2,vector<int>(m+2));
    {
        // 最近的v
        queue<pii> Q;
        FOR_(i,1,n) FOR_(j,1,m) dist[i][j]=INF;
        FOR_(i,1,n) FOR_(j,1,m) if (vec[i][j]=='v') Q.push({i,j}),dist[i][j]=0;
        while (Q.size()) {
            int x=Q.front().first,y=Q.front().second; Q.pop();
            REP_(i,4) {
                int dx=x+ax[i],dy=y+ay[i];
                if (dist[dx][dy]==INF) {
                    dist[dx][dy]=dist[x][y]+1;
                    Q.push({dx,dy});
                }
            }
        }
    }
    vector<string>().swap(s);

    // FOR_(i,1,n) {FOR_(j,1,m) printf("%d ",dist[i][j]); puts("");}

    int islandx=-1,islandy=-1;
    FOR_(i,1,n) FOR_(j,1,m) if (vec[i][j]=='#') islandx=i,islandy=j;
    auto getid=[&](int x,int y,int op) {
        return (x-1)*m+y+op*n*m;
    };
    vector<ar3> edges;
    FOR_(x,1,n) FOR_(y,1,m) if (vec[x][y]!='#') {
        REP_(i,2) {
            int dx=x+ax[i],dy=y+ay[i];
            if (vec[dx][dy]!='.'&&vec[dx][dy]!='v') continue;
            int w=min(dist[x][y],dist[dx][dy]);
            if (x==islandx-1&&dx==islandx&&y>islandy) {
                edges.push_back({w,getid(x,y,0),getid(dx,dy,1)});
                edges.push_back({w,getid(x,y,1),getid(dx,dy,0)});
            } else {
                edges.push_back({w,getid(x,y,0),getid(dx,dy,0)});
                edges.push_back({w,getid(x,y,1),getid(dx,dy,1)});
            }
        }
    }
    sort(edges.begin(),edges.end());
    reverse(edges.begin(),edges.end());

    vector<int> fa(n*m*4+1),w(n*m*4+1);
    FOR_(i,1,n*m*4) fa[i]=i;
    function<int(int)> getfa=[&](int x) {
        if (fa[x]==x) return x;
        return fa[x]=getfa(fa[x]);
    };

    LCA lca(n*m*4);
    int tot=n*m*2;
    for (auto &e:edges) {
        // printf("edge %d %d %d\n",e[0],e[1],e[2]);
        int x=getfa(e[1]),y=getfa(e[2]);
        // printf("x=%d; y=%d; e=%d %d;  %d\n",x,y,e[1],e[2],n*m*4);
        if (x!=y) {
            ++tot; w[tot]=e[0];
            // printf("merge %d %d; tot=%d; %d\n",x,y,tot,n*m*4);
            auto getpos=[&](int x) {return ar3{(x-1)%(n*m)/m+1,(x-1)%m+1,x/(n*m)}; };
            // printf("merge [%d %d %d], [%d %d %d]; w=%d\n",getpos(e[1])[0],getpos(e[1])[1],getpos(e[1])[2],
            //                                               getpos(e[2])[0],getpos(e[2])[1],getpos(e[2])[2],e[0]);

            fa[x]=fa[y]=tot;
            lca.addedge(tot,x);
            lca.addedge(tot,y);
        }
    }
    lca.solve(tot);

    FOR_(i,1,q) {
        int x,y;
        cin>>x>>y;
        printf("%d\n",w[lca.lca(getid(x,y,0),getid(x,y,1))]);
    }
    return 0;
}
int main() {
    int T; T=1;
    // cin>>T;
    startTimer();
    FOR_(_,1,T) {
        solve();
    }
    // printTimer();
}
/*
*/
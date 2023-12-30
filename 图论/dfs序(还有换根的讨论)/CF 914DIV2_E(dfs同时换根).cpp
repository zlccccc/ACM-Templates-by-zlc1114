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
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL maxn=2e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T fastgcd(T a, T b) {
    int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctz(diff);
        min_(b,a); a=abs(diff);
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

int n;
ll MAX[maxn*4],val[maxn*4];
void update(int x,int l,int r,int v,int L,int R) {
    // if (x==1) printf("update =%d %d %d %d %d %d\n",x,l,r,v,L,R);
    // if (x==1) printf("update=%d %d %d\n",l,r,v);
    if (l<=L&&R<=r) {val[x]+=v,MAX[x]+=v; return;}
    int mid=(L+R)/2;
    if (l<=mid) update(x<<1,l,r,v,L,mid);
    if (mid<r) update(x<<1|1,l,r,v,mid+1,R);
    MAX[x]=max(MAX[x<<1],MAX[x<<1|1])+val[x];
}
void DFS(int x,int L,int R,int v) {
    if (L==R) {printf("%d ",MAX[x]+v); return;}
    int mid=(L+R)/2;
    DFS(x<<1,L,mid,v+val[x]);
    DFS(x<<1|1,mid+1,R,v+val[x]);
}
vector<int> edge[maxn];
int dep[maxn],fa[maxn][20];
int id[maxn],out[maxn],tot;
void dfs1(int x,int f,int depth) {  // get dfn and depth
    id[x]=++tot; dep[x]=depth; 
    fa[x][0]=f;
    rep_(i,1,20) fa[x][i]=fa[fa[x][i-1]][i-1];
    for (int v:edge[x]) {
        if (v==f) continue;
        dfs1(v,x,depth+1);
    }
    out[x]=tot;
}
int res[maxn];
vector<pair<int,vector<int>>> que[maxn];
int kthfa(int x,int k) {
    rREP_(i,20) if ((k>>i)&1) x=fa[x][i];
    return x;
}
void dfs2(int x,int f) {
    auto upd=[&](int x,int y,int val) {  // 去除y以及其他y旁边的点
        if (id[y]<=id[x]&&id[x]<=out[y]) {  // y是x的anc(y包含x)
            if (x==y) update(1,1,n,val,1,n);
            else {
                int f=kthfa(x,dep[x]-dep[y]-1);
                update(1,1,n,val,1,n);
                update(1,id[f],out[f],-val,1,n);
            }
        } else {
            update(1,id[y],out[y],val,1,n);
        }
    };
    // printf("query x=%d\n",x);
    // DFS(1,1,n,0); puts("<- INIT-val");
    for (auto &Q:que[x]) {
        int id=Q.first;
        // printf("id=%d\n",id);
        auto &item=Q.second;
        for (int v:item) upd(x,v,-n);
        // printf("query %d=%d\n",id,MAX[1]);
        // DFS(1,1,n,0); puts("<- val");
        res[id]=MAX[1];
        for (int v:item) upd(x,v,n);
    }
    for (int v:edge[x]) {
        if (v==f) continue;
        update(1,id[v],out[v],-2,1,n);
        update(1,1,n,1,1,n);
        dfs2(v,x);
        update(1,id[v],out[v],2,1,n);
        update(1,1,n,-1,1,n);
    }
}
// 题意: 给棵2e5的树, 问去除一些点以后, 从x出发的最长长度是多长
// 换根dp一下, 然后直接取max就行了...
int solve() {
    int m;
    scanf("%d%d",&n,&m);
    FOR_(i,1,n-1) {
        int x,y;
        scanf("%d%d",&x,&y);
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    dfs1(1,0,0);
    FOR_(i,1,n) update(1,id[i],id[i],dep[i],1,n);
    FOR_(i,1,m) {
        int x,k;
        scanf("%d%d",&x,&k);
        vector<int> cur(k);
        REP_(o,k) scanf("%d",&cur[o]);
        que[x].push_back({i,move(cur)});
    }
    dfs2(1,0);
    FOR_(i,1,m) printf("%d\n",res[i]);
    return 0;
}
int main() {
    int T; T=1;
    // scanf("%d",&T);
    FOR_(_,1,T){
        solve();
    }
    return 0;
}
/*
7 2
1 2
1 3
1 4
3 5
4 6
3 7
1 6 5 1
2 6 7 3
*/
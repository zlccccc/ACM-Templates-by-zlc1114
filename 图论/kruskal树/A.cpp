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
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=2e5+107;
const ll MAXM=4e5+107;
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


namespace io {
    const int SIZE = (1 << 21) + 1;
    char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int qr;
    #define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
    inline void flush () {
        fwrite (obuf, 1, oS - obuf, stdout);
        oS = obuf;
    }
    inline void putc (char x) {
        *oS ++ = x;
        if (oS == oT) flush ();
    }
    template <class I>
    inline void gi (I &x) {
        for (c = gc(); c < '0' || c > '9'; c = gc());
        for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15);
    }
    template <class I>
    inline void print (I x) {
        if (!x) putc ('0');
        while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
        while (qr) putc (qu[qr --]);
    }
    struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}

// kruskal tree; 两点LCA为对应边上最小值
struct kruskal_tree {
    struct edge{int u,v,w;};
    vector<edge> e;
    int tot;//m:edges
    void addedge(int x,int y,int w) {
        e.push_back(edge{x,y,w});
    }
    int fa[maxn*2][21],son[maxn*2][2],_Fa[maxn*2],dtot;
    void init(int n) {
        int i; tot=n;
        FOR(i,1,n) _Fa[i]=i;
    }
    inline int getfa(int x) {
        if (_Fa[x]==x) return x;
        return _Fa[x]=getfa(_Fa[x]);
    }
    int in[maxn*2],out[maxn*2],back[maxn*2];
    void dfs(int x) {
        int i; in[x]=++dtot; back[dtot]=x;
        rep(i,1,20) fa[x][i]=fa[fa[x][i-1]][i-1];
        if (son[x][0]) fa[son[x][0]][0]=x,dfs(son[x][0]);
        if (son[x][1]) fa[son[x][1]][0]=x,dfs(son[x][1]);
        out[x]=dtot;
    }
    int val[maxn*2];
    void build(int op) {
        int i;
        memset(son,0,sizeof(son));
        memset(fa,0,sizeof(fa));
        // sort(e+1,e+1+m,[&](edge &x,edge &y){return x.w<y.w;});
        if (op) reverse(e.begin(), e.end());
        for (edge &_e:e) {
            int x=getfa(_e.u),y=getfa(_e.v);
            if (x!=y) {
                tot++; _Fa[x]=_Fa[y]=_Fa[tot]=tot;
                val[tot]=_e.w;
                son[tot][0]=x; son[tot][1]=y;
            }
        } dtot=0;
        REP(i,20) fa[0][i]=0;
        FOR(i,1,tot) if (getfa(i)==i) dfs(i);
    }
    int query_range_id(int x,int v) {
        int i;
        rREP(i,20) if (fa[x][i]&&val[fa[x][i]]<=v) x=fa[x][i];
        return x;
    }
}T[2];

int v[MAXM];
inline int lowbit(int x) {return x&-x;}
inline void update(int x,int val,int MAX) {
    for (;x<=MAX;x+=lowbit(x)) v[x]+=val;
}
inline int query(int x) {
    int ret=0;
    for (;x;x-=lowbit(x)) ret+=v[x];
    return ret;
}
int Ans[MAXM];
vector<pair<pii,int> > asks[MAXM];//position; mask; id
int main() {
    int n,m,q; int i;
    io::gi(n); io::gi(m); io::gi(q);
    T[0].init(n); T[1].init(n);
    FOR(i,1,m) {
        int x,y,c;
        io::gi(x),io::gi(y),io::gi(c); x++; y++;
        if (!c) T[c].addedge(x,y,i);//0：i-m+2
        else T[c].addedge(x,y,-i);//1: 1-i
    } T[0].build(0); T[1].build(1);

    FOR(i,1,q) {
        int x,t;
        io::gi(x); io::gi(t); x++;
        int id0=T[0].query_range_id(x,t);
        int id1=T[1].query_range_id(x,-t);
        int l0=T[0].in[id0],r0=T[0].out[id0]; 
        int l1=T[1].in[id1],r1=T[1].out[id1];
        l0--; l1--;
        asks[l0].push_back(make_pair(make_pair(l1,1),i));
        asks[l0].push_back(make_pair(make_pair(r1,-1),i));
        asks[r0].push_back(make_pair(make_pair(l1,-1),i));
        asks[r0].push_back(make_pair(make_pair(r1,1),i));
    }
    FOR(i,1,q) Ans[i]=0;

    FOR(i,1,T[0].dtot) {
        int back=T[0].back[i];
        if (back<=n) update(T[1].in[back],1,T[1].dtot);
        for (auto now:asks[i])
            Ans[now.second]+=query(now.first.first)*now.first.second;
    }
    FOR(i,1,q) {io::print(Ans[i]); io::putc('\n');}
}
/*
3 7 5
1 0 0
2 1 0
0 1 1
2 1 1
1 1 1
1 1 1
1 1 1
1 1
1 2
1 4
2 5
2 3
*/
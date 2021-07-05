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
const LL maxn=4e5+107;
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

// 通过x或y相连边数; 整体二分套个并查集; 板子
vector<pair<pii,int> > back[maxn*4];
int fa[maxn],sz[maxn];
int getfa(int x,int back_id) {
    if (fa[x]==x) return x;
    int ret=getfa(fa[x],back_id);
    if (ret!=fa[x]) back[back_id].push_back(make_pair(make_pair(x,fa[x]),sz[x]));
    return fa[x]=ret;
}
void rollback(int back_id) {
    reverse(back[back_id].begin(), back[back_id].end());
    for (auto now:back[back_id]) {
        fa[now.first.first]=now.first.second;
        sz[now.first.first]=now.second;
    } vector<pair<pii,int> >().swap(back[back_id]);
}
vector<pii> Q[maxn];
int ans[maxn];
void solve(int ID,int l,int r,const vector<pair<pii,pii> > &nodes) {//整体二分
    // printf("%d-%d: %d\n",l,r,ID);
    for (auto now:nodes) {
        pii e=now.first,pos=now.second;
        if (pos.first<=l&&r<=pos.second) {
            // printf("solve %d-%d(e %d %d): %d %d\n",l,r,pos.first,pos.second,e.first,e.second);
            int x=getfa(e.first,ID),y=getfa(e.second,ID);
            if (x!=y) {
                back[ID].push_back(make_pair(make_pair(x,fa[x]),sz[x]));
                back[ID].push_back(make_pair(make_pair(y,fa[y]),sz[y]));
                fa[x]=y; sz[y]+=sz[x];
            }
        }
    }
    for (auto now:nodes) {//roll-back
        pii e=now.first,pos=now.second;
        if (pos.first<=l&&r<=pos.second)
            getfa(e.first,ID),getfa(e.second,ID);
    }
    if (l==r) {
        for (auto v:Q[l]) {
            ans[v.first]=sz[getfa(v.second,ID)];
            // printf("query: %d %d\n",v.first,v.second);
        }
    } else {
        int mid=(l+r)/2;
        vector<pair<pii,pii> > nxt;
        for (auto now:nodes) {
            pii pos=now.second;
            if (pos.first<=l&&r<=pos.second) continue;
            if (pos.first<=mid) nxt.push_back(now);
        } solve(ID<<1,l,mid,nxt);
        nxt.clear();
        for (auto now:nodes) {
            pii pos=now.second;
            if (pos.first<=l&&r<=pos.second) continue;
            if (mid<pos.second) nxt.push_back(now);
        } solve(ID<<1|1,mid+1,r,nxt);
        nxt.clear();
    }
    rollback(ID);
}

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
using namespace io;

int x_[maxn],y_[maxn],c_[maxn],Ans[maxn];
int main() {
    int n,m,q; int i;
    // scanf("%d%d%d",&n,&m,&q);
    gi(n); gi(m); gi(q);
    vector<pair<pii,pii> > edges;
    // FOR(i,2,m+1) scanf("%d%d%d",&x_[i],&y_[i],&c_[i]);
    FOR(i,2,m+1) gi(x_[i]),gi(y_[i]),gi(c_[i]);
    FOR(i,1,q) {
        int x,t;
        // scanf("%d%d",&x,&t);
        gi(x); gi(t); x++; t++;
        Q[t].push_back(make_pair(i,x));
    }

    // x|y
    FOR(i,2,m+1) {
        int x=x_[i],y=y_[i],c=c_[i];
        pii pos;
        if (c==1) {
            pos.first=1; pos.second=i;
        } else {
            pos.first=i; pos.second=m+2;
        } x++; y++;
        edges.push_back(make_pair(make_pair(x,y),pos));
    } 
    FOR(i,1,n) fa[i]=i,sz[i]=1;
    solve(1,1,m+2,edges);
    FOR(i,1,q) Ans[i]=-ans[i];
    edges.clear();

    // FOR(i,1,q) printf("%d\n",Ans[i]);
    FOR(i,1,q) {print(Ans[i]); putc('\n');}
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
// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
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
#include <functional>
#include <random>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define REP_(I,N) for (int I=0;I<N;I++)
#define rREP_(I,N) for (int I=N-1;I>=0;I--)
#define rep_(I,S,N) for (int I=S;I<N;I++)
#define rrep_(I,S,N) for (int I=N-1;I>=S;I--)
#define FOR_(I,S,N) for (int I=S;I<=N;I++)
#define rFOR_(I,S,N) for (int I=N;I>=S;I--)
 
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
// const LL M=1e9+7;
const LL M=998244353;
// ll M=1;
const LL maxn=2e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
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
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
typedef array<int,2> ar2;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

// 题意: 给个[n<=100,m<=7]的矩阵, 问你最少把几个.变成#能让#联通
// 做法: 直接dsu维护一下就行了, 存一下id, 联通就直接2^m枚举merge一下, O(能过)
// 3 5
// ...#.
// .#...
// ....#
namespace DSU {
    typedef vector<int> Sta;
    map<Sta,int> sta2id; 
    vector<Sta> id2sta;
    void output_sta(Sta sta) {
        printf("(sta %d):[",sta2id[sta]);
        for (int v:sta) if (v!=-1) printf("%d ",v); else printf("- ");
        printf("]  ");
    }
    void output_sta(int k) {
        output_sta(id2sta[k]);
    }
    // get-current-state
    vector<int> fa;
    inline int getfa(int x) {
        // printf("getfa %d\n",x);
        if (fa[x]==x) return x;
        return fa[x]=getfa(fa[x]);
    }
    inline void merge(int x,int y) {
        x=getfa(x); y=getfa(y);
        if (x!=y) fa[x]=y;
    }
    int getid(Sta sta) {
        int id;
        if (sta2id.count(sta)) id=sta2id[sta];
        else id=id2sta.size(),id2sta.push_back(sta),sta2id[sta]=id;
        // output_sta(id); puts("<- sta");
        return id;
    }
    pii solve(int sta,int operation) { // color-removed; (next-status,color-removed)
        fa=id2sta[sta]; int n=fa.size(); // new-size
        // output_sta(sta); pr2(operation,n); puts("<- solve operation");
        REP_(i,n) { // newly-merged
            if ((operation>>i)&1) {
                assert((int)fa.size()==i+n);
                fa.push_back(fa.size()); // new-id
                if (fa[i]!=-1) merge(fa[i],fa[i+n]);// merge
                if (i&&((operation>>(i-1))&1)) merge(fa[i+n-1],fa[i+n]);
            } else fa.push_back(-1);
        }
        // puts("merge done"); printf("fasize=%d\n",fa.size());
        // for (int v:fa) printf("%d ",v); puts("<- f"); printf("n=%d\n",n);
        map<int,int> MP;
        REP_(i,n+n) if (fa[i]!=-1) MP[getfa(i)]=-1;
        // puts("merge done2"); 
        int newid=0;
        rep_(i,n,n+n) if (fa[i]!=-1&&MP[getfa(i)]==-1) MP[getfa(i)]=i-n,newid++;
        Sta newfa;
        rep_(i,n,n+n) if (fa[i]!=-1) newfa.push_back(MP[getfa(i)]); else newfa.push_back(-1);
        // output_sta(getid(newfa)); puts("<- new status");
        return {getid(newfa),MP.size()-newid};
    }
}
vector<pii> nxt_status[maxn];// cache
char str[maxn];
int main() {
    int n,m;
    scanf("%d%d",&n,&m);
    DSU::Sta zero(m,-1); int zero_id=DSU::getid(zero);
    vector<ar2> cur(DSU::id2sta.size(),{INF,INF});
    cur[zero_id][0]=0;
    FOR_(i,1,n+1) {
        int mask=0;
        if (i!=n+1) {
            scanf("%s",str);
            REP_(j,m) if (str[j]=='#') mask|=1<<j;
        }
        vector<ar2> nxt;
        REP_(sta,(int)cur.size()) {
            if (nxt_status[sta].size()==0) { // not prepared
                REP_(operation,(1<<m)) nxt_status[sta].push_back(DSU::solve(sta,operation));
            }
            REP_(o,2) if (cur[sta][o]!=INF) {
                REP_(operation,(1<<m)) if ((operation&mask)==mask) {
                    pii sol=nxt_status[sta][operation];
                    nxt.resize(DSU::id2sta.size(),{INF,INF});
                    if (o+sol.second>=2) continue;
                    min_(nxt[sol.first][o+sol.second],cur[sta][o]+__builtin_popcount(operation^mask));
                }
            }
        }
        cur.swap(nxt);
        // printf("i=%d:\n",i);
        // REP_(sta,(int)cur.size()) {
        //     DSU::output_sta(sta); printf(" val=[%d, %d]\n",cur[sta][0],cur[sta][1]);
        // } puts("");
    }
    int ans=min(cur[zero_id][0],cur[zero_id][1]);
    printf("%d\n",ans);
}
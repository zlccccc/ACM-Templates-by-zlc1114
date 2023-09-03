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
const LL maxn=1e6+107;
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

// ABC294Ex
// 给一个n<=30,m<=30的图, 问给图染色成k<=1e9个颜色, 有多少方案让相邻节点颜色不同
// 做法是暴搜, 复杂度是(xxx<2)^n; 跑的飞快
// 首先给定一个set, 可以把set内的度为0的点去掉, ans*=k或者k-1
// 然后考虑一下x多少sqrt(m)=6个点相邻, 考虑容斥一下至少x个颜色相同
// 每次容斥就考虑一下k=2^6的子集有哪些和当前点颜色相同; 这里也可以剪枝

// _e:原始id; eid:新的id
vector<int> reid(vector<int> _e,vector<int> eid,int tot) {
    vector<int> e(tot);
    REP_(i,(int)_e.size()) if (eid[i]!=-1) {
        for (int sta=_e[i];sta;) {
            int j=__builtin_ctz(sta); sta^=1<<j;
            // printf("%d %d %d\n",sta,i,j);
            if (eid[j]!=-1) e[eid[i]]|=1<<eid[j];
        }
    }
    return e;
}
// need split first
// solve second
int solve(vector<int> e,int k) {
    int n=e.size();
    if (n==0) return 1;
    if (n==1) return k;
    int min_deg=n+1,id=0; // id: current-id
    { // judge 0, 把空的点删掉
        vector<int> eid(e.size(),-1);
        ll base=1; int tot=0;
        REP_(i,n) {
            if (min_deg>=__builtin_popcount(e[i])) min_deg=__builtin_popcount(e[i]),id=i;
            if (__builtin_popcount(e[i])==0) base=base*k%M;
            else eid[i]=tot++;
        }
        vector<int> newe=reid(e,eid,tot);
        // REP_(i,n) printf("%d ",eid[i]); puts("<- eid");
        // REP_(i,(int)newe.size()) {pr2(newe[i],newe.size()); puts("<- new_e");}
        if (tot!=n) return solve(newe,k)*base%M; // remove no-use-nodes
    }
    { // 容斥一下
        ll oth;
        { // 至少0个点颜色相同
            vector<int> eid(e.size(),-1);
            int tot=0;// MASK-LOW-RANK
            REP_(i,n) if (i!=id) eid[i]=tot++;
            oth=solve(reid(e,eid,tot),k);
        } // 至少mask颜色相同, 容斥一下
        int ans=(ll)oth*k%M;
        for (int mask=e[id];mask;mask=(mask-1)&e[id]) {
            if (__builtin_popcount(mask)==1) add_(ans,M-oth); // 至少1个和原始id颜色相同,edge不会变
            else {
                ll op=1; int tot=0;
                vector<int> eid(e.size(),-1);
                REP_(i,n) if (i!=id) if (!((mask>>i)&1)) eid[i]=tot++; // 不merge
                REP_(i,n) if (i!=id) if ((mask>>i)&1) eid[i]=tot,op=M-op; // merge所有和原始id颜色相同的点
                vector<int> newe=reid(e,eid,tot+1);
                // printf("id=%d\n",id);
                // printf("solve %d\n",(int)e.size());
                // REP_(i,n) {pr2(e[i],n); puts("<- e");}
                // REP_(i,n) printf("%d ",eid[i]); puts("<- eid");
                // REP_(i,(int)newe.size()) {pr2(newe[i],newe.size()); puts("<- new_e");}
                if ((newe[tot]>>tot)&1) continue; // 自环了,答案为0
                int val=solve(newe,k);
                // printf("val=%d\n",val);
                add_(ans,val*op%M);
            }
        }
        return ans;
    }
}
int main() {
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    vector<int> e(n);
    FOR_(i,1,m) {
        int u,v;
        scanf("%d%d",&u,&v);
        u--; v--;
        e[u]|=1<<v; e[v]|=1<<u;
    }
    printf("%d\n",solve(e,k));
}
/*
6 5 2
1 2
2 3
3 4
4 1
1 6

4 2 2
1 2
3 4
*/
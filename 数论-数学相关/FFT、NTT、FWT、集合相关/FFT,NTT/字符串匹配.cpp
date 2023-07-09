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
const LL maxn=1.2e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
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

namespace BruteForce {
    vector<int> mul(const vector<int> &A,const vector<int> &B,int mod)  { //C=A*B
        int n=A.size(),m=B.size();
        int i,j;
        vector<int> C(n+m-1,0);
        REP(i,n) REP(j,m) C[i+j]=(C[i+j]+(ll)A[i]*B[j])%mod;
        return C;
    }
}
// 做字符串匹配
// FOR NTT
// 950009857: 7
// 998244353: 3
// 104857601: 3
// 167772161: 3
template<int MOD=998244353,int g=3>
struct NTT {
    static const int bruteforce_limit=16;
    vector<int> roots{0,1};
    inline int mul(int x,int y) {
        ll ret=(ll)x*y; (ret>MOD) &&(ret%=MOD);
        return ret;
    }
    int poww(int a,int b) {
        int ret=1;
        for (; b; b>>=1,a=mul(a,a))
            if (b&1) ret=mul(ret,a);
        return ret;
    }
    void dft(vector<int> &A,int len,int inv) {
        assert((int)A.size()==len);
        if (inv==-1) reverse(A.begin()+1, A.end());
        int i,j,k;
        // bitrev[i] = bitrev[i >> 1] >> 1 | (i & 1) << __builtin_ctz(len);
        for (i=1,j=len/2; i<len-1; i++) {
            if (i<j) swap(A[i],A[j]);
            k=len/2;
            while (j>=k) j-=k,k/=2;
            if (j<k) j+=k;
        }
        if ((int)roots.size()<len) {
            int k=__builtin_ctz(roots.size());
            roots.resize(len);
            while ((1<<k)<len) {
                int e=poww(g,(MOD-1)>>(k+1));
                for (int i=1<<(k-1); i<(1<<k); ++i) {
                    roots[2*i]=roots[i];
                    roots[2*i+1]=mul(roots[i],e);
                } ++k;
            }
        }
        for (i=1; i<len; i<<=1) { //fin version
            for (j=0; j<len; j+=i+i) { //merge length = i+i
                for (k=0; k<i; k++) {
                    int a=A[k+j];
                    // assert(k+i+j<(int)A.size());
                    // assert(k+i<(int)roots.size());
                    int b=mul(A[k+i+j],roots[k+i]);
                    int u=a+b; (u>=MOD) &&(u-=MOD); A[k+j]=u;
                    int v=a-b; (v<0) &&(v+=MOD); A[k+i+j]=v;
                }
            }
        }
        if (inv==-1) {
            int vn=poww(len,MOD-2);
            REP(i,len) A[i]=mul(A[i],vn);
        }
    }
    vector<int> mul(const vector<int> &A,const vector<int> &B) { //C=A*B
        int n=A.size(),m=B.size();
        if (min(n,m)<=bruteforce_limit)
            return BruteForce::mul(A,B,MOD);
        int len=1; int i;
        while (len<n+m-1) len<<=1;
        vector<int> _A(A),_B;
        _A.resize(len,0); dft(_A,len,1);
        if (A==B) _B=_A; else _B=B,_B.resize(len,0),dft(_B,len,1);
        REP(i,len) _A[i]=mul(_A[i],_B[i]);
        dft(_A,len,-1); _A.resize(n+m-1);
        return _A;
    }
};

// usage: match<mod,g> match(S,P,N,M)
template<int MOD=998244353,int g=3>
vector<int> match(char S[],char P[],int N,int M) {
    // S字符串中找P字符串(0开始); _字符为通配符,其他字符都得匹配上; 考虑把_设成0, 那么sum的时候判断(x-y)^2*y就可以了
    // (x-y)^2*y = x^2*y-2*x*y^2+y^3
    auto func=[&](char c) {
        if (c=='_') return 0;
        if (c=='.') return 1;
        if ('A'<=c&&c<='Z') return c-'A'+2;
        if ('a'<=c&&c<='z') return c-'a'+2+26;
        return -1;
    };
    NTT<MOD,g> ntt;
    vector<int> Match(N-M+1);
    {
        vector<int> A(N),B(M);
        REP_(i,N) A[i]=func(S[i])*func(S[i]);
        REP_(i,M) B[M-i-1]=func(P[i]);
        vector<int> C=ntt.mul(A,B);
        rep_(i,M-1,N) Match[i-(M-1)]=(Match[i-(M-1)]+C[i])%MOD;

        // for (int v:A) printf("%d ",v); puts("<- A");
        // for (int v:B) printf("%d ",v); puts("<- B");
        // for (int v:C) printf("%d ",v); puts("<- C");
        // for (int v:Match) printf("%d ",v); puts("<- Match");
    }
    {
        vector<int> A(N),B(M);
        REP_(i,N) A[i]=func(S[i]);
        REP_(i,M) B[M-i-1]=func(P[i])*func(P[i]);
        vector<int> C=ntt.mul(A,B);
        rep_(i,M-1,N) Match[i-(M-1)]=(Match[i-(M-1)]-2ll*C[i]+2ll*MOD)%MOD;

        // for (int v:A) printf("%d ",v); puts("<- A");
        // for (int v:B) printf("%d ",v); puts("<- B");
        // for (int v:C) printf("%d ",v); puts("<- C");
        // for (int v:Match) printf("%d ",v); puts("<- Match");
    }
    {
        int all=0;
        REP_(i,M) all=(all+func(P[i])*func(P[i])*func(P[i]))%MOD;
        for (int &v:Match) v=(v+all)%MOD;
        // for (int v:Match) printf("%d ",v); puts("<- Match");
    }
    return Match;
}
char S[maxn],P[maxn];
int main() {
    // \sum (x-y)^2 * y = x^2*y-2x*y^2+y^3;
    int L,W;
    scanf("%d%d",&L,&W);
    scanf("%s",S);
    scanf("%s",P);
    rREP_(i,L) S[i+W-1]=S[i];
    REP_(i,W-1) S[i]='.';
    REP_(i,W-1) S[i+W-1+L]='.';

    auto sol1=match<950009857,7>(S,P,L+W+W-2,W);
    auto sol2=match<998244353,3>(S,P,L+W+W-2,W);
    int ans=0;
    for (int i=0;i<(int)sol1.size();i++) if (!sol1[i]&&!sol2[i]) ans++;
    printf("%d\n",ans);
}
/*
3 5
ABC
_____3 5
ABC
_ABC_


3 5
ABC
_ABC_
*/
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
const LL M=1e9+7;
const LL maxn=1e6+107;
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

//m个式子,n个变量
//maximize C[i]*value
namespace Simplex {
    int n,m;//n变量, m式子
    const int maxn=500,maxm=5000;
    double A[maxm][maxn],B[maxm];
    double C[maxn];//base
    double v=0;
    const double inf=1e20;
    const double eps=1e-7;
    void pivot(int l,int e) {
        B[l]/=A[l][e];
        for (int i=1; i<=n; i++)
            if (i!=e) A[l][i]/=A[l][e];
        A[l][e]=1/A[l][e];
        for (int i=1; i<=m; i++)
            if (i!=l&&fabs(A[i][e])>eps) {
                B[i]-=B[l]*A[i][e];
                for (int j=1; j<=n; j++)
                    if (j!=e) A[i][j]-=A[l][j]*A[i][e];
                A[i][e]=-A[l][e]*A[i][e];
            }
        v+=C[e]*B[l];
        for (int i=1; i<=n; i++)
            if (i!=e) C[i]-=C[e]*A[l][i];
        C[e]=-C[e]*A[l][e];
    }
    double simplex() {
        int l,e;
        double t;
        while (true) {
            e=n+1;
            for (int i=1; i<=n; i++)
                if (C[i]>eps) {e=i; break;}
            if (e==n+1) break;
            t=inf; l=0;
            for (int i=1; i<=m; i++)
                if (A[i][e]>eps&&t>B[i]/A[i][e]) {
                    t=B[i]/A[i][e]; l=i;
                }
            if (t==inf) return inf;
            pivot(l,e);
        }
        return v;
    }
}
int main() {
    int n,m,i,j;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%lf",&Simplex::C[i]);
    FOR(i,1,m) {
        int l,r,c;
        scanf("%d%d%d",&l,&r,&c);
        FOR(j,l,r) Simplex::A[i][j]=1;
        Simplex::B[i]=c;
    }
    Simplex::n=n; Simplex::m=m;
    printf("%.0f",Simplex::simplex());
}
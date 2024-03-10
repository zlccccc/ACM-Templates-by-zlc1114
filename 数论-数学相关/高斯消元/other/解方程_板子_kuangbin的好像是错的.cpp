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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=1e6+7;
const long double eps=1e-15;
const double pi=acos(-1.0);
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M; return ret;}

//emmmm kuangbin模板好像是错的
//这里是求正整数的类似解,可能会不够精确
bool gauss(long double A[107][107],long double X[107],int n,int m) {
    int i,j,k;
    REP(i,n) {
        int id=i;
        rep(j,i+1,m) if (abs(A[j][i])>abs(A[id][i])) id=j;
        if (abs(A[id][i])<eps) continue;
        if (id!=i)
            {rep(j,i,n) swap(A[i][j],A[id][j]); swap(X[i],X[id]);}
        REP(k,m) if (k!=i) {
            X[k]-=A[k][i]/A[i][i]*X[i];
            rrep(j,i,n) A[k][j]-=A[k][i]/A[i][i]*A[i][j];
        }
    }
    REP(i,n) if (abs(A[i][i])<eps&&abs(X[i])>eps) return 0;
    rep(i,n,m) if (abs(X[i])>eps) return 0;
    REP(i,n) if (abs(A[i][i])<eps||abs(X[i])<eps) X[i]=0;
    else X[i]/=A[i][i];
    return 1;
}
int n,m;
long double A[107][107],X[107],Y[107],ALL;
int i,j,k;
int u[maxn],v[maxn],w[maxn],D[maxn];
int main() {
    scanf("%d%d",&n,&m);
    REP(i,m) {
        scanf("%d%d%d",&u[i],&v[i],&w[i]);
        D[u[i]]+=w[i];
    }
    REP(i,n) if (D[i]) A[i][i]=1;
    REP(i,n) A[n][i]=1; X[n]=1;
    REP(i,m) A[v[i]][u[i]]-=1.0*w[i]/D[u[i]];
//    int i,j;
//    FOR(i,0,n){
//        FOR(j,0,n-1) printf("%.5lf ",A[i][j]);printf("%lf",X[i]);puts("");
//    }
    if (!gauss(A,X,n,n+1)) {assert(0); return 0*puts("Impossible");}
    else {
        REP(i,n) assert(X[i]>=0&&X[i]<=1);
        REP(i,n) printf("%.19Lf\n",X[i]),ALL+=X[i];
    } assert(abs(ALL-1)<=1e-9);
    REP(i,m) Y[v[i]]+=X[u[i]]/D[u[i]]*w[i];
    REP(i,n) if (D[i]) assert(abs(Y[i]-X[i])<=1e-9);
}
/*
2 2
0 1 1
1 1 2
*/

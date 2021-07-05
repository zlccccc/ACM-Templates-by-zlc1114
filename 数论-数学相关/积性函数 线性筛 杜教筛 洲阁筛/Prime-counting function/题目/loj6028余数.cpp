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

int nxt[13];
LL H[maxn][13],L[maxn][13];
void calc(LL n,int M){
    LL p,k,m;int i;
    //2->p | 2->n/m
    for (m=1;m*m<=n;++m) {
        REP(i,M) H[m][i]=(n/m-i+M)/M;
        REP(i,2) H[m][i%M]--;
//        printf("%lld : ",n/m);
//        REP(i,M) printf("%lld ",H[m][i]);puts("");
    }FOR(p,1,m) {
        REP(i,M) L[p][i]=(p-i+M)/M;
        REP(i,2) L[p][i%M]--;
//        printf("%lld : ",p);
//        REP(i,M) printf("%lld ",L[p][i]);puts("");
    }
    FOR(p,2,m){
        if (L[p][p%M]==L[p-1][p%M]) continue;
        REP(i,M) nxt[i]=i*p%M;
        FOR(k,1,min(m-1,n/p/p)){
            if (p*k<m) REP(i,M) H[k][nxt[i]]-=H[p*k][i]-L[p-1][i];
            else REP(i,M) H[k][nxt[i]]-=L[n/p/k][i]-L[p-1][i];
        }rFOR(k,p*p,m) REP(i,M) L[k][nxt[i]]-=L[k/p][i]-L[p-1][i];
//        printf("%d: ",p);REP(i,M) printf("%d ",L[p][i]);puts("");
    }
}
int main() {
    LL n;int m,i;
    scanf("%lld%d",&n,&m);calc(n,m);
    REP(i,m) printf("%lld\n",H[1][i]);
}
/*
*/

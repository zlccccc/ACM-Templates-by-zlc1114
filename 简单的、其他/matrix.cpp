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
typedef long long ll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int T;
int n,m;
const int MAX=4;
struct matrix{
    int A[MAX][MAX];
    matrix(){
        memset(A,0,sizeof(A));
    }
}base;
matrix mul(const matrix &A,const matrix &B){
    matrix C; int i,j,k;
    REP(i,MAX) REP(j,MAX) REP(k,MAX)
        C.A[i][j]=((LL)A.A[i][k]*B.A[k][j]+C.A[i][j])%M;
    return C;
}
matrix poww(matrix a,ll b) {
    matrix ret; int i; REP(i,MAX) ret.A[i][i]=1;
    for (;b;b>>=1ll,a=mul(a,a))
        if (b&1) ret=mul(ret,a);
    return ret;
}
char a[107];
int i,j,k;
int main(){
    int x;
    base.A[0][0]=2; base.A[0][1]=1; base.A[0][2]=1; base.A[0][3]=0;
    base.A[1][0]=1; base.A[1][1]=2; base.A[1][2]=0; base.A[1][3]=1;
    base.A[2][0]=1; base.A[2][1]=0; base.A[2][2]=2; base.A[2][3]=1;
    base.A[3][0]=0; base.A[3][1]=1; base.A[3][2]=1; base.A[3][3]=2;
    FOR(i,1,20) printf("%d ",poww(base,i).A[0][0])
    printf("%d\n",poww(base,n).A[0][0]);
}
/*
*/

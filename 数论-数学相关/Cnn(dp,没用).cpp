#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3f;
const LL M=1e9+7;
const LL N=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}


LL a[N];
LL n,m;
LL i;
//C(n)(n)
const LL Cmax=1001;
LL C[Cmax][Cmax];
void buildC() {
    C[0][1]=C[1][1]=1;
    int i,j;
    FOR(j,2,Cmax) {
        C[0][j]=1;
        FOR(i,1,j) C[i][j]=(C[i-1][j-1]+C[i][j-1])%M;
    }
}
int main() {
    scanf("%d%d",&x,&y);
    printf("%d %d",b.x,b.y);
}
/*
*/

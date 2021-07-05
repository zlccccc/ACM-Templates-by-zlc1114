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
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int T;
LL f[1<<12|7],g[1<<12|7];
int a[12][12];
int main(){
    scanf("%d",&T);
    while (T--){
        int n,m;
        int i,j,k;
        scanf("%d%d",&n,&m);
        REP(i,n) REP(j,m) scanf("%d",&a[i][j]);
        REP(k,1<<(m+1)) g[k]=0;g[0]=1;
        REP(i,n){
            REP(j,m){
                REP(k,(1<<(m+1))){
                    int x=1<<j,y=1<<(j+1);//x:right; y:down
                    if (a[i][j]){
                        if ((k&x)&&(k&y)||!(k&x)&&!(k&y)) f[k]=g[k^x^y];
                        else f[k]=g[k]+g[k^x^y];
                    }else{
                        if (!(k&x)&&!(k&y)) f[k]=g[k];
                        else f[k]=0;
                    }
                }REP(k,(1<<(m+1))) g[k]=f[k];
            }rREP(k,(1<<(m+1))) g[k]=g[k>>1];
            REP(k,(1<<(m+1))) if (k&1) g[k]=0;
        }static int x;
        printf("Case %d: There are %lld ways to eat the trees.\n",++x,f[0]);
    }
}
/*
*/

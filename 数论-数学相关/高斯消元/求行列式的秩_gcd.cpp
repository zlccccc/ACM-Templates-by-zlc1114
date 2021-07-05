#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
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
const LL MOD=1e9+7;
const LL maxn=1e4+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%MOD) ret=1ll*ret*a%MOD;return ret;}

//辗转相除法是错的,这里是错误的求行列式秩的方法
//会爆LL
LL n,m;
LL i,j,k;
LL a[maxn][maxn];
LL ans;
int main(){
    while (~scanf("%I64d%I64d",&n,&m)){
        REP(i,n)
            REP(j,n) scanf("%I64d",&a[i][j]);
        ans=1;
        REP(i,n){
            rep(j,i+1,n){
                int x=i,y=j;
                while (a[y][i]){
                    LL t=a[x][i]/a[y][i];
                    rep(k,i,n) a[x][k]=(a[x][k]-a[y][k]*t)%m;
                    swap(x,y);
                }
                if (x!=i){
                    rep(k,i,n) swap(a[i][k],a[x][k]);
                    ans=(-ans+m)%m;
                }
            }
            ans=ans*a[i][i]%m;
            ans=(ans+m)%m;
        }
        printf("%I64d\n",ans);
    }
}
/*
*/

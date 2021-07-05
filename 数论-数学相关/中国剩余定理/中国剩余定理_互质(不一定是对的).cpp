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
const LL maxn=100+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%MOD) ret=1ll*ret*a%MOD;return ret;}

template<typename T>inline T poww(T a,T b,T MOD) {
    T ret=1;
    for (; b; b>>=1ll,a=1ll*a*a%MOD)
        ret=1ll*ret*a%MOD;
    return ret;
}
void exgcd(LL a,LL b,LL &x,LL &y){
    if (!b) {x=1;y=0;}
    else {exgcd(b,a%b,y,x);y-=a/b*x;}
}
int n,m;
int i,j,k;
vector<LL> P,O;
int ans;
LL chinese_remainder(vector<LL> &P,vector<LL> &O){
    LL ret=0;int i;LL M=1;
    REP(i,P.size()) M*=P[i];
    REP(i,P.size()){
        LL x,y,Mi=M/P[i];
        exgcd(Mi,P[i],x,y);
        (ret+=Mi*x*O[i])%M;
    }(ret<0)&&(ret+=M);
    return ret;
}
int main(){
	while (~scanf("%d",&n)){
        P.clear();O.clear();
        REP(i,n){
            LL k;
            scanf("%lld",&k);P.push_back(k);
            scanf("%lld",&k);O.push_back(k);
        }printf("%lld\n",chinese_remainder(P,O));
	}
}
/*
*/

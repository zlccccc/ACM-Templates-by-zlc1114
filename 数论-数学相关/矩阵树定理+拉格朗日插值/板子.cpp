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

//f(x)=y; n个->得到一个ans
//拉格朗日插值,f(x)=sigma{(x-xj)/(xi-xj)};{i!=j}
int n,m;
int i,j,k;
LL val[107],v_v[107];
LL f[107],g[107],ans[107];
int main(){
    g[0]=1;REP(i,n) rFOR(j,0,i) (g[j+1]+=g[j])%=M,(g[j]*=(M-v_v[i]))%=M;
    REP(k,n){
        LL rev=1,t=0;
        rFOR(i,0,n) f[i]=(g[i+1]+f[i+1]*v_v[k]%M+M)%M;
        REP(j,n) if (j!=k) (rev*=(v_v[k]-v_v[j]))%=M;
        (rev<0)&&(rev+=M);rev=powMM(rev,M-2);
        rev=(rev*val[k])%M;
        FOR(i,0,n) (ans[i]+=(LL)f[i]*rev%M)%=M;
    }FOR(i,0,n-1) printf("%lld ",ans[i]);
}
/*
*/

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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

//n^x(mod m)=m^(phi(m)+x%phi(m))%m (x>m)
inline int mod(LL a,int b){
    if (a<b) return a;
    return a%b+b;
}
inline int poww(int a,int b,int M){
    int ret=1;
    for (;b;b>>=1ll,a=mod(1ll*a*a,M))
        if (b&1) ret=mod(1ll*ret*a,M);
    return ret;
}
typedef pair<int,int> pii;
int P[maxn];
int phi(int x){
    int k=x;
    for (int i=2;i*i<=k;i++) if (k%i==0){
        x=x/i*(i-1);
        while (k%i==0) k/=i;
    }if (k!=1) x=x/k*(k-1);
    return x;
}
int a[maxn];
int tot;
int solve(int l,int r,int pos){
    if (l==r||pos==tot) return mod(a[l],P[pos]);
    return poww(a[l],solve(l+1,r,pos+1),P[pos]);
}
int n,m,q;
int i,j,k;
int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",&a[i]);
    P[1]=m;
    for (tot=1;P[tot]!=1;tot++) P[tot+1]=phi(P[tot]);
//    FOR(i,1,tot) printf("%d ",P[i]);puts("");
    scanf("%d",&q);
    FOR(i,1,q){
        int l,r;int ans=1;
        scanf("%d%d",&l,&r);
        printf("%d\n",solve(l,r,1)%m);
    }
}
/*
*/

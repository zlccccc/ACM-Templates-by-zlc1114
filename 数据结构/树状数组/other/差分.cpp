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
#include <iomanip>
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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

typedef pair<int,int> pii;
vector<pii> Q[maxn];
int n,m;
int i,j;
int f[maxn],a[maxn];
int ans[maxn];
LL A[maxn],B[maxn];//A*i+B
inline int lowbit(int x){return x&-x;}
void Add(int x,LL val,LL VAL){
    for (;x<=n;x+=lowbit(x)) (A[x]+=val)%=M,(B[x]+=VAL)%=M;
}
void add(int l,int r,LL val){
    Add(l,val,-((l-1)*val%M)+M);
    Add(r+1,M-val,r*val%M);
}
LL query(int x){
    LL ret=0;for (int i=x;x;x-=lowbit(x)) (ret+=A[x]*i+B[x])%=M;
    return ret;
}
LL query(int l,int r){
    return (query(r)-query(l-1)+M)%M;
}
int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",&a[i]),f[i]=i-1;
    FOR(i,1,m){
        int l,r;
        scanf("%d%d",&l,&r);
        Q[r].push_back(make_pair(l,i));
    }
    FOR(i,1,n){
        for (j=i;j;j=f[j]) a[j]=gcd(a[i],a[j]);
        for (j=i;j;j=f[j]) while (a[j]==a[f[j]]) f[j]=f[f[j]];
        for (j=i;j;j=f[j]) add(f[j]+1,j,a[j]);
        for (auto now:Q[i]){
            ans[now.second]=query(now.first,i);
        }
    }FOR(i,1,m) printf("%d\n",ans[i]);
}
/*
*/

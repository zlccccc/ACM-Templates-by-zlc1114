#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <set>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}

int a[maxn];
int n,i,j;
const int MAX=1000000;
inline int lowbit(int x) {return x&-x;}
inline void insert(int x) {
    for (; x<=MAX; x+=lowbit(x)) a[x]++;
}
inline int find(int x) {
    while (x&&!a[x]) x^=lowbit(x);
    if (!x) return 0;
    int t=lowbit(x)>>1,y=a[x];
    while (t) {
        if (y-a[x-t]) y-=a[x-t];
        else {y=a[x-t]; x=x-t;}
        t>>=1;
    }
    return x;
}
int ans;
const int MOD=19260817;
int main() {
    while (~scanf("%d",&n)) {
        ans=0;
        FOR(i,1,1000000) a[i]=0;
        REP(i,n) {
            scanf("%d",&j);
            if (j==0) continue;
            ans=ans+find(j);
//          printf("%d ",find(j));
            insert(j);
            ans%=MOD;
        }
        printf("%d\n",ans);
    }
}

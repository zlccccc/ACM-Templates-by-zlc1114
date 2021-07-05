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
inline T abs(T a) {return a>0?a:-a;}

LL a[N];
int n,m;
int i,j,x;
//binary chop==two split???
bool judge(LL mid) {
    if(a[mid]<x) return 1;
    return 0;
}
int solve() {
    LL l=0,r=n+1,mid;
    while(l+1<r) {
        mid=l+(r-l)/2;
        if(judge(mid)) l=mid;
        else r=mid;
    }
    if(l+1<=n&&a[l+1]==x) return l+1;
    return 0;
}

int main() {
    a[0]=-INFF;
    while(~scanf("%d%d",&n,&m)) {
        FOR(i,1,n) scanf("%d",a+i);
        REP(i,m) {
            scanf("%d",&x);
            j=solve();
            if(j!=0) printf("%d\n",j);
            else printf("error\n");
        }
    }
}
/*
*/

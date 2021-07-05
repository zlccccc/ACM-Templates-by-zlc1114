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
const double pi=acos(-1.0);
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M; return ret;}

inline int sgn(double x) {
    if (abs(x)<eps) return 0;
    if (x<0) return -1;
    return 1;
}
struct point {
    LL x,y;
    bool operator <(const point &a) const {
        if (y<a.y) return 1;
        if (y>a.y) return 0;
        return x<a.x;
    }
} p[maxn],P[maxn],p1[maxn];
inline LL X(point A,point B,point C) {
    return (B.x-A.x)*(C.y-A.y)-(B.y-A.y)*(C.x-A.x);
}
inline LL len(point A,point B) {
    return (A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y);
}
bool cmp(point A,point B) {
    LL cp=X(p[0],A,B);
    if (cp>0) return 1;
    if (cp<0) return 0;
    return len(p[0],A)<len(p[0],B);
//  return sgn(len(p[0],A)-len(p[0],B))<=0;
}
int n;
LL getMAX() { //求完凸包旋转卡壳
    int tot,i,j,m;
    LL ans=0;
    if (n==1) {
        tot=0;
        P[0]=p[0];
    } else if (n==2) {
        tot=1;
        P[0]=p[0];
        P[1]=p[1];
    } else {
        REP(i,n) if (p[i]<p[0]) swap(p[0],p[i]);
        sort(p+1,p+n,cmp);
        P[0]=p[0];
        P[1]=p[1];
        tot=1;
        rep(i,2,n) {
            while (tot&&X(P[tot-1],P[tot],p[i])<=0) tot--;
            P[++tot]=p[i];
        }
    } m=tot;
    FOR(i,0,tot) P[++m]=P[i];
    j=0; ans=0;
    FOR(i,0,m) {
        while (j<m&&len(P[i],P[j])<len(P[i],P[j+1])) j++;
        ans=max(ans,len(P[i],P[j]));
    } return ans;
}
inline int cmpx(point a,point b) {return a.x<b.x;}
inline int cmpy(point a,point b) {return a.y<b.y;}
LL getMIN(int l,int r) { //分治求最近点对,nsqrtn
    LL ans=0;
    int i,j;
    if (l>=r) return INFF;
    if (l+1==r) return len(p[l],p[r]);
    int mid=(l+r)>>1;
    ans=min(getMIN(l,mid),getMIN(mid+1,r));
    int cn=0;
    FOR(i,l,r) if (p[i].x-p[mid].x<ans) p1[cn++]=p[i];
    sort(p1,p1+cn,cmpy);
    REP(i,cn) {
        rep(j,i+1,cn) {
            if (p1[j].y-p1[i].y>=ans) break;
            ans=min(ans,len(p1[i],p1[j]));
        }
    } return ans;
}
int i,j,k;
LL ans;
int main() { //0->tot是凸包上的点
    while (~scanf("%d",&n)) {
        REP(i,n) scanf("%lld%lld",&p[i].x,&p[i].y);
        sort(p,p+n,cmpx);
        printf("%lld %lld\n",getMIN(0,n-1),getMAX());
    }
}
/*
*/

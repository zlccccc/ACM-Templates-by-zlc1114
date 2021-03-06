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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
struct node{
    double x,y;
    bool operator <(const node &a) const{
        if (y<a.y) return 1;
        if (y>a.y) return 0;
        return x<a.x;
    }
}p[maxn],P[maxn];
inline double X(node A,node B,node C){
    return (B.x-A.x)*(C.y-A.y)-(B.y-A.y)*(C.x-A.x);
}
inline double len(node A,node B){
    return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}
bool cmp(node A,node B){
    double cp=X(p[0],A,B);
    if (cp>0) return 1;
    if (cp<0) return 0;
    return len(p[0],A)<len(p[0],B);
}
int n,m;
double t;
int tot;
int i,j,k;
double ans;
int main(){
	while (~scanf("%d%lf",&n,&t)){
        REP(i,n) scanf("%lf%lf",&p[i].x,&p[i].y);
        ans=2*pi*t;
        if (n==1) printf("%.0lf",ans);
//        else if (n==2) printf("%.0lf",ans+len(p[0],p[1]));
        else {
            REP(i,n) if (p[i]<p[0]) swap(p[0],p[i]);
            sort(p+1,p+n,cmp);
            P[0]=p[0];
			P[1]=p[1];
			tot=1;
			rep(i,2,n){
				while (tot>0&&X(P[tot-1],P[tot],p[i])<=0) tot--;
				P[++tot]=p[i];
			}
			REP(i,tot) ans+=len(P[i],P[i+1]);
			ans+=len(P[0],P[tot]);
			printf("%.0lf",ans);
        }
        puts("");
	}

}
/*
*/

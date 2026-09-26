#include <sstream>
#include <fstream>
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
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG1
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void add(T &A,int B) {A+=B; (A>=M) &&(A-=M);}
template<typename T>inline void multi(T &A,ll B) {(A*=B)%=M;}
template<typename T>inline void mod(T &A,ll B=M) {A%=M;}
template<typename T>inline void maxi(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void mini(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int n,m;
char S[maxn];
int TaskA();
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_string() {while (~scanf("%s",S)) TaskA();}

// 离线后，维护上凸壳即可
inline int dcmp(double x) {
	return (x>eps)-(x<-eps);
}
struct Point {
	double x,y; int id;
	Point(double x=0,double y=0):x(x),y(y) {};
	bool operator < (const Point &R) const {
		if (dcmp(x-R.x)==0)
			return dcmp(y-R.y)<0;
		return dcmp(x-R.x)<0;
	}
	void input() {
		scanf("%lf%lf",&x,&y);
	}
	Point operator + (const Point &R) const {
		return Point(x + R.x , y + R.y);
	}
	Point operator - (const Point &R) const {
		return Point(x - R.x , y - R.y);
	}
	double operator ^ (const Point &R) const {
		return x * R.y - y * R.x;
	}
	double getk() {
		return y/x;
	}
} P[maxn],Q[maxn]; int top;
double ans[maxn];
void solve(int n) {
	int i; top=0;
	FOR(i,1,n) {
		if (!P[i].id) {
			while (top>1&&((P[i]-Q[top])^(Q[top]-Q[top-1]))<0) top--;
			Q[++top]=P[i];
		} else {
			int l=1,r=top;
			while (r-l>5) {
				int t=(r-l)/3,ml=l+t,mr=r-t;
				if ((P[i]-Q[ml]).getk()>(P[i]-Q[mr]).getk()) l=ml;
				else r=mr;
			} FOR(l,l,r) {
				ans[P[i].id]=max(ans[P[i].id],-(P[i]-Q[l]).getk());
				// printf("%d : %lf\n",P[i].id,-(P[i]-Q[l]).getk());
			}
		}
	}
}
int TaskA() {
	int i;
	scanf("%d",&n);
	FOR(i,1,n) P[i].input(),P[i].id=0;
	scanf("%d",&m);
	FOR(i,n+1,n+m) P[i].input(),P[i].id=i;
	sort(P+1,P+1+n+m);
	solve(n+m);
	FOR(i,1,n+m) P[i].x=-P[i].x,P[i].y=-P[i].y;
	reverse(P+1,P+1+n+m);
	solve(n+m);
	FOR(i,n+1,n+m) if (ans[i]<=eps) puts("No cross");
	else printf("%.10lf\n",ans[i]);
	return 0;
}
void initialize() {}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_one();
}
/*
*/
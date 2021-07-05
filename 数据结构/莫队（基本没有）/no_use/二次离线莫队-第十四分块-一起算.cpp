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

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

// 题意: 区间A[i]%B[i]=0的对数
// 做法: 第十四分块, 二次离线莫队然后再离线bigsmall算贡献, 用fractional cascading(分散层叠也行)
// 分散层叠: 每一层保存这层所有信息+一半下一层的信息(position)
// 那么只lowerbound, 然后while回去就行了, 复杂度k(层数)+log(lowerbound)
// 还是得老老实实算, 不能按贡献算, 因为有可能向前和向后的贡献不一致(?)
// [l,r] to [l,r'] = [1,  r(x)] to [(x+1),r'] - [1,l-1] to [r+1,r'] = sum_l[r']-sum_l[r]-[1,l-1] to [r+1,r']
// [l,r] to [l',r] =-[l(x+1),n] to [(x),l'-1] + [r+1,n] to [l,l'-1] = sum_r[l']-sum_r[l]+[r+1,n] to [l,l'-1](from r+1,rev)
// 下面式子是不对称的(贡献一致可以减常数)
// [l,r] to [l',r] = [1,   (x)] to [(x),l'-1] - [1,  r] to [l,l'-1] = sumlx[l'-1]-sumlx[l-1]-[1,r] to [l,l'-1]
// 二次离线的作用是如果可以O(1)查询某个点的值, O(sqrt)更新, 就可以for一遍范围直接加起来!
// 二次离线之后还是要再离线算其他的贡献
struct node {
	int l,r,pos,type;
} Q[maxn];
vector<node> Ql[maxn];
int A[maxn];
int BLOCK[maxn];// 莫队sqrt
const int SIZE=300;
int sumx[maxn],sumy[maxn];
ll suml[maxn],sumlx[maxn];
ll base[maxn],ans[maxn];//more
int C[maxn];//front
int SIZE_B=50;// big_small
int main() {
	int i;
	int n,q;
	scanf("%d%d",&n,&q);
	FOR(i,1,n) scanf("%d",&A[i]);
	FOR(i,1,n) BLOCK[i]=i/SIZE;
	FOR(i,1,q) scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].pos=i;
	sort(Q+1,Q+1+q,[&](node &x,node &y) {
		if (BLOCK[x.l]!=BLOCK[y.l]) return BLOCK[x.l]<BLOCK[y.l];
		else return bool((x.r<y.r)^(BLOCK[x.l]&1));
	});
	int l=1,r=0;
	FOR(i,1,q) {
		int l_l=Q[i].l,r_r=Q[i].r,base;
		base=-1; if (r>r_r) swap(r,r_r),base*=-1;
		if (r<r_r) Ql[l-1].push_back(node{r+1,r_r,i,base}); r=Q[i].r;
		base=-1; if (l>l_l) swap(l,l_l),base*=-1;
		if (l<l_l) Ql[r].push_back(node{l,l_l-1,i,base}); l=Q[i].l;
	}
	int k;
	//left
	FOR(i,1,100000) C[i]=0;
	FOR(i,1,n) {//x=ky or {kx=y and x>sqrt}
		suml[i]=C[A[i]];
		for (int k=1; k*k<=A[i]; k++) {
			if (A[i]%k==0) {
				C[k]++; if (k*k!=A[i]) C[A[i]/k]++;
			} //first
		}//==, 题意要算两遍
		if (A[i]>SIZE_B)
			for (int k=A[i]; k<=100000; k+=A[i]) C[k]++;
		sumlx[i]=C[A[i]];
		for (auto now:Ql[i]) {
			FOR(k,now.l,now.r) base[now.pos]+=C[A[k]]*now.type;
		}
	}//first
	FOR(k,1,SIZE_B) {
		FOR(i,1,n) {
			sumx[i]=sumx[i-1];  sumy[i]=sumy[i-1];
			if (A[i]==k) sumx[i]++;
			if (A[i]%k==0) {
				sumy[i]++;
				suml[i]+=sumx[i-1]; sumlx[i]+=sumx[i];
			}
		}
		FOR(i,1,n) for (auto now:Ql[i])
			base[now.pos]+=(ll)sumx[i]*(sumy[now.r]-sumy[now.l-1])*now.type;
	}
	FOR(i,1,n) suml[i]+=suml[i-1],sumlx[i]+=sumlx[i-1];
	l=1,r=0;
	FOR(i,1,q) {
		int l_l=Q[i].l,r_r=Q[i].r,x=Q[i].pos;
		base[i]=suml[r_r]-suml[r]+sumlx[l_l-1]-sumlx[l-1]+base[i]+base[i-1];
		ans[x]=base[i]+r_r-l_l+1;
		l=l_l; r=r_r;
	}
	FOR(i,1,q) printf("%lld\n",ans[i]);
}
/*
*/
// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define REP_(I,N) for (int I=0,END=(N);I<END;I++)
#define rREP_(I,N) for (int I=(N)-1;I>=0;I--)
#define rep_(I,S,N) for (int I=(S),END=(N);I<END;I++)
#define rrep_(I,S,N) for (int I=(N)-1,START=(S);I>=START;I--)
#define FOR_(I,S,N) for (int I=(S),END=(N);I<=END;I++)
#define rFOR_(I,S,N) for (int I=(N),START=(S);I>=START;I--)

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
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=1e-10;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
inline ll fastgcd(ll a, ll b) {  // __gcd()
    if (!b) return a;
    ll az=__builtin_ctzll(a),bz=__builtin_ctzll(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az, diff=b-a, az=__builtin_ctzll(diff);
        (b>a)&&(b=a), a=abs(diff);
    }
    return b<<z;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,5> ar5;
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));
vector<pii> direction4 = {{-1,0},{0,-1},{0,1},{1,0}};
vector<pii> direction8 = {{-1,-1},{-1,0},{1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

//dlx:求解精确覆盖 (n个点覆盖m个格子)
//link的意思是,r覆盖了c
//暴力枚举,n个点覆盖m个格子; 注意一定要init
struct DLX {
	int n,m;
    vector<int> U,D,R,L,col,row;
    vector<int> H,S; //S:cnt
	vector<int> ans;  // 
    DLX(int n=0,int m=0) {
        init(n,m);
    }
	void init(int _n,int _m) {
		n=_n; m=_m;
        ans.resize(n+1);  // select
        S.resize(m+1); H.resize(n+1, -1);
        U.resize(m+1); D.resize(m+1);
        L.resize(m+1); R.resize(m+1);
        col.resize(m+1); row.resize(m+1);
		FOR_(i,0,m) {
			S[i]=0;
			U[i]=D[i]=i;
			L[i]=i-1,R[i]=i+1;
		} R[m]=0; L[0]=m; // size: limit
	}
	void link(int r,int c) {
        assert(1<=r&&r<=n);
        assert(1<=c&&c<=m);
        int size=col.size();
		S[c]++;
        col.push_back(c);  // last position
        row.push_back(r);  // last position
        D.push_back(D[c]); U[D[c]]=size;
		D[c]=size; U.push_back(c);
        L.push_back(0); R.push_back(0);
		if (H[r]<0) H[r]=L[size]=R[size]=size;
		else {
			R[size]=R[H[r]]; L[R[H[r]]]=size;
			L[size]=H[r]; R[H[r]]=size;
		}
	}
	void remove(int c) {
		L[R[c]]=L[c]; R[L[c]]=R[c];
		for (int i=D[c]; i!=c; i=D[i])
			for (int j=R[i]; j!=i; j=R[j])
				U[D[j]]=U[j],D[U[j]]=D[j],S[col[j]]--;
	}
	void resume(int c) {
		for (int i=U[c]; i!=c; i=U[i])
			for (int j=L[i]; j!=i; j=L[j])
				U[D[j]]=D[U[j]]=j,S[col[j]]++;
		L[R[c]]=R[L[c]]=c;
	}
	//这里是找可行解; 最优解无法加估价函数剪枝
    vector<int> selected;  // selected
	bool dance() {
		if (R[0]==0) {
            static int res[9][9];
			for (int val:selected) {
				val--;
                int x=val/9/9,y=val/9%9,z=val%9;
                res[x][y]=z+1;
            }
            REP_(i,9) {
                REP_(j,9) {
                    printf("%d ",res[i][j]);
                } puts("");
            }
			return 1;
		}
		// cnt,pos:选择的个数; ans:选择的值(列)
		// if (pos>=cnt&&cnt!=INF) return;
		// if (R[0]==0) {cnt=min(cnt,pos); return;}
		int c=R[0];
		for (int i=R[0]; i; i=R[i])
			if (S[i]<S[c]) c=i;
		remove(c);
		for (int i=D[c]; i!=c; i=D[i]) {
			selected.push_back(row[i]);
			for (int j=R[i]; j!=i; j=R[j]) remove(col[j]);
			if (dance()) return 1;
			for (int j=L[i]; j!=i; j=L[j]) resume(col[j]);
            selected.pop_back();
		} resume(c);
		return 0;
	}
} dlx;

void add(int x,int y,int k) {
	int r=(x*9+y)*9+k;
    // printf("add %d %d %d\n",x,y,k);
	dlx.link(r,9*9*0+x*9+y+1);//position
	dlx.link(r,9*9*1+x*9+k);//行
	dlx.link(r,9*9*2+y*9+k);//列
	dlx.link(r,9*9*3+(x/3*3+y/3)*9+k);//块
}
int solve() {
    dlx.init(9*9*9,9*9*4);
    REP_(x,9) REP_(y,9) {
        int v;
        scanf("%d",&v);
        FOR_(z,1,9) if (!v||v==z) add(x,y,z);
        // FOR_(z,1,9) add(x,y,z);
    }
    dlx.dance();
    return 0;
}
int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(0), cout.tie(0);
    int T = 1;
    // cin>>T;
    // scanf("%d",&T);
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
}
/*
*/
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
#include <bitset>
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

// 题意: N个人,M个椅子,每个人只能坐[1,Li]|[Ri,M],求最多能坐多少人
// hall定理: 二分图; A->B (A<B)完美匹配当且仅当A中每k个在B中连着有至少k个点
// 引理(不常用): 如果A中每个连着最少t条边, B中每个连着最多t条边, 那么存在完美匹配; t任意
// 对于这个题来说: 最终选择的座位比人少; 任意座位集合A; B: [1,Lx][Rx,M]
// 座位当作A, 用定理, 所有区间满足: 对人的集合B, A->B ,|A|>=$加完边$的B 求下|A|-|B|>=0
// 枚举A的端点, 求: B的size最大值即可!
int MIN[maxn],lazy[maxn];
inline void add(int x,int val){
    lazy[x]+=val;MIN[x]+=val;
}void update(int x,int l,int r,int val,int L,int R){
    if (l<=L&&R<=r){add(x,val);return;}
    if (lazy[x]){
        add(x<<1,lazy[x]);
        add(x<<1|1,lazy[x]);
        lazy[x]=0;
    }int mid=(L+R)/2;
    if (l<=mid) update(x<<1,l,r,val,L,mid);
    if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
    MIN[x]=min(MIN[x<<1],MIN[x<<1|1]);
}int n,m;
vector<int> have[maxn];
int i,j,k;
int l,r;
int ans;
int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n){
        scanf("%d%d",&l,&r);
        have[l].push_back(r);
    }
    FOR(i,1,m) update(1,i,i,m-i+1,1,m+1);
    ans=min(0,m-n);//为啥会有这个问题呢
    FOR(i,0,m){
        if (i!=0) update(1,i+1,m+1,1,1,m+1);
        for (int r:have[i])
            update(1,i+1,r,-1,1,m+1);
        ans=min(ans,MIN[1]);
    }printf("%d\n",-ans);
}
/*
*/

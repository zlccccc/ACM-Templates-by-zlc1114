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
template<typename T>inline void pr2(T x,int k=64) {ll i; rREP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int n;
struct frac {
    int x,y;//x/y
    frac(int _x=1,int _y=1):x(_x),y(_y) {}
    bool operator < (const frac &A) const {
        return (ll)x*A.y<(ll)y*A.x;
    }
}
frac query(int x) {
} MIN[maxn]; //len
inline int lowbit(int x) {
    return x&-x;
}
void update(int x,frac val) {
    // printf("update: %d %d/%d\n",x,val.x,val.y);
    for (; x<=n; x+=lowbit(x))
        MIN[x]=min(val,MIN[x]);
    frac ans;
    // printf("query %d\n",x);
    for (; x; x-=lowbit(x))
        ans=min(ans,MIN[x]);
    return ans;
}
vector<pair<int,frac> > segment[maxn];
map<int,int> MP;//value,pos
int R[maxn],cnt[maxn];
int A[maxn],pos[maxn];
vector<pair<int,int> > queries[maxn];
frac ans[maxn];
int main() {
    // startTimer();
    int i,q;
    scanf("%d%d",&n,&q);
    FOR(i,1,n) {
        scanf("%d",&A[i]);
        assert(0<=A[i]&&A[i]<=n);
    } FOR(i,0,n) pos[i]=n+1;
    rFOR(i,1,n) {
        R[i]=pos[A[i]]; pos[A[i]]=i;
    } int now=0,tot=0;//now: mex from
    FOR(i,1,n) {//f[1]
        cnt[A[i]]++;
        if (cnt[now]) {
            while (cnt[now]) now++;
            MP[now]=i;//pos
        }
    } MP[INF]=n+1;//为了简化操作
    FOR(i,1,n) { //remove this 的贡献
        int position=i;//should_add
        while (1) {//不能直接remove
            auto it=MP.lower_bound(A[i]);
            if (it==MP.end()) break;
            if (it->second>=R[i]) break;//del this; position
            int len=it->second-i+1,x=it->first;//should+
            if (position==i) position=it->second;//first_change
            segment[i].push_back(make_pair(it->second,frac(len+1-x,len+1+x))); tot++;
            // printf("%d->%d: mex=%d; len=%d\n",i,it->second,it->first,len);
            // assert(len>=it->first);
            auto itt=it; itt++;
            int _R=itt->second; MP.erase(it);
            if (_R>R[i]) MP[x]=R[i];//insert_more
        }//not!
        if (position!=i&&A[i]) MP[A[i]]=position;
        // if (position!=i&&A[i]) printf("push_%d-%d\n",A[i],position);
    } assert(tot<=3*n);//最大3n以内; 应该说2n以内
    FOR(i,1,q) {//为了用树状数组倒着查emmmm
        int l,r;
        scanf("%d%d",&l,&r);
        assert(1<=l&&l<=r&&r<=n);
        queries[l].push_back(make_pair(r,i));
    } rFOR(i,1,n) {
        for (auto now:segment[i])
            update(now.first,now.second);
        for (auto now:queries[i])
            ans[now.second]=query(now.first);
    } FOR(i,1,q) {
        int g=gcd(ans[i].x,ans[i].y);
        printf("%d/%d\n",ans[i].x/g,ans[i].y/g);
    }
    char str[300];
    assert(scanf("%s",str)==EOF);
    // printTimer();
}
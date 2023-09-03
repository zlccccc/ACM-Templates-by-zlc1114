#include <sstream>
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
#include <functional>
#include <random>
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
// const LL M=1e9+7;
const LL M=998244353;
// ll M=1;
const LL maxn=1.5e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T fastgcd(T a, T b) {
    int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctz(diff);
        min_(b,a); a=abs(diff);
    }
    return b<<z;
}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));
 
int A[maxn];//id: topo
// 区间取min/区间取max; 查询MAX/SUM/MIN等等均可
// 取min只需要维护最大值次大值,次大值比x小的时候暴力递归即可
// 因为至少可以使得最大值和次大值区间合并; 取max同理
struct node{
    int MIN,MINCNT,IMIN;
    int MAX,MAXCNT,IMAX;
    ll SUM; int SIZE,ADD;
    node() {
        SUM=0; SIZE=ADD=0;
        MINCNT=0; MIN=IMIN=INF;
        MAXCNT=0; MAX=IMAX=-INF;
    }
    node(int val){
        SUM=val; SIZE=1; ADD=0;
        MIN=val; MINCNT=1; IMIN=INF;
        MAX=val; MAXCNT=1; IMAX=-INF;
    }
    void seq_add(int val) {
        ADD+=val;
        MIN+=val; IMIN+=val;
        MAX+=val; IMAX+=val;
        SUM+=(ll)SIZE*val;
    }
    void merge(const node &A) {
        SUM+=A.SUM; SIZE+=A.SIZE;
        if (MIN>A.MIN) IMIN=min(MIN,A.IMIN),MIN=A.MIN,MINCNT=A.MINCNT;
        else if (MIN==A.MIN) MINCNT+=A.MINCNT,IMIN=min(IMIN,A.IMIN);
        else IMIN=min(IMIN,A.MIN);
        if (MAX<A.MAX) IMAX=max(MAX,A.IMAX),MAX=A.MAX,MAXCNT=A.MAXCNT;
        else if (MAX==A.MAX) MAXCNT+=A.MAXCNT,IMAX=max(IMAX,A.IMAX);
        else IMAX=max(IMAX,A.MAX);
    }
}T[maxn*4];
ll nowans=0;
void update(int x,int l,int r,int val,int L,int R,int tag=1) {
    if (tag!=3&&T[x].SIZE==0) return; // not useful (nothing inside)
    // printf("update %d %d -> %d (%d-%d): tag=%d; val=%d sum=%lld, cnt=%d\n",x,l,r,L,R,tag,val,T[x].SUM,T[x].SIZE);
    // printf("MIN=%d(%d),%d; MAX=%d(%d),%d\n",T[x].MIN,T[x].MINCNT,T[x].IMIN,T[x].MAX,T[x].MAXCNT,T[x].IMAX);
    if (l<=L&&R<=r) {
        if (tag==0) { // tag=0:区间取max(real l->r)
            // if (!T[x].MINCNT) return; // no item in range L->R
            // if (T[x].IMIN>val) {
            //     if (T[x].MIN<val) {
            //         T[x].SUM+=(ll)(val-T[x].MIN)*T[x].MINCNT;
            //         T[x].MIN=val;
            //     } return;
            // }
        } else if (tag==1) { // tag=1:区间取min(real l->r)
            if (!T[x].MAXCNT) return; // no item in range L->R
            if (T[x].IMAX<val) {
                if (T[x].MAX>val) {
                    T[x].SUM+=(ll)(val-T[x].MAX)*T[x].MAXCNT;
                    T[x].MAX=val;
                } return;
            }
        } else if (tag==2) { // tag=2: 区间sum
            nowans+=T[x].SUM; // sum
            return;
        } else if (tag==3) { // tag=3: 单点set value
            assert(l==r);
            T[x]=node(val);
            return;
        } else if (tag==4) { // 区间add
            T[x].seq_add(val);
            return;
        } else if (tag==5) {
            if (L==R) {
                // printf("%d %d(pos=%d,x=%d) ",T[x].MAX,T[x].SUM,L,x);
                // printf("%d (pos=%d) ",T[x].MAX,x);
                printf("%d (val=%d) ",T[x].MAX,A[L]);
                return;
            }
        }// 区间set value == 区间MIN+区间MAX
    } int mid=(L+R)/2;
    // ADD
    if (T[x].ADD) T[x<<1].seq_add(T[x].ADD),T[x<<1|1].seq_add(T[x].ADD);
    // // MIN
    // update(x<<1,L,mid,T[x].MIN,L,mid,0);
    // update(x<<1|1,mid+1,R,T[x].MIN,mid+1,R,0);
    // MAX
    update(x<<1,L,mid,T[x].MAX,L,mid,1);
    update(x<<1|1,mid+1,R,T[x].MAX,mid+1,R,1);
    // down
    if (l<=mid) update(x<<1,l,r,val,L,mid,tag);
    if (mid<r) update(x<<1|1,l,r,val,mid+1,R,tag);
    // pushup
    T[x]=T[x<<1]; T[x].ADD=0;
    T[x].merge(T[x<<1|1]);
}
 
namespace BIT{
    int T[maxn];
    inline int lowbit(int x) {return x&-x;}
    void update(int x,int val) {
        for (;x<maxn;x+=lowbit(x)) T[x]++;
    }
    int query(int x) {
        int ret=0;
        for (;x;x-=lowbit(x)) ret+=T[x];
        return ret;
    }
}
// https://codeforces.com/contest/1290/problem/E
// 题意: 给个数组,问值域在[1,i]的节点组成的笛卡尔树subtree大小之和
// 做法: 答案是sum{i是j的祖先}+n
// 也就是笛卡尔树左边size+右边size+1; 先算右边再算左边
// 等价于A[i]>A[j]而且A[i]是[i->j]最大值, 维护一下这个范围有多大
// 先考虑i<j(原始位置)时每一个i的贡献,即\sum f[当前时刻][i能够控制的范围]-i
// 相当于给一个f[1,3,4,[?],4,5]数组中间插一个数字,变成[1,3,3,[4],5,6],修改一下范围
// 左边=min(左边,当前插入的pos),右边+=1; 用jry线段树维护sum即可
ll ans[maxn];
int p[maxn];
void solve(int n) { // to-right
    int i;
    FOR(i,1,n) p[A[i]]=i;
    memset(BIT::T,0,sizeof(BIT::T));
    // 维护i->right maxlength
    FOR(i,1,n*4) T[i]=node();
    FOR(i,1,n) {
        int pos=p[i]; nowans=0;
        int r=BIT::query(pos); BIT::update(pos,1);
        update(1,1,pos,r,1,n,1); // 区间min
        update(1,pos,n,1,1,n,4); // 区间+1
        update(1,pos,pos,i,1,n,3); // setval
        update(1,1,n,0,1,n,2); // 区间sum
        ans[i]+=nowans-(ll)i*(i+1)/2;
        // update(1,1,n,0,1,n,5); puts(""); // output)
        // printf("i=%d: p=%d; r=%d nowans=%d\n",i,pos,r,nowans);
    }
}
int main() {
    int n,i;
    scanf("%d",&n);
    // calculate rightson first; and then leftson
    FOR(i,1,n) scanf("%d",&A[i]);
    // \sum {j is anc of i} + n
    // A[j] < A[i] and A[i] is the maximum value of j->i
    solve(n);
    reverse(A+1,A+1+n);
    solve(n);
    reverse(A+1,A+1+n);
    FOR(i,1,n) ans[i]+=i;
    FOR(i,1,n) printf("%lld\n",ans[i]);
}
/*
1 7500
2 6000
5 4000
*/
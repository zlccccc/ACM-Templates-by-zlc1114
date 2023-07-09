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
const LL M=1e9+7;
// const LL M=998244353;
// ll M=1;
const LL maxn=1e6+107;
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

// 在线维护类似priority_queue的序列query操作
// 比如在线对并查集push(x,y,w),pop w最大的位置的边,对并查集查询

// 做法: 由于并查集操作是可逆的(对顺序有影响,但可以用栈push&pop)
// 维护一个堆,每次pop掉k个数字,保证k个数字中至少出现一半w最大的位置
// pop后,最大的那些数字倒着插进去;其他数字放到前面即可
// 这样基本可以保证下次查询pop可以直接pop掉
// 可以证明这么做的话query本身复杂度为qlogq
// 并查集可逆操作就是qlogq*logn;其中logq常数很小

// 题目:
// 问除了[L,R]的边是否存在奇环
// 暴力搞一下就完事
template<bool path_compression=true>
struct DSU {
    vector<int> checkpoint_;
    vector<pair<int,pii>> changes_;
    vector<pii> fa; // fa[x]<0: root; and we save its size
    DSU(int n) {fa.resize(n+1,{-1,0});} // fa<0: size; else: real-getfather
    inline pii getfa(int x) { // root,color
        if (path_compression) {
            if (fa[x].first<0) return pii{x,0}; // root
            pii ret=getfa(fa[x].first);
            ret.second^=fa[x].second; // color in the link
            if (ret!=fa[x]) changes_.push_back({x,fa[x]});
            return fa[x]=ret;
        } else {
            int col=0;
            while (fa[x].first>=0) col^=fa[x].second,x=fa[x].first;
            return pii{x,col};
        }
    }
    void checkpoint() {
        checkpoint_.push_back(changes_.size());
    }
    inline void undo() { // single undo
        auto p=changes_.back();
        fa[p.first]=p.second;
        changes_.pop_back();
    }
    void rollback() { // rollback to checkpoint (stack)
        // printf("rollback\n");
        while ((int)changes_.size()!=checkpoint_.back()) undo();
        checkpoint_.pop_back();
    }
    void merge_solve(int x,int y) {
        pii xval=getfa(x),yval=getfa(y);
        // printf("merge %d %d; fa,col=(%d %d)  (%d %d); pre_allcnt=%d\n",x,y,xval.first,xval.second,yval.first,yval.second,fa.back().first);
        int xcol=xval.second; x=xval.first;
        int ycol=yval.second; y=yval.first;
        // x=getfa(x); y=getfa(y);
        if (x==y) {
            if (xcol==ycol) {
                changes_.push_back({fa.size()-1,fa.back()});
                fa.back().first++;
            }
            return;
        }
        if (-fa[x].first>-fa[y].first) swap(x,y);
        changes_.push_back({x,fa[x]});
        changes_.push_back({y,fa[y]});
        fa[y].first+=fa[x].first; fa[x].first=y; // sz and fa
        fa[x].second=xcol^ycol^1;
    }
};

typedef pair<int,int> Args;

struct TheStack { // stack-like structure
    DSU<false> dsu;
    // DSU<true> dsu;
    int tot=0;
    TheStack(int n):dsu(n) { // rollback to checkpoint needs n+1!
        dsu.fa.push_back({0,0}); // odd number
    }
    void push(Args val) {
        int x=val.first,y=val.second;
        dsu.checkpoint();
        dsu.merge_solve(x,y);
    }
    void pop() {dsu.rollback();}
    bool good() {return dsu.fa.back().first==0;}
};
// single priority_queue
// unofficial impl: select the max and do more
struct ThePriorityQueue {
    typedef int Priority; // should be unique
    struct Item { // priority,item
        Priority priority;
        Args args;
    };
    struct Update { // priority,item,prefix_priority_max
        Priority priority,prefix_max;
        Args args;
    };
    // multi-dimension: reconstruct的时候每个dim分别pop_max即可
    TheStack the_stack; // a stack-like structure, which adopts rollback
    vector<Update> updates;
    ThePriorityQueue(int n):the_stack(n) {}
    Item pop_from_stack() { // return id
        Update val=updates.back();
        updates.pop_back(); //redo
        the_stack.pop(); // just pop from the stack
        // printf("pop from pq %d %d %d; prefix-max=%d\n",val.priority,val.args.first,val.args.second,val.prefix_max);
        return Item{val.priority,val.args};
    }
    void push(Priority w,Args args) { // new item
        Priority prefix_max=w;
        if (updates.size()&&updates.back().prefix_max>prefix_max) // prefix
            prefix_max=updates.back().prefix_max; // prefix-max; 如果有多个priority,需要修改max更新策略
        updates.push_back(Update{w,prefix_max,args});
        the_stack.push(args); // push the newly inserted item!
        // printf("push to pq %d %d %d; prefix-max=%d\n",w,args.first,args.second,prefix_max);
    }
    Item pop(int axis=0) { // axis: pop-axis
        assert(updates.size());
        vector<Item> redo;
        while (updates.back().priority!=updates.back().prefix_max) // priority, prefix_priority_max
            redo.push_back(pop_from_stack());
        Item popped=pop_from_stack(); // last-value
        // 多个priority:redo.size()*k*alpha; resolve
        int extra=min(redo.size(),updates.size());
        while (extra--)
            redo.push_back(pop_from_stack());
        // 多个priority: 从大到小按每个priority一个一个放(reverse)
        sort(redo.begin(),redo.end(),[&](Item x,Item y){return x.priority<y.priority;});
        for (auto val:redo) push(val.priority,val.args); // priority,args
        return popped; // the popped item could be roll-back! (just push)
    }
    bool good() {
        return the_stack.good();
    }
};

int U[maxn],V[maxn];
int A[maxn],R[maxn];
int main() {
    int n,m,q,i;
    scanf("%d%d%d",&n,&m,&q);
    ThePriorityQueue Q(n);
    FOR(i,1,m) scanf("%d%d",&U[i],&V[i]);
    FOR(i,1,m) Q.push(-i,{U[i],V[i]}); // maximum=r
    int r=1;
    FOR(i,0,m) {
        while (r<=m&&!Q.good()) r++,Q.pop(); // R must bigger than r
        if (!Q.good()) R[i]=r; else R[i]=r-1;
        if (i!=m) Q.push(-INF,{U[i+1],V[i+1]}); // remain 1->i
    }
    // FOR(i,0,m) printf("%d ",R[i]); puts("<- R");
    FOR(i,1,q) {
        int l,r;
        scanf("%d%d",&l,&r);
        if (R[l-1]>r) puts("YES");
        else puts("NO");
    }
}
/*
*/
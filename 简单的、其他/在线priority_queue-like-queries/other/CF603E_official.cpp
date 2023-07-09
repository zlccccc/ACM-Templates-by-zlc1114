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
// 给定(x,y,w)的边,问最小的w'使得w<w'的边子集让每个点度数为奇数
// 有个结论是让并查集中set元素个数都为偶数就可以了
template<bool path_compression=true>
struct DSU {
    vector<int> checkpoint_;
    vector<pii> changes_;
    vector<int> fa; // fa[x]<0: root; and we save its size
    DSU(int n) {fa.resize(n+1,-1);} // fa<0: size; else: real-getfather
    inline int getfa(int x) {
        if (path_compression) {
            if (fa[x]<0) return x;
            int ret=getfa(fa[x]);
            if (ret!=fa[x]) changes_.push_back({x,fa[x]});
            return fa[x]=ret;
        } else {
            while (fa[x]>=0) x=fa[x];
            return x;
        }
    }
    void checkpoint() {
        checkpoint_.push_back(changes_.size());
    }
    inline void undo() { // single undo
        pii p=changes_.back();
        fa[p.first]=p.second;
        changes_.pop_back();
    }
    void rollback() { // rollback to checkpoint (stack)
        while ((int)changes_.size()!=checkpoint_.back()) undo();
        checkpoint_.pop_back();
    }
    void merge(int x,int y) {
        x=getfa(x); y=getfa(y);
        if (x==y) return;
        if (-fa[x]>-fa[y]) swap(x,y);
        changes_.push_back({x,fa[x]});
        changes_.push_back({y,fa[y]});
        fa[y]+=fa[x]; fa[x]=y; // sz and fa
    }
    void merge_solve(int x,int y) {
        x=getfa(x); y=getfa(y);
        if (x==y) return;
        int newodds=fa.back();
        newodds-=fa[x]&1;
        newodds-=fa[y]&1;
        if (-fa[x]>-fa[y]) swap(x,y);
        changes_.push_back({x,fa[x]});
        changes_.push_back({y,fa[y]});
        fa[y]+=fa[x]; fa[x]=y; // sz and fa
        newodds+=fa[y]&1;
        if (newodds!=fa.back())
            changes_.push_back({fa.size()-1,fa.back()});
        fa.back()=newodds;
    }
};
struct TheStack { // stack-like structure
    // DSU<false> dsu;
    DSU<true> dsu;
    int tot=0;
    TheStack(int n):dsu(n) { // rollback to checkpoint needs n+1!
        dsu.fa.push_back(n); // odd number
    }
    void push(int x,int y) {
        dsu.checkpoint();
        dsu.merge_solve(x,y);
    }
    void pop() {dsu.rollback();}
    bool good() {return dsu.fa.back()==0;}
};
// single priority_queue
// official impl
struct ThePriorityQueue {
    typedef pair<int,int> Priority; // should be unique
    vector<pair<ar3,int>> items; // item (input), position in the stack 
    TheStack the_stack; // a stack-like structure, which adopts rollback
    vector<int> updates; // id in the stack
    set<Priority> where; // priority, id
    ThePriorityQueue(int n):the_stack(n) {}
    inline Priority priority(int id) {
        return make_pair(items[id].first[2],id);
    }
    void push_into_stack(int id) {
        items[id].second=updates.size(); // position
        updates.push_back(id); // updates id
        the_stack.push(items[id].first[0],items[id].first[1]); // insert into the stack
    }
    int pop_from_stack() { // return id
        int topid=updates.back();
        updates.pop_back(); //redo
        the_stack.pop(); // just pop from the stack
        return topid;
    }
    void insert(int id) { // insert into set
        where.insert(priority(id)); // insert priority into set
        push_into_stack(id);
    }
    void push(int x,int y,int w) { // new item
        items.push_back({{x,y,w},updates.size()});
        insert(items.size()-1); // push the newly inserted item!
    }
    pair<ar3,int> pop() {
        int bestid=where.rbegin()->second; // lastval-id
        // int need=items[bestid].second; // position of the last item in the stack
        if ((int)updates.back()==bestid) { // bestid == updates.back(); need==updates.size()-1
            pop_from_stack();
        } else { // relax the whole queue
            auto it=where.end();
            vector<int> redo_large,redo_small;
            int k=1; Priority split; // number of pops
            for (int q=0;q<(k+1)/2;q++) {
                it--; split=*it; int id=it->second; // >=split: large
                int need=items[id].second;
                if (q) redo_large.push_back(id);
                // else assert(bestid==split.second);
                k=max(k,(int)updates.size()-need);
            } // roll-back-insert
            reverse(redo_large.begin(),redo_large.end());
            vector<int> redo_all;
            while (k--) {
                int id=pop_from_stack();
                // printf("redo pop from stack %d %d\n",items[id].first[2],id);
                if (priority(id)<split) redo_small.push_back(id);
                redo_all.push_back(id);
            }
            // assert(redo_all.size()==redo_small.size()+redo_large.size()+1);
            // sort(redo_small.begin(),redo_small.end(),[&](int x,int y){return priority(x)<priority(y);});
            for (int id:redo_small) push_into_stack(id); // x,y,w
            for (int id:redo_large) push_into_stack(id); // x,y,w
        }
        where.erase(priority(bestid));
        return {items[bestid].first,bestid}; // the popped item could be roll-back! (just push)
    }
    bool good() {
        return the_stack.good();
    }
};

int A[maxn];
int main() {
    int n,m;
    scanf("%d%d",&n,&m);
    ThePriorityQueue Q(n);
    int ans=-1;
    while (m--) {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        if (!Q.good()||w<ans) Q.push(x,y,w);
        if (!Q.good()) puts("-1");
        else {
            auto p=Q.pop();
            while (Q.good()) p=Q.pop(); // value, id
            Q.insert(p.second);
            printf("%d\n",ans=p.first[2]);
        }
    }
}
/*
*/
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

        // int i;
        // FOR(i,1,fa.size()-2) printf("%d ",fa[i]); printf("<- fa; odd=%d\n",fa.back());
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
struct ThePriorityQueue {
    TheStack the_stack;
    vector<ar3> updates; // id
    set<pii> where; // priority, id
    ThePriorityQueue(int n):the_stack(n) {}
    void push(int x,int y,int w) {
        where.insert({w,updates.size()});
        updates.push_back({w,x,y}); // weight first
        the_stack.push(x,y);
    }
    ar3 pop() {
        int need=where.rbegin()->second; // pop-position
        if ((int)updates.size()==need) {
            auto top=updates.back();
            int w=updates.back()[0];
            updates.pop_back(); //redo
            where.erase({w,updates.size()});
            the_stack.pop(); // O(1)
            return top;
        } else { // relax
            vector<ar3> redo; // roll-back-insert
            int MIN=updates.size();

            while ((int)updates.size()>need) {
                redo.push_back(updates.back());
                int w=updates.back()[0];
                updates.pop_back(); //redo
                where.erase({w,updates.size()});
                the_stack.pop(); // O(1)
            }
            int extra=min(redo.size(),updates.size());
            while (extra--) {
                redo.push_back(updates.back());
                int w=updates.back()[0];
                updates.pop_back(); //redo
                where.erase({w,updates.size()});
                the_stack.pop(); // O(1)
            }
            sort(redo.begin(),redo.end()); // log
            auto popped=redo.back(); redo.pop_back();
            for (ar3 o:redo) push(o[1],o[2],o[0]); // x,y,w
            return popped;
        }
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
    while (m--) {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        Q.push(x,y,w);
        if (!Q.good()) puts("-1");
        else {
            auto p=Q.pop();
            while (Q.good())
                p=Q.pop();
            Q.push(p[1],p[2],p[0]);
            printf("%d\n",p[0]);
        }
    }
}
/*
*/
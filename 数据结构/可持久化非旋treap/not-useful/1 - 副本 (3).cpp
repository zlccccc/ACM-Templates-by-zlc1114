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
const LL maxn=1e6+107;
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

// 5e6
// 内存回收: 没写, 写的话可以直接用个东西保存指向它的pointer个数
namespace persist_treap {
    typedef pair<int,int> Pair;
    const int maxn=5e6;//maxn>=2
    const int more=1e6;
    const int reboot=1e4;
    struct node {
        int l,r,len,size;
        ll val,lazy,sum;
        node(ll _val=0) {
            l=r=len=0; val=_val; lazy=0;
            sum=val; size=1;
        }
    } T[maxn+more]; //maxn+maxk*40
    int root,startpos;//ends
    void init() {
        root=0; T[0].size=0;//0:no use
    } // no del_node(just rebuild it!)
    int insnode(ll x) {//value
        int pos=++startpos;
        T[pos]=node(x);
        return pos;
    }
    int persistnode(int ini) { //newnode
        int pos=++startpos;
        T[pos]=T[ini];
        return pos;
    }
    void ADD(int x,ll val) { //update-subtree
        T[x].lazy+=val; T[x].val+=val;
        T[x].sum+=T[x].size*val;
    }
    bool pushdown(int x) {
        if (!T[x].lazy) return 0;
        if (T[x].l) {
            T[x].l=persistnode(T[x].l);
            ADD(T[x].l,T[x].lazy);
        }
        if (T[x].r) {
            T[x].r=persistnode(T[x].r);
            ADD(T[x].r,T[x].lazy);
        }
        T[x].lazy=0;
        return 1; // changed; -1/2空间
    }
    void pushup(int x) {
        T[x].sum=T[x].val;
        T[x].len=0; T[x].size=1;
        if (T[x].l) {
            T[x].sum+=T[T[x].l].sum;
            T[x].len=max(T[x].len,T[T[x].l].len+1);
            T[x].size+=T[T[x].l].size;
        }
        if (T[x].r) {
            T[x].sum+=T[T[x].r].sum;
            T[x].len=max(T[x].len,T[T[x].r].len+1);
            T[x].size+=T[T[x].r].size;
        }
    }
    int merge(int x,int y,bool downx=0,bool downy=0) {
        if (!x||!y) return x|y;
        if (T[x].len>T[y].len) {
            if (!downx) x=persistnode(x);
            bool okay=pushdown(x);
            T[x].r=merge(T[x].r,y,okay,downy);
            pushup(x); return x;
        } else {
            if (!downy) y=persistnode(y);
            bool okay=pushdown(y);
            T[y].l=merge(x,T[y].l,downx,okay);
            pushup(y); return y;
        }
    }
    pii split(int x,int k,bool down=0) { // to 2 trees
        if (!x) return make_pair(0,0);
        if (!down) x=persistnode(x);
        bool persisted=pushdown(x); //persist:newnode
        // printf("split: %lld; sz=%d; k=%d\n",T[x].val,T[x].size,k);
        pii P;
        if (!k||T[T[x].l].size>=k) {
            // printf("to_left %d\n",T[x].l);
            P=split(T[x].l,k,persisted);
            T[x].l=P.second; pushup(x); P.second=x;
        } else {
            P=split(T[x].r,k-T[T[x].l].size-1,persisted);
            T[x].r=P.first; pushup(x); P.first=x;
        } return P;
    }

    ll query(int l,int r) {//用个东西记录一下??
        pii A=split(root,l-1);
        // output(A.first); puts("A.first");
        pii B=split(A.second,r-l+1);
        // output(B.first); puts("B.first"); 
        // output(B.second); puts("B.second"); 
        return T[B.first].sum;
    }
    int merge_3(int x,int y,int z) {
        if (T[x].len<T[z].len)
            return merge(merge(x,y),z);
        else return merge(x,merge(y,z));
    }
    void update(int l,int r,ll val) {
        pii A=split(root,l-1);
        pii B=split(A.second,r-l+1);
        ADD(B.first,val);
        root=merge_3(A.first,B.first,B.second);
    }
    void insert(int k,int val) {//after kth
        pii A=split(root,k);
        int y=insnode(val);
        // output(A.first); puts("okay");
        // printf("root=%d\n",root);
        root=merge_3(A.first,y,A.second);
    }
    void transto(int l,int r,int x,int y) {
        pii A=split(root,l-1);
        pii B=split(A.second,r-l+1);
        pii A_=split(root,x-1);
        pii B_=split(A_.second,y-x+1);
        root=merge_3(A.first,B_.first,B.second);
    }
    int build(int A[],int l,int r) {
        if (l>r) return 0;
        int mid=(l+r)/2;
        int ret=insnode(A[mid]);
        T[ret].l=build(A,l,mid-1);
        T[ret].r=build(A,mid+1,r);
        pushup(ret);
        return ret;
    }

    void print_dfs(int x,int A[],int &tot) { //way=0: output; way=1: to_list
        if (!x) return;
        pushdown(x);
        print_dfs(T[x].l,A,tot);
        A[++tot]=T[x].val;
        print_dfs(T[x].r,A,tot);
    }
    int A[maxn],tot;
    void output(int x=root) {
        tot=0; print_dfs(x,A,tot); int i;
        FOR(i,1,tot) printf("%d%c",A[i]," \n"[i==tot]);
    }

    void rebuild() {
        tot=0; print_dfs(root,A,tot);
        startpos=0; //ed=0; todo ed not right
        root=build(A,1,tot);
    }
    void selective_rebuild() {
        static int times; ++times;
        if (startpos>maxn) rebuild();
        if (times>reboot) rebuild(),times=0;
    }
}
int i;
int A[maxn];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    T=1;
    FOR(_,1,T){
        int i,n,m;
        scanf("%d%d",&n,&m);
        FOR(i,1,n) scanf("%d",&A[i]);
        persist_treap::init();
        // FOR(i,1,n) persist_treap::insert(i,A[i]);
        persist_treap::root=persist_treap::build(A,1,n);
        FOR(i,1,m) {
            int op,l,r;
            scanf("%d%d%d",&op,&l,&r);
            if (op==1) {
                int d;
                scanf("%d",&d);
                persist_treap::update(l,r,d);
            } else if (op==2) {
                int x,y;
                scanf("%d%d",&x,&y);
                persist_treap::transto(l,r,x,y);
            } else {
                printf("%lld\n",persist_treap::query(l,r));
            }
            persist_treap::selective_rebuild();
            // persist_treap::output();
        }
    }
    return 0;
}
/*
0
5 100
1 2 3 4 5
3 3 5
3 1 2
3 1 1
3 4 4
3 5 5
2 1 3 3 5
3 3 5
1 2 4 2
3 3 5
2 1 3 3 5
3 1 5
*/
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
const LL maxn=2000+107;
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

// 题意: A树有多少个和B树同构的子树(B总共12个节点)
// 做法: 对B树进行哈希, 然后构造转移方案并转移
namespace tree_hash {
    const int maxk=12;
    vector<int> baseedge[1<<maxk|7];
    void init(int n) {
        int i,j;
        REP(i,(1<<n)) REP(j,n) if ((i>>j)&1)
            baseedge[i].push_back(j);
    }
    typedef unsigned int type;
    struct tree {
        int e[maxk];//baseedge
        void init(int n) {memset(e,0,n*sizeof(int));}
        type dfs(int x,int fa) {//encode
            // printf("dfs: %d %d\n",x,fa);
            static int sz[maxk];
            type ret=0; sz[x]=1;
            vector<pair<type,int> > tmp;//count
            for (int v:baseedge[e[x]]) if (v!=fa) {
                    type val=dfs(v,x)<<1|1; sz[x]+=sz[v];
                    tmp.push_back(make_pair(val,sz[v]*2));
                } sort(tmp.begin(), tmp.end());
            reverse(tmp.begin(), tmp.end());
            for (pair<type,int>v:tmp)
                ret=(ret<<v.second)|v.first;
            return ret;
        }
        type unrooted(int n) {
            vector<type> tmp; int i;
            REP(i,n) tmp.push_back(dfs(i,i));
            sort(tmp.begin(), tmp.end());
            return tmp[0];//字典序minimize
        }
    };
    set<type> S;//hash_answer
    typedef pair<tree,type> ptt;
    vector<pair<tree,type> > Trees[13];//size
    tree merge(const tree &x,const tree &y,int sizex,int sizey) {
        tree ret; int i,j;
        ret.init(sizex+sizey);
        REP(i,sizex) REP(j,sizex) if ((x.e[i]>>j)&1) {
            ret.e[i]|=1ull<<j;
            ret.e[j]|=1ull<<i;
        }
        REP(i,sizey) REP(j,sizey) if ((y.e[i]>>j)&1) {
            ret.e[i+sizex]|=1ull<<(j+sizex);
            ret.e[j+sizex]|=1ull<<(i+sizex);
        }
        ret.e[0]|=1ull<<sizex;
        ret.e[sizex]|=1ull<<0;
        return ret;
    }
    int tot;
    short id[1<<(maxk*2)];//last=0所以可以去掉
    typedef pair<type,int> pti;
    vector<pti> edges[8007];//这里是个暴力, 在外边再搞一次比较好
    void getall(int n) {
        tree ini; ini.init(1);//ini.dfs=0
        Trees[1].push_back(make_pair(ini,0));
        int _,o; tot=0;
        S.insert(0); id[0]=++tot;
        FOR(_,1,n-1) {//size
            for (ptt tmp:Trees[_]) {
                int i; tree &ori=tmp.first;
                // pr2(ori.dfs(0,0),_*2-2); printf(" : %d",ori.dfs(0,0)); puts(" <- ori");
                REP(i,_) {
                    tree nxt=ori;
                    nxt.e[_]=1ull<<i;
                    nxt.e[i]|=1ull<<_;
                    type v=nxt.dfs(0,0);
                    // pr2(nxt.dfs(0,0),_*2); printf(" : %d",nxt.dfs(0,0)); puts(" <- nxt");
                    if (S.count(v)) continue;
                    Trees[_+1].push_back(make_pair(nxt,v));
                    S.insert(v); id[v]=++tot;
                    // assert(v<(1<<(maxk*2-1)));
                }
            }
        }
        // int all=0;
        // FOR(_,1,n) {
        //  printf("%d: %d\n",_,(int)Trees[_].size());
        //  all+=Trees[_].size();
        //  // for (tree ori:Trees[_]) pr2(ori.dfs(0,0),_*2-2); puts("");
        // } printf("size_all=%d\n",all);
        // printf("tot=%d\n",tot);
        FOR(_,1,n) FOR(o,1,n-_){
            for (ptt tmpx:Trees[_]) {
                tree &x=tmpx.first; type ox=tmpx.second;
                for (ptt tmpy:Trees[o]) {
                    tree &y=tmpy.first; type oy=tmpy.second;
                    type o_nxt=merge(x,y,_,o).dfs(0,0);
                    edges[id[ox]].push_back(make_pair(id[oy],id[o_nxt]));
                }
            }
        }
    }
}
vector<int> edge[2007];
int value[2007][7900],tmp[7900],all[7900];
void dfs(int x,int fa) {
    int i; value[x][1]=1;//base
    for (int v:edge[x]) if (v!=fa){
        dfs(v,x);
        FOR(i,1,tree_hash::tot) tmp[i]=0;
        FOR(i,1,tree_hash::tot) if (value[x][i])
            for (tree_hash::pti k:tree_hash::edges[i])
                add_(tmp[k.second],(ll)value[x][i]*value[v][k.first]%M);
        FOR(i,1,tree_hash::tot) add_(value[x][i],tmp[i]);
    }
    // printf("dfs: %d %d\n",x,fa);
    // FOR(i,1,tree_hash::tot) if (value[x][i]) printf("%d: %d\n",i,value[x][i]);
    FOR(i,1,tree_hash::tot) add_(all[i],value[x][i]);
}
int main() {
    tree_hash::init(12);
    tree_hash::getall(12);
    int n,i,q;
    scanf("%d",&n);
    FOR(i,1,n-1) {
        int u,v; scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    } dfs(1,0);
    scanf("%d",&q);
    while (q--) {
        int m;
        tree_hash::tree tmp; tmp.init(12);
        scanf("%d",&m);
        vector<tree_hash::type> V;
        FOR(i,1,m-1) {
            int u,v;
            scanf("%d%d",&u,&v);
            u--; v--;
            tmp.e[u]|=1ull<<v;
            tmp.e[v]|=1ull<<u;
        } REP(i,m) V.push_back(tree_hash::id[tmp.dfs(i,i)]);
        sort(V.begin(), V.end());
        V.erase(unique(V.begin(), V.end()),V.end());
        int ans=0;
        for (int v:V) add_(ans,all[v]);
        printf("%d\n",ans);
    }
}
/*
5 3
2 3 1 4 5
2 3
1 1 3 5
2 3

5 3
2 3 1 1 2
2 3
1 1 3 5
2 3
*/
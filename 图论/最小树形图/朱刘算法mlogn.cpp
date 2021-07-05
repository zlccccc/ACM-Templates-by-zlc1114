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


namespace heap {
    const int maxn=1e5+7;
    struct node {
        int l,r,len;
        int u,v,val,lz;
        node(int _u=0,int _v=0,int _val=0):
            u(_u),v(_v),val(_val) {l=r=len=0; lz=0;}
    } T[maxn]; int tot;
    //不能直接swap x和儿子, 否则可能不满足堆性质
    void update(int x,int val) {
        T[x].lz+=val; T[x].val-=val;
    }
    void pushdown(int x) {
        if (T[x].lz) {
            if (T[x].l) update(T[x].l,T[x].lz);
            if (T[x].r) update(T[x].r,T[x].lz);
            T[x].lz=0;
        } 
    }
    int merge(int x,int y) {
        if (!x||!y) return x|y;
        pushdown(x); pushdown(y);
        if (T[x].val>T[y].val) swap(x,y);
        T[x].r=merge(T[x].r,y);
        if (T[T[x].l].len<T[T[x].r].len) swap(T[x].l,T[x].r);
        T[x].len=T[T[x].r].len+1;
        return x;
    }
    int pop(int x) {
        pushdown(x);
        return merge(T[x].l,T[x].r);
    }
}
namespace O {
    const int maxn=1e5+7;
    const int maxm=1e5+7;
    int Root[maxm],etot;
    void init() {etot=0;}
    void addedge(int u,int v,int len) {
        heap::T[++etot]=heap::node(u,v,len);
    }
    struct _info {//pre为preuid;maxtot=maxm
        int pre,len,eid;//position(id) and length
        void init(int _pre,int _len,int _eid) {
            pre=_pre; len=_len; eid=_eid;
        }
    } Info[maxm];
    //id:circle_id(father);top:tree_anc
    inline int getfa(int fa[],int x) {
        if (fa[x]==x) return x;
        return fa[x]=getfa(fa,fa[x]);
    } int id[maxm],top[maxm];//并查集;
    bool getTopValue(int i) {
        while (Root[i]) {
            heap::node &e=heap::T[Root[i]];
            if (getfa(id,e.u)==getfa(id,e.v)) {
                Root[i]=heap::pop(Root[i]);
            } else {
                Info[i].init(e.u,e.val,Root[i]);
                Root[i]=heap::pop(Root[i]);
                // printf("%d: %d; pos=%d\n",e.v,e.val,Root[i]);
                return 1;
            }
        } return 0;
    }
    int idfa[maxm],useid[maxm];//changes_fa
    int used[maxm];//output; 记录edge
    int solve(int root,int n) {
        int ret=0,i,lastnid=n;
        FOR(i,1,n) id[i]=top[i]=i,Info[i].len=INF;
        FOR(i,1,etot) { //initialize
            heap::node &e=heap::T[i];
            Root[e.v]=heap::merge(Root[e.v],i);
        }
        FOR(i,1,n) if (i!=root&&!getTopValue(i)) return -1;
        // puts("ok1");
        FOR(i,1,lastnid) {
            if (i==root) continue;
            _info &info=Info[i];
            int f=getfa(top,info.pre);
            //choose; 之后再更新
            useid[i]++; ret+=info.len; idfa[i]=i;
            if (f==i) {//circle
                ++lastnid; Info[lastnid].len=INF;
                top[lastnid]=id[lastnid]=lastnid;
                for (int x=getfa(id,info.pre); ; x=getfa(id,Info[x].pre)) {
                    heap::update(Root[x],Info[x].len);
                    Root[lastnid]=heap::merge(Root[lastnid],Root[x]);
                    id[x]=top[x]=idfa[x]=lastnid;//缩环
                    if (x==i) break;
                } //update edges
                if (!getTopValue(lastnid)) return -1;
            } else top[getfa(id,i)]=info.pre;//getfa=getid
        }
        rFOR(i,1,lastnid) if (useid[i]) {//remove_to_top
            static int ids[maxn];
            int x=0,k;
            for (int k=heap::T[Info[i].eid].v; k!=i; k=idfa[k]) ids[x++]=k;
            REP(k,x) idfa[ids[k]]=i,useid[ids[k]]=0;
            used[Info[i].eid]=1;
        }
        return ret;
    }
    //debug
    vector<pair<int,int> > check_edge[maxn];
    bool vis[maxn];
    void addcheck_edge_check(int u,int v,int i) {
        check_edge[u].push_back(make_pair(v,i));
    }
    void bfs(int x,int n) {//x=root
        queue<int> Q;
        Q.push(x); vis[x]=1;
        while (Q.size()) {
            int x=Q.front(); Q.pop();
            for (auto e:check_edge[x]) {
                int i=e.second;
                if (vis[e.first]) continue;
                if (!used[i]) continue;
                Q.push(e.first); vis[e.first]=1;
            }
        } int i;
        FOR(i,1,n) {
            if (!vis[i]) debug("no! %d\n",i);
        }
    }
}
int ini[maxn];
int n,m,i;
int u,v,w;
int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d%d",&n,&m);
    O::init();
    FOR(i,1,m) {
        if (scanf("%d%d%d",&u,&v,&w)!=3) {
            puts("input not right");
            return 0;
        };
        ini[i]=w;
        O::addedge(u,v,w);
        O::addcheck_edge_check(u,v,i);
    }
    int ans=O::solve(1,n);
    printf("%d\n",ans);
    if (ans!=-1) {
        O::bfs(1,n);
        FOR(i,1,m) if (ini[i]&&O::used[i])
            printf("%d ",i),ans--;
        if (ans) printf("\nnotok: %d\n",ans);
    }
}
/*
*/

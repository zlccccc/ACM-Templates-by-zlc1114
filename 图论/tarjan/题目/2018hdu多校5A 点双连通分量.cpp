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
const LL maxn=1e6+7;
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
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

// 2018hdu多校5A
// 题意: 每两个点之间只能有两条路径
// 也就是仙人掌
// 求\sum flow(i,j)^i^j, i<j
// 做法: 有环的话, 一定会切掉环上的一个边
// 所以把贡献加到其他里, 做个lca即可
struct edges {
    int u,v,len;
} e[maxn];
vector<edges> E;
namespace tarjan{// 边双连通分量, 这里是在做仙人掌
    struct Edge {
        int to,next,id;
        Edge(int _to=0,int _next=-1,int _id=0):to(_to),next(_next),id(_id) {};
    } edge[maxn*2];
    int head[maxn],etot;
    inline void addedge(int u,int v,int id) {
        edge[++etot]=Edge(v,head[u],id); head[u]=etot;
    }
    int dfn[maxn],low[maxn],tot;
    bool vis[maxn],used[maxn];
    int S[maxn],top;
    void tarjan(int x,int fa) {
        low[x]=dfn[x]=++tot; vis[x]=1;
        for (int i=head[x]; ~i; i=edge[i].next) {
            int v=edge[i].to;
            if (used[edge[i].id]) continue;
            if (v==fa) continue;
            S[++top]=edge[i].id;
            used[edge[i].id]=1;
            if (!dfn[v]) {
                tarjan(v,x);
                low[x]=min(low[x],low[v]);
                if (dfn[x]<=low[v]){//割边和边双联通
                    vector<int> Eid;
                    while (1){
                        int id=S[top--];
                        Eid.push_back(id);
                        if (id==edge[i].id) break;
                    } if (low[v]==dfn[x]){//双联通, 在这里dp
                        // printf(" one :");
                        // for (auto now:Eid) printf("%d ",now); puts("");
                        int id=Eid[0],l;
                        for (auto now:Eid) if (e[now].len<e[id].len) id=now; l=e[id].len;
                        for (auto now:Eid) e[now].len+=l;
                        for (auto now:Eid) if (now!=id) E.push_back(e[now]);
                    } else for (auto now:Eid) E.push_back(e[now]);//割边
                }
            } else if (vis[v])
                low[x]=min(low[x],dfn[v]);
        }
    }
    void init(int n,int m){
        int i;
        FOR(i,1,m) used[i]=0;
        FOR(i,1,n) head[i]=-1,dfn[i]=0; etot=tot=0;
        FOR(i,1,m) addedge(e[i].u,e[i].v,i),addedge(e[i].v,e[i].u,i);
        FOR(i,1,n) if (!dfn[i]) tarjan(i,0);
    }
}


namespace fastIO {//感觉没问题, 测试几次
#define BUF_SIZE 100000
    namespace Istream {
        bool IOerror = 0;
        inline char ic() {
            static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
            if (p1==pend) {
                p1=buf;
                pend=buf+fread(buf,1,BUF_SIZE,stdin);
                if (pend == p1) {IOerror = 1; return -1;}
            } return *p1++;
        }
        inline bool blank(char ch) {
            return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
        }
        template<typename T>
        inline void readPositive(T &x) {//no
            char ch;
            while (blank(ch=ic()));
            if (IOerror) return;
            for (x=0; '0'<=ch&&ch<='9'; ch=ic()) x=x*10+ch-'0';
        }
        template<typename T>
        inline void read(T &x) {
            char ch; T op=1;
            while (blank(ch=ic()));
            if (IOerror) return;
            if (ch=='-') op=-1,ch=ic();
            for (x=0; '0'<=ch&&ch<='9'; ch=ic()) x=x*10+ch-'0';
            x*=op;
        }
        inline void read(char &c) {
            c=ic();
        }
        inline void read(char *s) { //len
            char ch;
            while (blank(ch=ic()));
            if (IOerror) return;
            for (; !blank(ch)&&!IOerror; ch=ic()) *s++=ch;
            *s='\0';
        }
    }
    namespace Ostream {
        char buf[BUF_SIZE], *p1 = buf, *pend = buf + BUF_SIZE;
        inline void flush() {
            fwrite(buf,1,p1-buf,stdout);
            p1=buf;
        }
        inline void oc(char ch) {
            if (p1 == pend) flush();
            *p1++=ch;
        }
        inline void println() {
            oc('\n');
        }
        template<typename T>
        inline void print(T x) {
            static char s[27],*s1=s;
            if (!x) *s1++='0';
            if (x<0) oc('-'),x=-x;
            while (x) *s1++=x%10+'0',x/=10;
            do {s1--; oc(*s1);} while (s1!=s);
        }
        inline void print(char s) {
            oc(s);
        }
        inline void print(char *s) {
            for (; *s; oc(*s++));
        }
        inline void print(const char *s) {
            for (; *s; oc(*s++));
        }
        inline void print(string s) {
            for (unsigned i=0; i<s.length(); i++) oc(s[i]);
        }
        struct _flush {
            ~_flush() {flush();}
        } fflush;
    };
    template<typename T>
    inline void read(T &x) {Istream::readPositive(x);}
    inline void read(char *x) {Istream::read(x);}
    template<typename T>
    inline void print(T x) {Ostream::print(x);}
    template<typename T>
    inline void println(T x) {print(x); Ostream::oc('\n');}
}
using namespace fastIO;

int fa[maxn];
int cnt[maxn][31][2];
inline int getfa(int x){
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
}
int main() {
    int T;
    read(T);
    while (T--){
        int i,k; E.clear();
        read(n); read(m);
        FOR(i,1,m) read(e[i].u),read(e[i].v),read(e[i].len);
        tarjan::init(n,m);
        sort(E.begin(), E.end(),[](edges &A,edges &B){
            return A.len>B.len;
        });
        // for (auto now:E) printf("E : %d - %d  %d\n",now.u,now.v,now.len);
        // FOR(i,1,m) printf("e: %d-%d %d\n",e[i].u,e[i].v,e[i].len);
        __int128 ans=0;
        // int j;
        // FOR(i,2,5) ans+=i^1^10;
        // FOR(i,2,5) FOR(j,i+1,5) ans+=i^j^11;
        // printf("ans=%llu\n",ans); ans=0;
        FOR(i,1,n) {
            fa[i]=i;
            REP(k,31) cnt[i][k][(i>>k)&1]=1,cnt[i][k][!((i>>k)&1)]=0;
        } for (auto now:E){
            int x=getfa(now.u),y=getfa(now.v);
            assert(x!=y); int o,_o;
            // printf("merge: %d %d\n",x,y);
            fa[x]=y;
            REP(k,31) REP(o,2) REP(_o,2){
                ans+=(__int128)cnt[x][k][o]*cnt[y][k][_o]*((o^_o^((now.len>>k)&1))<<k);
                // if (k<=6) printf("%d : %d %d : %d\n",k,o,_o,cnt[x][k][o]*cnt[y][k][_o]);
            }
            REP(k,31) REP(o,2){
                cnt[y][k][o]+=cnt[x][k][o];
            }
            // printf("%llu\n",ans);
        } println(ans);
    }
}
/*
*/

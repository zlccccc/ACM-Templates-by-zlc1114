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
            char ch; x=0;
            while (blank(ch=ic()));
            if (IOerror) return;
            for (x=0; '0'<=ch&&ch<='9'; ch=ic()) x=x*10+ch-'0';
        }
        template<typename T>
        inline void read(T &x) {
            char ch; T op=1; x=0;
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
    inline void read(T &x) {Istream::read(x);}
    inline void read(char *x) {Istream::read(x);}
    template<typename T>
    inline void print(T x) {Ostream::print(x);}
    template<typename T>
    inline void println(T x) {print(x); Ostream::oc('\n');}
}
using namespace fastIO;

int A[maxn];
namespace tree{
    struct Info {
        ll v,t,cnt;
        void init(){v=t=0; cnt=1;}
    };
    struct TreeInfo{
        int l,r,fa;//light:self
        Info chain,light;
        ll lzv,lzk,lzb;//v0+=lzv; t0+=k*v0+b
        void init() {
            light.init(); clearlz();
            l=r=fa=0; chain.init();
        }
        void update(const ll &v,const ll &k,const ll &b) {
            change(v,k,b);
            chain.t+=(k*chain.v+b)*chain.cnt;
            lzk+=k; lzb+=b+k*lzv;
            chain.v+=v*chain.cnt;
            lzv+=v;
        }
        void change(const ll &v,const ll &k,const ll &b) {
            light.t+=k*chain.v+b*chain.cnt;
            light.v+=v;
        }
        bool lz() {
            return lzv||lzk||lzb;
        }
        void clearlz() {
            lzv=lzk=lzb=0;
        }
    }T[maxn];
    inline Info merge(const Info &left,const Info &right) {
        Info ret;
        ret.v=left.v+right.v;
        ret.t=left.t+right.t;
        ret.cnt=left.cnt+right.cnt;
        return ret;
    }
    inline void pushup(int x) {
        T[x].chain=T[x].light;
        if (T[x].l) T[x].chain=merge(T[T[x].l].chain,T[x].chain);
        if (T[x].r) T[x].chain=merge(T[x].chain,T[T[x].r].chain);
    }
    inline void pushdown(int x) {
        if (T[x].lz()) {
            if (T[x].l) T[T[x].l].update(T[x].lzv,T[x].lzk,T[x].lzb);
            if (T[x].r) T[T[x].r].update(T[x].lzv,T[x].lzk,T[x].lzb);
            T[x].clearlz();
        }
    }
    int id[maxn],S[maxn],tot;//S:sum
    void buildTree(int &x,int l,int r) {
        x=0; if (l>r) return;
        int m=lower_bound(S+l,S+r,(S[r]+S[l-1])/2)-S;
        x=id[m];
        buildTree(T[x].l,l,m-1);
        buildTree(T[x].r,m+1,r);
        if (T[x].l) T[T[x].l].fa=x;
        if (T[x].r) T[T[x].r].fa=x;
        pushup(x);
    }
    vector<int> edge[maxn];
    int top[maxn],son[maxn],root[maxn],sz[maxn];
    void dfs1(int x,int fa) {
        sz[x]=1;
        for (int v:edge[x]) {
            if (v==fa) continue;
            dfs1(v,x); sz[x]+=sz[v];
            if (!son[x]||sz[son[x]]<sz[v]) son[x]=v;
        }
    }
    void dfs2(int x,int fa,int topx){
        top[x]=topx; T[x].init();
        T[x].init();
        for (int v:edge[x]) {
            if (v==fa||v==son[x]) continue;
            dfs2(v,x,v); int sonv=root[v];
            T[sonv].fa=x;
        }
        if (son[x]) dfs2(son[x],x,topx);
        if (top[x]==x) {
            tot=0; S[0]=0;
            for (int v=x;v;v=son[v]) {
                id[++tot]=v;
                S[tot]=sz[v]-sz[son[v]];
                S[tot]+=S[tot-1];
            } buildTree(root[x],1,tot);
        }
    }
    void update(int x,ll value,int op) {
        while (x) {
            tot=0; S[0]=0;
            for (;x!=root[top[x]];x=T[x].fa) S[++tot]=x;
            S[++tot]=x; x=T[x].fa; int i;
            rFOR(i,1,tot) pushdown(x);
            FOR(i,1,tot) {
                int f=S[tot+1];
                if (op==1) T[x].change(value,0,0);
                else T[x].change(0,value,0);
                if (T[f].r==x) 
                pushup(x);
            }
        }
    }
    void getans() {

    }
} int lastans=0;
int main(){
    int n,m,i;
    read(n); read(m);
    FOR(i,1,n) read(A[i]);
    FOR(i,1,n-1) {
        int u,v; read(u); read(v);
        tree::edge[u].push_back(v);
        tree::edge[v].push_back(u);
    } tree::dfs1(1,0); tree::dfs2(1,0,1);
    // printf("%d\n",tree::getAns());
    // FOR(i,1,n) printf("%d ",tree::T[i].fa);
    FOR(i,1,m) {
        int x,y; read(x); read(y);
        x^=lastans;
        tree::update(x,y); 
        println(lastans=tree::getAns());
    }
}
/*
*/
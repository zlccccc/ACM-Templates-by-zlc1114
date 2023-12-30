// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define REP_(I,N) for (int I=0,END=(N);I<END;I++)
#define rREP_(I,N) for (int I=(N)-1;I>=0;I--)
#define rep_(I,S,N) for (int I=(S),END=(N);I<END;I++)
#define rrep_(I,S,N) for (int I=(N)-1,START=(S);I>=START;I--)
#define FOR_(I,S,N) for (int I=(S),END=(N);I<=END;I++)
#define rFOR_(I,S,N) for (int I=(N),START=(S);I>=START;I--)

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
const LL maxn=2e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD) {A%=MOD; A+=MOD; A%=MOD;}
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
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));


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
    // inline void read(T &x) {Istream::readPositive(x);}
    inline void read(T &x) {Istream::read(x);} //negative
    inline void read(char *x) {Istream::read(x);}
    template<typename T>
    inline void print(T x) {Ostream::print(x);}
    template<typename T>
    inline void println(T x) {print(x); Ostream::oc('\n');}
}
using namespace fastIO;

namespace Chain {
    vector<pii> cur;
    vector<int> edge[maxn];
    int son[maxn],sz[maxn],fa[maxn];//changes
    int top[maxn],id[maxn],dep[maxn],tot;
    void dfs1(int u,int f,int depth){
        int mx=-1; fa[u]=f;
        sz[u]=1; dep[u]=depth; son[u]=0;
        for (int v:edge[u]) {
            if (v==f) continue;
            dfs1(v,u,depth+1);
            sz[u]+=sz[v];
            if (sz[v]>mx) mx=sz[v],son[u]=v;
        }
    }
    void dfs2(int u,int f,int x){
        top[u]=x; id[u]=++tot;
        if (son[u]) dfs2(son[u],u,x);
        for (int v:edge[u]){
            if (v==son[u]||v==f) continue;
            dfs2(v,u,v);
        }
    }
    void Query(int x,int y){
        int ret=0;
        while (top[x]!=top[y]){
            if (dep[top[x]]<dep[top[y]]) swap(x,y);
            cur.push_back({id[top[x]],id[x]});
            x=fa[top[x]];
            // printf("x=%d; y=%d; dep=%d %d\n",x,y,dep[x],dep[y]);
        }
        if (dep[x]>dep[y]) swap(x,y);
        cur.push_back({id[x],id[y]});
    }
}
namespace ST {
    const int DMAX=18;
    int up[maxn][DMAX],down[maxn][DMAX],tot;
    vector<int> e[maxn*DMAX*2+1];
    int d[maxn*DMAX*2+1];
    void addedge(int x,int y) {
        // printf("addedge %d->%d\n",x,y);
        d[y]++; e[x].push_back(y);
    };
    int pw[maxn];
    void init(int n) {
        FOR_(i,1,tot) e[i].clear(),d[i]=0; tot=0;
        // FOR_(i,1,n) up[Chain::id[i]][0]=down[Chain::id[i]][0]=++tot;
        FOR_(i,2,n) pw[i]=pw[i>>1]+1;
        FOR_(i,1,n) up[i][0]=down[i][0]=++tot;
        // FOR_(i,1,n) printf("%d ",up[i][0]); puts(" <- up-0");
        rFOR_(i,1,n) {
            REP_(j,DMAX-1) {
                if (i+(1<<(j+1))-1>n) break;
                up[i][j+1]=++tot;
                addedge(up[i][j],up[i][j+1]);
                if (i+(1<<j)<=n) addedge(up[i+(1<<j)][j],up[i][j+1]);
            }
            REP_(j,DMAX-1) {
                if (i+(1<<(j+1))-1>n) break;
                down[i][j+1]=++tot;
                addedge(down[i][j+1],down[i][j]);
                if (i+(1<<j)<=n) addedge(down[i][j+1],down[i+(1<<j)][j]);
            }
        }
    }
    void update(int l,int r,int op,int idx) {  // op==1: down; op==2: up
        if (l>r) return;
        int p=pw[r-l+1],m=r-(1<<p)+1,id=down[idx][0];
        // printf("solve %d->%d\n",l,r);
        // printf("%d->%d %d->%d; id=%d;w=%d pw=%d\n",l,l+(1<<p)-1,m,r,id,down[l][p],p);
        if (op==1) addedge(id,down[l][p]);
        else addedge(up[l][p],id);
        if (l==m) return;
        if (op==1) addedge(id,down[m][p]);
        else addedge(up[m][p],id);
    }
    int res[maxn];
    int solve(int n) {
        queue<int> Q;
        int val=0;
        FOR_(i,1,tot) if (!d[i]) Q.push(i);
        while (Q.size()) {
            int x=Q.front(); Q.pop();
            // printf("bfs x=%d\n",x);
            // FOR_(i,1,n) {REP_(j,DMAX) printf("%d",d[up[i][j]]); printf(" ");} puts("<- up - du");
            // FOR_(i,1,n) {REP_(j,DMAX) printf("%d",d[down[i][j]]); printf(" ");} puts("<- down - du");
            // FOR_(i,1,n) REP_(j,DMAX) if (up[i][j]==x) printf("current=%d; up %d\n",i,j);
            // FOR_(i,1,n) REP_(j,DMAX) if (down[i][j]==x) printf("current=%d; down %d\n",i,j);
            if (x<=n) res[x]=++val;
            for (int v:e[x]) {
                d[v]--; if (!d[v]) Q.push(v);
            }
        }
        if (val==n) return 1;
        else return 0;  // Not Found
    }
}
// 题意: 给棵2e5的树, 连x->[u->v]或者[u->v]->x的边, 然后拓扑排序
// 这里是写了ST表然后连nlogn的边, 目前发现时间还不如线段树多个log...
int ans[maxn];
int solve() {
    int n,m;
    // scanf("%d%d",&n,&m);
    read(n); read(m);
    FOR_(i,1,n-1) {
        int x,y;
        // scanf("%d%d",&x,&y);
        read(x); read(y);
        Chain::edge[x].push_back(y);
        Chain::edge[y].push_back(x);
    }
    Chain::dfs1(1,0,1);
    Chain::dfs2(1,0,1);
    ST::init(n);
    FOR_(i,1,m) {
        int op,a,b,c;
        // scanf("%d%d%d%d",&op,&a,&b,&c);
        read(op); read(a); read(b); read(c);
        Chain::cur.clear();
        Chain::Query(a,b);
        // printf("id=%d\n",Chain::id[c]);
        // for (auto &now:Chain::cur) printf("(%d,%d) ",now.first,now.second); puts("<- now");
        bool inside=false;
        auto solve=[&](int l,int r) {
            if (l>r) return;
            int pw=0; while ((1<<pw)<=r-l+1) pw++; pw--;
            int m=r-(1<<pw)+1;
            // printf("solve %d->%d\n",l,r);
            // printf("%d->%d %d->%d; id=%d;w=%d pw=%d\n",l,l+(1<<pw)-1,m,r,Chain::id[c],down[l][c],pw);
        };
        for (auto &now:Chain::cur) {
            int idx=Chain::id[c];
            if (now.first<=idx&&idx<=now.second) {
                ST::update(now.first,idx-1,op,idx);
                ST::update(idx+1,now.second,op,idx);
            } else {
                ST::update(now.first,now.second,op,idx);
            }
        }
    }
    if (!ST::solve(n)) {print("-1"); return 0;}
    FOR_(i,1,n) ans[i]=ST::res[Chain::id[i]];
    FOR_(i,1,n) {print(ans[i]); print(" ");}
    return 0;
}
int main() {
    int T; T=1;
    // scanf("%d",&T);
    FOR_(_,1,T){
        solve();
    }
    return 0;
}
/*
7 2
1 2
1 3
1 4
3 5
4 6
3 7
1 6 5 1
2 6 7 3
*/
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

// 树链u->v合并, 卡常, 跑的飞快
namespace LB {
    typedef int BaseType;
    const int MaxBit=20;
    struct L_B {
        vector<BaseType> vec;
        L_B() {clear();}
        void clear() {vec.clear();}
        void insert(BaseType x) {
            if (vec.size()==MaxBit) return;
            for (auto &now:vec) x=min(x,x^now);
            if (x) vec.push_back(x);
        }
        BaseType XORMIN(BaseType x) {  // limit:>=index
            if (vec.size()==MaxBit) return 0;
            for (auto &now:vec) x=min(x,now^x);
            return x;
        }
        void merge(L_B B) {
            if (B.vec.size()>vec.size()) swap(vec,B.vec);
            if (vec.size()==MaxBit) return;
            for (auto &now:B.vec) insert(now);
        }
    };
}
using namespace LB;

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

int A[maxn];
vector<int> edge[maxn];
int fa[maxn][18],dep[maxn];
L_B T[maxn][18];
void dfs(int x,int f,int depth) {
    fa[x][0]=f; T[x][0].insert(A[x]); dep[x]=depth;
    rep_(i,1,18) {
        fa[x][i]=fa[fa[x][i-1]][i-1];
        T[x][i]=T[x][i-1],T[x][i].merge(T[fa[x][i-1]][i-1]);
    }
    // REP_(i,18) rREP_(k,18) if (T[x][i].b[k]) printf("solve x=%d i=%d: %d\n",x,i,T[x][i].b[k]);
    for (int v:edge[x]) if (v!=f) dfs(v,x,depth+1);
}

int lca(int x,int y) {
    if (dep[x]<dep[y]) swap(x,y);
    rREP_(i,18) if (dep[x]-dep[y]>=1<<i) x=fa[x][i];
    if (x==y) return x;
    rREP_(i,18) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
int dis(int x,int y) {
    return dep[x]+dep[y]-2*dep[lca(x,y)];
}

int main() {
    int n;
    read(n);
    FOR_(i,1,n) read(A[i]);
    FOR_(i,1,n-1) {
        int x,y;
        read(x); read(y);
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    dfs(1,0,1);
    int q; read(q);
    FOR_(i,1,q) {
        int x,y,k;
        read(x); read(y); read(k);
        int f=lca(x,y);
        // printf("f=%d; d=%d; %d\n",f,dep[f],dep[x]);
        L_B cur;
        rREP_(i,18) if (dep[x]-(1<<i)>=dep[f]) cur.merge(T[x][i]),x=fa[x][i];
        rREP_(i,18) if (dep[y]-(1<<i)>=dep[f]) cur.merge(T[y][i]),y=fa[y][i];
        // printf("x=%d; y=%d; f=%d\n",x,y,f);
        cur.insert(A[f]);
        if (cur.XORMIN(k)==0) println("YES"); else println("NO");
    }
}
/*
*/
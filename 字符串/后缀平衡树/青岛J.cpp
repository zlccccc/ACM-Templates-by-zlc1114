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

// 替罪羊树...这道题卡splay,treap
// 题意：加字符，减字符，query子串个数
// 做法：建后缀自动机+LCT; right集个数
// 或者后缀顺序建平衡树然后树上query
// 后缀平衡树的顺序是倒着的, 倒着的后缀rank
// 以上是https://www.nowcoder.net/acm/contest/59/C
// 由于这个是倒着的rank, 反过来的情况非常常见(往前加)
// 这个直接用这个板子insert, query即可
const double alpha=0.75;
namespace SAT {
    const ull MAX=(1ull<<63)-1;
    struct node {
        int son[2]; int pre,size;
        int sum,val; ull rank; char c;
        void initval(char _c) {
            son[0]=son[1]=0; pre=0;
            size=sum=val=1; rank=0; c=_c;
        }
    } T[maxn];
    int cnt,root,last;
    inline bool cmp(int x,int y) {//x<y
        assert(x!=y);
        if (T[x].c!=T[y].c) return T[x].c<T[y].c;
        return T[T[x].pre].rank<T[T[y].pre].rank;//same:
    }
    void pushup(int x){
        T[x].size=1; T[x].sum=T[x].val;
        if (T[x].son[0]) {
            T[x].size+=T[T[x].son[0]].size;
            T[x].sum+=T[T[x].son[0]].sum;
        } if (T[x].son[1]) {
            T[x].size+=T[T[x].son[1]].size;
            T[x].sum+=T[T[x].son[1]].sum;
        }
    }
    int id[maxn],tot;
    bool rebuildRoot;//手动rebuild_{root}
    void getrank(int x) {
        if (T[x].son[0]) getrank(T[x].son[0]);
        if (!rebuildRoot||T[x].val) id[++tot]=x;
        if (T[x].son[1]) getrank(T[x].son[1]);
    }
    void rerank(int &x,int l,int r,ull L,ull R) {
        x=0; if (l>r) return;
        ull mid=(L+R)/2; int m=(l+r)/2;
        x=id[m]; T[x].rank=mid;
        rerank(T[x].son[0],l,m-1,L,mid-1);
        rerank(T[x].son[1],m+1,r,mid+1,R);
        pushup(x);
    }
    void rebuild(int &x,ull l,ull r) {
        if (!x) return;
        tot=0; getrank(x);
        rerank(x,1,tot,l,r);
    }
    void ins(int &x,ull l,ull r) {
        ull mid=(l+r)/2;
        if (!x) {x=cnt; if (l<=r) T[x].rank=mid; return;}
        int p=cmp(x,cnt);
        int &son=T[x].son[p];
        if (p==0) ins(son,l,mid-1);
        else ins(son,mid+1,r);
        pushup(x); //changes
        if (max(T[T[x].son[0]].size,T[T[x].son[1]].size)>
                T[x].size*alpha) rebuild(x,l,r);
    }
    void insert(char c) {
        T[++cnt].initval(c);
        T[cnt].pre=last; last=cnt;
        ins(root,1,MAX);
        if (!T[cnt].rank) {
            rebuildRoot=true;
            rebuild(root,1,MAX);
            rebuildRoot=false;
        }
    }
    void insert(char s[]) {
        int len=strlen(s),i;
        REP(i,len) insert(s[i]);
    }
    bool cmp(int k,char s[],int len) {//smaller //okay!
        for (int i=0; i<len; i++,k=T[k].pre) {
            if (!k) return 1;
            if (s[i]!=T[k].c) return T[k].c<s[i];
        } return 0;
    }
    int query(char s[],int len) {
        int ret=0;
        for (int now=root; now;) {
            if (!cmp(now,s,len)) now=T[now].son[0];
            else {
                ret+=T[now].val+T[T[now].son[0]].sum,
                     now=T[now].son[1];
            }
        } return ret;
    }
    int query(char s[]) {
        int len=strlen(s);
        reverse(s,s+len); s[len]='Z'+1;// s[len+1]=0;
        return query(s,len+1)-query(s,len);
    }
    void del(int k) {
        for (; k&&last; last=T[last].pre,k--) {
            int now;
            for (now=root; now!=last;) {
                T[now].sum--;
                int p=T[last].rank>=T[now].rank;
                now=T[now].son[p];
            } assert(last==now);
            T[last].val=0; T[last].sum--;
        } if (!last) root=0;
    }
    void init(){
        cnt=root=last=0;
    }
}

//2017icpc青岛J
//题意: 每个串找个后缀拼起来
//query 后缀最小序是多少
//倒着加, 然后找个最小rank把剩下的都去掉即可
char pool[maxn],*st=pool;
char *A[maxn]; int len[maxn];
char ans[maxn];int L;
int main() {
    int T;
    scanf("%d",&T);
    while (T--){
        int i,j;
        SAT::init(); L=0; st=pool;
        scanf("%d",&n);
        REP(i,n) {
            A[i]=st,scanf("%s",A[i]);
            st+=(len[i]=strlen(A[i]));
        }
        rREP(i,n) {
            // printf("i=%d;\n",i);
            rREP(j,len[i]) SAT::insert(A[i][j]);
            int k=SAT::last; ull MIN=SAT::T[k].rank;int l=0;
            REP(j,len[i]) {//del_cnt
                if (MIN>SAT::T[k].rank) MIN=SAT::T[k].rank,l=j; 
                k=SAT::T[k].pre;
            } SAT::del(l);
            rrep(j,l,len[i]) ans[L++]=A[i][j]; ans[L]=0;
        } reverse(ans,ans+L);
        printf("%s\n",ans);
    }
    return 0;
}
/*
*/
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

// 2016南宁D
// 复杂度是所有串的len和
// 题意: 是否存在一个排列, 使得能一一对应
// 做法: 求每个点前相同val的len差, 然后直接AC自动机
// 修改fail的写法
namespace ACM {
    const int maxn=1e6+7;
    map<int,int> next[maxn];
    int fail[maxn],len[maxn],tot;
    bool mark[maxn];
    void init() {
        tot=0; len[0]=0; fail[0]=0; mark[0]=0; next[0].clear();
    }
    void insert(int s[],int n) {
        int i,p=0;
        REP(i,n) {
            int c=s[i];
            if (!next[p].count(c)) {
                next[p][c]=++tot; len[tot]=len[p]+1;
                fail[tot]=0; mark[tot]=0;
                next[tot].clear();
            } p=next[p][c];
        } mark[p]=1;
    }
    int Q[maxn],ST,ED;
    inline int getnext(int x,int c){
        for (;;x=fail[x]){
            if (len[x]+1<=c) c=0;
            if (!x||next[x].count(c)) break;
        } if (next[x].count(c)) return next[x][c];
        return x;
    }
    void buildAC() {
        ST=0; ED=-1; Q[++ED]=0;
        while (ST<=ED) {
            int p=Q[ST++];
            for (auto now:next[p]){
                int c=now.first,nxt=now.second;
                if (p) fail[nxt]=getnext(fail[p],c);
                else fail[nxt]=0;
                Q[++ED]=nxt;
            } mark[p]|=mark[fail[p]];
        }
    }
    bool query(int a[],int n) {
        int p=0,have=0,i;
        REP(i,n) {
            int c=a[i]; p=getnext(p,c);
            have|=mark[p];
        } return have;
    }
}
int A[maxn],pre[255];//pre
int main() {
    int T,_t;
    scanf("%d",&T);
    FOR(_t,1,T) {
        ACM::init();
        printf("Case #%d: ",_t);
        scanf("%d",&n);
        int i,k,len;
        FOR(i,1,n) {
            scanf("%s",str); len=strlen(str);
            FOR(k,'A','Z') pre[k]=len;
            REP(k,len) A[k]=max(0,k-pre[(int)str[k]]),pre[(int)str[k]]=k;
            ACM::insert(A,len);
        } ACM::buildAC();
        scanf("%d",&n);
        FOR(i,1,n) {
            scanf("%s",str); len=strlen(str);
            FOR(k,'A','Z') pre[k]=len;
            REP(k,len) A[k]=max(0,k-pre[(int)str[k]]),pre[(int)str[k]]=k;
            if (ACM::query(A,len)) printf("Y");
            else printf("N");
            printf("%c"," \n"[i==n]);
        }
    }
}
/*
*/

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
// const LL M=585698298;
// const LL M=998244353;
const LL M=1e9+7;
// ll M=1;
const LL maxn=2e6+107;
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

// Count代表串出现次数
// len[fail[x]]+1->len[x]为x代表的后缀串
vector<int> sub[maxn];
struct SAM{
    int next[maxn][26],fail[maxn],len[maxn];
    int cnt,last;
    int Count[maxn]; // 串出现次数
    void init(){
        cnt=last=0;fail[0]=-1;len[0]=0;
        memset(next[0],0,sizeof(next[0]));
    }
    void add(int c){
        int np=++cnt,p=last;
        memset(next[np],0,sizeof(next[np]));
        len[np]=len[p]+1;
        for (;p!=-1&&!next[p][c];p=fail[p]) next[p][c]=np;
        if (p==-1) fail[np]=0;
        else {
            int q=next[p][c];
            if (len[p]+1==len[q]) fail[np]=q;
            else{
                int nq=++cnt;len[nq]=len[p]+1;
                memcpy(next[nq],next[q],sizeof(next[q]));
                fail[nq]=fail[q];
                fail[np]=fail[q]=nq;
                for (;p!=-1&&next[p][c]==q;p=fail[p]) next[p][c]=nq;
            }
        }
        last=np;
        Count[last]=1;
    }

    int S[maxn],id[maxn];
    ll solve(){
        int i,ret=0;
        FOR(i,1,cnt) S[len[i]]++;
        FOR(i,1,cnt) S[i]+=S[i-1];
        FOR(i,1,cnt) id[S[len[i]]--]=i;
        rFOR(i,1,cnt) {
            int x=id[i];
            Count[fail[x]]+=Count[x];
            for (int v:sub[Count[x]]) if (len[fail[x]]<v&&v<=len[x]) ret+=Count[x];
            // ret+=len[x]/Count[x]-len[fail[x]]/Count[x];
        }
        // FOR(i,1,cnt) printf("x=%d; len[x]=%d; len[fail[x]]=%d; count=%d\n",i,len[i],len[fail[i]],Count[i]);
        return ret;
    }
    char a[maxn];
    void dfs(int x=0,int len=0){
        int i;
        if (fail[x]!=-1)
            printf("%-3d(fail:%-3d,len=%-2d->%-2d;cnt=%-2d):%s\n",x,fail[x],this->len[fail[x]]+1,this->len[x],Count[x],a);
        REP(i,26){
            if (next[x][i]){
                a[len]=i+'a';
                dfs(next[x][i],len+1);
                a[len]=0;
            }
        }
    }
}sam;
char str[maxn];
int main() {
    int n,i;
    scanf("%d%s",&n,str);
    for (int i=1;i<=n;i++)
        for (int j=i;j<=n;j+=i) sub[j].push_back(i);
    sam.init();
    REP(i,n) sam.add(str[i]-'a');
    ll ans=sam.solve();
    // sam.dfs();
    printf("%lld\n",ans);
}
/*
*/
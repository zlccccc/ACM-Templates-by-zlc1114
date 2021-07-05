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

//对于sans,diff,slink:
//sans是把之前的series_ans保留下来; dp on pam
//diff相同时,sans一定会与上一个相同(由于对称的特殊性)
//所以只需改变diff改变时的ans即可 dp on initial

//区间 本质不同 回文串数; 每个r对应的fail是一堆区间(son-max to x)所以区间更新
//由于border的特性, 可以通过等差数列的方法来分类更新答案
//bzoj5384,跳border+bit可以做到两个log

//注意每次更新每个series是更新最右部分答案
//leftposition=i-pam.len[pam.anc[p]]+1
//rightpostion=l+pam.diff[p]-1(final) (left+1 - right为不是回文串)
struct PAM {
    int next[maxn][27];
    int fail[maxn];
    int len[maxn];//长度
    int diff[maxn];//length(this-fail)
    int anc[maxn];//diff不同的fail,共log个
    int S[maxn];//字符
    int last;//上一个字符节点
    int n,tot;//n表示字符位置
    int newnode(int l) {
        memset(next[tot],0,sizeof(next[tot]));
        len[tot]=l;//不是1...
        return tot++;
    }
    void init() {
        tot=0; last=n=0;
        newnode(0); newnode(-1);
        S[n]=-1; fail[0]=1;
    }
    int getfail(int x) {
        while (S[n-len[x]-1]!=S[n]) x=fail[x];
        return x;
    }
    int add(int c) {
        S[++n]=c;
        int cur=getfail(last);
        if (!next[cur][c]) {
            int now=newnode(len[cur]+2);
            fail[now]=next[getfail(fail[cur])][c];
            diff[now]=len[now]-len[fail[now]];
            if (diff[now]==diff[fail[now]])
                anc[now]=anc[fail[now]];
            else anc[now]=now;
            next[cur][c]=now;//这里一定要在fail后边=_=
        } return last=next[cur][c];
    }
    char a[maxn];
    void dfs(int p,int len=0) {
        int c;
        printf("%-20s (p=%-5d, length=%-5d fail=%-5d anc=%-5d diff=%-5d)",a,p,this->len[p],fail[p],anc[p],diff[p]);
        // if (p>=2) printf("%d len=%lld\n",);
        puts("");
        REP(c,26) if (next[p][c]) {
            a[len]=c+'a';
            dfs(next[p][c],len+1);
            a[len]=0;
        }
    }
} pam;
int dfn[maxn],out[maxn],tot;
vector<int> edge[maxn];
void getdfn(int x) {
    dfn[x]=++tot;
    for (int _=0; _<(int)edge[x].size(); _++)
        getdfn(edge[x][_]);
    out[x]=tot;
}
namespace SEG {
    int MAX[maxn<<2];
    void init(int val) {
        memset(MAX,0,(val+1)*sizeof(int)*4);
    }
    int query(int x,int l,int r,int L,int R) {
        if (l<=L&&R<=r) return MAX[x];
        int mid=(L+R)/2,ret=0;
        if (l<=mid) ret=max(ret,query(x<<1,l,r,L,mid));
        if (mid<r) ret=max(ret,query(x<<1|1,l,r,mid+1,R));
        return ret;
    }
    void update(int x,int pos,int val,int L,int R) {
        if (L==R) {MAX[x]=val; return;}
        int mid=(L+R)/2;
        if (pos<=mid) update(x<<1,pos,val,L,mid);
        else update(x<<1|1,pos,val,mid+1,R);
        MAX[x]=max(MAX[x<<1],MAX[x<<1|1]);
    }
}
namespace BIT {
    int sum[maxn],n;
    void init(int val) {
        memset(sum,0,(val+1)*sizeof(int)); n=val;
    }
    inline int lowbit(int x) {return x&-x;}
    void add(int x,int val) {
        for (; x<=n; x+=lowbit(x)) sum[x]+=val;
    }
    inline int get(int x) {
        int ret=0;
        for (; x; x-=lowbit(x)) ret+=sum[x];
        return ret;
    }
}
vector<pair<int,int> > queries[maxn];
char str[maxn];
int id[maxn];
ll ans[maxn];
int main() {
    int n,q;
    scanf("%d%d%s",&n,&q,str);
    int i;
    pam.init();
    REP(i,n) id[i+1]=pam.add(str[i]-'a');
    // pam.dfs(0); puts("0");//2
    // pam.dfs(1); puts("1");//1
    REP(i,pam.tot) edge[i].clear();
    REP(i,pam.tot) if (i!=1) edge[pam.fail[i]].push_back(i);
    tot=0; getdfn(1);
    FOR(i,1,q) {
        int l,r; scanf("%d%d",&l,&r);
        queries[r].push_back(make_pair(l,i));
    } BIT::init(n);
    SEG::init(tot);
    FOR(i,1,n) {
        for (int p=id[i]; pam.len[p]>0; p=pam.fail[pam.anc[p]]) {
            int l=max(1,SEG::query(1,dfn[p],out[p],1,tot)-pam.len[p]+1+1);//left-maxposition
            int r=i-pam.len[pam.anc[p]]+1+1;//+1:series-start; 等差数列一起算(比较特殊,可以一起+1)
            BIT::add(l,1); BIT::add(r,-1);
        } SEG::update(1,dfn[id[i]],i,1,tot);
        for (int _=0; _<(int)queries[i].size(); _++)
            ans[queries[i][_].second]=BIT::get(queries[i][_].first);
    }
    int Ans=0;
    FOR(i,1,q) Ans=(Ans+(ll)ans[i]*i)%M;
    printf("%d\n",Ans);
}
/*
11 1
ababaaababa
1 10
*/

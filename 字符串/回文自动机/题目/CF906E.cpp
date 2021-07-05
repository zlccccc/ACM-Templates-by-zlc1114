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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct Ptree{
    int next[maxn][27];//空间可优化
    int fail[maxn];
    int len[maxn];//长度
    int diff[maxn];//length(this-fail)
    int slink[maxn];//diff不同的fail,共log个
//    slink用来算sans,sabs转移得到ans //用来求的是分成串的个数
    int S[maxn];//字符
    int last;//上一个字符节点
    int n,tot;//n表示字符位置
    int newnode(int l){
        memset(next[tot],0,sizeof(next[tot]));
        len[tot]=l;//不是1...
        return tot++;
    }
    void init(){
        tot=0;last=n=0;
        newnode(0);newnode(-1);
        S[n]=-1;//减少特判
        fail[0]=1;
    }
    int getfail(int x){
        while(S[n-len[x]-1]!=S[n]) x=fail[x];
        return x;
    }
    void add(int c){
        c-='a';
        S[++n]=c;
        int cur=getfail(last);
        if (!next[cur][c]){
            int now=newnode(len[cur]+2);
            fail[now]=next[getfail(fail[cur])][c];
            next[cur][c]=now;
            diff[now]=len[now]-len[fail[now]];
            if (diff[now]==diff[fail[now]]) slink[now]=slink[fail[now]];
            else slink[now]=fail[now];
        }
        last=next[cur][c];
    }
}T;
int n,m,q;
int i,j,k;
int sans[maxn],spre[maxn];
int cnt[maxn],pre[maxn],lef[maxn];
char a[maxn],b[maxn],c[maxn];
int main(){
    scanf("%s%s",a,b);
    n=strlen(a);T.init();m=0;
    REP(i,n) c[++m]=a[i],c[++m]=b[i];
    FOR(i,1,m){
        T.add(c[i]);cnt[i]=INF;
        if (!(i&1)&&c[i]==c[i-1]) cnt[i]=cnt[i-2],pre[i]=pre[i-2];
        for (int v=T.last;T.len[v]>0;v=T.slink[v]){
            sans[v]=cnt[i-(T.len[T.slink[v]]+T.diff[v])];
            spre[v]=i-(T.len[T.slink[v]]+T.diff[v])+2;
            if (T.diff[v]==T.diff[T.fail[v]]){
                if (sans[v]>sans[T.fail[v]]){
                    sans[v]=sans[T.fail[v]];
                    spre[v]=spre[T.fail[v]];
                }
            }
            if (!(i&1)){
                if (sans[v]+1<cnt[i]){
                    cnt[i]=sans[v]+1;
                    lef[i]=spre[v];
                    pre[i]=i;
                }
            }
        }
    }
    if (cnt[m]>=INF) return 0*puts("-1");
    printf("%d\n",cnt[m]);
    i=m;
    while (1){
        if (pre[i]!=i) i=pre[i];
        if (!i) break;
        printf("%d %d\n",lef[i]/2,i/2);
        i=lef[i]-2;
    }
}
/*
*/

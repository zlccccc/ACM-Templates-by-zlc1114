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

//这里的len不可以直接使用~ 原因是这里的len指的是原串len
//fail过后,len是可以直接使用的~ (会fail到确定的节点上)
//这个fail的含义是说后缀相同,向前拓展的val(一个一个拓展len差项)
//sam反向不为拓扑序!注意自己进行拓扑排序
//更新时注意len的限制!(因为更新时可能根本没有考虑前缀len)
//注意nq在更新时更新时val和q是相等的,也就是说,维护值时nq要完全和q一样
//sum{len[x]-len[fail[x]]}=不同串个数,每个串代表fail->this的len
//每个串的位置建议存的时候就保留下来~ 要不就有点麻烦了
//复制出来的虚拟节点在计算次数时不参与计算~
//也就是说计算相同串个数时,复制出来的只是个虚拟的节点
//query时在末尾加个0可以去掉很多的判断!
//加空字符时注意len,这个len有两个作用:避免topo排错,减少add特判
//加的不是root,就是个空字符,dfs的话只能dfs一个串!从后往前递推可行
struct SAM{
    int next[maxn][26],fail[maxn],len[maxn];
    int cnt,last;
    void init(){
        cnt=last=0;fail[0]=-1;len[0]=0;
        memset(next[0],0,sizeof(next[0]));
    }int CNT[maxn];bool OK[maxn];
    void addempty(){//加个分隔符
        int np=++cnt;last=np;len[np]=1;fail[np]=0;
        memset(next[np],0,sizeof(next[np]));
    }
    void add(int c,bool mark){
        int np=++cnt,p=last;
        memset(next[np],0,sizeof(next[np]));
        len[np]=len[p]+1;
        CNT[np]=mark;OK[np]=!mark;
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
                OK[nq]=OK[q];CNT[nq]=0;
            }
        }
        last=np;
    }
    int S[maxn],Q[maxn];//Q:id
    void solve(int l,int r){
        int i;
        FOR(i,1,cnt) S[i]=0;
        FOR(i,1,cnt) S[len[i]]++;
        FOR(i,1,cnt) S[i]+=S[i-1];
        FOR(i,1,cnt) Q[S[len[i]]--]=i;
        rFOR(i,1,cnt) CNT[fail[Q[i]]]+=CNT[Q[i]];
        FOR(i,1,cnt) if (CNT[i]<l||r<CNT[i]) OK[i]=0;
        FOR(i,1,cnt) CNT[i]=0;
    }LL Solve(){
        int i;LL ret=0;
        FOR(i,1,cnt) if (OK[i]) ret+=len[i]-len[fail[i]];
        return ret;
    }
    char a[maxn];
    void dfs(int x=0,int len=0){
        int i;
        printf("%-3d %-3d ",CNT[x],OK[x]);
        printf("%-3d(fail:%-3d):%s\n",x,fail[x],a);
        REP(i,26){
            if (next[x][i]){
                a[len]=i+'a';
                dfs(next[x][i],len+1);
                a[len]=0;
            }
        }
    }
}sam;
int n,m,T;
int i,j,k;
char a[maxn];
int main(){
    scanf("%s",a);
    n=strlen(a);sam.init();
    REP(i,n) sam.add(a[i]-'a',0);
    scanf("%d",&n);
    FOR(i,1,n){
        sam.addempty();
        int l,r;
        scanf("%s%d%d",a,&l,&r);
        int i,n=strlen(a);
        REP(i,n) sam.add(a[i]-'a',1);
        sam.solve(l,r);
//        sam.dfs();
    }printf("%I64d\n",sam.Solve());
}
/*
ppppppppppp
1
pppppppppppp 2 4
*/

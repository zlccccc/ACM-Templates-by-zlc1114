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
const LL maxn=4e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct SAM{
    //这里的len不可以直接使用~ 原因是这里的len指的是原串len
    //fail过后,len是可以直接使用的~ (会fail到确定的节点上)
    //这个fail的含义是说后缀相同,向前拓展的val
    //反向不为拓扑序!注意自己进行拓扑排序
    //更新时注意len的限制!(因为更新时可能根本没有考虑前缀len)
    //注意nq在更新时更新时val和q是相等的,也就是说,维护值时nq要完全和q一样
    //query时在末尾加个0可以去掉很多的判断!
    //sum{len[x]-len[fail[x]]}=不同串个数,每个串代表fail->this的len
    //每个串的位置建议存的时候就保留下来~ 要不就有点麻烦了
    int next[maxn][26],fail[maxn],len[maxn];
    int cnt,last;
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
    }
    char a[maxn];
    void dfs(int x=0,int len=0){
        int i;
        printf("%-3d(fail:%-3d):%s\n",x,fail[x],a);
        REP(i,10){
            if (next[x][i]){
                a[len]=i+'0';
                dfs(next[x][i],len+1);
                a[len]=0;
            }
        }
    }
}sam;
const int M_M=2012;
int n,m,T;
int i,j,k;
char a[maxn];
int cnt[maxn],val[maxn];
int S[maxn],Q[maxn];//Q:id
int main(){
    while (~scanf("%d",&n)){
        sam.init();
        while (n--){
            scanf("%s",a);
            int n=strlen(a);
            REP(i,n) sam.add(a[i]-'0');
            sam.add(10);
        }FOR(i,1,sam.cnt) S[i]=0;
        FOR(i,1,sam.cnt) S[sam.len[i]]++;
        FOR(i,1,sam.cnt) S[i]+=S[i-1];
        FOR(i,1,sam.cnt) Q[S[sam.len[i]]--]=i;
        FOR(i,1,sam.cnt) val[i]=cnt[i]=0;
        cnt[0]=1;val[0]=0;
        FOR(i,0,sam.cnt){
            REP(j,10){
                if (!i&&!j) continue;
                if (!sam.next[Q[i]][j]) continue;
                (cnt[sam.next[Q[i]][j]]+=cnt[Q[i]])%=M_M;
                (val[sam.next[Q[i]][j]]+=val[Q[i]]*10+cnt[Q[i]]*j)%=M_M;
            }
        }int ans=0;
//        FOR(i,1,sam.cnt) printf("%4d ",Q[i]);puts("");
//        FOR(i,0,sam.cnt) printf("%4d ",cnt[i]);puts("");
//        FOR(i,0,sam.cnt) printf("%4d ",val[i]);puts("");
//        sam.dfs();
        FOR(i,1,sam.cnt) (ans+=val[i])%=M_M;
        printf("%d\n",ans);
    }
}
/*
2
321
123
*/

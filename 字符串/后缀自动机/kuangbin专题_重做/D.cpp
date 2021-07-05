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
const LL maxn=5e5+7;
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
    int next[maxn][26],fail[maxn],len[maxn];
    int cnt,last;
    void init(){
        cnt=last=0;fail[0]=-1;len[0]=0;
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
        REP(i,26){
            if (next[x][i]){
                a[len]=i+'a';
                dfs(next[x][i],len+1);
                a[len]=0;
            }
        }
    }
}sam;

int n,m;
int i,j,k;
char a[maxn];
LL cnt[maxn];
int S[maxn],Q[maxn];//Q:id
int ans[maxn],p,l;
int main(){
    scanf("%s",a);
    n=strlen(a);
    sam.init();
    REP(i,n) sam.add(a[i]-'a');
    p=0;
//    sam.dfs();
    REP(i,n){
        int c=a[i]-'a';
        p=sam.next[p][c];
        cnt[p]++;
    }FOR(i,1,sam.cnt) S[sam.len[i]]++;
    FOR(i,1,n) S[i]+=S[i-1];
    FOR(i,1,sam.cnt) Q[S[sam.len[i]]--]=i;
    rFOR(i,1,sam.cnt){
        cnt[Q[i]]=1;
        REP(j,26) if (sam.next[Q[i]][j]) cnt[Q[i]]+=cnt[sam.next[Q[i]][j]];
    }int q;
    scanf("%d",&q);
    while (q--){
        int p=0,now,m=0;
        scanf("%d",&now);
        while (now){
            int c=0;if (p) now--;
            if (!now) break;
            while (!sam.next[p][c]||now>cnt[sam.next[p][c]]){
                now-=cnt[sam.next[p][c]];
                c++;
            }p=sam.next[p][c];
            a[m++]=c+'a';
        }a[m]=0;
        puts(a);
    }
}
/*
aabaa
100
*/

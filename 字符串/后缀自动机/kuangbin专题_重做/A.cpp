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

struct SAM{
    //这里的len不可以直接使用~ 原因是这里的len指的是原串len
    //fail过后,len是可以直接使用的~ (会fail到确定的节点上)
    int next[maxn][26],fail[maxn],len[maxn];
    int cnt,last;
    void init(){
        last=++cnt;
    }
    void add(int c){
        int np=++cnt,p=last;
        memset(next[np],0,sizeof(next[np]));
        len[np]=len[p]+1;
        for (;p&&!next[p][c];p=fail[p]) next[p][c]=np;
        if (!p) fail[np]=1;
        else {
            int q=next[p][c];
            if (len[p]+1==len[q]) fail[np]=q;
            else{
                int nq=++cnt;len[nq]=len[p]+1;
                memcpy(next[nq],next[q],sizeof(next[q]));
                fail[nq]=fail[q];
                fail[np]=fail[q]=nq;
                for (;p&&next[p][c]==q;p=fail[p]) next[p][c]=nq;
            }
        }
        last=np;
    }
        char a[maxn];
        void dfs(int x=1,int len=0){
            int i;
            printf("%s\n",a);
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
char a[maxn],b[maxn];
int ans,p,len;
int main(){
    scanf("%s%s",a,b);
    n=strlen(a);m=strlen(b);
    sam.init();
    REP(i,n) sam.add(a[i]-'a');
//    sam.dfs(1,0);
    p=1;len=0;
    REP(i,m){
        int c=b[i]-'a';
        for (;p&&!sam.next[p][c];p=sam.fail[p],len=sam.len[p]);
        if (!p) p=1,len=0;
        else p=sam.next[p][c],len++;
        ans=max(ans,len);
    }
    printf("%d\n",ans);
}
/*
*/

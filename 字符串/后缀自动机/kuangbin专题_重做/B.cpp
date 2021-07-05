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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct SAM{
    //这里的len不可以直接使用~ 原因是这里的len指的是原串len
    //fail过后,len是可以直接使用的~ (会fail到确定的节点上)
    //这个fail的含义是说后缀相同,向前拓展的val
    //反向为拓扑序!更新时注意len的限制!(因为更新时可能根本没有考虑前缀len)
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
char a[maxn];
int len[maxn],L[maxn],S[maxn],Q[maxn];
int ans,p,l;
int main(){
    scanf("%s",a);
    n=strlen(a);
    sam.init();
    REP(i,n) sam.add(a[i]-'a');
    FOR(i,1,sam.cnt) S[sam.len[i]]++;
    FOR(i,1,n) S[i]+=S[i-1];
    FOR(i,1,sam.cnt) Q[S[sam.len[i]]--]=i;
    FOR(i,1,sam.cnt) L[i]=sam.len[i];
    while (~scanf("%s",a)){
        p=l=0;n=strlen(a);
        REP(i,n){
            int c=a[i]-'a';
            if (sam.next[p][c]) p=sam.next[p][c],l++;
            else{
                for (;p!=-1&&!sam.next[p][c];p=sam.fail[p]);
                if (p==-1) p=l=0;
                else l=sam.len[p]+1,p=sam.next[p][c];
            }len[p]=max(len[p],l);
        }rFOR(i,1,sam.cnt) len[sam.fail[Q[i]]]=max(len[sam.fail[Q[i]]],len[Q[i]]);
        FOR(i,0,sam.cnt) L[i]=min(L[i],len[i]),len[i]=0;
    }FOR(i,0,sam.cnt) ans=max(ans,L[i]);
    printf("%d\n",ans);
}
/*
*/

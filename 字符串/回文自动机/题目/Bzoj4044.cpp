#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
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
const LL MOD=1e9+7;
const LL maxn=3e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%MOD) ret=1ll*ret*a%MOD;return ret;}

//题意:一个字符串,几种操作:把一个串前面加字符,后面加字符,翻转后加到后边
//求最小的操作次数
struct Ptree{
    int next[maxn][4];
    int fail[maxn];
    int len[maxn];
    int S[maxn];
    int F[maxn],half[maxn];//used
    int last,n,tot;
    int newnode(int l){
        memset(next[tot],0,sizeof(next[tot]));
        len[tot]=F[tot]=l;
        return tot++;
    }
    void init(){
        tot=0;last=n=0;
        newnode(0);newnode(-1);
        S[n]=-1;fail[0]=1;
        F[0]=1;
    }
    int getfail(int x){
        while (S[n-len[x]-1]!=S[n]) x=fail[x];
        return x;
    }
    int add(int c){
        S[++n]=c;
        int cur=getfail(last);
        if (!next[cur][c]){
            int now=newnode(len[cur]+2);
            fail[now]=next[getfail(fail[cur])][c];
            next[cur][c]=now;
            if (len[now]&1) F[now]=len[now];
            else F[now]=F[cur]+1;
            int pre=next[getfail(half[cur])][c];//这里我错了2h...这里pre貌似不能当全局变量来维护(TLE?)
            while (len[pre]>len[now]/2) pre=fail[pre];
            if (!(len[now]&1))
                F[now]=min(F[now],len[now]/2+1-len[pre]+F[pre]);
            half[now]=pre;
//                printf("now=%d; len=%d; F=%d; fail=%d,pre=%d; len[pre]=%d,nextpre=%d\n",now,len[now],F[now],cur,pre,len[pre],next[pre][c]);
//                printf("len=%d %d\n",len[now]/2+1-len[pre]+F[pre],len[now]/2-len[pre]+F[pre]+1);
        }last=next[cur][c];
        return len[last]-F[last];
    }
}PT;
inline int remark(char c){
    if (c=='A') return 0;
    if (c=='T') return 1;
    if (c=='C') return 2;
    return 3;
}
char a[maxn];
int T;
int main(){
    scanf("%d",&T);
    while (T--){
        int i,j,k;
        scanf("%s",a);
        int n=strlen(a),ans=0;
        PT.init();
        REP(i,n) ans=max(ans,PT.add(remark(a[i])));
        printf("%d\n",n-ans);
    }
}
/*
10
AAAAAAAAA
AAGGGGAAGGGGAA
AGCTTGCA
AAAA
AAACAGTCCTGACAAAAAAAAAAAAC
*/

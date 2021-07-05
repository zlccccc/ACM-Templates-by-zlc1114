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
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

// CF741D 辣鸡题
// 问你重排能回文的最长串多长
// 直接上就可以了... 看下dfs顺序就行了
vector<int> edge[maxn];
int sz[maxn],son[maxn];
void dfs1(int x) {
    int mx=0; sz[x]=1;
    for (int v:edge[x]) {
        dfs1(v); sz[x]+=sz[v];
        if (sz[v]>mx) son[x]=v,mx=sz[v];
    }
}
int A[maxn],dep[maxn];
int ans[maxn],MX[1<<22|7];
map<int,int> MP[maxn];
int Merge(map<int,int> &A,map<int,int> &B,int x) { //B->A
    int ret=0,i;
    for (auto now:B) {
        int p=now.first,l=now.second;
        if (MX[p]) ret=max(ret,MX[p]+l-2*dep[x]);
        REP(i,22) {
            p=now.first^(1<<i);
//            printf("now=%d; p=%d; %d %d %d\n",now.first,p,MX[p],l,dep[x]);
            if (MX[p]) ret=max(ret,MX[p]+l-2*dep[x]);
        }
    }//merge
    for (auto now:B) {
        int p=now.first,l=now.second;
        MX[p]=max(MX[p],l); A[p]=MX[p];
    } map<int,int>().swap(B);
    return ret;
}
void dfs2(int x) {
    for (int v:edge[x]) if (v!=son[x]) {
            dfs2(v); ans[x]=max(ans[x],ans[v]);
            for (auto now:MP[v]) MX[now.first]=0;
        } if (son[x]) {
        dfs2(son[x]); ans[x]=max(ans[x],ans[son[x]]);
    }//cal
    MP[x][A[x]]=dep[x];
    if (son[x]) {
        ans[x]=max(ans[x],Merge(MP[son[x]],MP[x],x));
        swap(MP[x],MP[son[x]]);
    } else MX[A[x]]=dep[x];
    for (int v:edge[x]) if (v!=son[x]) {
            ans[x]=max(ans[x],Merge(MP[x],MP[v],x));
        }
}
int main() {
    int n,i,j,k;
    char c;
    scanf("%d",&n);
    FOR(i,2,n) {
        int fa;
        scanf("%d %c",&fa,&c);
        A[i]=A[fa]^(1<<(c-'a'));
        dep[i]=dep[fa]+1;
        edge[fa].push_back(i);
    } dfs1(1); dfs2(1);
    FOR(i,1,n) printf("%d ",ans[i]);
    return 0;
}
/*
*/

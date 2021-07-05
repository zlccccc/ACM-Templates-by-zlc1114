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
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M; return ret;}
//http://codeforces.com/gym/100962/attachments
//题意是求路径上最小没出现数字
//主要思路是分类,每个点进出各算一次可以消除影响
//点的直接加个lca即可
const int SIZE=500;
vector<pair<int,int> > edge[maxn];
int cl[maxn],cr[maxn],val[maxn],dfn[maxn<<1];
int tot;
int dfs(int x,int fa) {
    cl[x]=++tot; dfn[tot]=x;
    for (auto now:edge[x]) if (now.first!=fa) {
            dfs(now.first,x);
            val[now.first]=now.second;
        } cr[x]=++tot; dfn[tot]=x;
}
int block[maxn<<1];
struct node {
    int l,r,id;
} Q[maxn];
int cmp(node a,node b) {
    if (block[a.l]==block[b.l]) return a.r<b.r;
    return block[a.l]<block[b.l];
}
bool vis[maxn];
int cnt[maxn],cur[maxn];//block,now
void change(int x) {
    x=dfn[x]; vis[x]^=1;
    if (vis[x]) {
        if (!cur[val[x]]) cnt[block[val[x]]]++;
        cur[val[x]]++;
    } else {
        cur[val[x]]--;
        if (!cur[val[x]]) cnt[block[val[x]]]--;
    }
}
int ans[maxn];
int L,R;
int main() {
    int n,q;
    int i;
    scanf("%d%d",&n,&q);
    FOR(i,0,n*2+1) block[i]=i/SIZE;
    REP(i,n-1) {
        int u,v,len;
        scanf("%d%d%d",&u,&v,&len); len=min(len,n+1);
        edge[u].push_back(make_pair(v,len));
        edge[v].push_back(make_pair(u,len));
    }
    val[1]=n+1; dfs(1,0);
    REP(i,q) {
        int a,b;
        scanf("%d%d",&a,&b);
        if (cl[a]>cl[b]) swap(a,b);
        if (cr[a]>cr[b]) Q[i].l=cl[a]+1,Q[i].r=cl[b];
        else Q[i].l=cr[a],Q[i].r=cl[b];
        Q[i].id=i;
    }
    sort(Q,Q+q,cmp);
    L=1; R=0;
    REP(i,q) {
        while (L<Q[i].l) {change(L); L++;}
        while (R>Q[i].r) {change(R); R--;}
        while (L>Q[i].l) {L--; change(L);}
        while (R<Q[i].r) {R++; change(R);}
        int now=0;
        while (cnt[now]==SIZE) now++;
        now*=SIZE;
        while (cur[now]) now++;
        ans[Q[i].id]=now;
    }
    REP(i,q) printf("%d\n",ans[i]);
}
/*
*/

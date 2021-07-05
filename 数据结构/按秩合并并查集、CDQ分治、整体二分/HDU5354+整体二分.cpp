#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
const LL INF=0x3f3f3f3f;
const LL INFF=0x1f3f3f3f3f3f3f3fll;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}
inline LL powMM(LL a,LL b){
    LL ret=1;
    while (b){
        if (b&1) ret=ret*a%M;
        a=a*a%M;
        b>>=1;
    }
    return ret;
}

// 求删去每个点后图是否存在奇环(主要是整体二分思想)
// 直接更改边在两边对答案的影响
// 然后递归的往下做
typedef pair<int,int>  pii;
#define fi first
#define se second
#define mp make_pair
vector<pii> E[maxn<<2],have[maxn<<2],back[maxn<<2];//防爆栈 
int fa[maxn],val[maxn];
pii getfa(int x){
    int ret=x,color=val[ret];
    while (fa[ret]!=ret) ret=fa[ret],color^=val[ret];
    return mp(ret,color);
}
int sz[maxn];
int ans[maxn];
void solve(int X,int l,int r){
    bool flag=0;
    int i;
    for(pii e:have[X]){
        pii x=getfa(e.fi);
        pii y=getfa(e.se);
        if (x.fi==y.fi){
            if (x.se==y.se){
                flag=1;
                break;
            }
        }else{
            if (sz[x.fi]>sz[y.fi]) swap(x,y);
            back[X].push_back(mp(x.fi,x.se^y.se));
            fa[x.fi]=y.fi;
            sz[y.fi]+=sz[x.fi];
            val[x.fi]^=x.se^y.se;
        }
    }
    if (flag){
        FOR(i,l,r) ans[i]=0;
    }else if (l<r){
        int mid=(l+r)/2;
        for (pii e:E[X]){
            if ((l<=e.fi&&e.fi<=mid)||(l<=e.se&&e.se<=mid))
                E[X<<1].push_back(e);
            else have[X<<1].push_back(e);
            if ((mid+1<=e.fi&&e.fi<=r)||(mid+1<=e.se&&e.se<=r))
                E[X<<1|1].push_back(e);
            else have[X<<1|1].push_back(e);
        }
        solve(X<<1,l,mid);
        solve(X<<1|1,mid+1,r);
    }
    for (pii u:back[X]){
        sz[fa[u.fi]]-=sz[u.fi];
        fa[u.fi]=u.fi;
        val[u.fi]^=u.se;
    }
    vector<pii>().swap(E[X]);
    vector<pii>().swap(have[X]);
    vector<pii>().swap(back[X]);
}
int n,m;
int i;
int main()
{
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%d%d",&n,&m);
        FOR(i,1,n) fa[i]=i,sz[i]=1,ans[i]=1,val[i]=1;
        FOR(i,1,m){
            int u,v;
            scanf("%d%d",&u,&v);
            if (u>v) swap(u,v);
            E[1].push_back(make_pair(u,v));
        }
        solve(1,1,n);
        FOR(i,1,n) printf("%d",ans[i]);puts("");
    }
}
/*
*/

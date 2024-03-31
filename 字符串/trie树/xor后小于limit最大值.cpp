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
const LL maxn=1e5+7;
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

//x xor v->max;
//没注释的是v<limit
//注释的是xor后小于limit
//计数问题有个套路:
//先算出全部,然后for一边容斥
int nxt[maxn*20*10][2],tot;
int cnt[maxn*20*10];
LL xornum,limit;
void Ins(int &now,int k,int val) {
    if (!now) now=++tot;
    cnt[now]+=val;
    if (k==-1) return;
    int c=(xornum>>k)&1;
    Ins(nxt[now][c],k-1,val);
}
LL Que(int now,int k,bool mark) { //mark:have limit
    if (!now||!cnt[now]) return -INFF;
    if (k==-1) return 0;
    int c=(xornum>>k)&1,lim=(limit>>k)&1;
    LL ret=-INFF;
    if (!lim&&mark) {
        return (c<<k)+Que(nxt[now][0],k-1,mark);
//        return Que(nxt[now][c],k-1,mark);
    } else {
        ret=(1ll<<k)+Que(nxt[now][c^1],k-1,mark&&!(c&1));
        if (ret<0) ret=Que(nxt[now][c],k-1,mark&&(c&1));
//        ret=(1ll<<k)+Que(nxt[now][c^1],k-1,mark);
//        if (ret<0) ret=Que(nxt[now][c],k-1,0);
    } return ret;
}
vector<int> pre[maxn];
bool mark[maxn];
int main() {
    int i,j,T;
    FOR(i,1,100000) {
        for (j=i; j<=100000; j+=i)
            pre[j].push_back(i);
    } int n;
    scanf("%d",&n);
    tot=100000;
    FOR(i,1,n) {
        int op;
        int x,k,s;
        scanf("%d",&op);
        if (op==1) {
            scanf("%d",&x);
            if (mark[x]) continue;
            xornum=x;
            for (int v:pre[x]) Ins(v,20,1);
            mark[x]=1;
        } else {
            scanf("%d%d%d",&x,&k,&s);
            if (x%k!=0||s-x<0) {
//                printf("%d %d\n",x%k,s-x);
                puts("-1");
                continue;
            } xornum=x; limit=s-x;
            int ans=Que(k,20,1);
            if (ans<0) puts("-1");
            else printf("%d\n",ans^x);
        }
    }
}
/*
*/

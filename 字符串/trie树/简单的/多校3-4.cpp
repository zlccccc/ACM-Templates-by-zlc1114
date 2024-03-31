#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=5e5+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;
const double eps=0.000001;

//求i<j<k&&i^j<j^k的三元组个数
//维护val //left,right各一个
int T,n;
LL ans;
int i,j;
int a[maxn*32];
int nxt[maxn*32][2];
LL num[maxn*32],last[maxn*32];
LL sum[maxn][32][2];//只有这位。。。
int cnt,now;
int main() {
    scanf("%d",&T);
    while (T--) {
        ans=0;
        cnt=0;
        scanf("%d",&n);
        FOR(i,1,n) scanf("%d",&a[i]);
        FOR(i,1,n) {
            rREP(j,32) {
                int mark=((a[i]&(1<<j))!=0);
                sum[i][j][0]=sum[i-1][j][0];
                sum[i][j][1]=sum[i-1][j][1];
                sum[i][j][mark]++;
            }
        }
        rFOR(i,1,n) {
            now=0;
            rREP(j,32) {
                int mark=((a[i]&(1<<j))!=0);
                if (nxt[now][mark^1])
                    ans+=last[nxt[now][mark^1]]
                        -num[nxt[now][mark^1]]*sum[i][j][mark];
                if (!nxt[now][mark]) break;
                now=nxt[now][mark];
            }
            now=0;
            rREP(j,32) {
                int mark=((a[i]&(1<<j))!=0);
                if (!nxt[now][mark]) nxt[now][mark]=++cnt;
                now=nxt[now][mark];
                last[now]+=sum[i-1][j][mark^1];//这点之前
                num[now]++;
            }
        }
        printf("%lld\n",ans);
        FOR(i,0,cnt) num[i]=last[i]=nxt[i][0]=nxt[i][1]=0;
        FOR(i,1,n) REP(j,32)
            sum[i][j][0]=sum[i][j][1]=0;
    }
}
/*
*/

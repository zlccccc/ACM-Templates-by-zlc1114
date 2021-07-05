#include <sstream>
#include <fstream>
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

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

//UVALive 8191 
set<pair<pii,int> > POS;
int cnt[maxn];
void update(int col,int x){
    // printf(" actual :%d: %d\n",col,x);
    // printf("  erase : %d %d\n",cnt[col],col);
    cnt[col]+=x;
    // printf("  insert : %d %d\n",cnt[col],col);
}

void update(int l,int r,int x){
    // printf("update: %d %d: %d\n",l,r,x);
    auto final=make_pair(make_pair(l,r),x);
    while (l<=r){
        auto it=POS.upper_bound(make_pair(make_pair(l,INF),0)); it--;
        // printf("%d ",it->second);
        auto now=*it; POS.erase(it);
        // printf("%d %d %d\n",now.first.first,now.first.second,now.second);
        int nxtl=now.first.second+1;
        if (now.first.first<l){
            pair<int,int> remain;
            remain.first=now.first.first;
            remain.second=l-1;
            if (remain.first<=remain.second)
                POS.insert(make_pair(remain,now.second));
        }
        if (now.first.second>r){
            pair<int,int> remain;
            remain.first=r+1;
            remain.second=now.first.second;
            if (remain.first<=remain.second)
                POS.insert(make_pair(remain,now.second));
            nxtl=r+1;
        }
        update(now.second,-(nxtl-l));
        update(x,nxtl-l);
        l=nxtl;
    } POS.insert(final);
    // puts("after:");
    // for (auto now:POS) printf(" %d-%d : %d\n",now.first.first,now.first.second,now.second);
}
int main() {
    int l,c;
    while(~scanf("%d%d%d",&l,&c,&n)){
        int i; POS.clear();
        FOR(i,1,c) cnt[i]=0; cnt[1]=l; int ans=0;
        POS.insert(make_pair(make_pair(1,l),1));
        FOR(i,1,n){
            int p,x,a,b;
            // printf("S=%d\n",S);
            scanf("%d%d%d%d",&p,&x,&a,&b);
            int S=cnt[p];
            int m1=(a+(ll)S*S)%l+1;
            int m2=(a+(ll)(S+b)*(S+b))%l+1;
            if (m1>m2) swap(m1,m2);
            update(m1,m2,x);
        } FOR(i,1,c) ans=max(ans,cnt[i]);
        printf("%d\n",ans);
    }
}
/*
*/
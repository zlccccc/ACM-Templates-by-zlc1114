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
const LL maxn=50+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M; return ret;}

namespace LB {
    typedef long long BaseType;
    const int MaxBit=63;
    struct L_B {
        BaseType b[MaxBit]; bool have_0;
        L_B() {clear();}
        void clear() {memset(b,0,sizeof(b)); have_0=0;}
        BaseType XORMIN(BaseType x) {
            int i;
            rREP(i,MaxBit) if ((b[i]^x)<x) x^=b[i];
            return x;
        }
        BaseType XORMAX(BaseType x) {
            int i;
            rREP(i,MaxBit) if ((b[i]^x)>x) x^=b[i];
            return x;
        }
        void insert(BaseType x) {
            int i;
            if (!have_0&&!XORMIN(x)) have_0=1;
            rREP(i,MaxBit) if ((x>>i)&1) {
                if (!b[i]) b[i]=x; x^=b[i];
            }
        }
        void rebuild() {
            int i,j;
            rREP(i,MaxBit) rREP(j,i) if ((b[i]>>j)&1) b[i]^=b[j];
        }
        BaseType querykth(BaseType k) {
            BaseType ret=0; int i; k-=have_0;
            REP(i,MaxBit) if (b[i]) {if (k&1) ret^=b[i]; k>>=1;}
            if (k) return -1;
            return ret;
        }
    } A;
    //求交 merge的思路: 只要A中merge之后的线性无关组
    L_B merge(const L_B &A,const L_B &B) {
        int i,j; L_B ret; ret.clear();
        static BaseType base[MaxBit],tmp[MaxBit];//previous_A
        REP(i,MaxBit) tmp[i]=A.b[i],base[i]=1ll<<i;
        REP(i,MaxBit) if (B.b[i]) {//正者反着应该没区别
            BaseType now=B.b[i];
            bool okay=1; BaseType k=0;//base; A
            rREP(j,MaxBit) if ((now>>j)&1) {
                if (tmp[j]) {
                    now^=tmp[j]; k^=base[j];
                } else {
                    tmp[j]=now; base[j]=k; okay=0; break;
                }
            }
            if (okay) {
                BaseType should=0;
                REP(j,MaxBit) if ((k>>j)&1) should^=A.b[j];
                ret.insert(should);
            }
        }
        return ret;
    }
}
using namespace LB;
int main() {
    int i,j,T,n,m,x=0;
    LL k;
    scanf("%d",&T);
    while (T--) {
        scanf("%d",&n);
        A.clear();
        REP(i,n) scanf("%lld",&k),A.insert(k);
        A.rebuild();
        scanf("%d",&m);
        printf("Case #%d:\n",++x);
        REP(i,m) scanf("%lld",&k),printf("%lld\n",A.querykth(k));
    }
}
/*
2
2
1 2
4
1 2 3 4

3
1 2 3
5
1 2 3 4 5
*/

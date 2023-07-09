// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
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
#include <functional>
#include <random>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define REP_(I,N) for (int I=0;I<N;I++)
#define rREP_(I,N) for (int I=N-1;I>=0;I--)
#define rep_(I,S,N) for (int I=S;I<N;I++)
#define rrep_(I,S,N) for (int I=N-1;I>=S;I--)
#define FOR_(I,S,N) for (int I=S;I<=N;I++)
#define rFOR_(I,S,N) for (int I=N;I>=S;I--)

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
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
// template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T fastgcd(T a, T b) {
    int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctz(diff);
        min_(b,a); a=abs(diff);
    }
    return b<<z;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

// 分解质因数, n^1/4
namespace PollardRho {
    LL mul(LL a,LL b,LL M) {
        // LL ret=0;
        // for (; b; b>>=1,(a+=a)>=M&&(a-=M))
        //     if (b&1)(ret+=a)>=M&&(ret-=M);{
        // return ret;
        a=(a%M+M)%M, b=(b%M+M)%M;
        return (((a*b)-(LL)((long double)a*b/M)*M)%M+M)%M;
    }
    LL poww(LL a,LL b,LL M) {
        LL ret=1;
        for (; b; b>>=1,a=mul(a,a,M))
            if (b&1) ret=mul(ret,a,M);
        return ret;
    }
    vector<int> bs={2,3,7,31,61};
    bool check(LL a,LL n,LL x,LL t) {
        LL ret=poww(a,x,n);
        LL last=ret;
        for (ret=mul(ret,ret,n); t--; last=ret,ret=mul(ret,ret,n))
            if (ret==1&&last!=1&&last!=n-1) return true;
        if (ret!=1) return true;
        return false;
    }
    bool Miller_Robin(LL x) {
        for (int p:bs) if(x==p) return 1;
        LL res=x-1, k=0;
        for(; !(res&1); res>>=1,++k);
        for (int p:bs) {
            LL pre=poww(p,res,x), now;
            for(int t=k;t--;swap(now,pre))
                if ((now=mul(pre, pre, x)) == 1 && pre != 1 && pre != x-1)
                    return 0;
            if(pre != 1) return 0;
        }
        return 1;
    }
    LL Rho(LL x, LL c) {
        LL i=1,j=0,sum=1,a=rand()%(x-1)+1,b=a,d=1;
        while(d==1) {
            sum=mul(sum,abs((a=(mul(a,a,x)+c)%x)-b),x);
            if(++j==i) i<<=1, b=a, d=__gcd(sum, x);
            if(!(j&1023)) d=__gcd(sum, x);
        }
        return d==x?Rho(x,c+1):d;
    }
    map<LL, int>mp;
    void Pollard(LL x) {
        if(x == 1) return;
        if(Miller_Robin(x)) { ++mp[x]; return; }
        LL tmp=Rho(x, 3);
        Pollard(tmp), Pollard(x/tmp);
    }
    vector<pair<LL,int> > Solve(LL x) {
        mp.clear(); Pollard(x);
        vector<pair<LL,int> > re;
        for(auto &p:mp) re.push_back(p);
        return re;
    }
}
// https://ac.nowcoder.com/acm/contest/60254/J
// 题意:与x互质的第x个数字, x<=1e18
// 分解质因数之后容斥一下就行了
int main() {
    int T,_; T=1;
    // scanf("%d",&T);
    FOR(_,1,T){
        ll n,k;
        scanf("%lld%lld",&n,&k);
        ll l=0,r=n;
        auto primes=PollardRho::Solve(n);
        // for (auto now:primes) printf("%lld %d\n",now.first,now.second);
        while (l+1<r) {
            ll mid=(l+r)/2;
            ll nowcnt=mid;
            vector<pair<ll,int>> cur={{mid,1}};
            for (auto &pr:primes) {
                vector<pair<ll,int>> nxt=cur;
                ll p=pr.first;
                for (auto nowval:cur) if (nowval.first>=p) {
                    nowcnt-=nowval.first/p*nowval.second;
                    // printf("p=%d; nowcnt-=%lld\n",p,nowval.first/p*nowval.second);
                    nxt.push_back({nowval.first/p,-nowval.second});
                }
                cur.swap(nxt);
            }
            // printf("mid=%lld; nowcnt=%lld\n",mid,nowcnt);
            if (nowcnt>=k) r=mid;
            else l=mid;
        }
        printf("%lld\n",r);
    }
}
/*
100
10 2
2 1
5 1
*/

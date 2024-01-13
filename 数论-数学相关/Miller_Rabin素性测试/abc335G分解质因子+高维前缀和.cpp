// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define REP_(I,N) for (int I=0,END=(N);I<END;I++)
#define rREP_(I,N) for (int I=(N)-1;I>=0;I--)
#define rep_(I,S,N) for (int I=(S),END=(N);I<END;I++)
#define rrep_(I,S,N) for (int I=(N)-1,START=(S);I>=START;I--)
#define FOR_(I,S,N) for (int I=(S),END=(N);I<=END;I++)
#define rFOR_(I,S,N) for (int I=(N),START=(S);I>=START;I--)

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

// 复杂度n^1/4
namespace PollardRho {
    std::mt19937 rng(time(0));
    std::mt19937_64 rng64(time(0));
    inline ll fastgcd(ll a, ll b) {
        if (!a) return b;
        ll az=__builtin_ctzll(a),bz=__builtin_ctzll(b),z=min(az,bz),diff; b>>=bz;
        while (a) {
            a>>=az; diff=b-a; az=__builtin_ctzll(diff);
            (b>a)&&(b=a);; a=abs(diff);
        }
        return b<<z;
    }
    // 这个快一点点
    using u64 = uint64_t;
    u64 mul(u64 a, u64 b, u64 p){  // 汇编速度比__int128快一点
        asm("mulq\t%3" : "=a"(a), "=d"(b) : "a"(a), "r"(b));
        asm("divq\t%4" : "=a"(a), "=d"(b) : "a"(a), "d"(b), "r"(p));
        return b;
    }
    // ll mul(ll a, ll b, ll p) {  // long double这个方法测下来比__int128慢一倍
    //     return (__int128)a*b%p;
    //     ll res=a*b-(ll)((long double)a/p*b+0.5L)*p;
    //     if(res<p) return res;
    //     else return res+p;
    // }
    ll poww(ll a,ll b,ll M) {
        ll ret=1;
        for (; b; b>>=1,a=mul(a,a,M))
            if (b&1) ret=mul(ret,a,M);
        return ret;
    }
    // miller-rabin质数选取: https://miller-rabin.appspot.com/#
    bool MillerRabin(ll x) {
        // static const ll bs[]={2,7,41,61};
        static const ll bs[]={2,3,7,31,61};
        // static const ll bs[]={2,3,7,31,61,9375,3722628058}; // 1e11内满足
        // static const ll bs[]={2,2570940,211991001,3749873356};  // 4e13内满足
        // static const ll bs[]={2,2570940,880937,610386380,4130785767};  // 3e16内满足
        // static const ll bs[]={2,325,9375,28178,450775,9780504,1795265022};  // 2^64内都满足
        if (x<4) return x>=2;
        if (!(x&1)) return false;
        ll res=x-1,k=__builtin_ctzll(res); res>>=k;
        for (auto p:bs) {
            p%=x; if (p<=1) continue;
            ll pre=poww(p,res,x),now;
            if (pre==1) continue;
            for(int t=k;t--;swap(now,pre))
                if ((now=mul(pre,pre,x))==1&&pre!=1&&pre!=x-1)
                    return false;
            if(pre!=1) return false;
        }
        return true;
    }
    ll Rho(ll x, ll c=3) {  // 找一个因数; pollard-rho做法是直接f(f(x))和f(x)看是否一样,一样的话就找到答案了
        ll i=1,j=0,sum=1,a=rng()%(x-1)+1,b=a,d=1;
        while (d==1) {
            sum=mul(sum,abs((a=(mul(a,a,x)+c)%x)-b),x);  // 这里有abs; 所以a和b不要是unsigned
            if(++j==i) i<<=1, b=a, d=fastgcd(sum, x);
            // if(!(j&1023)) d=fastgcd(sum, x);
            if(!(j&127)) d=fastgcd(sum, x);
        }
        return d==x?Rho(x,c+1):d;
    }
    map<ll, int> mp;
    void Pollard(ll x) {
        if(x==1) return;
        if (MillerRabin(x)) { ++mp[x]; return; }
        ll tmp=Rho(x);
        Pollard(tmp), Pollard(x/tmp);
    }
    // <质因子,次数>
    vector<pair<ll,int>> Solve(ll x) {
        mp.clear(); Pollard(x);
        vector<pair<ll,int>> re;
        for(auto &p:mp) re.push_back(p);
        return re;
    }

    // 获取factor并搞成可以高维前缀和的形式
    vector<ll> GetFactor(const vector<pair<ll,int>> &primes) {
        int length=1;
        for (auto &pr:primes) length*=pr.second+1;
        vector<ll> factor(length); factor[0]=1;
        int len=1;
        for (auto &pr:primes) {
            int nxtlen=len*(pr.second+1);
            REP_(_,pr.second) {  // 如果是积性函数; 直接在这里solve就可以了; i/len就是当前用了几个pr.first的prime
                REP_(i,nxtlen-len) factor[i+len]=factor[i]*pr.first;
            }
            len=nxtlen;
        }
        return factor;
    }
    vector<ll> GetFactor(ll x) {
        return GetFactor(Solve(x));
    }

    // 高维前缀和
    unordered_map<ll,int> SubSum(const vector<pair<ll,int>> &primes,const unordered_map<ll,int> &MP) {
        vector<ll> factor=GetFactor(primes); // factors
        vector<int> result(factor.size());  // 不用hashMap, 直接做前缀和速度会快点(少hashMap的常数)
        REP_(i,factor.size()) {  // 初始化
            ll x=factor[i]; auto it=MP.find(x);
            if (it!=MP.end()) result[i]=it->second;
        }
        // for (auto p:MP) printf("%lld %d \n",p.first,p.second); puts("< initial");
        int len=1;
        for (auto &pr:primes) {
            int nxtlen=len*(pr.second+1);
            REP_(i,factor.size()/nxtlen) {  // i次
                REP_(j,nxtlen-len) {
                    // assert(factor[nxtlen*i+j+len]==factor[nxtlen*i+j]*pr.first);
                    result[nxtlen*i+j+len]+=result[nxtlen*i+j];  // 直接当数组用了
                }
            }
            len*=pr.second+1;
            // printf("solve %lld %d\n",pr.first,pr.second);
            // REP_(i,factor.size()) printf("%lld:%d ",factor[i],result[i]); puts(" current prefixsum");
        }
        // 这里就已经是高维前缀和了; 再转到unordered_map里面
        unordered_map<ll,int> ret;
        REP_(i,factor.size()) ret[factor[i]]+=result[i];
        return ret;
    }
}

// 题意: 给n和p<=1e13; 问存在k使得A[i]^k%p==A[j]的(i,j)对数
// 等价于A[i]和A[j]循环节满足f(A[j])%f(A[i])==0
// 循环节的话一定是p-1的因子; 所以可以对p-1先做因式分解; 然后找最长循环节
ll A[maxn],B[maxn];
int solve() {
    int n; ll p;
    cin>>n>>p;
    FOR_(i,1,n) cin>>A[i];
    auto primes=PollardRho::Solve(p-1);
    // for (auto &pr:primes) {
    //     printf("pollard: %lld %d\n",pr.first,pr.second);
    // }
    unordered_map<ll,int> MP;
    FOR_(i,1,n) {
        ll multi=1;
        for (auto &pr:primes) {  // 得到A[i]所在的循环节
            ll x=pr.first;
            FOR_(_,1,pr.second) {
                if (PollardRho::poww(A[i],(p-1)/(multi*pr.first),p)==1)  // 循环节?
                    multi*=pr.first;
                else break;
            }
        }
        MP[multi]++;
    }
    // for (auto &y:MP) for (auto &x:MP) if (y.first>=x.first&&y.first%x.first==0) {
    //     printf("%lld %lld: %d * %d\n",x.first,y.first,x.second,y.second);
    //     // res+=(ll)y.second*x.second; // 会TLE
    // }

    // for (auto &x:MP) printf("solve: %lld %d\n",x.first,x.second);
    auto subSum=PollardRho::SubSum(primes,MP);

    // 获取所有p-1的因子; 然后高维前缀和; 这么直接搞速度也还可以
    // unordered_map<ll,int> subSum;
    // auto factor=PollardRho::GetFactor(primes);

    // for (auto &x:MP) subSum[x.first]+=MP[x.first];
    // for (auto &pr:primes) {
    //     for (auto &x:factor) if (x%pr.first==0) subSum[x]+=subSum[x/pr.first];
    //     // for (auto &x:factor) printf("%lld:%d ",x,subSum[x]); puts("<- subsum");
    // }

    ll res=0;
    for (auto &x:MP) {
        res+=(ll)MP[x.first]*subSum[x.first];
        // for (auto &y:MP) if (y.first>=x.first&&y.first%x.first==0) res+=(ll)y.second*x.second;
        // printf("%lld: %d * %d\n",x.first,MP[x.first],subSum[x.first]);
    }
    cout<<res;
    return 0;
}
int main() {
    int T; T=1;
    // cin>>T;
    // scanf("%d",&T);
    FOR_(_,1,T){
        solve();
    }
}
/*
10 29
1 2 3 3 4 6 7 8 9 10
*/
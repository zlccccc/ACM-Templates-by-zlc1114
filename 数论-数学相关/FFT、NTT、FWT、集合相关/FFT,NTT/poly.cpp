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
// const LL M=1e9+7;
const LL maxn=1e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a, ll b, ll mod) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

// FOR NTT
namespace NTT {
    // change inv and root from jiangly codes
    const int MOD=998244353;
    const int g=3;
    vector<int> roots{0,1};
    inline int mul(int x,int y) {
        ll ret=(ll)x*y; (ret>MOD)&&(ret%=MOD);
        return ret;
    }
    int poww(int a,int b) {
        int ret=1;
        for (; b; b>>=1,a=mul(a,a))
            if (b&1) ret=mul(ret,a);
        return ret;
    }
    void dft(vector<int> &A,int len,int inv) {
        assert((int)A.size()==len);
        if (inv==-1) reverse(A.begin()+1, A.end());
        int i,j,k;
        // bitrev[i] = bitrev[i >> 1] >> 1 | (i & 1) << __builtin_ctz(len);
        for (i=1,j=len/2; i<len-1; i++) {
            if (i<j) swap(A[i],A[j]);
            k=len/2;
            while (j>=k) j-=k,k/=2;
            if (j<k) j+=k;
        }
        if ((int)roots.size()<len) {
            int k=__builtin_ctz(roots.size());
            roots.resize(len);
            while ((1<<k)<len) {
                int e=poww(g,(MOD-1)>>(k+1));
                for (int i=1<<(k-1);i<(1<<k);++i) {
                    roots[2*i]=roots[i];
                    roots[2*i+1]=mul(roots[i],e);
                } ++k;
            }
        }
        for (i=1;i<len;i<<=1) {//fin version
            for (j=0; j<len; j+=i+i) { //merge length = i+i
                for (k=0; k<i; k++) {
                    int a=A[k+j];
                    assert(k+i+j<(int)A.size());
                    assert(k+i<(int)roots.size());
                    int b=mul(A[k+i+j],roots[k+i]);
                    int u=a+b; (u>=MOD) &&(u-=MOD); A[k+j]=u;
                    int v=a-b; (v<0) &&(v+=MOD); A[k+i+j]=v;
                }
            }
        }
        if (inv==-1) {
            int vn=poww(len,MOD-2);
            REP(i,len) A[i]=mul(A[i],vn);
        }
    }
    vector<int> mul(vector<int> A,vector<int> B) { //C=A*B
        int n=A.size(),m=B.size();
        int len=1; int i;
        while (len<n+m-1) len<<=1;
        vector<int> C;
        A.resize(len,0); B.resize(len,0); C.resize(len,0);
        dft(A,len,1); dft(B,len,1);
        REP(i,len) C[i]=mul(A[i],B[i]);
        dft(C,len,-1);
        C.resize(n+m-1);
        return C;
    }
}

struct poly {
    static const int MOD=998244353;
    vector<int> v;
    poly() {}
    poly(int val) {if (val) v={val};}
    poly(const vector<int> &vec): v(vec) {
        while (v.size()&&!v.back()) v.pop_back();
    }
    int size() const {
        return v.size();
    }
    const int operator [](int n) const {
        if (n<0||n>size()) return 0;
        return v[n];
    }
    friend poly operator + (const poly a,const poly &b) {
        vector<int> ret(max(a.size(),b.size())); int i;
        REP(i,(int)ret.size()) ((ret[i]=a[i]+b[i])>=MOD)&&(ret[i]-=MOD);
        return poly(ret);
    }
    friend poly operator - (const poly a,const poly &b) {
        vector<int> ret(max(a.size(),b.size())); int i;
        REP(i,(int)ret.size()) ((ret[i]=a[i]-b[i])<0)&&(ret[i]+=MOD);
        return poly(ret);
    }
    friend poly operator*(poly a, poly b) {
        int sz = 1, tot = a.size() + b.size() - 1;
        while (sz < tot)
            sz *= 2;
        a.v.resize(sz, 0);
        b.v.resize(sz, 0);
        NTT::dft(a.v,sz,1);
        NTT::dft(b.v,sz,1);
        for (int i = 0; i < sz; ++i)
            a.v[i] = 1ll * a[i] * b[i] % MOD;
        NTT::dft(a.v,sz,-1);
        return poly(a.v);
    }
    // friend poly operator * (poly a,poly b) {
    //     return poly(NTT::mul(a.v,b.v));
    // }
    poly &operator += (poly b) {
        return (*this) = (*this) + b;
    }
    poly &operator -= (poly b) {
        return (*this) = (*this) - b;
    }
    poly &operator *= (poly b) {
        return (*this) = (*this) * b;
    }
    poly modxk(int k) const {
        k=min(k,size());
        return poly(vector<int>(v.begin(),v.begin()+k));//多一次copy; 可能无所谓
    }
    poly divxk(int k) const {
        if (size()<=k) return poly();
        return poly(vector<int>(v.begin()+k,v.end()));//多一次copy; 可能无所谓
    }

    poly inv(int m) const {
        poly x(powMM(v[0], MOD - 2,MOD));
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (poly(2) - modxk(k) * x)).modxk(k);
        }
        return x.modxk(m);
    }
    // poly inv(int m) const {//length=m
    //     poly x(powMM(v[0],MOD-2,MOD));
    //     for (int k=1;k<m;) {
    //         k<<=1;
    //         // printf("k=%d\n",k);
    //         // x.print();
    //         // (2-modxk(k)).print();
    //         // (x*(2-(modxk(k)*x))).print();
    //         // (x*(2-modxk(k)*x)).print();
    //         x=(x*(poly(2)-modxk(k)*x)).modxk(k);
    //     }
    //     return x.modxk(m);
    // }
    void print() {
        for (int val:v) printf("%d ",val);
        puts("<- poly val");
    }
};

int ans[maxn];
int main() {
    int n,i,k;
    scanf("%d",&n);
    vector<int> v;
    REP(i,n) scanf("%d",&k),v.push_back(k);
    poly _v(v);
    _v.inv(n).print();
    // poly _z=_v.inv(n);
    // (_z*_v).print();
}
/*
4 100 200
1 2 3 4
*/

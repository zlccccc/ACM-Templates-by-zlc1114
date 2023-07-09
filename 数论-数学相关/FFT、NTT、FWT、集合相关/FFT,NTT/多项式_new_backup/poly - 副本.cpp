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


namespace BruteForce {
    vector<int> mul(const vector<int> &A,const vector<int> &B,int mod) { //C=A*B
        int n=A.size(),m=B.size();
        int i,j;
        vector<int> C(n+m-1);
        REP(i,n) REP(j,m) add_(C[i+j],(ll)A[i]*B[j]%mod,mod);
        return C;
    }
}

// FOR NTT
namespace NTT {
    static const int MOD=998244353;
    static const int g=3;
    static const int bruteforce_limit=8;
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
                    // assert(k+i+j<(int)A.size());
                    // assert(k+i<(int)roots.size());
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
        if (min(n,m)<=bruteforce_limit)
            return BruteForce::mul(A,B,MOD);
        int len=1; int i;
        while (len<n+m-1) len<<=1;
        vector<int> C;
        A.resize(len,0); B.resize(len,0); C.resize(len,0);
        dft(A,len,1); dft(B,len,1);
        REP(i,len) C[i]=mul(A[i],B[i]);
        dft(C,len,-1);
        A.resize(n); B.resize(m); C.resize(n+m-1);
        return C;
    }
}

namespace FFT { // 任意模数fft
    const int maxn=1<<18|7;
    static const int bruteforce_limit=16;
    struct complex {
        double a,b;
        complex(double _a=.0,double _b=.0):a(_a),b(_b) {}
        complex operator+(const complex x)const {return complex(a+x.a,b+x.b);}
        complex operator-(const complex x)const {return complex(a-x.a,b-x.b);}
        complex operator*(const complex x)const {return complex(a*x.a-b*x.b,a*x.b+b*x.a);}
    };
    vector<complex> wn;
    void initwn(int l) {
        if ((int)wn.size()==l) return;
        wn.resize(l); int i;
        REP(i,l) wn[i]=complex(cos(2*pi*i/l),sin(2*pi*i/l));
    }
    void fft(vector<complex> &A,int len,int inv) {
        assert((int)A.size()==len);
        int i,j,k; initwn(len);
        for (i=1,j=len/2; i<len-1; i++) {
            if (i<j) swap(A[i],A[j]);
            k=len/2;
            while (j>=k) j-=k,k/=2;
            if (j<k) j+=k;
        } for (i=2; i<=len; i<<=1) {
            for (j=0; j<len; j+=i) {
                for (k=j; k<(j+i/2); k++) {
                    complex a,b; a=A[k];
                    b=A[k+i/2]*wn[(ll)(k-j)*len/i];
                    A[k]=a+b; A[k+i/2]=a-b;
                }
            }
        } if (inv==-1) REP(i,len) A[i]=complex(A[i].a/len,A[i].b/len);
    }
    inline complex conj(complex &A) {return complex(A.a,-A.b);}
    vector<int> mul(vector<int> &A,vector<int> &B,int mod) { //C=A*B
        static vector<complex> x1,x2,x3,x4;
        int n=A.size(),m=B.size();
        if (min(n,m)<=bruteforce_limit)
            return BruteForce::mul(A,B,mod);
        int len=1;
        while (len<n+m-1) len<<=1;
        vector<int> C(len);
        x1.resize(len); x2.resize(len);
        x3.resize(len); x4.resize(len);
        static const int S=1<<15 ; int i;
        A.resize(len,0); B.resize(len,0);
        REP(i,len) x1[i]=complex(A[i]/S,A[i]%S);
        REP(i,len) x2[i]=complex(B[i]/S,B[i]%S);
        fft(x1,len,1); fft(x2,len,1);
        REP(i,len) {//这个k1, b1就是前面的, 这就减掉了一半常数
            int j=(len-i)&(len-1);
            complex k1=(conj(x1[i])+x1[j])*complex(0.5,0);//dft k1
            complex b1=(conj(x1[i])-x1[j])*complex(0,0.5);//dft b1
            complex k2=(conj(x2[i])+x2[j])*complex(0.5,0);//dft k2
            complex b2=(conj(x2[i])-x2[j])*complex(0,0.5);//dft b2
            x3[i]=k1*k2+k1*b2*complex(0,1);
            x4[i]=b1*k2+b1*b2*complex(0,1);
        } fft(x3,len,-1); fft(x4,len,-1);
        REP(i,len) {
            ll kk=x3[i].a+0.5,kb=x3[i].b+0.5;
            ll bk=x4[i].a+0.5,bb=x4[i].b+0.5;
            C[i]=((kk%mod*S%mod+kb+bk)%mod*S%mod+bb)%mod;
        }
        A.resize(n); B.resize(m); C.resize(n+m-1);
        return C;
    }
}

struct poly {
    // static const int MOD=19260817;
    static const int MOD=998244353;
    friend poly operator * (poly a,poly b) {
        return poly(NTT::mul(a.v,b.v));
        // return poly(FFT::mul(a.v,b.v,MOD));
    }
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
        if (n<0||n>=size()) return 0;
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
    poly &operator += (poly b) {
        return (*this) = (*this) + b;
    }
    poly &operator -= (poly b) {
        return (*this) = (*this) - b;
    }
    poly &operator *= (poly b) {
        return (*this) = (*this) * b;
    }
    poly modxk(int k) const { // %(x^k)
        k=min(k,size());
        return poly(vector<int>(v.begin(),v.begin()+k));//多一次copy; 可能无所谓
    }
    poly divxk(int k) const { // /()
        if (size()<=k) return poly();
        return poly(vector<int>(v.begin()+k,v.end()));//多一次copy; 可能无所谓
    }
    poly mulT(poly b) const {  // self * reverse(b)
        if (b.size() == 0) return poly();
        int n = b.size();
        std::reverse(b.v.begin(), b.v.end());
        return ((*this) * b).divxk(n - 1);
    }
    poly deriv() const { // 求导
        if (v.empty()) return poly();
        std::vector<int> res(size() - 1);
        for (int i = 0; i < size() - 1; ++i)
            res[i] = 1ll * (i + 1) * v[i + 1] % MOD;
        return poly(res);
    }
    poly integr() const { // 积分
        if (v.empty()) return poly();
        std::vector<int> res(size() + 1);
        for (int i = 0; i < size(); ++i)
            res[i + 1] = (ll) v[i] * powMM(i+1,MOD-2,MOD) % MOD;
        return poly(res);
    }
    poly inv(int m) const {
        poly x(powMM(v[0],MOD-2,MOD));
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x*(2-modxk(k)*x)).modxk(k);
        }
        return x.modxk(m);
    }
    poly log(int m) const {
        return (deriv()*inv(m)).integr().modxk(m);
    }
    poly exp(int m) const {
        poly x(1);
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (1 - x.log(k) + modxk(k))).modxk(k);
        }
        return x.modxk(m);
    }
    poly sqrt(int m) const {
        poly x(1),y(powMM(v[0],MOD-2,MOD));
        int k=1; int div2=powMM(2,MOD-2,MOD);
        while (k<m) {
            x.print("<- x\n");
            y.print("<- y\n");
            x.inv(k).print("<-x inv\n");
            k*=2;
            x=((x*x+modxk(k))*div2*y).modxk(k);
            // if (k<m) y=(y*(2-(x*y).modxk(k*2))).modxk(k*2);
            if (k<m) y=(y*(2-(x*y).modxk(k))).modxk(k);
        }
        return x.modxk(m);
    }
    // vector<int> eval(std::vector<int> x) const {//多项式多点求值/插值
    //     if (size() == 0)
    //         return std::vector<int>(x.size(), 0);
    //     const int n = std::max(int(x.size()), size());
    //     std::vector<poly> q(4 * n);
    //     std::vector<int> ans(x.size());
    //     x.resize(n);
    //     std::function<void(int, int, int)> build = [&](int p, int l, int r) {
    //         if (r - l == 1) {
    //             q[p] = std::vector<int> {1, (MOD - x[l]) % MOD};
    //         } else {
    //             int m = (l + r) / 2;
    //             build(2 * p, l, m);
    //             build(2 * p + 1, m, r);
    //             q[p] = q[2 * p] * q[2 * p + 1];
    //         }
    //     };
    //     build(1, 0, n);
    //     std::function<void(int, int, int, const poly &)> work = [&](int p, int l, int r, const poly &num) {
    //         if (r - l == 1) {
    //             if (l < int(ans.size()))
    //                 ans[l] = num[0];
    //         } else {
    //             int m = (l + r) / 2;
    //             work(2 * p, l, m, num.mulT(q[2 * p + 1]).modxk(m - l));
    //             work(2 * p + 1, m, r, num.mulT(q[2 * p]).modxk(r - m));
    //         }
    //     };
    //     work(1, 0, n, mulT(q[1].inv(n)));
    //     return ans;
    // }
    void print(const char* s="\n") {
        for (int val:v) printf("%d ",val); printf("%s",s);
        // puts("<- poly val");
    }
};

namespace problems {
    // 无限背包, A是物体size, m是最大size
    // f(x) = 1/\mul(1-x^i)
    // 求ln(x)然后exp
    // ln'(1/(1-x^i))=i*x^(i-1)/(1-x^i)
    vector<int> Knapsack(vector<int> A,int m) {
        vector<int> ret(m+1);
        vector<int> cnt(m+1);
        for (int v:A) if (v<=m) cnt[v]++;
        for (int i=1;i<=m;i++) {
            for (int j=i-1;j<=m;j+=i) ret[j]+=i*cnt[i];
        }
        poly res(ret);
        res=res.integr().exp(m+1);
        // res.print(); puts("<- v");
        return res.v;
    }
}

int ans[maxn];
int main() {
    int n,i,k;
    scanf("%d",&n);
    vector<int> v;
    REP(i,n) scanf("%d",&k),v.push_back(k);
    poly _v(v);
    // (_v*_v).print();
    // _v.exp(n).print();
    // poly _z=_v.exp(n);
    // _z.print();
    // _v.inv(n).print();
    _v.sqrt(n).print();
    // (_z*_v).print();

    // // 无限背包
    // int n,m,k,i;
    // scanf("%d%d",&n,&m);
    // vector<int> A;
    // FOR(i,1,n) scanf("%d",&k),A.push_back(k);
    // auto res=problems::Knapsack(A,m);
    // int ans=0;
    // FOR(i,1,m) add_(ans,res[i],19260817);
    // printf("%d\n",ans);
}
/*
4 100 200
1 2 3 4
*/

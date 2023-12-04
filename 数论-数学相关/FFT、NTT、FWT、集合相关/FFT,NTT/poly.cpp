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
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD) {A%=MOD; A+=MOD; A%=MOD;}
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

inline ll powMM(ll a, ll b, ll mod) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}

namespace BruteForce {
    vector<int> mul(const vector<int> &A,const vector<int> &B,int mod)  { //C=A*B
        int n=A.size(),m=B.size();
        if (!n||!m) return vector<int>();
        vector<int> C(n+m-1,0);
        REP_(i,n) REP_(j,m) add_(C[i+j],(ll)A[i]*B[j]%mod,mod);
        return C;
    }
}

// FOR NTT
namespace NTT {
    static const int MOD=998244353;
    static const int g=3;
    static const int bruteforce_limit=16;
    vector<int> roots{0,1};
    inline int mul(int x,int y) {
        ll ret=(ll)x*y; (ret>MOD) &&(ret%=MOD);
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
                for (int i=1<<(k-1); i<(1<<k); ++i) {
                    roots[2*i]=roots[i];
                    roots[2*i+1]=mul(roots[i],e);
                } ++k;
            }
        }
        for (i=1; i<len; i<<=1) { //fin version
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
            REP_(i,len) A[i]=mul(A[i],vn);
        }
    }
    vector<int> mul(const vector<int> &A,const vector<int> &B) { //C=A*B
        int n=A.size(),m=B.size();
        if (min(n,m)<=bruteforce_limit)
            return BruteForce::mul(A,B,MOD);
        int len=1;
        while (len<n+m-1) len<<=1;
        vector<int> _A(A),_B;
        _A.resize(len,0); dft(_A,len,1);
        if (A==B) _B=_A; else _B=B,_B.resize(len,0),dft(_B,len,1);
        REP_(i,len) _A[i]=mul(_A[i],_B[i]);
        dft(_A,len,-1); _A.resize(n+m-1);
        return _A;
    }
}

namespace FFT { // 任意模数fft
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
        wn.resize(l);
        REP_(i,l) wn[i]=complex(cos(2*pi*i/l),sin(2*pi*i/l));
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
        } if (inv==-1) REP_(i,len) A[i]=complex(A[i].a/len,A[i].b/len);
    }
    inline complex conj(complex &A) {return complex(A.a,-A.b);}
    vector<int> mul(const vector<int> &A,const vector<int> &B,int mod) { //C=A*B
        static vector<complex> x1,x2,x3,x4;
        int n=A.size(),m=B.size();
        if (min(n,m)<=bruteforce_limit)
            return BruteForce::mul(A,B,mod);
        int len=1;
        while (len<n+m-1) len<<=1;
        vector<int> C(len);
        x1.resize(len); x2.resize(len);
        x3.resize(len); x4.resize(len);
        static const int S=1<<15;
        REP_(i,n) x1[i]=complex(A[i]/S,A[i]%S);
        rep_(i,n,len) x1[i]=complex(); fft(x1,len,1);
        if (A==B) x2=x1;
        else {
            REP_(i,m) x2[i]=complex(B[i]/S,B[i]%S); rep_(i,m,len) x2[i]=complex();
            fft(x2,len,1);
        }
        REP_(i,len) {//这个k1, b1就是前面的, 这就减掉了一半常数
            int j=(len-i)&(len-1);
            complex k1=(conj(x1[i])+x1[j])*complex(0.5,0);//dft k1
            complex b1=(conj(x1[i])-x1[j])*complex(0,0.5);//dft b1
            complex k2=(conj(x2[i])+x2[j])*complex(0.5,0);//dft k2
            complex b2=(conj(x2[i])-x2[j])*complex(0,0.5);//dft b2
            x3[i]=k1*k2+k1*b2*complex(0,1);
            x4[i]=b1*k2+b1*b2*complex(0,1);
        } fft(x3,len,-1); fft(x4,len,-1);
        REP_(i,len) {
            ll kk=x3[i].a+0.5,kb=x3[i].b+0.5;
            ll bk=x4[i].a+0.5,bb=x4[i].b+0.5;
            C[i]=((kk%mod*S%mod+kb+bk)%mod*S%mod+bb)%mod;
        }
        C.resize(n+m-1);
        return C;
    }
}

namespace polynomial {
    static const int MOD=998244353;
    // static const int MOD=1e9+7;
    static const int g=3;
    inline int norm(int n) { return 1 << std::__lg(n * 2 - 1); }
    struct poly {
        vector<int> v;
        friend poly operator * (const poly &a,const poly &b) {
            return poly(NTT::mul(a.v,b.v));
            // return poly(FFT::mul(a.v,b.v,MOD));
        }
        poly() {}
        poly(int val) {if (val) v= {val};}
        // init usage:
        // A.init(T+1,[&](int x){
        //     return inv[x]%M*inv[x]%M*inv[x]%M;
        // });
        void init(int size, std::function<int(int)> f = [](int) {return 0;}) {
            v.resize(size);
            for (int i=0; i<size; i++) v[i]=f(i);
        }
        poly(const vector<int> &vec): v(vec) {
            while (v.size()&&!v.back()) v.pop_back();
        }
        poly(const vector<int> &vec,int size): v(vec) {
            v.resize(size);
        }
        poly rev() const {
            return poly(std::vector<int>(v.rbegin(),v.rend()));
        }
        void append(const poly &r) {
            v.insert(v.end(),r.v.begin(),r.v.end());
        }
        int size() const {
            return v.size();
        }
        poly resize(int size) {
            v.resize(size);
            return (*this);
        }
        poly alignxk(int k) const {
            return poly(v, k);
        }
        const int operator [](int n) const {
            if (n<0||n>=size()) return 0;
            return v[n];
        }
        friend poly operator + (const poly &a,const poly &b) {
            vector<int> ret(max(a.size(),b.size()));
            REP_(i,(int)ret.size())((ret[i]=a[i]+b[i])>=MOD)&&(ret[i]-=MOD);
            return poly(ret);
        }
        friend poly operator - (const poly &a,const poly &b) {
            vector<int> ret(max(a.size(),b.size()));
            REP_(i,(int)ret.size())((ret[i]=a[i]-b[i])<0)&&(ret[i]+=MOD);
            return poly(ret);
        }
        friend poly operator/(const poly &a, const poly &b) {
            return a.divide(b).first;
        }
        friend poly operator%(const poly &a, const poly &b) {
            return a.divide(b).second;
        }
        friend poly operator^(const poly &a, const poly &b) {
            return poly(a.v)^=b;
        }
        poly &operator += (poly b) {return (*this) = (*this) + b;}
        poly &operator -= (poly b) {return (*this) = (*this) - b;}
        poly &operator *= (poly b) {return (*this) = (*this) * b;}
        poly &operator ^= (const poly &r) {
            if (r.size() < size()) resize(r.size());
            for (int i = 0; i < size(); i++) v[i] = 1LL * v[i] * r[i] % MOD;
            return (*this);
        }
        poly modxk(int k) const { // %(x^k)
            k=min(k,size());
            return poly(vector<int>(v.begin(),v.begin()+k));//多一次copy; 可能无所谓
        }
        poly divxk(int k) const { // /(x^k)
            if (size()<=k) return poly();
            return poly(vector<int>(v.begin()+k,v.end()));//多一次copy; 可能无所谓
        }
        poly mulxk(int k) const { // *(x^k)
            if (!size()) return poly();
            vector<int> ret(v);
            ret.insert(ret.begin(),k,0);
            return poly(ret);
        }
        poly subpoly(int l,int r) const {
            return divxk(l).modxk(r-l+1);
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
        poly inv(int m) const { // 求逆 O(nlogn)
            poly x(powMM(v[0],MOD-2,MOD));
            int k = 1;
            while (k < m) {
                k *= 2;
                x = (x*(2-modxk(k)*x)).modxk(k);
            }
            return x.modxk(m);
        }
        poly log(int m) const { // 多项式对数函数 O(nlogn)
            // 当且仅当 [x^0]f(x) = 1 时， f(x)有对数多项式
            return (deriv()*inv(m)).integr().modxk(m);
        }
        poly exp(int m) const { // 多项式指数函数 O(nlogn)
            // 当且仅当 [x^0]f(x) = 0 时， f(x)有指数多项式
            // 否则 e 的泰勒展开不收敛
            poly x(1);
            int k = 1;
            while (k < m) {
                k *= 2;
                x = (x*(1-x.log(k)+modxk(k))).modxk(k);
            }
            return x.modxk(m);
        }
        poly sqrt(int m) const { // 多项式开根， 需满足[x^0] = 1
            poly x(1);
            int k=1;
            while (k<m) {
                k*=2;
                x=(x+modxk(k)*x.inv(k)).modxk(k)*((MOD+1)/2);
            }
            return x.modxk(m);
        }
        poly pow(int m,int _m=-1) { //高端的power写法; 注意乘法对MOD取模 exp对phi(MOD)取模; 取模是(x-m)%m+m;
            int n=size(),p=-1;
            if (_m==-1) _m=m;
            poly b; b.resize(n);
            for (int i=0;i<n;++i) if (v[i]) {p=i; break;}
            if (p==-1) return poly(!m);
            if (m==0) return poly(!!v[0]);
            if ((ll)m*p>=n) return b;
            int mu=powMM(v[p],_m,MOD),di=powMM(v[p],MOD-2,MOD);
            poly c=divxk(p).modxk(n-m*p)*di;
            c=c.log(n-m*p)*m;
            c=c.exp(n-m*p);
            b=c.mulxk(m*p)*mu;
            return b;
        }

        poly sin() const {
            int i = powMM(g, (MOD - 1) / 4,MOD);
            poly p = i * (*this);
            p = p.exp(p.size());
            poly q = (MOD - i) * (*this);
            q = q.exp(q.size());
            poly r = (p - q) * powMM(2 * i % MOD, MOD - 2,MOD);
            return r;
        }
        poly cos() const {
            int i = powMM(g, (MOD - 1) / 4,MOD);
            poly p = i * (*this);
            p = p.exp(p.size());
            poly q = (MOD - i) * (*this);
            q = q.exp(q.size());
            poly r = (p + q) * powMM(2, MOD - 2,MOD);
            return r;
        }
        poly tan() const { return sin() / cos(); }
        poly cot() const { return cos() / sin(); }
        poly arcsin() { // 要保证常数项是0
            poly sq = (*this) * (*this).modxk(size());
            for (int i = 0; i < size(); ++i)
                sq.v[i] = sq.v[i] ? MOD - sq.v[i] : 0;
            sq.v[0] = 1 + sq.v[0];
            if (sq.v[0] >= MOD) sq.v[0] -= MOD;
            poly r = (deriv() * sq.sqrt(size()).inv(size())).integr();
            return r;
        }
        poly arccos() { // 要保证常数项是0
            poly r = arcsin();
            for (int i = 0; i < size(); ++i)
                r.v[i] = r.v[i] ? MOD - r.v[i] : 0;
            return r;
        }
        poly arctan() { // 要保证常数项是0
            poly sq = (*this) * (*this).modxk(size());
            sq.v[0] = 1 + sq.v[0];
            if (sq.v[0] >= MOD) sq.v[0] -= MOD;
            poly r = (deriv() * sq.inv(size())).integr();
            return r;
        }
        poly arccot() { // 要保证常数项是0
            poly r = arctan();
            for (int i = 0; i < size(); ++i)
                r.v[i] = r.v[i] ? MOD - r.v[i] : 0;
            return r;
        }
        std::pair<poly, poly> divide(const poly &g) const {
            int n = v.size(), m = g.size();
            if (n < m) return make_pair(poly(), v);
            poly fR = rev();
            poly gR = g.rev().alignxk(n - m + 1);
            poly gRI = gR.inv(gR.size());
            poly qR = (fR * gRI).modxk(n - m + 1);
            poly q = qR.rev();
            poly r = ((*this) - g * q).modxk(m - 1);
            return std::make_pair(q, r);
        }
        vector<int> eval(std::vector<int> x) const { //多项式多点求值, 和底下等价
            if (size() == 0)
                return std::vector<int>(x.size(), 0);
            const int n = std::max(int(x.size()), size());
            std::vector<poly> q(4 * n);
            std::vector<int> ans(x.size());
            x.resize(n);
            std::function<void(int, int, int)> build = [&](int p, int l, int r) {
                if (r - l == 1) {
                    q[p] = std::vector<int> {1, (MOD - x[l]) % MOD};
                } else {
                    int m = (l + r) / 2;
                    build(2 * p, l, m);
                    build(2 * p + 1, m, r);
                    q[p] = q[2 * p] * q[2 * p + 1];
                }
            };
            build(1, 0, n);
            std::function<void(int, int, int, const poly &)> work = [&](int p, int l, int r, const poly &num) {
                if (r - l == 1) {
                    if (l < int(ans.size())) ans[l] = num[0];
                } else {
                    int m = (l + r) / 2;
                    work(2 * p, l, m, num.mulT(q[2 * p + 1]).modxk(m - l));
                    work(2 * p + 1, m, r, num.mulT(q[2 * p]).modxk(r - m));
                }
            };
            work(1, 0, n, mulT(q[1].inv(n)));
            return ans;
        }
        poly inter(const poly &y) const { // 多项式多点插值, 和底下等价
            vector<poly> Q(v.size() * 4), P(v.size() * 4);
            function<void(int, int, int)> build = [&](int p, int l, int r) {
                int m = (l + r) >> 1;
                if (l == r) {
                    Q[p] = poly({(MOD-v[m])%MOD,1});
                } else {
                    build(p * 2, l, m);
                    build(p * 2 + 1, m + 1, r);
                    Q[p] = Q[p * 2] * Q[p * 2 + 1];
                }
            };
            build(1, 0, v.size() - 1);
            poly f;
            f.v.resize((int)(Q[1].size()) - 1);
            for (int i = 0; i + 1 < Q[1].size(); i += 1) f.v[i] = (ll)Q[1][i + 1] * (i + 1)%MOD;
            poly g = f.eval(v);
            function<void(int, int, int)> work = [&](int p, int l, int r) {
                int m = (l + r) >> 1;
                if (l == r) {
                    P[p].v.push_back((ll)y[m]*powMM(g[m],MOD-2,MOD)%MOD);
                    return;
                }
                work(p * 2, l, m);
                work(p * 2 + 1, m + 1, r);
                P[p].v.resize(r - l + 1);
                poly A = P[p * 2] * Q[p * 2 + 1];
                poly B = P[p * 2 + 1] * Q[p * 2];
                for (int i=0;i<=r-l;i++) P[p].v[i]=(A[i]+B[i])%MOD;
            };
            work(1, 0, v.size() - 1);
            return P[1];
        }

        void print(const char* s="\n") const {
            for (int val:v) printf("%d ",val); printf("%s",s);
        }
        void read(int n) {
            v.resize(n);
            REP_(i,n) scanf("%d",&v[i]),v[i]=(v[i]%MOD+MOD)%MOD;
        }
    };

    vector<int> evaluate(const poly &f, vector<int> x) { // 多点求值, f(x)=y
        int n = max(f.size(),(int)x.size());
        if (!f.size()) return vector<int>(x.size(),0);
        vector<int> y(x.size());
        x.resize(n);
        vector<poly> up(n*2); // build
        for (int i=0; i<n; ++i) up[i+n]=poly({1,(MOD-x[i])%MOD});
        for (int i=n-1; i; --i) up[i]=up[i<<1]*up[i<<1|1];
        vector<poly> down(n * 2);
        down[1]=f.mulT(up[1].inv(n));
        for (int i=2; i<n*2; ++i) down[i]=down[i>>1].mulT(up[i^1]).modxk(up[i].size());
        for (int i=0; i<(int)y.size(); ++i) y[i]=down[i+n][0];
        return y;
    }
    poly interpolate(const vector<int> &x, const vector<int> &y) { // 多项式插值, f(x)=y
        int n = x.size();
        assert(x.size()==y.size());
        vector<poly> up(n*2);
        for (int i=0; i<n; ++i) up[i+n]=poly({(MOD-x[i])%MOD,1});
        for (int i=n-1; i; --i) up[i]=up[i<<1]*up[i<<1|1];
        poly a=evaluate(up[1].deriv(),x);
        for (int i=0; i<n; ++i) a.v[i]=y[i]*powMM(a[i],MOD-2,MOD)%MOD;
        vector<poly> down(n*2);
        for (int i=0; i<n; ++i) down[i+n]=poly(a[i]);
        for (int i=n-1; i; --i) down[i]=down[i<<1]*up[i<<1|1]+down[i<<1|1]*up[i<<1];
        return down[1];
    }
    // Cayley-Hamilton定理
    // F(A)=0; A是个矩阵, F是特征多项式
    // 特征多项式=1/生成函数(即分母)
    // 求出x^k % A即可, 这个就是贡献的k
    // A[n] = \sum f[x] * A[n-x]
    // 求l->r项: 手动算出A[k]->A[k+r-l],然后pow即可
    vector<int> Cayley_Hamilton(const vector<int> &A, const vector<int> &f, int l,int r) {
        poly base=A,modfx=1-poly(f);
        if (!base.size()) return poly().v;
        else if (base.size()==1) {
            base=base/modfx;
        }
        assert(base.size()+r-l+1>=modfx.size()); // 否则需要计算A(x)=B(x)+A(x)f(x); B可以分治fft
        assert(l>=base.size()); // 否则要特判l->r; 如果l<base.size需要去掉这些部分
        int len=base.size()+r-l+1-modfx.size();
        base=base.divxk(len); l-=len; r-=len; // 把没用的区间都去掉, 速度略快一丢丢
        modfx=modfx.rev();
        poly pw({0,1}),mul(1);
        for (int k=l;k;k>>=1) {
            if (k&1) mul=pw*mul%modfx;
            pw=pw*pw%modfx;
        }
        poly fin=(base*mul.rev()).divxk(base.size()-1).modxk(r-l+1);
        return fin.v;
    }
    static const int bruteforce_limit=32;
    // 分治fft
    // f[i]+=f[i-j]*g[j]
    vector<int> half_self_fft(const vector<int> &f, const vector<int> &g,int n) {
        poly _g(g),ret;
        ret.resize(n);
        function<void(int, int, int)> work = [&](int p,int l,int r) {
            if (r-l<bruteforce_limit) {
            // if (r-l<2) {
                rep_(i,l,r) {
                    if (i<(int)f.size()) ret.v[i]=f[i]; 
                    rep_(j,1,r-i) add_(ret.v[i+j],(ll)ret[i]*g[j]%MOD,MOD);
                }
                return;
            }
            int m=(l+r)>>1;
            work(p*2,l,m);
            poly mul=ret.subpoly(l,m-1)*_g.subpoly(1,r-l-1);
            rep_(i,m,r) add_(ret.v[i],mul[i-l-1],MOD);
            work(p*2+1,m,r);
        };
        work(1,0,n);
        return ret.v;
    }
    // 无限背包, A是物体size, m是最大size
    // f(x) = 1/\mul(1-x^i)
    // 求ln(x)然后exp
    // ln'(1/(1-x^i))=i*x^(i-1)/(1-x^i)
    vector<int> Knapsack(vector<int> A,int m) {
        vector<int> ret(m+1);
        vector<int> cnt(m+1);
        for (int v:A) if (v<=m) cnt[v]++;
        for (int i=1; i<=m; i++) {
            for (int j=i-1; j<=m; j+=i) ret[j]+=i*cnt[i];
        }
        poly res(ret);
        res=res.integr().exp(m+1);
        // res.print(); puts("<- v");
        return res.v;
    }

    // 像这种dp题都可以用分治fft做:
    // f[1]=f[2]=1;
    // FOR(i,3,n) { // last-color
    //     FOR(j,1,i-1) {
    //         add_(f[i],f[i-j]*f[j]%M*fac[i-1]*inv[i-j]*inv[j-1]%M);
    //         if (j!=i-1) add_(f[i],f[i-j]*f[j]%M*C(i-1,j-1)%M);
    //     }
    // }
    // 分治fft(卷自己)
    // f[x+y]+=f[x]*f[y]*...; 枚举x or y in range(l,m); 计算另一半的贡献即可
    //F0=1
    //Fn=An*\sum{i+j<n}∑FiFj
    int A[maxn];
    vector<int> solve_ATC315Ex(int n) {
        vector<int> ans; ans.resize(n+1,0);
        vector<int> prefsum; prefsum.resize(n+1,0);
        function<void(int, int, int)> work = [&](int p,int l,int r) {
            // printf("work %d %d\n",l,r);
            if (r-l==1) { // 这里直接改成2也可以的
                prefsum[l]=(ans[l]+prefsum[l-1])%MOD; // x+y=l
                ans[l]=(ll)prefsum[l-1]*A[l]%MOD;
                prefsum[l]=(ans[l]*2ll+prefsum[l])%MOD; // 0,l
                // printf("l=%d: %d %d\n",l,prefsum[l],ans[l]);
                return;
            }
            if (r-l<=bruteforce_limit) { // 这里不写也可以
                rep_(i,l,r) {
                    rep_(j,l,i) { // l<=j<i; no i-j limit
                        add_(ans[i],(ll)ans[j]*ans[i-j]%MOD,MOD);
                    }
                    rep_(j,1,min(l,i-l+1)) { // j<l and l<=i-j<i;
                        add_(ans[i],(ll)ans[j]*ans[i-j]%MOD,MOD);
                    }
                    prefsum[i]=(ans[i]+prefsum[i-1])%MOD; // x+y=i
                    ans[i]=(ll)prefsum[i-1]*A[i]%MOD;
                    prefsum[i]=(ans[i]*2ll+prefsum[i])%MOD; // 0,i
                    // printf("i=%d: %d %d\n",i,prefsum[i],ans[i]);
                }
                return;
            }
            int m=(l+r)>>1;
            work(p*2,l,m);
            // printf("work p=%d: sol 0 ans=%d l,r=%d->%d\n",p,ans[l],l,r);
            {
                vector<int> xv,yv;
                // x=i-j, y=j;  x or y in range(l,m)
                rep_(i,l,m) xv.push_back(ans[i]); // x=l->m-1
                rep_(i,1,r-l) yv.push_back(ans[i]); // y=1->r-l-1
                poly mul=poly(xv)*poly(yv);
                rep_(i,m,r) add_(ans[i],mul[i-l-1],MOD);
            }
            // printf("work p=%d: sol 1 ans=%d l,r=%d->%d\n",p,ans[l],l,r);
            {
                vector<int> xv,yv;
                // x=i-j, y=j;  x or y in range(l,m)
                rep_(i,1,min(r-l,l)) xv.push_back(ans[i]); // x
                rep_(i,l,m) yv.push_back(ans[i]); // y=l->m
                poly mul=poly(xv)*poly(yv);
                rep_(i,m,r) add_(ans[i],mul[i-l-1],MOD);
            }
            // printf("work p=%d: sol 2 ans=%d l,r=%d->%d\n",p,ans[l],l,r);
            work(p*2+1,m,r);
        };
        ans[0]=prefsum[0]=1;
        work(1,1,n+1); // l->r左闭右开
        // for (int v:ans) printf("%d ",v); puts("<- solve");
        return ans;
    }
}
using namespace polynomial;

char str[maxn];
int ans[maxn];
int main() {
    int n,m;
    scanf("%d",&n);
    vector<int> v;
    // REP_(i,n) scanf("%d",&m),v.push_back(m);
    // poly _v(v);
    // // (_v*_v).print();
    // // _v.exp(n).print();
    // // poly _z=_v.exp(n);
    // // _z.print();
    // _v.inv(n).print();
    // _v.sqrt(n).print();
    // (_z*_v).print();
    v.push_back(0);
    rep_(i,1,n) scanf("%d",&m),v.push_back(m);
    vector<int> ans=half_self_fft({1},v,n);
    for (int v:ans) printf("%d ",v);


    // // 无限背包
    // int n,m,k,i;
    // scanf("%d%d",&n,&m);
    // vector<int> A;
    // FOR(i,1,n) scanf("%d",&k),A.push_back(k);
    // auto res=problems::Knapsack(A,m);
    // int ans=0;
    // FOR(i,1,m) add_(ans,res[i],19260817);
    // printf("%d\n",ans);
    // 除法
    // scanf("%d%d",&n,&m);
    // poly a,b;
    // a.read(n+1); b.read(m);
    // // a.eval(b.v);
    // auto ans=evaluate(a,b.v);
    // for (int v:ans) printf("%d\n",v);
    // scanf("%d",&n);
    // scanf("%s",str);
    // int len=strlen(str);
    // ll k=0;
    // REP_(i,len) {
    //     k=((k*10ll)+str[i]-'0');
    //     if (k>MOD) k=MOD+k%MOD;
    // }
    // ll _k=0;
    // REP_(i,len) {
    //     _k=((_k*10ll)+str[i]-'0');
    //     if (_k>MOD-1) _k=MOD-1+_k%(MOD-1);
    // }
    // // vector<int> a(n),b(n);

    // scanf("%d%d",&n,&m);
    // poly a;
    // a.read(n);
    // // a.pow(k,_k).resize(n).print();
    // // if (m==0) a.sin().resize(n).print();
    // // if (m==1) a.cos().resize(n).print();
    // if (m==0) a.arcsin().resize(n).print();
    // if (m==1) a.arctan().resize(n).print();

    // scanf("%d",&n);
    // vector<int> a(n),b(n);
    // REP_(i,n) scanf("%d%d",&a[i],&b[i]);
    // // poly ans=interpolate(a,b).resize(n);
    // poly ans=poly(a).inter(poly(b)).resize(n);
    // ans.print();

    // // auto ans=a.divide(b.v);
    // // ans.first.resize(n-m+1).print();
    // // ans.second.resize(m).print();
    // // for (int v:ans) printf("%d\n",v);
    // // a.read(n+1); b.read(m+1);
    // // poly((a*b).v,n+m+1).print();
    // // a.read(n);
    // // a.pow(m).print();

    // scanf("%d%d",&n,&m);
    // poly a,b;
    // b.read(m); b=b.mulxk(1);
    // a.read(m);
    // auto ans=Cayley_Hamilton(a.v,b.v,n,n);
    // for (int v:ans) printf("%d\n",v);
}
/*
6 4
3 -1 0 4
-2 3 1 5

5 4
3 -1 0 4
-2 3 1 5
*/

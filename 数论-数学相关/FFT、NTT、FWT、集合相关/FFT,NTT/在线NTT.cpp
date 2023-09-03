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
// template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
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
    vector<int> mul(const vector<int> &A,const vector<int> &B,int mod)  { //C=A*B
        int n=A.size(),m=B.size();
        if (!n||!m) return vector<int>();
        vector<int> C(n+m-1,0);
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++) add_(C[i+j],(ll)A[i]*B[j]%mod,mod);
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
        // bitrev[i] = bitrev[i >> 1] >> 1 | (i & 1) << __builtin_ctz(len);
        for (int i=1,j=len/2; i<len-1; i++) {
            if (i<j) swap(A[i],A[j]);
            int k=len/2;
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
        for (int i=1; i<len; i<<=1) { //fin version
            for (int j=0; j<len; j+=i+i) { //merge length = i+i
                for (int k=0; k<i; k++) {
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
            for (int i=0; i<len; i++) A[i]=mul(A[i],vn);
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
        for (int i=0; i<len; i++) _A[i]=mul(_A[i],_B[i]);
        dft(_A,len,-1); _A.resize(n+m-1);
        return _A;
    }

    // push_back(fi,gi); 结果存在vector<int>h; 返回hi
    struct online_ntt {
        vector<int> f,g,h;
        map<int,pair<vector<int>,vector<int>>> fg_prefix_dft; // dft
        pair<vector<int>,vector<int>> &get_fg_prefix_dft(int len) {
            if (fg_prefix_dft.find(len)!=fg_prefix_dft.end()) return fg_prefix_dft[len];
            vector<int> vf(f.begin(),f.begin()+len);
            vector<int> vg(g.begin(),g.begin()+len);
            NTT::dft(vf,len,1); NTT::dft(vg,len,1);
            fg_prefix_dft[len]= {move(vf),move(vg)};
            return fg_prefix_dft[len];
        }
        int push_back(int fi,int gi) {
            f.push_back(fi); g.push_back(gi);
            int n=f.size(),len=1<<__builtin_ctz(n);
            int upd_h_size=n-1+len;
            if ((int)h.size()<upd_h_size) h.resize(upd_h_size);
            // 计算[0,min(n,len+len))*[n-len,n)对h[n-1,n-1+len)的贡献

            // if (len<=1) {
            if (len<=NTT::bruteforce_limit) {
                for (int j=n-len; j<n; j++) {
                    for (int i=n-1-j; i<min(n,n-1+len-j); i++) {
                        // assert(n-1<=i+j&&i+j<n-1+len);
                        add_(h[i+j],(ll)f[i]*g[j]%MOD,MOD);
                        if (len!=n) add_(h[i+j],(ll)f[j]*g[i]%MOD,MOD); // [0,n) [0,n)会重复计算
                    }
                }
            } else if (n!=len) {
                // Convolve f[0, 2 * len) * g[n - len, n) -> h[n - 1, n - 1 + len)
                // 这里是算1+2+4+8+...的贡献,每个n都会算log次
                std::vector<int> tmpf{f.end()-len,f.end()},tmpg{g.end()-len,g.end()};
                tmpf.resize(len*2); tmpg.resize(len*2);
                NTT::dft(tmpf,len*2,1); NTT::dft(tmpg,len*2,1);
                pair<vector<int>,vector<int>> p=get_fg_prefix_dft(len*2);
                vector<int> &vf=p.first,&vg=p.second;
                vector<int> vh(len*2);
                for (int i=0; i<len*2; i++) vh[i]=((ll)tmpf[i]*vg[i]+(ll)vf[i]*tmpg[i])%MOD;
                NTT::dft(vh,len*2,-1);
                for (int i=0; i<len; i++) add_(h[n-1+i],vh[len-1+i],MOD);
            } else {
                // Convolve f[0, len) * g[0, len) -> h[len - 1, len * 2 - 1)
                // FFT是循环卷积, 通过一些trick可以减少1/2常数
                pair<vector<int>,vector<int>> p=get_fg_prefix_dft(len);
                vector<int> &vf=p.first,&vg=p.second;
                vector<int> vh(vf.size());
                for (int i=0; i<len; i++) vh[i]=(ll)vf[i]*vg[i]%MOD;
                NTT::dft(vh,len,-1);
                // 这里是循环卷积,要删掉最开始的0->len-2这部分的值(这部分的值在h里面算过了)
                for (int i=n; i<n+n-1; i++) add_(h[i],vh[i-n],MOD),add_(h[i],MOD-h[i-n],MOD);
                add_(h[n-1],vh[n-1],MOD);
            }
            // for (int v:h)  printf("%d ",v); puts("<- h");
            return h[n-1];
        }
    };
}

#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
void solve_ATC315Ex() {
    NTT::online_ntt ntt;
    int n,i;
    scanf("%d",&n);
    vector<int> A(n+1),F(n+1);
    FOR(i,1,n) scanf("%d",&A[i]);
    ll sum=0;
    F[0]=1;
    FOR(i,1,n) {
        add_(sum,ntt.push_back(F[i-1],F[i-1]),NTT::MOD);
        F[i]=sum*A[i]%NTT::MOD;
    }
    FOR(i,1,n) printf("%d ",F[i]);
    puts("");
}
int main() {
    int T,_; T=1;
    // T=10000;
    // scanf("%d",&T);
    FOR(_,1,T) {
        solve_ATC315Ex();
    }
}
/*
20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20

20
900000000 900000000 900000000 900000000 900000000 900000000 900000000 900000000 900000000 900000000 900000000 900000000 900000000 900000000 900000000 900000000 900000000
900000000 900000000 900000000 900000000 900000000 900000000 900000000 900000000 900000000 900000000 900000000 900000000 900000000 900000000 900000000 900000000 900000000
*/
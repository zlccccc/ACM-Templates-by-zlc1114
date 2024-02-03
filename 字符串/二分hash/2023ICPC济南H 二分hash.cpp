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
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=1e-10;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
inline ll fastgcd(ll a, ll b) {  // __gcd()
    if (!a) return b;
    ll az=__builtin_ctzll(a),bz=__builtin_ctzll(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctzll(diff);
        (b>a)&&(b=a); a=abs(diff);
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
    
struct Hash{
    vector<int> px,val; int MOD,P;
    Hash(int n=1,int p=19260817,int mod=1e9+7) {
        // printf("hash %d %d %d\n",n,p,mod);
        px.resize(n+1); val.resize(n+1);
        P=p; MOD=mod; px[0]=1;
        FOR_(i,1,n) px[i]=(LL)px[i-1]*p%MOD;
    }
    void set(int a[]){ // id start from 0
        val[0]=0; int n=val.size()-1;
        FOR_(i,1,n) val[i]=((LL)val[i-1]*P+a[i-1])%MOD;
    }
    int get(int l,int r){
        l++; r++;
        // printf("get %d %d\n",l,r);
        int ret=val[r]-(LL)val[l-1]*px[r-l+1]%MOD;
        (ret<0)&&(ret+=MOD); return ret;
    }
};

// 题意:计算每个位置改成另一个字符后,对每个i的\sum{lcp(i,x)}答案最大是多少
// 做法:二分hash,相当于先截断然后添加新的贡献,分情况讨论下贡献就行了
int A[maxn];
ll chg[maxn]; // 计算A[0]更改成任意一个值
map<int,ll> MP[maxn];  // 更改带来的贡献
ll f0[maxn],f1[maxn];  // 更改导致lcp变化
int solve() {
    int n;
    scanf("%d",&n);
    REP_(i,n) scanf("%d",&A[i]);
    Hash hash(n);
    hash.set(A);
    auto getlcp=[&](int x,int y,function<int(int,int)> hashvalue) {   // [x,n], [y,n]的lcp是多少
        int l=0,r=n-max(x,y)+1;
        while (l+1<r) {
            int mid=(l+r)/2;
            if (hashvalue(x,x+mid-1)==hashvalue(y,y+mid-1)) l=mid;
            else r=mid;
        }
        // printf("getlcp %d %d: %d\n",x,y,l);
        return l;
    };
    FOR_(i,0,n) f0[i]=f1[i]=0,MP[i].clear();
    
    ll base=0;
    REP_(i,n) {
        int firlen=getlcp(0,i,[&](int l,int r){return hash.get(l,r);});
        base+=firlen;
    
        if (i) {
            // 修改此处的值会使得更改答案:
            f1[i]++; f1[i+firlen]--;
            f0[i]-=i+firlen; f0[i+firlen]+=i+firlen;
    
            f1[0]++; f1[min(i,firlen)]--;
            f0[0]-=firlen; f0[min(i,firlen)]+=firlen;
        }
    
        // firlen和i+firlen第一个不相同
        // printf("i=%d: length=%d\n",i,firlen);
        if (i+firlen!=n) {  // i=1的时候不会变化的
            // 更改成这个value以后结果会变高
            int r0=firlen+1,ri=i+firlen+1;
            {
                int x,y;
                x=firlen; y=A[i+firlen];
                int seclen=getlcp(0,i,[&](int l,int r){  // A[x]=y的时候的lcp
                    if (r<x||l>x) return hash.get(l,r);
                    return (int)(((ll)hash.get(l,x-1)*hash.px[r-x+1]+(ll)y*hash.px[r-x]+hash.get(x+1,r))%hash.MOD);
                });
                // printf("secid=%d; second length = %d; move=%d\n",i+firlen,seclen,min(seclen,i+firlen-r0));
                MP[x][y]+=max(0,seclen-firlen);
                // printf("1 last move=%d %d; second length = %d(change=%d,%d); upd=%d\n",r0,ri,seclen+1,x,y,seclen-firlen);
            }
            {
                int x,y;
                x=i+firlen; y=A[firlen];
                int seclen=getlcp(0,i,[&](int l,int r){  // A[x]=y的时候的lcp
                    if (r<x||l>x) return hash.get(l,r);
                    return (int)(((ll)hash.get(l,x-1)*hash.px[r-x+1]+(ll)y*hash.px[r-x]+hash.get(x+1,r))%hash.MOD);
                });
                // printf("secid=%d; second length = %d; move=%d\n",i+firlen,seclen,min(seclen,i+firlen-r0));
                MP[x][y]+=max(0,seclen-firlen);
                // printf("2 last move=%d %d; second length = %d(change=%d,%d); upd=%d\n",r0,ri,seclen+1,x,y,seclen-firlen);
            }
        }
    }
    // printf("base=%lld\n",base);
    FOR_(i,1,n) f0[i]+=f0[i-1];
    FOR_(i,1,n) f1[i]+=f1[i-1];
    ll res=0;
    rep_(i,0,n) {
        ll cur=f1[i]*i+f0[i]+base;
        for (auto &p:MP[i]) {
            // printf("%d %d\n",p.first,p.second);
            cur=max(cur,f1[i]*i+f0[i]+base+p.second);
        }
        // printf("solve %d contribution: %d; cur=%lld; %lld; res=%lld\n",i,f1[i]*i+f0[i],cur,cur^(i+1),res);
        res+=cur^(i+1);
    }
    printf("%lld\n",res);
    return 0;
}
int main() {
    int T; T=1;
    cin>>T;
    startTimer();
    FOR_(_,1,T) {
        solve();
    }
    // printTimer();
}
/*
10
12
1 1 4 5 1 4 1 9 1 9 8 10
15
17
18
20
15
19
15
19
15
18
17
17
*/
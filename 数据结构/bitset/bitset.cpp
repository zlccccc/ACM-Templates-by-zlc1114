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
// #include <bitset>
#include <functional>
#include <random>
using namespace std;

#define FOR_(I,S,N) for (int I=(S),i##_end=(N);I<=i##_end;I++)
#define rFOR_(I,S,N) for (int I=(N),i##_end=(S);I>=i##_end;I--)
#define REP_(I,N) for (int I=(0),i##_end=(N)-1;I<=i##_end;I++)
#define rREP_(I,N) for (int I=(N)-1,i##_end=(0);I>=i##_end;I--)
#define rep_(I,S,N) for (int I=(S),i##_end=(N)-1;I<=i##_end;I++)
#define rrep_(I,S,N) for (int I=(N)-1,i##_end=(S);I>=i##_end;I--)

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
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) debug("%d",(x>>i)&1); putchar(' ');}
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

// const int mod = 1e9+7;
const int mod=998244353;
// int mod=1;
struct mint {
    long long x;
    mint():x(0) {}
    mint(long long x):x((x%mod+mod)%mod) {}
    // mint(long long x):x(x){}
    mint &fix() { x = (x%mod+mod)%mod; return *this;}
    mint operator-() const { return mint(0) - *this;}
    mint operator~() const { return mint(1) / *this;}
    mint &operator+=(const mint &a) { if ((x+=a.x)>=mod) x-=mod; return *this;}
    mint &operator-=(const mint &a) { if ((x+=mod-a.x)>=mod) x-=mod; return *this;}
    mint &operator*=(const mint &a) { (x*=a.x)%=mod; return *this;}
    mint &operator/=(const mint &a) { (x*=a.pow(mod-2).x)%=mod; return *this;}
    mint operator+(const mint &a)const { return mint(*this) += a;}
    mint operator-(const mint &a)const { return mint(*this) -= a;}
    mint operator*(const mint &a)const { return mint(*this) *= a;}
    mint operator/(const mint &a)const { return mint(*this) /= a;}
    mint pow(long long t) const {
        mint ret=1,cur=x;
        for (; t; t>>=1ll,cur=cur*cur)
            if (t&1) ret=ret*cur;
        return ret;
    }
    bool operator<(const mint &a)const { return x < a.x;}
    bool operator==(const mint &a)const { return x == a.x;}
};

struct custom_bitset {
    int N;
    vector<uint32_t> bits;
    custom_bitset(int N=0,int val=0): N(N) {
        reset(val);
    }
    void reset(int val=0) {
        assert(val==0||val==1);
        if (val==1) val=-1;
        bits.assign((N+31)/32,val);
        _clean_last();
    } 
    custom_bitset(const string &s): N(s.size()) {
        bits.assign((N+31)/32,0);
        REP_(i,s.size()) set(i,s[i]-'0');
    }
    custom_bitset(const custom_bitset &oth): N(oth.N),bits(oth.bits) {}
    custom_bitset resize(int M) {
        N=M;
        bits.resize((N+31)/32);
        _clean_last();
        return *this;
    }
    void _clean_last() {
        if (N!=(int)bits.size()*32)
            bits.back()&=(1u<<(N-32*(bits.size()-1)))-1;
    }
    void clear() {
        fill(bits.begin(),bits.end(),0);
    }
    void clear_memory() {
        N=0;
        vector<uint32_t>().swap(bits);
    }

    custom_bitset & operator &= (const custom_bitset &oth) {
        resize(max(oth.N,N));
        REP_(i,oth.bits.size()) bits[i]&=oth.bits[i];
        return *this;
    }
    custom_bitset & operator |= (const custom_bitset &oth) {
        resize(max(oth.N,N));
        REP_(i,oth.bits.size()) bits[i]|=oth.bits[i];
        return *this;
    }
    custom_bitset & operator ^= (const custom_bitset &oth) {
        resize(max(oth.N,N));
        REP_(i,oth.bits.size()) bits[i]^=oth.bits[i];
        return *this;
    }
    custom_bitset & operator <<= (int x) {
        if (x<0) {*this>>=-x; return *this;}
        if (x>=N) {clear(); return *this;}
        int y=x>>5,z=x&31;
        if (z) rrep_(i,y+1,bits.size()) bits[i]=(bits[i-y]<<z)|(bits[i-y-1]>>(32-z));
        else rrep_(i,y+1,bits.size()) bits[i]=bits[i-y];
        bits[y]=bits[0]<<z;
        REP_(i,y) bits[i]=0;
        _clean_last();
        return *this;
    }
    custom_bitset & operator >>= (int x) {
        if (x<0) {*this<<=-x; return *this;}
        if (x>=N) {clear(); return *this;}
        int y=x>>5,z=x&31;
        // printf("y=%d; z=%d; bitsize=%d\n",y,z,bits.size());
        if (z) REP_(i,bits.size()-y-1) bits[i]=(bits[i+y]>>z)|(bits[i+y+1]<<(32-z));
        else REP_(i,bits.size()-y-1) bits[i]=bits[i+y];
        bits[bits.size()-y-1]=bits[bits.size()-1]>>z;
        rep_(i,bits.size()-y,bits.size()) bits[i]=0;
        return *this;
    }
    // // 修改长度; 我感觉还是别用比较好
    // inline void fix() {
    //     while (bits.back()==0) bits.pop_back();
    //     N=min(N,bits.size()*32);
    // }

    custom_bitset operator & (const custom_bitset &x) const {
        custom_bitset ans(*this); ans&=x;
        return ans;
    }
    custom_bitset operator | (const custom_bitset &x) const {
        custom_bitset ans(*this); ans|=x;
        return ans;
    }
    custom_bitset operator ^ (const custom_bitset &x) const {
        custom_bitset ans(*this); ans^=x;
        return ans;
    }
    custom_bitset operator << (int x) const {
        custom_bitset ans(*this); ans<<=x;
        // printf("ans.size=%d\n",ans.bits.size());
        return ans;
    }
    custom_bitset operator >> (int x) const {
        custom_bitset ans(*this); ans>>=x;
        return ans;
    }
    custom_bitset operator ~ () const {
        custom_bitset ans(N);
        REP_(i,bits.size()) ans.bits[i]=~bits[i];
        ans._clean_last();
        return ans;
    }
    bool get(int x) const {
        assert(0<=x&&x<N);
        int y=x>>5,z=x&31;
        return bits[y]>>z&1;
    }
    bool operator [](int x) const {
        return get(x);
    }
    void set(int x,bool val=1) {
        assert(0<=x&&x<N);
        int y=x>>5,z=x&31;
        bits[y]|=1<<z;
        if (!val) bits[y]^=1<<z;
    }
    bool operator < (const custom_bitset &oth) const {
        REP_(i,min(bits.size(),oth.bits.size()))
            if (bits[i]!=oth.bits[i]) return bits[i]<oth.bits[i];
        return N<oth.N;
    }
    int next(int x) {
        if (x>=N) return N;
        if (x<0) x=0;
        int y=x>>5,z=x&31;
        uint32_t v=(bits[y]>>z)<<z;
        if (v) return y<<5|__builtin_ctz(v);
        rep_(i,y+1,bits.size()) if (bits[i]) return i<<5|__builtin_ctz(bits[i]);
        return N;
    }
    custom_bitset substr(int l,int r) { // subset[l->r-1]
        // { // first impl; O(N)/32
        //     assert(0<=l&&l<r&&r<=N);
        //     custom_bitset ans(*this); ans>>=l;
        //     ans.resize(r-l);
        //     return ans;
        // }
        { // second impl; O(r-l)/32
            custom_bitset ans(r-l);
            int x=l,y=x>>5,z=x&31;
            if (z) REP_(i,min(bits.size()-y-1,ans.bits.size()))
                ans.bits[i]=(bits[i+y]>>z)|(bits[i+y+1]<<(32-z));
            else REP_(i,min(bits.size()-y-1,ans.bits.size()))
                ans.bits[i]=bits[i+y];
            if (bits.size()-y-1<ans.bits.size()) ans.bits[bits.size()-y-1]=bits[bits.size()-1]>>z;
            rep_(i,bits.size()-y,min(bits.size(),ans.bits.size())) ans.bits[i]=0;
            ans._clean_last();
            return ans;
        }
    }

    // 预处理bitset的num
    static inline int BitNum(unsigned int x) {
        static vector<int> a;
        if (a.size()==0) {
            a.resize(1<<16); a[0]=0;
            rep_(i,1,1<<16) a[i]=a[i>>1]+(i&1);
        }
        return a[x>>16]+a[x&65535];
    }
    int count() const {
        int ret=0;
        for (int v:bits) ret+=BitNum(v);
        return ret;
    }

    // reverse前x位,返回一个长度为x的bitset
    static inline unsigned int BitReverse(unsigned int x) {
        static vector<unsigned int> a;
        if (a.size()==0) {
            a.resize(1<<16); a[0]=0;
            rep_(i,1,1<<16) a[i]=(a[i>>1]>>1)|((i&1)<<15);
        }
        return a[x>>16]|(a[x&65535]<<16);
    }
    custom_bitset reverse(int x) const {
        int y=x>>5,z=x&31;
        custom_bitset ans(x-z+32);
        FOR_(i,max(0,y-(int)bits.size()+1),y) ans.bits[i]=BitReverse(bits[y-i]);
        return (ans>>(32-z)).resize(x);
    }

    // 相邻两位合并成一位, op[0]=or; op[1]=and; op[2]=xor
    static inline unsigned int BitMerge(unsigned int x,int op) {
        static vector<unsigned int> vec[3];
        assert(op<3);
        vector<unsigned int> &a=vec[op];
        if (a.size()==0) {
            a.resize(1<<16);
            rep_(k,0,1<<16) {
                int now=0;
                REP_(i,8) {
                    if (op==0) now|=(((k>>(i*2))&1)|((k>>(i*2+1))&1))<<i;
                    if (op==1) now|=(((k>>(i*2))&1)&((k>>(i*2+1))&1))<<i;
                    if (op==2) now|=(((k>>(i*2))&1)^((k>>(i*2+1))&1))<<i;
                } a[k]=now;
            }
        }
        return (a[x>>16]<<8)|a[x&65535];
    }
    custom_bitset const bitmerge(int op) const {//相邻两位合并
        custom_bitset ret((N+1)/2);
        REP_(i,bits.size()) {
            if (i&1) ret.bits[i>>1]|=BitMerge(bits[i],op)<<16;
            else ret.bits[i>>1]|=BitMerge(bits[i],op);
        }
        ret._clean_last(); // 如果有^之类的操作需要clean,这里实际上不太需要
        return ret;
    }

    void print() {
        REP_(i,N) printf("%d",get(i));
    }
    string to_string() const {
        string S;
        REP_(i,N) S+='0'+get(i);
        S+=" count=";
        S+=std::to_string(count());
        return S;
    }
};

// 背包bitset,小于n能构成哪些val
// 如果sum=n,复杂度nsqrtn/32; 否则复杂度n^2/32
custom_bitset possible_subsets_knapsack(int n, const vector<int> &sizes) {
    vector<int> freq(n + 1, 0);
    for (int s : sizes)
        if (1 <= s && s <= n) freq[s]++;
    custom_bitset knapsack(n+1);
    knapsack.set(0);
    FOR_(s,1,n) {
        if (freq[s] >= 3) {
            int move = (freq[s] - 1) / 2;
            if (2 * s <= n) freq[2 * s] += move;
            freq[s] -= 2 * move;
        }
        for (int r = 0; r < freq[s]; r++)
            knapsack|=knapsack<<s;
    }
    return knapsack;
}

// https://codeforces.com/contest/1856/problem/E2
// 题意: 给一棵树, 每个树的所有子树size分成两组, 求\sum乘积最大值
// 就是子树做背包; 问分成两摞乘积最大和是多少
// 考虑子树最大size大于当前一半,答案是确定的; 否则直接做背包
// 如果所有子树size都小于当前一半,可以分log层; 否则背包总size是k,用bitset复杂度nsqrtn/32
void solve_CF1856E() {
    int n;
    scanf("%d",&n);
    vector<vector<int>> edge(n+1);
    vector<int> sz(n+1);
    function<ll(int)> dfs=[&](int x) {
        ll ret=0; sz[x]=1;
        for (int v:edge[x]) {
            ret+=dfs(v);
            sz[x]+=sz[v];
        }
        for (int v:edge[x])
            if (sz[v]>=(sz[x]-1)/2) return ret+(ll)sz[v]*(sz[x]-1-sz[v]);
        // printf("i=%d\n",x);
        vector<int> vec;
        for (int v:edge[x]) vec.push_back(sz[v]);
        // custom_bitset knapsack=possible_subsets_knapsack((sz[x]-1)/2,vec);
        // ll mor=0;
        // FOR_(i,0,(sz[x]-1)/2) if (knapsack[i]) mor=max(mor,(ll)i*(sz[x]-1-i));
        custom_bitset knapsack=possible_subsets_knapsack((sz[x]-1),vec);
        ll k=knapsack.next((sz[x]-1)/2),mor=k*(sz[x]-1-k);
        return ret+mor;
    };
    FOR_(i,2,n) {
        int f; scanf("%d",&f);
        edge[f].push_back(i);
    }
    printf("%lld\n",dfs(1));
}

// https://ac.nowcoder.com/acm/contest/145/C
// 题意: n=2^18的字符串, 每次操作把相邻两个位置合并
// 2^k -> 2^k-1, 每次operation随机选|,&,^
// 问有多少种情况最终答案是1
void solve_NowCoder145C() {
    int n; string s;
    cin>>n;
    cin>>s;
    // REP_(i,1<<n) s+=((rand()&1)+'0');
    // cout<<s<<endl;

    custom_bitset bit(s);
    map<custom_bitset,int> MP;
    MP[bit]=1;
    assert(bit.N==1<<n);
    bit.resize(1<<n);
    REP_(i,n) {
        // printf("%d: %d\n",i,MP.size());
        map<custom_bitset,int> nxt;
        for (auto &p:MP) {
            nxt[p.first.bitmerge(0)]+=p.second;
            nxt[p.first.bitmerge(1)]+=p.second;
            nxt[p.first.bitmerge(2)]+=p.second;
        }
        // for (auto &p:nxt)
        //     cout<<p.first.to_string()<<" "<<p.second<<endl;
        MP.swap(nxt);
    }
    for (auto &now:MP) {
        if (now.first.count()) {
            // all+=now.second;
            // printf("%d\n",now.second);
            cout<<now.second;
            return;
        }
    }
    cout<<0;
}

// https://codeforces.com/contest/914/problem/F
// 题意: 子字符串匹配, 长度1e5
// 大概就是把字符串拿出来暴力匹配, 复杂度n^2/32
void solve_CF914F() {
    string s;
    cin>>s;
    vector<custom_bitset> T(26,custom_bitset(s.size()));
    REP_(i,s.size()) T[s[i]-'a'].set(i);
    int q; cin>>q;
    while (q--){
        int op; cin>>op;
        if (op==1){
            int pos; char c;
            cin>>pos>>c; pos--;
            T[s[pos]-'a'].set(pos,0);
            s[pos]=c;
            T[s[pos]-'a'].set(pos);
        }else{
            int l,r; string b;
            cin>>l>>r>>b; l--;
            if ((int)b.length()>r-l) puts("0");
            else {
                // custom_bitset matching(r-l);
                // matching.reset(1);
                // REP_(i,b.size()) matching&=(T[b[i]-'a'].substr(l,r)>>i);

                int maxlen=r-l-b.length()+1;
                custom_bitset matching(maxlen);
                matching.reset(1);
                // REP_(i,b.size()) matching&=(T[b[i]-'a']>>(l+i)).resize(maxlen);
                REP_(i,b.size()) matching&=T[b[i]-'a'].substr(l+i,l+i+maxlen);
                printf("%d\n",matching.count());
            }
        }
    }
}

void check() {
    string s;
    while (cin>>s) {
        custom_bitset bit(s);
        cout<<s<<" <- initial bitset  length="<<bit.N<<endl;
        vector<int> reverse={0,5,31,33,64,67};
        for (int v:reverse) cout<<bit.reverse(v).to_string()<<" <- reverse "<<v<<"\n";

        vector<int> shift={-1,0,31,33,64,67};
        for (int v:shift) cout<<(bit<<v).to_string()<<"  <- s << "<<v<<endl;
        for (int v:shift) cout<<(bit>>v).to_string()<<"  <- s >> "<<v<<endl;

        for (int v:shift) cout<<(~(bit>>v)).to_string()<<"  <- ~(rev) s >> "<<v<<endl;
    }
}
int main() {
    // check();
    // solve_CF1856E();
    // solve_NowCoder145C();
    solve_CF914F();
}
/**/
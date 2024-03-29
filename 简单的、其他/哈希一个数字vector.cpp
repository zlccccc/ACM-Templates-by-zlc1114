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
const LL maxn=3e5+7;
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

class Solution {
public:
    vector<long long> Hash;
    void InitHash(const vector<long long> &vec={}) {
        for (long long v:vec) Hash.push_back(v);
        sort(Hash.begin(),Hash.end());
        Hash.erase(unique(Hash.begin(),Hash.end()),Hash.end());
    }
    inline int getId(long long x) {return lower_bound(Hash.begin(),Hash.end(),x)-Hash.begin()+1;}
    vector<long long> res;
    inline int lowbit(int x) {return x&-x;}
    inline void update(int x,long long y) {
        for (;x<res.size();x+=lowbit(x)) res[x]=max(res[x],y);
    }
    inline long long get(int x) {
        long long ret=0;
        for (;x;x-=lowbit(x)) ret=max(ret,res[x]);
        return ret;
    }
    long long maxBalancedSubsequenceSum(vector<int>& nums) {
        Hash.clear();
        for (int i=0;i<nums.size();i++) Hash.push_back(nums[i]-i);
        InitHash();
        res.resize(Hash.size()+1);
        fill(res.begin(),res.end(),0);
        long long ans=-1e18;
        for (int i=0;i<nums.size();i++) {
            int id=getId(nums[i]-i);
            long long cur=get(id)+nums[i];
            ans=max(ans,cur);
            update(id,cur);
        }
        return ans;
    }
};
int main() {
}
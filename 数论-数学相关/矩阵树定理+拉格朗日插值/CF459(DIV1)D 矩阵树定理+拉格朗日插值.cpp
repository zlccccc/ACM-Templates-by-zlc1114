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

const int mod = 1e9+7;
// const int mod=998244353;
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
struct comb {
    vector<mint> f, g; // f:fac; g:inv
    comb() {}
    comb(int mx):f(mx+1),g(mx+1) {
        f[0] = 1;
        FOR_(i,1,mx) f[i] = f[i-1]*i;
        g[mx] = f[mx].pow(mod-2);
        rFOR_(i,1,mx) g[i-1] = g[i]*i;
    }
    mint operator()(int a, int b) {
        if (a < b) return 0;
        return f[a]*g[b]*g[a-b];
    }
} C(maxn);

struct Edge {
    Edge(int from,int to,int k=1):from(from),to(to),k(k) {};
    int from,to,k;
}; // from->to总共k条边

// CF459(DIV1)D
// 题意:求生成树中含k条给定树边的生成树个数
// 做法:为给定边加不同权值,然后矩阵树定理
// 具体来说, 假设ans(x)是用了x条边的结果,那么ans(x)*{i^x}=val(i)是可以算的
// 相当于问你ans(x)这个多项式的系数; 拉格朗日插值就好了

// matrix tree定理: 生成树数量=|度数矩阵-边矩阵|; 度数的话要分入度和出度; 无向图的话都加上
// best定理: 欧拉回路数量=\mul(outdegree)*(in)生成树数量; out和in反过来结果也一样
//          证明的话考虑欧拉回路每个点连的最后那条边, 会构成一颗有向树
struct Matrix {
    vector<vector<mint>> D;
    int n;
    Matrix() {n=0;}
    Matrix(int n, int val = 0) : n(n), D(n, vector<mint>(n, val)) {}
    vector<mint>& operator[](const int &x) {return D[x];}
    const vector<mint>& operator[](const int &x) const {return D[x];}
    Matrix lead(int k) { // 去除k行k列
        Matrix res(n - 1);
        REP_(i,n) {
            if(i == k) continue;
            REP_(j,n) {
                if(j == k) continue;
                res[i - (i > k)][j - (j > k)] = D[i][j];
            }
        }
        return res;
    }
    Matrix lead(const vector<int> &x, const vector<int> &y) { // 只有x行y列
        Matrix res(x.size());
        assert(x.size()==y.size());
        for(int i = 0; i < x.size(); i++) {
            for(int j = 0; j < y.size(); j++) {
                res[i][j] = D[x[i]][y[j]];
            }
        }
        return res;
    }
    mint det() {
        mint ans=1;
        REP_(i,n) {
            int r = i;
            while(r < n - 1 && D[r][i] == 0) r++;
            if (r != i) swap(D[r], D[i]), ans*=-1;
            if (D[i][i] == 0) return 0;
            mint inv=mint(1)/D[i][i];
            rep_(k,i+1,n) rrep_(j,i,n)
                D[k][j]-=D[k][i]*inv*D[i][j];
        }
        REP_(i,n) ans*=D[i][i];
        return ans;
    }
    void output() {
        REP_(i,n) {
            REP_(j,n) printf("%lld ",D[i][j].x);
            puts("");
        }
    }
    // 求边连起来的连通块; filterEdge: 删除只有1个节点而且没有边的连通块
    static vector<pair<vector<int>,vector<Edge>>> MergeComponents(vector<Edge> edges,int n,bool filterEdge=true) {
        vector<int> fa(n);
        REP_(i,n) fa[i]=i;
        function<int(int)> getfa=[&](int x) {
            if (fa[x]==x) return x;
            return fa[x]=getfa(fa[x]);
        };
        for (auto &e:edges) {
            int x=getfa(e.from),y=getfa(e.to);
            if (x!=y) fa[x]=y;
        }
        // 合并相同component
        vector<pair<vector<int>,vector<Edge>>> items(n),components;
        REP_(i,n) items[getfa(i)].first.push_back(i);
        for (auto &e:edges) items[getfa(e.from)].second.push_back(e);
        if (filterEdge) {
            for (auto &item:items) if (item.second.size()) components.emplace_back(move(item));  // 不是1个节点构成的连通块
        } else {
            for (auto &item:items) if (item.first.size()) components.emplace_back(move(item));  // 所有连通块
        }
        return components;
    }
    mint MatrixTreeSingleComponent(const vector<Edge> &edges, bool from=true) {
        for (auto &e:edges) {
            D[e.from][e.to]-=e.k;
            if (from) D[e.from][e.from]+=e.k;
            else D[e.to][e.to]+=e.k;
        }
        return lead(0).det();
    }
    static mint MatrixTree(const vector<Edge> &E,int n,bool filterEdge=true,bool singleComponent=true) {
        vector<Edge> edges;
        for (auto &e:E) if (e.k>0) edges.push_back(e);  // filter
        auto components=MergeComponents(edges,n,filterEdge);  // 连通块
        // 如果存在多个连通块这里返回是0(请特殊处理~)
        if (components.size()==0) return 1;
        if (singleComponent&&components.size()!=1) return 0;
        mint res = 1;
        vector<int> id(n);  // 有节点度数为0就把这个节点先删掉了; 做映射
        for (auto &component:components) {
            auto &curNodes=component.first;
            auto &curEdges=component.second;

            // printf("solve ");
            // for (int v:curNodes) printf("%d ",v);
            // for (auto &e:curEdges) printf("[%d-%d %d] ",e.from,e.to,e.k); puts("");

            int tot=0;
            for (int v:curNodes) id[v]=tot++;
            vector<Edge> convertEdges;
            for (auto &e:curEdges) convertEdges.push_back({id[e.from],id[e.to],e.k});
            res*=Matrix(n).MatrixTreeSingleComponent(convertEdges);
        }
        return res;
    }
    static mint BestTheoremSingleComponent(const vector<Edge> &E,int n) {  // n个节点固定了
        vector<Edge> edges;
        for (auto &e:E) if (e.k>0) edges.push_back(e);  // filter
        if (edges.size()==0) return 1;
        vector<int> indeg(n),outdeg(n);
        for (auto &e:edges) indeg[e.from]+=e.k,outdeg[e.to]+=e.k;
        REP_(i,n) if (indeg[i]!=outdeg[i]) return 0;  // 无法构成回路
        // 求内/外向生成树个数 (一样的)
        mint res=Matrix(n).MatrixTreeSingleComponent(edges,true);
        // 求欧拉回路个数
        REP_(i,n) res*=C.f[outdeg[i]-1];  // * x!
        for (auto &e:edges) res*=C.g[e.k];  // 相同边只算一次; / x!
        return res;
    }
    // x->y有k条边; 求欧拉回路数量; filterEdge: 去掉一个节点没有边构成的连通块(欧拉回路要求); singleComponent: 只能有一个连通块(欧拉回路要求)
    static mint BestTheorem(const vector<Edge> &E,int n,bool filterEdge=true,bool singleComponent=true) {
        vector<Edge> edges;
        for (auto &e:E) if (e.k>0) edges.push_back(e);  // filter
        auto components=MergeComponents(edges,n,filterEdge);  // 连通块
        // 如果存在多个连通块这里返回是0(请特殊处理~)
        if (components.size()==0) return 1;
        if (singleComponent&&components.size()!=1) return 0;
        mint res = 1;
        vector<int> id(n);  // 有节点度数为0就把这个节点先删掉了; 做映射
        for (auto &component:components) {
            auto &curNodes=component.first;
            auto &curEdges=component.second;

            // printf("solve ");
            // for (int v:curNodes) printf("%d ",v);
            // for (auto &e:curEdges) printf("[%d-%d %d] ",e.from,e.to,e.k); puts("");

            int tot=0;
            for (int v:curNodes) id[v]=tot++;
            vector<Edge> convertEdges;
            for (auto &e:curEdges) convertEdges.push_back({id[e.from],id[e.to],e.k});
            res*=BestTheoremSingleComponent(convertEdges,tot);
        }
        return res;
    }
};

// 拉格朗日插值
// f(x)=\sum{(x-xj)/(xi-xj)};{i!=j}
vector<mint> lagrange(vector<mint> id,vector<mint> val) {
    int n=val.size();
    vector<mint> f(n+1),g(n+1),ans(n);
    g[0]=1;
    REP_(i,n) rFOR_(j,0,i) g[j+1]+=g[j],g[j]*=-id[i];
    REP_(k,n) {
        mint rev=1;
        rREP_(i,n) f[i]=g[i+1]+f[i+1]*id[k];
        REP_(j,n) if (j!=k) rev*=id[k]-id[j];
        rev=mint(1)/rev*val[k];
        REP_(i,n) ans[i]+=f[i]*rev;
    }
    return ans;
}

int n;
int e[107][107];
int solve() {
    int n;
    cin>>n;
    REP_(i,n-1) {
        int x,y;
        scanf("%d%d",&x,&y);
        x--; y--;
        e[x][y]=e[y][x]=1;
    }
    vector<mint> id;
    vector<mint> val;
    REP_(k,n) {
        vector<Edge> edges;
        REP_(x,n) REP_(y,n) {
            if (e[x][y]) edges.push_back({x,y,k});
            else edges.push_back({x,y,1});
        }
        id.push_back(k);
        val.push_back(Matrix::MatrixTree(edges,n));
    }
    // for (auto &v:val) cout<<v.x<<" "; puts("<- g");
    auto res=lagrange(id,val);
    for (auto &v:res) cout<<v.x<<" ";
    return 0;
}
int main() {
    int T; T=1;
    FOR_(_,1,T) solve();
}
/*
*/
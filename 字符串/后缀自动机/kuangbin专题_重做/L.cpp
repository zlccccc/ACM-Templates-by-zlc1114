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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

//这里的len不可以直接使用~ 原因是这里的len指的是原串len
//fail过后,len是可以直接使用的~ (会fail到确定的节点上)
//这个fail的含义是说后缀相同,向前拓展的val(一个一个拓展len差项)
//sam反向不为拓扑序!注意自己进行拓扑排序
//更新时注意len的限制!(因为更新时可能根本没有考虑前缀len)
//注意nq在更新时更新时val和q是相等的,也就是说,维护值时nq要完全和q一样
//sum{len[x]-len[fail[x]]}=不同串个数,每个串代表fail->this的len
//每个串的位置建议存的时候就保留下来~ 要不就有点麻烦了
//复制出来的虚拟节点在计算次数时不参与计算~
//也就是说计算相同串个数时,复制出来的只是个虚拟的节点
//query时在末尾加个0可以去掉很多的判断!
//加空字符时注意len,这个len有两个作用:避免topo排错,减少add特判
//加的不是root,就是个空字符,dfs的话只能dfs一个串!从后往前递推可行
//如果是在一颗树上建,那么直接计数排序按len排是错的!一定注意!
struct SAM{
    int next[maxn][26],fail[maxn],len[maxn];
    int cnt,last;
    void init(){
        cnt=last=0;fail[0]=-1;len[0]=0;
        memset(next[0],0,sizeof(next[0]));
    }map<int,int> have[maxn];
    void add(int c,int id){
        int np=++cnt,p=last;
        memset(next[np],0,sizeof(next[np]));
        len[np]=len[p]+1;
        for (;p!=-1&&!next[p][c];p=fail[p]) next[p][c]=np;
        if (p==-1) fail[np]=0;
        else {
            int q=next[p][c];
            if (len[p]+1==len[q]) fail[np]=q;
            else{
                int nq=++cnt;len[nq]=len[p]+1;
                memcpy(next[nq],next[q],sizeof(next[q]));
                fail[nq]=fail[q];//Last[nq]=Last[q];
                fail[np]=fail[q]=nq;
                for (;p!=-1&&next[p][c]==q;p=fail[p]) next[p][c]=nq;
            }
        }
        last=np;//Last[np]=last;
        have[np][id]++;
    }
    void add(char a[],int id){
        int n=strlen(a),i;last=0;
        REP(i,n) {
            add(a[i]-'a',id);
//            printf("add: %d\n",last);
        }//print();
    }
    void merge(map<int,int> &A,map<int,int> &B){
        if (A.size()<B.size()) swap(A,B);
        for (auto now:B) A[now.first]+=now.second;
        B.clear();//delete &B;
    }
    vector<int> edge[maxn];
    LL Ans[maxn];
    void DFS(int x,int k){
        for (int v:edge[x]){DFS(v,k);merge(have[x],have[v]);}
        if (have[x].size()>=k)
            for (auto v:have[x])
                Ans[v.first]+=(LL)v.second*(len[x]-len[fail[x]]);
    }
    void solve(int k){
        int i,j;
        FOR(i,0,cnt) edge[i].clear();
        FOR(i,1,cnt) edge[fail[i]].push_back(i);
        DFS(0,k);
    }
    void print(){
        int i;
        FOR(i,1,cnt) {
            printf("%-2d (fail=%-3d ; divlen=%d; len=%d):",i,fail[i],len[i]-len[fail[i]],len[i]);
            for (auto v:have[i]) printf("%2d(%2d) ",v.first,v.second);puts("");
        }
    }
    char a[maxn];
    void dfs(int x=0,int len=0){
        int i;
//        for (auto v:have[x]) printf("%2d(%2d) ",v.first,v.second);puts("");
        printf("%-3d(fail:%-3d,len=%-2d):%s\n",x,this->len[x],fail[x],a);
        REP(i,26){
            if (next[x][i]){
                a[len]=i+'a';
                dfs(next[x][i],len+1);
                a[len]=0;
            }
        }
    }
}sam;
int n,m,T;
int i,j,k;
char a[maxn];
int main(){
    scanf("%d%d",&n,&k);
    sam.init();
    FOR(i,1,n){
        scanf("%s",a);
        sam.add(a,i);
    }sam.solve(k);
//    sam.dfs();sam.print();
    FOR(i,1,n) printf("%I64d ",sam.Ans[i]);
}
/*
*/

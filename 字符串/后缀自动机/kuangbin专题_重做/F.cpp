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
const LL maxn=4e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct SAM{
    //这里的len不可以直接使用~ 原因是这里的len指的是原串len
    //fail过后,len是可以直接使用的~ (会fail到确定的节点上)
    //这个fail的含义是说后缀相同,向前拓展的val
    //反向不为拓扑序!注意自己进行拓扑排序
    //更新时注意len的限制!(因为更新时可能根本没有考虑前缀len)
    //注意nq在更新时更新时val和q是相等的,也就是说,维护值时nq要完全和q一样
    //query时在末尾加个0可以去掉很多的判断!
    int next[maxn][27],fail[maxn],len[maxn];
    bool deleted[maxn];
    int cnt,last;
    int End,L,lid[maxn];
    int id[maxn],Pre[maxn],Last[maxn];
    void init(){
        cnt=last=0;fail[0]=-1;len[0]=0;L=End=0;Last[0]=0;
        memset(next[0],0,sizeof(next[0]));
    }
    void add(int c){
        int np=++cnt,p=last;
        deleted[np]=0;Pre[cnt]=End;End=cnt;//linked-list
        L++;lid[np]=L;id[np]=cnt;Last[cnt]=np;
        memset(next[np],0,sizeof(next[np]));
        len[np]=len[p]+1;
        for (;p!=-1&&(!next[p][c]||deleted[id[next[p][c]]]);p=fail[p]) next[p][c]=np;
        if (p==-1) fail[np]=0;
        else {
            int q=next[p][c];
            if (len[p]+1==len[q]) fail[np]=q;
            else{
                int nq=++cnt;len[nq]=len[p]+1;
                memcpy(next[nq],next[q],sizeof(next[q]));
                id[nq]=id[q];deleted[nq]=0;lid[nq]=lid[q];
                fail[nq]=fail[q];
                fail[np]=fail[q]=nq;
                for (;p!=-1&&next[p][c]==q;p=fail[p]) next[p][c]=nq;
            }
        }
        last=np;
    }
    void del(int len){
        while (len--) {
            deleted[End]=1,End=Pre[End];
            L--;//printf("del %d:%d\n",End,id[End]);
        }last=Last[End];
    }
    int query(int len){
        int p=0,k;
        add(0);
        REP(k,len){
            int i;
            REP(i,27){
                if (i==0&&k==0) continue;
                if (next[p][i]&&!deleted[id[next[p][i]]]) break;
            }if (i==27) break;
            p=next[p][i];
//            printf("id %d %d\n",p,id[p]);
        }
//        printf("lid[%d]=%d ; k=%d\n ",p,lid[p],k);
        del(1);
        return lid[p]-k+1;
    }
    char a[maxn];
    void dfs(int x=0,int len=0){
        int i;
        printf("%d %d %d ;",End,cnt,L);
        printf("%-3d(fail:%-3d):%s\n",x,fail[x],a);
        REP(i,26){
            if (next[x][i]){
                a[len]=i+'a';
                dfs(next[x][i],len+1);
                a[len]=0;
            }
        }
    }
}sam;

int n,m;
int i,j,k;
char a[maxn];
int main(){
    while (~scanf("%s",a)){
        n=strlen(a);
        sam.init();
        REP(i,n) sam.add(a[i]-'a'+1);
//        sam.dfs();
        int q;
        scanf("%d",&q);
        while (q--){
            int op;
            scanf("%d",&op);
            if (op==1){
                scanf("%s",&a);
                int n=strlen(a);
                REP(i,n) sam.add(a[i]-'a'+1);
            }else if (op==2){
                int len;
                scanf("%d",&len);
                printf("%d\n",sam.query(len));
            }else if (op==3){
                int len;
                scanf("%d",&len);
                sam.del(len);
            }
        }
    }
}
/*
*/

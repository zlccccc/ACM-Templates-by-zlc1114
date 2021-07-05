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
    //�����len������ֱ��ʹ��~ ԭ���������lenָ����ԭ��len
    //fail����,len�ǿ���ֱ��ʹ�õ�~ (��fail��ȷ���Ľڵ���)
    //���fail�ĺ�����˵��׺��ͬ,��ǰ��չ��val
    //����Ϊ������!ע���Լ�������������
    //����ʱע��len������!(��Ϊ����ʱ���ܸ���û�п���ǰ׺len)
    //ע��nq�ڸ���ʱ����ʱval��q����ȵ�,Ҳ����˵,ά��ֵʱnqҪ��ȫ��qһ��
    //queryʱ��ĩβ�Ӹ�0����ȥ���ܶ���ж�!
    //ÿ������λ�ý�����ʱ��ͱ�������~ Ҫ�����е��鷳��
    int next[maxn][26],fail[maxn],len[maxn];
    int L[maxn],R[maxn];
    int cnt,last;
    void init(){
        cnt=last=0;fail[0]=-1;len[0]=0;
        memset(next[0],0,sizeof(next[0]));
    }
    void add(int c){
        int np=++cnt,p=last;
        memset(next[np],0,sizeof(next[np]));
        len[np]=len[p]+1;L[np]=R[np]=len[p]+1;
        for (;p!=-1&&!next[p][c];p=fail[p]) next[p][c]=np;
        if (p==-1) fail[np]=0;
        else {
            int q=next[p][c];
            if (len[p]+1==len[q]) fail[np]=q;
            else{
                int nq=++cnt;len[nq]=len[p]+1;
                memcpy(next[nq],next[q],sizeof(next[q]));
                fail[nq]=fail[q];L[nq]=R[nq]=len[q];
                fail[np]=fail[q]=nq;
                for (;p!=-1&&next[p][c]==q;p=fail[p]) next[p][c]=nq;
            }
        }
        last=np;
    }
    char a[maxn];
    void dfs(int x=0,int len=0){
        int i;
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

int n,m,T;
int i,j,k;
char a[maxn];
int S[maxn],Q[maxn];
int main(){
    scanf("%d",&T);
    while (~scanf("%s",a)&&a[0]!='#'){
        n=strlen(a);
        sam.init();
        REP(i,n) sam.add(a[i]-'a');
        FOR(i,1,n) S[i]=0;
        FOR(i,1,sam.cnt) S[sam.len[i]]++;
        FOR(i,1,n) S[i]+=S[i-1];
        FOR(i,1,sam.cnt) Q[S[sam.len[i]]--]=i;
        LL ans=0;
        rFOR(i,1,sam.cnt){
            sam.L[sam.fail[Q[i]]]=min(sam.L[sam.fail[Q[i]]],sam.L[Q[i]]);
            sam.R[sam.fail[Q[i]]]=max(sam.R[sam.fail[Q[i]]],sam.R[Q[i]]);
            int l=sam.len[sam.fail[Q[i]]],r=sam.len[Q[i]],m=sam.R[Q[i]]-sam.L[Q[i]];
            ans+=min(r,m)-min(l,m);
        }
//        sam.dfs();
//        FOR(i,1,sam.cnt) printf("%d",sam.L[i]);puts("<- L");
//        FOR(i,1,sam.cnt) printf("%d",sam.R[i]);puts("<- R");
//        FOR(i,1,sam.cnt) printf("%d",sam.len[i]);puts("<- len");
//        FOR(i,1,sam.cnt) printf("%d",sam.fail[i]);puts("<- fail");
//        FOR(i,1,sam.cnt) printf("%d",sam.len[sam.fail[i]]);puts("<- fail len");
        printf("%d\n",ans);
    }
}
/*
*/

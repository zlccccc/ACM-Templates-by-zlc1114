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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

//�����len������ֱ��ʹ��~ ԭ���������lenָ����ԭ��len
//fail����,len�ǿ���ֱ��ʹ�õ�~ (��fail��ȷ���Ľڵ���)
//���fail�ĺ�����˵��׺��ͬ,��ǰ��չ��val(һ��һ����չlen����)
//sam����Ϊ������!ע���Լ�������������
//����ʱע��len������!(��Ϊ����ʱ���ܸ���û�п���ǰ׺len)
//ע��nq�ڸ���ʱ����ʱval��q����ȵ�,Ҳ����˵,ά��ֵʱnqҪ��ȫ��qһ��
//sum{len[x]-len[fail[x]]}=��ͬ������,ÿ��������fail->this��len
//ÿ������λ�ý�����ʱ��ͱ�������~ Ҫ�����е��鷳��
//���Ƴ���������ڵ��ڼ������ʱ���������~
//Ҳ����˵������ͬ������ʱ,���Ƴ�����ֻ�Ǹ�����Ľڵ�
//queryʱ��ĩβ�Ӹ�0����ȥ���ܶ���ж�!
//�ӿ��ַ�ʱע��len,���len����������:����topo�Ŵ�,����add����
//�ӵĲ���root,���Ǹ����ַ�,dfs�Ļ�ֻ��dfsһ����!�Ӻ���ǰ���ƿ���
struct SAM{
    int next[maxn][26],fail[maxn],len[maxn];
    int cnt,last;
    void init(){
        cnt=last=0;fail[0]=-1;len[0]=0;
        memset(next[0],0,sizeof(next[0]));
    }int CNT[maxn];bool OK[maxn];
    void addempty(){//�Ӹ��ָ���
        int np=++cnt;last=np;len[np]=1;fail[np]=0;
        memset(next[np],0,sizeof(next[np]));
    }
    void add(int c,bool mark){
        int np=++cnt,p=last;
        memset(next[np],0,sizeof(next[np]));
        len[np]=len[p]+1;
        CNT[np]=mark;OK[np]=!mark;
        for (;p!=-1&&!next[p][c];p=fail[p]) next[p][c]=np;
        if (p==-1) fail[np]=0;
        else {
            int q=next[p][c];
            if (len[p]+1==len[q]) fail[np]=q;
            else{
                int nq=++cnt;len[nq]=len[p]+1;
                memcpy(next[nq],next[q],sizeof(next[q]));
                fail[nq]=fail[q];
                fail[np]=fail[q]=nq;
                for (;p!=-1&&next[p][c]==q;p=fail[p]) next[p][c]=nq;
                OK[nq]=OK[q];CNT[nq]=0;
            }
        }
        last=np;
    }
    int S[maxn],Q[maxn];//Q:id
    void solve(int l,int r){
        int i;
        FOR(i,1,cnt) S[i]=0;
        FOR(i,1,cnt) S[len[i]]++;
        FOR(i,1,cnt) S[i]+=S[i-1];
        FOR(i,1,cnt) Q[S[len[i]]--]=i;
        rFOR(i,1,cnt) CNT[fail[Q[i]]]+=CNT[Q[i]];
        FOR(i,1,cnt) if (CNT[i]<l||r<CNT[i]) OK[i]=0;
        FOR(i,1,cnt) CNT[i]=0;
    }LL Solve(){
        int i;LL ret=0;
        FOR(i,1,cnt) if (OK[i]) ret+=len[i]-len[fail[i]];
        return ret;
    }
    char a[maxn];
    void dfs(int x=0,int len=0){
        int i;
        printf("%-3d %-3d ",CNT[x],OK[x]);
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
int main(){
    scanf("%s",a);
    n=strlen(a);sam.init();
    REP(i,n) sam.add(a[i]-'a',0);
    scanf("%d",&n);
    FOR(i,1,n){
        sam.addempty();
        int l,r;
        scanf("%s%d%d",a,&l,&r);
        int i,n=strlen(a);
        REP(i,n) sam.add(a[i]-'a',1);
        sam.solve(l,r);
//        sam.dfs();
    }printf("%I64d\n",sam.Solve());
}
/*
ppppppppppp
1
pppppppppppp 2 4
*/

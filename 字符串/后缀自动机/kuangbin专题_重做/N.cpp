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
const LL maxn=2e6+7;
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
//�������һ�����Ͻ�,��ôֱ�Ӽ�������len���Ǵ��!һ��ע��!
struct SAM{
    int next[maxn][27],fail[maxn],len[maxn];
    int cnt,last;
    void init(){
        cnt=last=0;fail[0]=-1;len[0]=0;
        memset(next[0],0,sizeof(next[0]));
    }
    int CNT[maxn],num[maxn];
    void add(int c){
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
                fail[nq]=fail[q];num[nq]=num[q];
                fail[np]=fail[q]=nq;
                for (;p!=-1&&next[p][c]==q;p=fail[p]) next[p][c]=nq;
            }
        }
        last=np;
        CNT[last]++;
    }
    bool NOT[maxn];
    int S[maxn],Q[maxn];
    int solve(){
        int i,j;
        FOR(i,0,cnt) S[i]=0;
        FOR(i,1,cnt) S[len[i]]++;
        FOR(i,1,cnt) S[i]+=S[i-1];
        FOR(i,1,cnt) Q[S[len[i]]--]=i;
        rFOR(i,1,cnt) CNT[fail[Q[i]]]+=CNT[Q[i]];
        FOR(i,1,cnt) num[i]+=(CNT[i]==1);
//        dfs();
        FOR(i,1,cnt) CNT[i]=0;
    }
    int Solve(int k){
        int ret=INF,i;
        FOR(i,1,cnt)
            if (num[i]==k)
                ret=min(ret,len[fail[i]]+1);
        if (ret==INF) return -1;
        return ret;
    }
    void print(){
    }
    char a[maxn];
    void dfs(int x=0,int len=0){
        int i;
        printf("CNT=%3d  num=%3d  ",CNT[x],num[x]);
        printf("%-3d(fail:%-3d,len=%-2d):%s\n",x,fail[x],this->len[x],a);
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
    sam.init();n=strlen(a);
    REP(i,n) sam.add(a[i]-'a');
    sam.solve();
    sam.add(26);
    scanf("%s",a);
    n=strlen(a);
    REP(i,n) sam.add(a[i]-'a');
    sam.solve();
    printf("%d\n",sam.Solve(2));
}
/*
*/

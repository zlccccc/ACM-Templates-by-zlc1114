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

// 1����:������k���Ӵ��г��ֵ��Ӵ�����
// 2����:sigma{ѭ����ƥ��cnt}

// �����len������ֱ��ʹ��~ ԭ���������lenָ����ԭ��len
// fail����,len�ǿ���ֱ��ʹ�õ�~ (��fail��ȷ���Ľڵ���)
// ���fail�ĺ�����˵��׺��ͬ,��ǰ��չ��val(һ��һ����չlen����)
// sam����Ϊ������!ע���Լ�������������
// ����ʱע��len������!(��Ϊ����ʱ���ܸ���û�п���ǰ׺len)
// ע��nq�ڸ���ʱ����ʱval��q����ȵ�,Ҳ����˵,ά��ֵʱnqҪ��ȫ��qһ��
// sum{len[x]-len[fail[x]]}=��ͬ������,ÿ��������fail->this��len
// ÿ������λ�ý�����ʱ��ͱ�������~ Ҫ�����е��鷳��
// ���Ƴ���������ڵ��ڼ������ʱ���������~
// Ҳ����˵������ͬ������ʱ,���Ƴ�����ֻ�Ǹ�����Ľڵ�
// queryʱ��ĩβ�Ӹ�0����ȥ���ܶ���ж�!
// �ӿ��ַ�ʱע��len,���len����������:����topo�Ŵ�,����add����
// �ӵĲ���root,���Ǹ����ַ�,dfs�Ļ�ֻ��dfsһ����!�Ӻ���ǰ���ƿ���
// �������һ�����Ͻ�,��ôֱ�Ӽ�������len���Ǵ��!һ��ע��!
// ע�⿴�Ӵ�ʱ���ظ�~
// С����:����ÿ���ڵ��Ӧ��len��һ����,�����Ҫ��l->r��Ӧ�����Ա������ҵ���Ӧ�Ĵ�
// ��fail����׺��ʱ,ѹ��·����һ��λ��Ϊpos[i]-len[fail[i]]
// ע��һ����:���������ǲ����ܱ�֤len[fail]!=len��
// ֻ��bfs trie���Ա�֤,���������а�fail��������׺��
// dfs trie��ʱ�临�Ӷ���trieҶ�����Ⱥ�=_=!֤��..ֱ�ӵ����
// ֻ��bfs���ȶ��ı�֤���Ӷ�,���Ǻ���û����������
struct SAM{
    int next[maxn][26],fail[maxn],len[maxn];
    int cnt,last;
    void init(){
        cnt=last=0;fail[0]=-1;len[0]=0;
        memset(next[0],0,sizeof(next[0]));
    }
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
                fail[nq]=fail[q];
                fail[np]=fail[q]=nq;
                for (;p!=-1&&next[p][c]==q;p=fail[p]) next[p][c]=nq;
            }
        }
        last=np;
    }
    // 1:trie�Ͻ���,����ʽ�ϲ�set
    map<int,int> have[maxn];
    int Next[maxn][26],Last[maxn],tot;
    void add(char a[],int id){
        int n=strlen(a),i,p=0;last=0;
        REP(i,n) {
            int c=a[i]-'a';
            if (Next[p][c]) p=Next[p][c],last=Last[p];
            else add(c),Last[p=Next[p][c]=++tot]=last;
            have[last][id]++;
        }
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
        int i;
        FOR(i,0,cnt) edge[i].clear();
        FOR(i,1,cnt) edge[fail[i]].push_back(i);
        DFS(0,k);
    }
    // 2:��queryǰ������cnt[np]++����fail����
    set<int> A;int CNT[maxn];
    LL query(char a[]){
        int i;LL ret=0;
        int n=strlen(a),p=0,l=0;A.clear();
        REP(i,n+n-1){
            int c=a[i%n]-'a';
            if (next[p][c]) l++,p=next[p][c];
            else {
                while (p!=-1&&!next[p][c]) p=fail[p];
                if (p==-1) p=l=0;
                else l=len[p]+1,p=next[p][c];
            }while (len[fail[p]]>=n) p=fail[p],l=len[p];
            if (l>=n){
                if (A.count(p)) continue;
                A.insert(p);
                ret+=CNT[p];
            }
            // if (l>=n) printf("i=%2d ret+id(%2d); l=%2d; +=%d\n",i,p,l,CNT[p]);
        }return ret;
    }

    void print(){
        int i;
        FOR(i,1,cnt) {
        }
    }
    char a[maxn];
    void dfs(int x=0,int len=0){
        int i;
        for (auto v:have[x])
            printf("%2d(%2d) ",v.first,v.second);
        puts("");
        // printf("%-3d(fail:%-3d,len=%-2d):%s\n",x,fail[x],this->len[x],a);
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
    // sam.dfs();sam.print();
    FOR(i,1,n) printf("%I64d ",sam.Ans[i]);
}
/*
*/

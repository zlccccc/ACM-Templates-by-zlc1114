#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=5e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}

int nxt[maxn][26],pre[maxn],len[maxn];
//pre为上一个可以接受的位置 (树形结构,前缀相等,类似AC自动机fail指针),这样可以去除很多无用的边 
int cnt,last;
void add(int c){
	int np=++cnt,p=last;
	len[np]=len[p]+1;
	for (;p&&!nxt[p][c];p=pre[p]) nxt[p][c]=np;//边表示字符 
	if (!p) pre[np]=1;
	else{
		int q=nxt[p][c];
		if (len[p]+1==len[q]) pre[np]=q;
		else{
			int nq=++cnt;len[nq]=len[p]+1;//new一个新节点(松弛(copy一遍))来保证结构稳定 
			memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
			pre[nq]=pre[q];
			pre[np]=pre[q]=nq;
			for (;p&&nxt[p][c]==q;p=pre[p]) nxt[p][c]=nq;
		}
	}
	last=np;
}
//void dfs(int x,int len){
//	int i;
//	printf("%s\n",a);
//	REP(i,27){
//		if (nxt[x][i]){
//			a[len]=i+'a';
//			dfs(nxt[x][i],len+1);
//			a[len]=0;
//		}
//	}
//}
char a[maxn],b[maxn];
int n,m;
int i,j,k;
int ans,now,nowlen;
int main()
{
	scanf("%s%s",a,b);
	n=strlen(a);
	m=strlen(b);
//	printf("%d",n);
	last=++cnt;//1开始 //注意 
	REP(i,n) add(a[i]-'a');
	now=1;
	REP(i,m){
		while (now&&!nxt[now][b[i]-'a']) now=pre[now],nowlen=len[now];
		if (!now) now=1,nowlen=0;
		if (nxt[now][b[i]-'a']){
			now=nxt[now][b[i]-'a'];
			nowlen++;
		}
		ans=max(ans,nowlen);
	}
	printf("%d\n",ans);
}
/*
*/

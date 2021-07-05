#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
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
const LL MOD=1e9+7;
const LL maxn=5e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%MOD) ret=1ll*ret*a%MOD;return ret;}


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
			int nq=++cnt;len[nq]=len[p]+1;//new一个新节点(松弛(copy一遍))来保证结构稳定(或len相等) 
			memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
			pre[nq]=pre[q];
			pre[np]=pre[q]=nq;
			for (;p&&nxt[p][c]==q;p=pre[p]) nxt[p][c]=nq;
		}
	}
	last=np;
}
char a[maxn];
int n,m,Q;
int i,j,k;
int S[maxn],K[maxn];
int F[maxn];
int now;
int main()
{
	scanf("%s",a);
	n=strlen(a);
	last=++cnt;//1开始 
	REP(i,n) add(a[i]-'a');
	now=1;
	REP(i,n){
		now=nxt[now][a[i]-'a'];
		F[now]++;
	}
	FOR(i,1,cnt) S[len[i]]++;
	FOR(i,1,n) S[i]+=S[i-1];
	FOR(i,1,cnt) K[S[len[i]]--]=i;//hash
	rFOR(i,1,cnt){
		F[K[i]]=1; 
		REP(j,26) F[K[i]]+=F[nxt[K[i]][j]];//有的没连pre 
	}
	scanf("%d",&Q);
	while (Q--){
		scanf("%d",&k);
		now=1;
		while (k){
			if (k==0) break;
			i=0;
			while (F[nxt[now][i]]<k){
				k-=F[nxt[now][i]];
				i++;
			}
			printf("%c",i+'a');
			now=nxt[now][i];
			k--;
		}
		puts("");
	}
}
/*
*/

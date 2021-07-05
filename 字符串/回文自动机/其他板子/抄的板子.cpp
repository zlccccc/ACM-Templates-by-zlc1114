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
const LL maxn=200007;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}

struct Ptree{
	int next[maxn][27];
	int fail[maxn];
	int cnt[maxn];//真正个数
//	int num[maxn];//右端点结尾的maxnum
	int len[maxn];//长度
	int S[maxn];//字符
	int last;//上一个字符节点
	int n,tot;//n表示字符位置
	int newnode(int l){
		memset(next[tot],0,sizeof(next[tot]));
		cnt[tot]=0;
//		num[tot]=0;
		len[tot]=l;//不是1...
		return tot++;
	}
	void init(){
		tot=0;
		newnode(0);
		newnode(-1);
		last=n=0;
		S[n]=-1;//减少特判
		fail[0]=1;
	}
	int getfail(int x){
		while(S[n-len[x]-1]!=S[n]) x=fail[x];
		return x;
	}
	void add(int c){
		c-='a';
		S[++n]=c;
		int cur=getfail(last);
		if (!next[cur][c]){
			int now=newnode(len[cur]+2);
			fail[now]=next[getfail(fail[cur])][c];
			next[cur][c]=now;
//			num[now]=num[fail[now]]+1;
		}
		last=next[cur][c];
		cnt[last]++;
	}
	void count(){//count完才对
		int i;
		rREP(i,tot) cnt[fail[i]]+=cnt[i];
	}
}T1,T2;
LL ans;
void dfs(int x,int y){
	int i;
	REP(i,27){
		int u=T1.next[x][i],v=T2.next[y][i];
		if (u&&v){
			ans+=1ll*T1.cnt[u]*T2.cnt[v];
			dfs(u,v);
		}
	}
}
char a[maxn],b[maxn];
void solve(){
	scanf("%s%s",a,b);
	int len1=strlen(a),len2=strlen(b);
	int i,j;
	T1.init();T2.init();
	REP(i,len1) T1.add(a[i]);
	REP(j,len2) T2.add(b[j]);
	T1.count();
	T2.count();
	dfs(0,0);
	dfs(1,1);
}
int main(){
	int T,x=0;
	scanf("%d",&T);
	while (T--) {
		ans=0;
		solve();
		printf("Case #%d: %lld\n",++x,ans);
	}
}
/*
*/

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
#include <bitset>
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
const LL M=998244353;
const LL maxn=10e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M; return ret;}

//替罪羊树...这道题卡splay,treap
//题意：加字符，减字符，query子串个数
//做法：建后缀自动机+LCT；right集个数或者后缀顺序建平衡树然后树上query
//https://www.nowcoder.net/acm/contest/59/C
const double alpha=0.7;//奇了怪了..为啥0.7-0.8改改还T的
struct sat {
	struct node {
		int son[2];
		node() {son[0]=son[1]=0;}
	} T[maxn];
	ULL rank[maxn]; int size[maxn],val[maxn];
	int pre[maxn]; char c[maxn];
	int cnt,root,last;
	inline bool cmp(int x,int y) {
		return c[x]<c[y]||
		       (c[x]==c[y]&&rank[pre[x]]<rank[pre[y]]);
	}
	int tot;
	int f[maxn];
	void getrank(int x) {
		if (T[x].son[0]) getrank(T[x].son[0]);
		f[++tot]=x;//不能加if (val[x]);原因我也不知道
		if (T[x].son[1]) getrank(T[x].son[1]);
	}
	void rerank(int &x,int l,int r,ULL L,ULL R) {
		x=0; if (l>r) return;
		ULL mid=(L+R)/2; int m=(l+r)/2;
		x=f[m]; rank[x]=mid;
		rerank(T[x].son[0],l,m-1,L,mid-1);
		rerank(T[x].son[1],m+1,r,mid+1,R);
		size[x]=val[x]+size[T[x].son[0]]+size[T[x].son[1]];
	}
	void rebuild(int &x,ULL l,ULL r) {
		if (!x) return;
		tot=0; getrank(x);
		rerank(x,1,tot,l,r);
	}
	void ins(int &x,ULL l,ULL r) {
		ULL mid=(l+r)/2;
		if (!x) {x=cnt; rank[x]=mid; return;}
		size[x]++;
		int p=cmp(x,cnt);
		int &son=T[x].son[p];
		if (p==0) ins(son,l,mid-1);
		else ins(son,mid+1,r);
		if (max(size[T[x].son[0]],size[T[x].son[1]])>=
		        size[x]*alpha) rebuild(x,l,r);
	}
	void insert(char s[]) {
		int len=strlen(s),i;
		REP(i,len) {
			c[++cnt]=s[i]; size[cnt]=1; val[cnt]=1;
			pre[cnt]=last; last=cnt;
			ins(root,1ull,1ull<<63);
		}
	}
	bool cmp(int k,char s[],int len) {
		for (int i=0; i<len; i++,k=pre[k]) {
			if (!k) return 1;
			if (s[i]!=c[k]) return c[k]<s[i];
		} return 0;
	}
	int query(char s[],int len) {
		int ret=0;
		for (int now=root; now;) {
			if (!cmp(now,s,len)) now=T[now].son[0];
			else {
				ret+=val[now]+size[T[now].son[0]],
				     now=T[now].son[1];
			}
		} return ret;
	}
	int query(char s[]) {
		int len=strlen(s);
		reverse(s,s+len); s[len]='Z'+1; s[len+1]=0;
		return query(s,len+1)-query(s,len);
	}
	void del(int k) {
		int now,p;
		while (k--) {
			for (now=root; now!=last;) {
				size[now]--;
				p=rank[last]>rank[now];
				now=T[now].son[p];
			} val[last]=0; size[last]--;
			last=pre[last];
		}
	}
} SAT;
int mask;
void decodeWithMask(char s[],int mask) {
	int len=strlen(s),j;
	REP(j,len) {
		mask=(mask*131+j)%len;
		char t=s[j];
		s[j]=s[mask];
		s[mask]=t;
	}
}
int n,m,i;
char a[3000007],op[20];
int main() {
	scanf("%d",&n);
	scanf("%s",a);
	SAT.insert(a);
	while (n--) {
		scanf("%s",op);
		if (op[0]=='Q') {
			scanf("%s",a);
			decodeWithMask(a,mask);
			int ans=SAT.query(a);
			printf("%d\n",ans); mask^=ans;
		} else if (op[0]=='D') {
			scanf("%d",&i);
			SAT.del(i);
		} else {
			scanf("%s",a);
			decodeWithMask(a,mask);
			SAT.insert(a);
		}
	}
	return 0;
}
/*
*/

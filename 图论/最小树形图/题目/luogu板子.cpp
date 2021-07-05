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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M; return ret;}

namespace O {
	const int maxn=107;
	const int maxm=10007;
	struct Edge {//id,pre!=0
		int u,v,len,id,pre;//id->usedID(new)
		Edge(int _u=0,int _v=0,int _len=0,int _id=0):
			u(_u),v(_v),len(_len),id(_id),pre(0) {}
	} edge[maxm]; int etot;
	void init() {etot=0;}
	void addedge(int u,int v,int len,int id) {
		edge[etot++]=Edge(u,v,len,id);
	}
	//id:circle_id(father);
	inline int getfa(int fa[],int x) {
		if (fa[x]==x) return x;
		return fa[x]=getfa(fa,fa[x]);
	}
	//used:ini_edge
	int used[maxm];
	//top,id:father and ancestor
	int top[maxn*2],id[maxn*2];
	//len:correction(circle)
	//pre:nodepre; eid:Used_id
	int pre[maxn*2],len[maxn*2],eid[maxn*2];
	int solve(int root,int n) {
		int ret=0,i,lastnid=n;
		FOR(i,1,n) id[i]=top[i]=i,len[i]=INF;
		REP(i,etot) { //initialize
			Edge &e=edge[i];
			if (e.u!=e.v&&e.len<len[e.v]) {
				len[e.v]=e.len,eid[e.v]=i;
				pre[e.v]=e.u;
			}
		}
		FOR(i,1,lastnid) {
			if (i==root) continue;
			if (len[i]==INF) return -1;
			int f=getfa(top,pre[i]);
			Edge &e=edge[eid[i]];//choose
			if (e.pre) used[e.pre]--;//choose
			used[e.id]++; ret+=len[i];//choose
			if (f==i) {//circle
				int k; ++lastnid; len[lastnid]=INF;
				top[lastnid]=id[lastnid]=lastnid;
				for (int x=pre[i]; ;x=getfa(id,pre[x])) {
					//use and delete
					REP(k,etot) { // update edges
						Edge &e=edge[k];
						if (k==eid[x]) e.len=INF;//remove
						else if (getfa(id,e.v)==x)
							e.len-=len[x],e.pre=edge[eid[x]].id;
					}
					id[x]=top[x]=lastnid;
					if (x==i) break;
				}
				//update edges
				REP(k,etot) {
					if (k==eid[i]) continue;
					Edge &ne=edge[k];
					if (getfa(id,ne.v)==lastnid) {
						ne.u=getfa(id,ne.u);
						ne.v=getfa(id,ne.v);
						//update_newedge
						if (ne.u!=ne.v&&ne.len<len[ne.v]) {
							len[ne.v]=ne.len,eid[ne.v]=k;
							pre[ne.v]=ne.u;
						}
					}
				}
			} else top[getfa(top,i)]=pre[i];//getfa=getid
		}
		return ret;
	}
}
int root;
int init[maxn];
int main() {
	// freopen("input.txt","r",stdin);
	// freopen("output.txt","w",stdout);
	int n,m,i;
	scanf("%d%d%d",&n,&m,&root);
	O::init();
	FOR(i,1,m) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		init[i]=w;
		O::addedge(u,v,w,i);
	}
	int ans=O::solve(root,n);
	printf("%d\n",ans);
}
/*
*/

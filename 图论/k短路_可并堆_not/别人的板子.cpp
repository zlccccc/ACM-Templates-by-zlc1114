#include<map>
#include<set>
#include<deque>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<vector>
#include<string>
#include<bitset>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<climits>
#include<complex>
#include<iostream>
#include<algorithm>
using namespace std;

const int maxn = 110000;
const int maxp = 8100;

struct edge {
	int x,y,c,next,f;
	bool v,flag;
} a[maxn]; int len,first[maxp];
void ins(int x,int y,int c) {
	len++;
	a[len].x = x; a[len].y = y; a[len].c = c;
	a[len].next = first[x]; first[x] = len;
	a[len].v = false;
}

struct edgef {
	int y,c,next;
} af[maxn]; int lenf,firstf[maxp];
bool vl[maxp];
void insf(int x,int y,int c) {
	lenf++;
	af[lenf].y = y; af[lenf].c = c;
	af[lenf].next = firstf[x]; firstf[x] = lenf;
}

struct node {
	int lc,rc,dist,c,y;
} tr[maxp*100]; int total;

int newnode(int c,int y) {
	total++;
	tr[total].lc = tr[total].rc = 0;
	tr[total].dist = 0;
	tr[total].c = c;
	tr[total].y = y;
	return total;
}
int merge(int x,int y) {
	if (!x || !y) return x|y;
	if (tr[x].c > tr[y].c) swap(x,y);
	int ret=++total; tr[ret] = tr[x];
	int k = merge(tr[ret].rc,y);
	if (tr[tr[ret].lc].dist <= tr[k].dist) swap(tr[ret].lc,k);
	tr[ret].rc = k;
	tr[ret].dist = tr[tr[ret].lc].dist+1;
	return ret;
}

int n,m,k;
int st,ed;
int dis[maxp],next_[maxp];

struct fi {
	int x,d;
};
bool operator <(fi x, fi y) {
	return x.d > y.d;
}
priority_queue< fi >Q;

void get_dis() {
	dis[ed] = 0;
	fi tmp;
	tmp.x = ed; tmp.d = 0;
	Q.push(tmp);
	while (!Q.empty()) {
		fi x = Q.top(); Q.pop();
		if (dis[x.x] < x.d) continue;
		for (int k=firstf[x.x]; k; k=af[k].next) {
			int y = af[k].y; vl[y] = true;
			if (dis[y] > x.d+af[k].c) {
				dis[y] = x.d+af[k].c;
				tmp.x = y; tmp.d = dis[y];
				Q.push(tmp);
			}
		}
	}
}

int sta[maxp],tp;
int root[maxp];
void solve(int x) {
	if (x == ed) {
		for (int k=first[x]; k; k=a[k].next) {
			int y = a[k].y;
			if (!a[k].flag) continue;
			if (!a[k].v)
				root[x] = merge(root[x],newnode(a[k].f,a[k].y));
		}
		return ;
	}
	for (int k=first[x]; k; k=a[k].next) {
		int y = a[k].y;
		if (!a[k].flag) continue;
		if (!a[k].v)
			root[x] = merge(root[x],newnode(a[k].f,a[k].y));
		else root[x] = merge(root[x],root[y]);
	}
}

struct G {
	int u,x,d;
};
bool operator <(G x,G y) {
	return x.d > y.d;
};
priority_queue< G >q;

int main() {
	len = 0; memset(first,0,sizeof first);
	lenf = 0; memset(firstf,0,sizeof firstf);

	int x,y,c;

	scanf("%d%d",&n,&m);
	for (int i=1; i<=m; i++) {
		scanf("%d%d%d",&x,&y,&c);
		ins(x,y,c); a[len].flag = true;
		insf(y,x,c);
	}
	scanf("%d%d%d",&st,&ed,&k);
	if (st == ed) k++;

	for (int i=1; i<=n; i++) dis[i] = INT_MAX,vl[i] = false;
	get_dis();
	if (k == 1) {
		if (vl[st])
			printf("%d\n",dis[st]);
		else printf("-1\n");
		return 0;
	}
	for (int i=1; i<=len; i++) {
		a[i].f = a[i].c - dis[a[i].x]+dis[a[i].y];
		if (dis[a[i].y] == INT_MAX) a[i].flag = false;
	}
	for (int i=1; i<=n; i++) {
		if (i == ed) continue;
		for (int k=first[i]; k; k=a[k].next) {
			y = a[k].y;
			if (!a[k].flag) continue;
			if (dis[i] == dis[y]+a[k].c) {
				a[k].v = true;
				next_[i] = y;
				break;
			}
		}
	}

	memset(root,0,sizeof root);
	total = 0;
	for (int i=1; i<=n; i++)
		if (!root[i]) {
			if (dis[i] == INT_MAX) continue;
			sta[tp=1] = i;
			while (1) {
				x = sta[tp];
				if (x == ed) break;
				if (!root[ next_[ x ] ]) sta[++tp] = next_[x];
				else break;
			}
			while (tp) {
				solve(sta[tp]);
				tp--;
			}
		}

	k-=2;
	G ss;
	ss.u = st; ss.d = tr[root[st]].c; ss.x = root[st];
	q.push(ss);
	while (k--) {
		G tmp = q.top(); q.pop();
		if (tmp.u == 0) {
			printf("-1\n");
			return 0;
		}
		if (tr[tmp.x].lc) {
			G tmp1;
			tmp1.u = tmp.u;
			tmp1.d = -tr[tmp.x].c;
			tmp1.x = merge(tr[tmp.x].lc,tr[tmp.x].rc);
			tmp1.d += tr[tmp1.x].c + tmp.d;
			q.push(tmp1);
		}
		G tmp2;
		tmp2.u = tr[tmp.x].y;
		tmp2.d = tmp.d + tr[root[tmp2.u]].c;
		tmp2.x = root[tmp2.u];
		q.push(tmp2);
	}
	G ans = q.top();
	if (ans.u == 0) {
		printf("-1\n");
		return 0;
	}
	if (vl[st])
		printf("%d\n",dis[st]+ans.d);
	else printf("-1\n");

	return 0;
}
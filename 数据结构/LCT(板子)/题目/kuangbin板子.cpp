//HDU 4010
//��̬ά��һ��ɭ�֣�Ҫ��֧��һ�²���:
//link(a,b) : ���a,b����ͬһ�������У���ͨ����a,b֮�����ߵķ�ʽ����������������
//cut(a,b) : ���a,b��ͬһ�������У���a!=b,��a��Ϊ��������ĸ��Ժ��ж�b���丸�׽�� ������
//ADD(a,b,w): ���a,b��ͬһ�������У���a,b֮��·�������е�ĵ�Ȩ����w
//query(a,b): ���a,b��ͬһ�������У�����a,b֮��·���ϵ�Ȩ�����ֵ
#include <iostream>
using namespace std;
const int MAXN = 300010;
int ch[MAXN][2],pre[MAXN],key[MAXN];
int add[MAXN],rev[MAXN],Max[MAXN];
bool rt[MAXN];

void Update_Add(int r,int d)
{
	if(!r)return;
	key[r] += d;
	add[r] += d;
	Max[r] += d;
}
void Update_Rev(int r)
{
	if(!r)return;
	swap(ch[r][0],ch[r][1]);
	rev[r] ^= 1;
}
void push_down(int r)
{
	printf("Pushdown %d %d\n",r,add[r]);
	if(add[r])
	{
		Update_Add(ch[r][0],add[r]);
		Update_Add(ch[r][1],add[r]);
		add[r] = 0;
	}
	if(rev[r])
	{
		Update_Rev(ch[r][0]);
		Update_Rev(ch[r][1]);
		rev[r] = 0;
	}
}
void push_up(int r)
{
	Max[r] = max(max(Max[ch[r][0]],Max[ch[r][1]]),key[r]);
	printf("PUSHUP:%d %d\n",r,Max[r]);
}
void Rotate(int x)
{
	int y = pre[x], kind = ch[y][1]==x;
		printf("  ROTATE,x=%d,kind=%d\n",x,kind^1);//ǡ���෴=_= 
	ch[y][kind] = ch[x][!kind];
	pre[ch[y][kind]] = y;
	pre[x] = pre[y];
	pre[y] = x;
	ch[x][!kind] = y;
	if(rt[y])
		rt[y] = false, rt[x] = true;
	else
		ch[pre[x]][ch[pre[x]][1]==y] = x;
	push_up(y);
}
//P�����Ƚ�����㵽r��·�������еĽ��ı�����·�
void P(int r)
{
	if(!rt[r])P(pre[r]);
	push_down(r);
}
void Splay(int r)
{
	P(r);
	while( !rt[r] )
	{
		int f = pre[r], ff = pre[f];
		if(rt[f])
			Rotate(r);
		else if( (ch[ff][1]==f)==(ch[f][1]==r) ) Rotate(f), Rotate(r);


		else
			Rotate(r), Rotate(r);
	}
	push_up(r);
}
int Access(int x)
{
	int y = 0;
	for( ; x ; x = pre[y=x])
	{
		printf("Access:%d %d\n",x,y);
		Splay(x);
		rt[ch[x][1]] = true, rt[ch[x][1]=y] = false;
		push_up(x);
	}
	return y;
}
//�ж��Ƿ���ͬ��(��ʵ��������splay)
bool judge(int u,int v)
{
	while(pre[u]) u = pre[u];
	while(pre[v]) v = pre[v];
	return u == v;
}
//ʹr��Ϊ�����ڵ����ĸ�
void mroot(int r)
{
	Access(r);
	puts("MakeRoot:Access OK");
	Splay(r);
	puts("MakeRoot:Splay OK");
	Update_Rev(r);
	puts("MakeRoot:Rev OK");
}
//���ú�u��ԭ��u��v��lca,v��ch[u][1]�ֱ����lca��2������
//(ԭ��u��v���ڵ�2������)
void lca(int &u,int &v)
{
	Access(v), v = 0;
	while(u)
	{
		Splay(u);
		if(!pre[u])return;
		rt[ch[u][1]] = true;
		rt[ch[u][1]=v] = false;
		push_up(u);
		u = pre[v = u];
	}
}
void link(int u,int v)
{
	if(judge(u,v))
	{
		puts("-1");
		return;
	}
	mroot(u);
	pre[u] = v;
}
//ʹu��Ϊu�������ĸ�������v�������׵ı߶Ͽ�
void cut(int u,int v)
{
	if(u == v || !judge(u,v))
	{
		puts("-1");
		return;
	}
	mroot(u);
	puts("CUT:MAKEROOT OK");
	Splay(v);
	puts("CUT:Splay OK");
	pre[ch[v][0]] = pre[v];
	pre[v] = 0;
	rt[ch[v][0]] = true;
	ch[v][0] = 0;
	push_up(v);
}
void ADD(int u,int v,int w)
{
	if(!judge(u,v))
	{
		puts("-1");
		return;
	}
	lca(u,v);
	Update_Add(ch[u][1],w);
	Update_Add(v,w);
	key[u] += w;
	push_up(u);
}
void query(int u,int v)
{
	if(!judge(u,v))
	{
		puts("-1");
		return;
	}
//	lca(u,v);
//	printf("%d\n",max(max(Max[v],Max[ch[u][1]]),key[u]));
	mroot(u);
	Access(v);
	Splay(v);
	printf("%d\n",Max[v]);
}

struct Edge
{
	int to,next;
} edge[MAXN*2];
int head[MAXN],tot;
void addedge(int u,int v)
{
	edge[tot].to = v;
	edge[tot].next = head[u];
	head[u] = tot++;
}
void dfs(int u)
{
	for(int i = head[u]; i != -1; i = edge[i].next)
	{
		int v = edge[i].to;
		if(pre[v] != 0)continue;
		pre[v] = u;
		dfs(v);
	}
}

int main()
{
//freopen("in.txt","r",stdin);
//freopen("out.txt","w",stdout);
int n,q,u,v; while(scanf("%d",&n) == 1)
	{
		tot = 0;
		for(int i = 0; i <= n; i++)
		{
			head[i] = -1;
			pre[i] = 0;
			ch[i][0] = ch[i][1] = 0;
			rev[i] = 0;
			add[i] = 0;
			rt[i] = true;
		}
		Max[0] = -2000000000;
		for(int i = 1; i < n; i++)
		{
			scanf("%d%d",&u,&v);
			addedge(u,v);
			addedge(v,u);
		}
		for(int i = 1; i <= n; i++)
		{
			scanf("%d",&key[i]);
			Max[i] = key[i];
		}
		scanf("%d",&q);
		pre[1] = -1;
		dfs(1);
		pre[1] = 0;
		int op;
		while(q--)
		{
			scanf("%d",&op);
			if(op == 1)
			{
				int x,y;
				scanf("%d%d",&x,&y);
				link(x,y);
			}
			else if(op == 2)
			{
				int x,y;
				scanf("%d%d",&x,&y);
				cut(x,y);
			}
			else if(op == 3)
			{
				int w,x,y;
				scanf("%d%d%d",&w,&x,&y);
				ADD(x,y,w);
			}
			else
			{
				int x,y;
				scanf("%d%d",&x,&y);
				query(x,y);
			}
		}
		printf("\n");
	}
	return 0;
}


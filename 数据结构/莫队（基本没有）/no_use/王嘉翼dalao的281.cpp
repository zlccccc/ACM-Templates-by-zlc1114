#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<queue>
#include<vector>
using namespace std;

const int N=100010;
int stk[N],a[N],rmq[N][20],r[N],l[N],Log[N],top,S,n,m,x,y;
long long ans[N],dl[N],dr[N],now;
struct query{
    int l,r,id;
    friend bool operator <(const query &a,const query &b){
        if(a.l/S==b.l/S) return a.r<b.r;
        return a.l/S<b.l/S;
    }
}q[N];

inline void Read(int &x){
    static char c;
    int f=1;
    for(c=getchar();c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
    for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
    x=x*f;
}
int query(int l,int r){
    int tmp=Log[r-l+1];
    if(a[rmq[l][tmp]]<a[rmq[r-(1<<tmp)+1][tmp]])
    return rmq[l][tmp];
    else return rmq[r-(1<<tmp)+1][tmp];
}
void changel(int l,int r,long long k){
    int tmp=query(l,r);
    now+=k*a[tmp]*(r-tmp+1);
    now+=k*(dr[l]-dr[tmp]);
}
void changer(int l,int r,long long k){
    int tmp=query(l,r);
    now+=k*a[tmp]*(tmp-l+1);
    now+=k*(dl[r]-dl[tmp]);
}
void pretreat(){
    for(int i=1;i<=n;i++) Log[i]=(int)log2(i);
    for(int i=1;i<=n;i++){
        while(top&&a[stk[top]]>a[i]) r[stk[top--]]=i;
        l[i]=a[stk[top]]==a[i]?l[stk[top]]:stk[top];
        stk[++top]=i;
    }
    while(top) r[stk[top--]]=n+1;
    for(int i=1;i<=n;i++) dl[i]=dl[l[i]]+1ll*(i-l[i])*a[i];
    for(int i=n;i;i--) dr[i]=dr[r[i]]+1ll*(r[i]-i)*a[i];
    for(int i=1;i<=n;i++) rmq[i][0]=i;
    for(int i=1;(1<<i)<=n;i++)
     for(int j=1;j<=n-(1<<i)+1;j++)
     if(a[rmq[j][i-1]]<a[rmq[j+(1<<(i-1))][i-1]])
     rmq[j][i]=rmq[j][i-1];
     else rmq[j][i]=rmq[j+(1<<(i-1))][i-1];
}
int b[100005];
int main(){
//    Read(n); Read(m);
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&b[i]);
    for(int i=1;i<n;i++)
    {
        a[i]=-abs(b[i]-b[i+1]);
    }
    S=(int)sqrt(n);
//    for(int i=1;i<=n;i++) Read(a[i]);
    pretreat();
    for(int i=1;i<=m;i++){
        Read(q[i].l); Read(q[i].r);
        q[i].r--;
        q[i].id=i;
    }
    sort(q+1,q+1+m);
    x=y=1; now=a[1];
    for(int i=1;i<=m;i++){
        if(q[i].r>y) while(y!=q[i].r) y++,changer(x,y,1);
        if(q[i].l>x) while(x!=q[i].l) changel(x,y,-1),x++;
        if(q[i].l<x) while(x!=q[i].l) x--,changel(x,y,1);
        if(q[i].r<y) while(y!=q[i].r) changer(x,y,-1),y--;
        ans[q[i].id]=now;
    }
    for(int i=1;i<=m;i++) printf("%lld\n",-ans[i]);
    return 0;
}
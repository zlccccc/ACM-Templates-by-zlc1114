#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}

vector<int> v;//学到的hash方法 
int getid(int x){return lower_bound(v.begin(),v.end(),x)-v.begin()+1;}
int root[maxn],a[maxn],cnt;
struct Tnode{
    int left,right,sum;
}T[maxn*40];
void update(int l,int r,int &x,int y,int pos){
    T[++cnt]=T[y];T[cnt].sum++;x=cnt;
    if (l==r) return;
    int mid=(l+r)/2;
    if (mid>=pos) update(l,mid,T[x].left,T[y].left,pos);
    else update(mid+1,r,T[x].right,T[y].right,pos);
}
int query(int l,int r,int x,int y,int k){
    if (l==r) return l;
    int mid=(l+r)/2;
    int sum=T[T[y].left].sum-T[T[x].left].sum;
    if (sum>=k) return query(l,mid,T[x].left,T[y].left,k);
    else return query(mid+1,r,T[x].right,T[y].right,k-sum);
}
int n,m;
int i,j,k,ii;
int main()
{
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",&a[i]),v.push_back(a[i]);
    sort(v.begin(),v.end());v.erase(unique(v.begin(),v.end()),v.end());
    FOR(i,1,n) update(1,n,root[i],root[i-1],getid(a[i]));
    REP(ii,m){
        scanf("%d%d%d",&i,&j,&k);
        printf("%d\n",v[query(1,n,root[i-1],root[j],k)-1]);
    }
    return 0;
}
/*
*/

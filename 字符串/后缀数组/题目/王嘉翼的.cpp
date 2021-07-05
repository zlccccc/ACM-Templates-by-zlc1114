#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <queue>
#include <set>
#include <map>
#include <list>
#include <stack>
#define mp make_pair
typedef long long ll;
typedef unsigned long long ull;
const int MAX=1e6+1000;
const int INF=1e9+5;
using namespace std;

int ttt;


typedef pair<int,int> pii;
int n,k;
int rankk[MAX],lcp[MAX],saa[MAX];
int len;
int tmp[MAX];
int f[MAX];
void getf(string x,int m)
{
    f[0]=f[1]=0;
    for(int i=2,j=0;i<=m;i++)
    {
        while(j&&x[j+1]!=x[i])
            j=f[j];
        if(x[j+1]==x[i])
            j++;
        f[i]=j;
    }
}
int kmp(string x,string y)
{
    getf(x,x.size());
    for(int i=1,j=0;i<=y.size();i++)
    {
        while(j&&x[j+1]!=y[i])
            ttt++,j=f[j];
        if(x[j+1]==y[i])
            j++;ttt++;
        if(j>=x.size()-1)
            return i;
    }
    return 0;
}
int t[MAX],t2[MAX],c[MAX];
void construct_sa1(string s,int *sa,int m)
{
    n=s.length();
    int i;
    int *x=t,*y=t2;
    for(i=0;i<m;i++)
        c[i]=0;
    for(i=0;i<n;i++)
        c[x[i]=(char)s[i]]++;
    for(i=1;i<m;i++)
        c[i]+=c[i-1];
    for(i=n-1;i>=0;i--)
        sa[--c[x[i]]]=i;
    for(int k=1;k<=n;k<<=1)
    {
        int p=0;
        for(i=n-k;i<n;i++)
            y[p++]=i;
        for(i=0;i<n;i++)
            if(sa[i]>=k)
                y[p++]=sa[i]-k;
        for(i=0;i<m;i++)
            c[i]=0;
        for(i=0;i<n;i++)
            c[x[y[i]]]++;
        for(i=0;i<m;i++)
            c[i]+=c[i-1];
        for(i=n-1;i>=0;i--)
            sa[--c[x[y[i]]]]=y[i];
        swap(x,y);
        p=1;x[sa[0]]=0;
        for(i=1;i<n;i++)
            x[sa[i]]=((y[sa[i-1]]==y[sa[i]])&&(y[sa[i-1]+k]==y[sa[i]+k]))?p-1:p++;
        if(p>=n)
            break;
        m=p;
    }
        for(int i=0;i<s.length();++i)
    {
        rankk[i]=x[i]+1;
    }
}
void construct_lcp(string S,int *sa,int *lcp)
{
    int n=S.length();
    for(int i=0;i<=n;++i)rankk[sa[i]]=i;
    int h=0;
    lcp[0]=0;
    for(int i=0;i<n;++i)
    {
        int j=sa[rankk[i]-1];
        if(h>0)--h;
        for(;j+h<n&&i+h<n;++h)
            if(S[j+h]!=S[i+h])
            break;
        lcp[rankk[i]-1]=h;
    }

}
string s,T,C;
string tem;
void solve()
{
    len=C.length();
    getf(" "+C,C.length()+1);
    int s1=s.length();
    s+='\0'+T;
    construct_sa1(s,saa,200);
    construct_lcp(s,saa,lcp);
    int ans=0;
    for(int i=2;i<s.length();++i)
    {
        if((saa[i]<s1)!=(saa[i+1]<s1))
        {
            if(lcp[i]&&lcp[i]>ans)
            {
                ans=lcp[i];
            }
        }
    }
    int an=0;
    for(int i=2;i<s.length();++i)
    {
        if((saa[i]<s1)!=(saa[i+1]<s1))
        {
            if(lcp[i]==ans)
            {
                int now=kmp(" "+C," "+s.substr(saa[i],lcp[i]));
                if(!now)
                {
                    an=lcp[i];
                }
                else
                {
                    an=max(an,max(now-len,lcp[i]-now));
                }
                if(an==ans)
                    break;
            }
        }
    }
    printf("%d\n",an);
}
int main()
{
    while(cin>>s>>T>>C)
        solve(),printf("%d\n",ttt);
        
    return 0;
}
/*
aaaaaaaabacadae
aaaac
*/

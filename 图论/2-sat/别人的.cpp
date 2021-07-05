    #include<cstdio>  
    #include<cstring>  
    #include<vector>  
    using namespace std;  
    const int maxn= 1000+10;  
    struct TwoSAT  
    {  
        int n;  
        vector<int> G[maxn*2];  
        int S[maxn*2],c;  
        bool mark[maxn*2];  
      
        bool dfs(int x)  
        {  
            if(mark[x^1]) return false;  
            if(mark[x]) return true;  
            mark[x]=true;  
            S[c++]=x;  
      
            for(int i=0;i<G[x].size();i++)  
                if(!dfs(G[x][i])) return false;  
            return true;  
        }  
      
        void init(int n)  
        {  
            this->n=n;  
            for(int i=0;i<n*2;i++) G[i].clear();  
            memset(mark,0,sizeof(mark));  
        }  
      
        void add_clause(int x,int xval,int y,int yval)  
        {  
            x=x*2+xval;  
            y=y*2+yval;  
            G[x].push_back(y);  
        }  
      
        bool solve()  
        {  
            for(int i=0;i<2*n;i+=2)  
            if(!mark[i] && !mark[i+1])  
            {  
                c=0;  
                if(!dfs(i))  
                {  
                    while(c>0) mark[S[--c]]=false;  
                    if(!dfs(i+1)) return false;  
                }  
            }  
            return true;  
        }  
    }TS;  
    int main()  
    {  
        int n,m;  
        while(scanf("%d%d",&n,&m)==2)  
        {  
            TS.init(n);  
            while(m--)  
            {  
                int a,b,va,vb;  
                scanf("%d%d%d%d",&a,&b,&va,&vb);  
                TS.add_clause(a,va,b,vb^1);  
                TS.add_clause(b,vb,a,va^1);  
            }  
            printf("%s\n",TS.solve()?"YES":"NO");  
        }  
        return 0;  
    }  

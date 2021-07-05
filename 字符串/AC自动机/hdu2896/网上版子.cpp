#include <bits/stdc++.h>  
#define maxn 1000010  
#define tot 505  
using namespace std;  
struct Aho{  
    struct state{  
        int next[128];  
        int fail,id;  
    }stateTable[tot*140];  
    queue<int>q;  
    int size;  
    int ans[tot];  
    inline void init(){  
        while(q.size())q.pop();  
        for(int i=0;i<tot;++i){  
            memset(stateTable[i].next,0,sizeof(stateTable[i].next));  
            stateTable[i].fail=stateTable[i].id=0;  
        }  
        memset(ans,0,sizeof(ans));  
        size=1;  
    }  
    inline void insert(char *s,int id){  
        int n=strlen(s);  
        int now=0;  
        for(int i=0;i<n;++i){  
            char c=s[i];  
            if(!stateTable[now].next[c])  
                stateTable[now].next[c]=size++;  
            now=stateTable[now].next[c];  
        }  
        stateTable[now].id=id;  
    }  
    inline void build(){  
        stateTable[0].fail=-1;  
        q.push(0);  
        while(q.size()){  
            int u=q.front();  
            q.pop();  
            for(int i=0;i<128;++i)  
                if(stateTable[u].next[i]){  
                    if(u==0)stateTable[stateTable[u].next[i]].fail=0;  
                    else{  
                        int v=stateTable[u].fail;  
                        while(v!=-1){  
                            if(stateTable[v].next[i]){  
                                stateTable[stateTable[u].next[i]].fail=stateTable[v].next[i];  
                                break;  
                            }  
                            v=stateTable[v].fail;  
                        }  
                        if(v==-1)stateTable[stateTable[u].next[i]].fail=0;  
                    }  
                    q.push(stateTable[u].next[i]);  
                }  
            }  
        }  
    inline int match(char *s){  
        int n=strlen(s);  
        int res=0,now=0,tmp;  
        for(int i=1;i<=tot;++i)ans[i]=0;  
        for(int i=0;i<n;++i){  
            char c=s[i];  
            while(now!=0&&stateTable[now].next[c]==0)now=stateTable[now].fail;  
            now=stateTable[now].next[c];  
            if(now==-1)now=0;  
            tmp=now;  
            while(tmp!=0&&!ans[stateTable[tmp].id]){  
                if(stateTable[tmp].id){  
                    ans[stateTable[tmp].id]=1;  
                    res++;  
                }  
                tmp=stateTable[tmp].fail;  
                if(res>=3)return res;  
            }  
        }  
        return res;  
    }  
}aho;  
char s[maxn];  
int main(){  
    int n,m,cnt;  
    while(scanf("%d",&n)!=EOF){  
        aho.init();  
        cnt=0;  
        for(int i=1;i<=n;++i){  
            scanf("%s",s);  
            aho.insert(s,i);  
        }  
        aho.build();  
        scanf("%d",&m);  
        for(int i=1;i<=m;++i){  
            scanf("%s",s);  
            if(aho.match(s)){  
                printf("web %d:",i);  
                for(int i=1;i<=n;++i)  
                    if(aho.ans[i])  
                        printf(" %d",i);  
                printf("\n");  
                cnt++;  
            }  
        }  
        printf("total: %d\n",cnt);  
    }  
    return 0;  
} 

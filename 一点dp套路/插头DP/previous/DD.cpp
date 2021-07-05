#include<cstdio>
#include<cstring>
#define N 20
#define N1 20010
#define N2 13131
char map[N][N];
int parenthese[4]={0,-1,1,0};
int n,m,ex,ey;
struct node{
    int head[N2];
    int size;//hash值的层数
    int state[N1];
    int next[N1];
    long long s[N1];
    void init(){
        size=0;memset(head,-1,sizeof(head));
    }
    void insert1(int st,long long value){
        int h=st%N2;
        for (int i=head[h];i!=-1;i=next[i]){
            if (state[i]==st){
                s[i]+=value;return;
            }
        }
        state[size]=st;s[size]=value;
        next[size]=head[h];head[h]=size++;
    }
    long long answer(int st){
        int h=st%N2;
        for (int i=head[h];i!=-1;i=next[i]) if (state[i]==st) return s[i];
        return 0;
    }
}hash[2];
int idx,cur;
int sets(int st,int x,int v){
    x<<=1;
    return (st& ~(3<<x))|(v<<x);
}
int get(int st,int x){
    x<<=1;//将x由四进制位数转换为二进制的位数
    return(st>>x)&3;  //将st四进制的末尾以（二进制的两位）与3按位& 返回
}
int getl(int st,int x){
    int l=x,cnt=1;
    while (cnt) cnt+=parenthese[get(st,--l)];
    return l;
}
int getr(int st,int x){
    int r=x,cnt=-1;
    while (cnt) cnt+=parenthese[get(st,++r)];
    return r;
}
void updata(int x,int y,int st,long long value){
    int p=get(st,y),q=get(st,y+1);
    if (map[x][y]=='*'){
        if (p==0&&q==0) hash[cur].insert1(st,value);
        return ;
    }
    if (p==0&&q==0){
        if (x==n-1||y==m-1) return;//到行尾或者列尾不能再放置插头 否则不能形成闭合回路
        st=sets(st,y,1);
        st=sets(st,y+1,2);
        hash[cur].insert1(st,value);//继承上一行状态的数量
        return;
    }
    if (p==0||q==0){
        if (x<n-1){
            int newstate=st;
            newstate=sets(st,y,p+q);
            newstate=sets(newstate,y+1,0);
            hash[cur].insert1(newstate,value);
        }
        if (y<m-1){
            st=sets(st,y,0);
            st=sets(st,y+1,p+q);
            hash[cur].insert1(st,value);
        }
        return;
    }
    int newstate=st;
    newstate=sets(st,y,0);newstate=sets(newstate,y+1,0);//首先将状态清0
    if (p==1&&q==1) {
        newstate=sets(newstate,getr(st,y+1),1);
        //给y+1这个匹配的2号插头改为一号插头
        hash[cur].insert1(newstate,value);
        return;
    }
    if (p==1&&q==2) {
        if (x==ex&&y==ey) hash[cur].insert1(newstate,value);else return;
    }
    if (p==2&&q==2) {
        newstate=sets(newstate,getl(st,y),2);
        hash[cur].insert1(newstate,value);
        return;
    }
    if (p==2&&q==1) hash[cur].insert1(newstate,value);
}
int main(){
//    freopen("ural1519.in","r",stdin);
//    freopen("ural1519.out","w",stdout);
    scanf("%d%d",&n,&m);
    for (int i=0;i<n;++i) scanf("%s",map[i]);
    for (int i=0;i<n;++i)
        for (int j=0;j<m;++j) if (map[i][j]=='.') ex=i,ey=j;
    //printf("%d %d",ex,ey);
    hash[0].init();
    hash[0].size=1;hash[0].state[0]=0;
    hash[0].s[0]=1;idx=0;
    for (int i=0;i<n;++i){
        int size1=hash[idx].size;
        for (int j=0;j<size1;++j) hash[idx].state[j]<<=2;
        for (int j=0;j<m;++j){
            size1=hash[idx].size;
            cur=idx^1;
            hash[cur].init();
            for (int z=0;z<size1;++z) updata(i,j,hash[idx].state[z],hash[idx].s[z]);
            idx=cur;
      printf("%d %d\n",i,j);
      for (int i=0;i<hash[idx].size;++i) {
            for (int j=0;j<=m;j++) printf("%d",get(hash[idx].state[i],j));
            printf("   %d %d\n",hash[idx].s[i],hash[idx].size);
      }puts("");
        }
      for (int i=0;i<hash[idx].size;++i) {
            for (int j=0;j<=m;j++) printf("%d",get(hash[idx].state[i],j));
            printf("   %d %d\n",hash[idx].s[i],hash[idx].size);
      }puts("");
    }

    printf("%lld",hash[cur].answer(0));

    scanf("%d",&n);
    return 0;
}

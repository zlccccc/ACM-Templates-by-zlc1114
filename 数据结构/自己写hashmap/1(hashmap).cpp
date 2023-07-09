
template<typename T1,typename T2> struct hashmap{
    const static int seed=999991;
    const static int maxn=1e6+7;
    struct node{
        T1 key;T2 val;int next;
        node(){};
        node(T1 k,T2 v,int n):key(k),val(v),next(n){};
    }T[maxn];//更好地空间局部性?(雾)
    int head[seed],size;
    void clear(){
        memset(head,-1,sizeof(head));
        size=0;
    }
    void insert(T1 pos,T2 val){
        int x=pos%seed;
        T[size]=node(pos,val,head[x]);
        head[x]=size++;
    }
    T2 &operator [](T1 x){
        for (int i=head[x%seed];~i;i=T[i].next)
            if (T[i].key==x) return T[i].val;
        insert(x,0);
        return T[size-1].val;
    }
};


namespace Hash{
    typedef unsigned int uint;
    const uint S=16,S1=32-S,M=1996090921;
    #define H(x) ((uint)x*M>>S1)
    struct node{int x,y,t;}h[(1<<S)+105];
    int T=1; // time
    inline void insert(int x){
        node *p=h+H(x);
        for (;p->t==T;++p)
            if (p->x==x){++p->y; return;}
        p->t=T; p->x=x; p->y=1;
    }
    inline int find(int x){
        for (node *p=h+H(x);p->t==T;++p)
            if (p->x==x)return p->y;
        return 0;
    }
    #undef H
} using namespace Hash;
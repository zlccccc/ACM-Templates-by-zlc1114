
struct linknode{
    struct node{
        int key,val;int next;
        node(){};
        node(int k,int v,int n):key(k),val(v),next(n){};
    }T[maxn];//���õؿռ�ֲ���?(��)
    int head[maxn],size;
    void clear(){
        memset(head,-1,sizeof(head));
        size=0;
    }
    int get(int x,int y){
        for (int i=head[x];~i;i=T[i].next)
            if (T[i].key==y) return T[i].val;
        return 0;
    }
    void insert(int pos,int key,int val){
        T[size]=node(key,val,head[pos]);
        head[pos]=size++;
    }
};

#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int MAXN = 300005;

struct TrieInfo {
    int To[26],Fa[4][32],ref,l;
};

struct Match {
    int l,r,len;

    Match(void) {}
    Match(int a,int b,int c) : l(a),r(b),len(c) {}

} Info[MAXN],Map[26];

int Sa[MAXN],Rank[MAXN],Ti[MAXN],Cnt;
int Final[MAXN],Next[MAXN],total,Ans[MAXN];

namespace Trie {
    const int MAXN = 100005;

    TrieInfo T[MAXN];

    int Trans[MAXN],A[MAXN],cnt;

    void First() {
        cnt = 1;
        Trans[1] = -1;
    }

    int Insert(int cur,char c) {
        c = c - 'a';
        if (T[cur].To[c])
            return T[cur].To[c];
        T[++ cnt].Fa[0][1] = cur;
        T[cnt].l = T[cur].l + 1;
        Trans[cnt] = c;
        return (T[cur].To[c] = cnt);
    }

    int Getfa(int u,int dep) {
        int cur = u;
        for(int i = 0; i < 4; i ++,dep >>= 5) {
            int p = (dep & 31);
            if (!p)
                continue;
            cur = T[cur].Fa[i][p];
        }
        return cur;
    }

    void Work() {
        for(int i = 2; i < 32; i ++)
            for(int j = 1; j <= cnt; j ++)
                T[j].Fa[0][i] = T[T[j].Fa[0][i - 1]].Fa[0][1];
        for(int i = 1; i < 4; i ++)
            for(int j = 1; j < 32; j ++)
                for(int k = 1; k <= cnt; k ++) {
                    if (j == 1)
                        T[k].Fa[i][j] = T[T[k].Fa[i - 1][31]].Fa[i - 1][1];
                    else
                        T[k].Fa[i][j] = T[T[k].Fa[i][j - 1]].Fa[i][1];
                }
    }

    void Add(int p,int v) {
        for(; p <= Cnt; p += p & -p)
            A[p] += v;
    }

    int Sum(int p) {
        if (p < 0)
            return 0;
        int tmp = 0;
        for(; p; p -= p & -p)
            tmp += A[p];
        return tmp;
    }

    int Sum(int l,int r) {
        if (l > r)
            return 0;
        return Sum(r) - Sum(l - 1);
    }

    void Dfs(int Now) {
        Add(Rank[Now],1);
        for(int j = Final[Now]; j; j = Next[j]) {
            Ans[j] = Sum(Info[Ti[j]].l,Info[Ti[j]].r);
            if (!Info[Ti[j]].len)
                Ans[j] = 0;
        }
        for(int i = 0; i < 26; i ++)
            if (T[Now].To[i])
                Dfs(T[Now].To[i]);
        Add(Rank[Now],-1);
    }

    void GetAns() {
        Dfs(1);
    }
}

namespace SAM {
    struct Node {
        int To[26],fail,len,down,ref;
    } T[MAXN];

    int Go[MAXN][26];
    int Q[MAXN],Ord[MAXN],S,cnt;

    bool cmp(int a,int b) {
        return T[a].len < T[b].len;
    }

    int Add(int Lst,int c,int l,int cur) {
        int Nt = ++ cnt,p = Lst;
        T[Nt].len = l;
        for(; p && !T[p].To[c]; p = T[p].fail)
            T[p].To[c] = Nt;
        if (!p)
            T[Nt].fail = S;
        else if (T[T[p].To[c]].len == T[p].len + 1)
            T[Nt].fail = T[p].To[c];
        else {
            int q = ++ cnt,qt = T[p].To[c];
            T[q] = T[qt];
            T[q].len = T[p].len + 1;
            T[qt].fail = T[Nt].fail = q;
            for(; p && T[p].To[c] == qt; p = T[p].fail)
                T[p].To[c] = q;
        }
        return Nt;
    }

    void Dfs(int Now) {
        if (T[Now].ref)
            Sa[++ Cnt] = T[Now].ref,Rank[T[Now].ref] = Cnt;
        for(int i = 0; i < 26; i ++)
            if (Go[Now][i])
                Dfs(Go[Now][i]);
    }

    void Mark(int tnod,int snod) {
        T[snod].down = T[snod].ref = tnod;
        for(int i = 0; i < 26; i ++)
            if (Trie::T[tnod].To[i])
                Mark(Trie::T[tnod].To[i],T[snod].To[i]);
    }

    void Build() {
        int fi = 0,en = 1;
        Q[1] = 1;
        S = cnt = 1;
        Trie::T[1].ref = 1;
        T[1].ref = 1;
        while (fi < en) {
            int u = Q[++ fi];
            TrieInfo &c = Trie::T[u];
            for(int i = 0; i < 26; i ++)
                if (c.To[i]) {
                    TrieInfo &cur = Trie::T[c.To[i]];
                    cur.ref = Add(c.ref,i,cur.l,c.To[i]);
                    Q[++ en] = c.To[i];
                }
        }
        Mark(1,1);
        for(int i = 1; i <= cnt; i ++)
            Ord[i] = i;
        sort(Ord + 1,Ord + cnt + 1,cmp);
        for(; cnt > 1; cnt --) {
            int v = Ord[cnt],u = T[v].fail;
            T[u].down = T[v].down;
            TrieInfo &cur = Trie::T[T[v].down];
            int k = Trie::Getfa(T[u].down,cur.l - (T[cur.ref].len - T[u].len));
            Go[u][Trie::Trans[k]] = v;
        }
        Dfs(1);
    }
}

struct Quer {
    int type,s,t;
    char c;
} Q[MAXN];

int Refer[MAXN],Len[MAXN],N,M,Tc;

inline bool Small(int suf,const Match &a) {
    return Rank[suf] < a.l;
}

inline bool Large(int suf,const Match &a) {
    return Rank[suf] > a.r;
}

Match Merge(const Match &a,const Match &b) {
    if (a.l > a.r)
        return Match(0,-1,a.len + b.len);
    int l = a.l,r = a.r,l1 = a.l - 1,r1 = a.r + 1,mid;
    for(; l <= r;) {
        mid = l + r >> 1;
        if (Small(Trie::Getfa(Sa[mid],a.len),b))
            l1 = mid,l = mid + 1;
        else
            r = mid - 1;
    }
    for(l = a.l,r = a.r; l <= r;) {
        mid = l + r >> 1;
        if (Large(Trie::Getfa(Sa[mid],a.len),b))
            r1 = mid,r = mid - 1;
        else
            l = mid + 1;
    }
    return Match(l1 + 1,r1 - 1,a.len + b.len);
}

char a[MAXN];
void DFS(int x=1,int len=0) {
//        printf("%-3d(fail:%-3d,len=%-2d; rank=%-2d):%s\n",x,fail[x],this->len[x],rank[x],a);
    printf("%d fail=%d len=%d:%s\n",x+1,SAM::T[x].fail+1,SAM::T[x].len,a);
    for (int i=0; i<26; i++)
        if (SAM::T[x].To[i]) {
            a[len]=i+'a';
            DFS(SAM::T[x].To[i],len+1);
            a[len]=0;
        }
}

int main() {
    Trie::First();
    N = 1;
    Refer[1] = 1;
    scanf("%d", &M);
    for(int i = 1; i <= M; i ++) {
        int type,s,t;
        char c;
        scanf("%d%d", &type, &s);
        if (type == 1) {
            scanf(" %c", &c);
            s = Refer[s];
            Refer[++ N] = Trie::Insert(s,c);
        }
        if (type == 2) {
            scanf("%d %c", &t, &c);
            Q[i].type = s + 1;
            Q[i].s = t;
            Q[i].c = c;
        }
        if (type == 3 || type == 4)
            scanf("%d", &t),Q[i].type = type,Q[i].s = s,Q[i].t = t;
    }
    Trie::Work();
    SAM::Build();
//    DFS();
    Tc = 1;
    Info[1].l = 1,Info[1].r = Cnt;
    for(int i = 0; i < 26; i ++) {
        int l = 1,r = Cnt,mid;
        Map[i].r = Cnt + 1;
        for(; l <= r;) {
            mid = l + r >> 1;
            if (Trie::Trans[Sa[mid]] < i)
                Map[i].l = mid,l = mid + 1;
            else
                r = mid - 1;
        }
        for(l = 1,r = Cnt; l <= r;) {
            mid = l + r >> 1;
            if (Trie::Trans[Sa[mid]] > i)
                Map[i].r = mid,r = mid - 1;
            else
                l = mid + 1;
        }
        Map[i].l ++,Map[i].r --;
        Map[i].len = 1;
    }
    for(int i = 1; i <= M; i ++) {
        Quer &c = Q[i];
        if (!c.type)
            continue;
        if (c.type != 4)
            ++ Tc;
        if (c.type == 4) {
            ++ total;
            c.t = Refer[c.t];
            Next[total] = Final[c.t],Final[c.t] = total;
            Ti[total] = c.s;
        } else {
            //We must merge reversely.
            if (c.type == 1)
                Info[Tc] = Merge(Info[c.s],Map[c.c - 'a']);
            if (c.type == 2)
                Info[Tc] = Merge(Map[c.c - 'a'],Info[c.s]);
            if (c.type == 3)
                Info[Tc] = Merge(Info[c.t],Info[c.s]);
        }
    }
//    DFS();
    Trie::GetAns();
    for(int i = 1; i <= total; i ++)
        printf("%d\n", Ans[i]);
    return 0;
}

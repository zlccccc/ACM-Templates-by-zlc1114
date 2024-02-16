// 二维sum,常数看起来很小
template <class T> struct fenwick {
    int n;
    vector<T> t;
    fenwick(int _n = -1) : n(_n), t(n + 1) {}
    void add(int i, T a) {
        for (++i; i <= n; i += i & -i)
            t[i] += a;
    }
    T sum(int i) const {
        T s = 0;
        for (; i; i -= i & -i)
            s += t[i];
        return s;
    }
    T sum(int l, int r) const { return sum(r) - sum(l); }
};

template <class T> struct fenwick2d {
    int n;
    vector<pair<int, int>> ps;
    vector<vector<int>> ys;
    vector<fenwick<T>> ft;
    void add_point(int x, int y) { ps.emplace_back(x, y); }
    void build() {
        sort(begin(ps), end(ps));
        ps.erase(unique(begin(ps), end(ps)), end(ps));
        n = size(ps);
        ys.resize(n + 1), ft.resize(n + 1);
        for (int i = 0; i <= n; ++i) {
            for (int j = i + 1; j <= n; j += j & -j)
                ys[j].push_back(ps[i].second);
            sort(begin(ys[i]), end(ys[i]));
            ys[i].erase(unique(begin(ys[i]), end(ys[i])), end(ys[i]));
            ft[i] = fenwick<T>(size(ys[i]));
        }
    }
    int zip(int x) const { return lower_bound(begin(ps), end(ps), make_pair(x, -inf<int>)) - begin(ps); }
    int zip(int i, int y) const { return lower_bound(begin(ys[i]), end(ys[i]), y) - begin(ys[i]); }
    void add(int x, int y, T a) {
        int i = lower_bound(begin(ps), end(ps), make_pair(x, y)) - begin(ps);
        assert(ps[i] == make_pair(x, y));
        for (++i; i <= n; i += i & -i)
            ft[i].add(zip(i, y), a);
    }
    T sum(int x, int y) const {
        T s = 0;
        for (int i = zip(x); i; i -= i & -i)
            s += ft[i].sum(zip(i, y));
        return s;
    }
    T sum(int lx, int rx, int ly, int ry) const { return sum(rx, ry) - sum(rx, ly) - sum(lx, ry) + sum(lx, ly); }
};
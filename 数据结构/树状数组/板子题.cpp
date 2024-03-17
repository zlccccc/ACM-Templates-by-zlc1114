// 二维sum,常数看起来很小; 这里是求左闭右开区间的sum
template <class T> struct fenwick {
    vector<T> t;
    fenwick(int n = -1) : t(n + 1) {} // 范围 [1,n]; n=t.size()-1
    void add(int i, T a) {
        assert(1 <= i && i < (int)t.size());
        for (; i < (int)t.size(); i += i & -i)
            t[i] += a;
    }
    T sum(int i) const {
        T s = {0};
        for (; i; i -= i & -i)
            s += t[i];
        return s;
    }
    T sum(int l, int r) const { return sum(r) - sum(l - 1); }
};

template <class T> struct fenwick2d { // id-range: int; 单点修改区间求和
    vector<pair<int, int>> ps;
    vector<int> xs;
    vector<vector<int>> ys;
    vector<fenwick<T>> ft;
    void add_point(int x, int y) { ps.emplace_back(x, y); }
    void build() {
        for (auto [x, y] : ps)
            xs.push_back(x);
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        ys.resize(xs.size() + 1), ft.resize(xs.size() + 1);
        for (auto [x, y] : ps) {
            for (int j = zip(x); j <= (int)xs.size(); j += j & -j)
                ys[j].push_back(y);
        }
        for (int i = 1; i <= (int)xs.size(); ++i) {
            sort(ys[i].begin(), ys[i].end());
            ys[i].erase(unique(ys[i].begin(), ys[i].end()), ys[i].end());
            ft[i] = fenwick<T>(ys[i].size());
        }
    }
    int zip(int x) const { return upper_bound(xs.begin(), xs.end(), x) - xs.begin(); }
    int zip(int i, int y) const { return upper_bound(ys[i].begin(), ys[i].end(), y) - ys[i].begin(); }
    void add(int x, int y, T a) {
        int i = zip(x);
        assert(1 <= i && i <= (int)xs.size() && xs[i - 1] == x);
        for (; i <= (int)xs.size(); i += i & -i) {
            int j = zip(i, y);
            assert(1 <= j && j <= (int)ys[i].size() && ys[i][j - 1] == y);
            ft[i].add(j, a);
        }
    }
    T sum(int x, int y) const { // 这个板子不算边界的
        T s = {0};
        for (int i = zip(x); i; i -= i & -i)
            s += ft[i].sum(zip(i, y));
        return s;
    }
    T sum(int lx, int ly, int rx, int ry) const { return sum(rx, ry) - sum(rx, ly - 1) - sum(lx - 1, ry) + sum(lx - 1, ly - 1); }
};

// 区间加; 区间求sum
template <class T> struct rangeFenwick2d {
    struct RDMat {
        T i, x, y, xy;
        RDMat(T _i = 0, T _x = 0, T _y = 0, T _xy = 0) : i(_i), x(_x), y(_y), xy(_xy) {}
        RDMat &operator+=(const RDMat &a) {
            i += a.i, x += a.x, y += a.y, xy += a.xy;
            return *this;
        }
    };
    fenwick2d<RDMat> bit;
    void add_point(int lx, int ly, int rx, int ry) {
        bit.add_point(lx, ly);
        bit.add_point(lx, ry + 1);
        bit.add_point(rx + 1, ly);
        bit.add_point(rx + 1, ry + 1);
    }
    void build() { bit.build(); }
    void add(int x, int y, T val) { // 添加一个右下角的矩阵
        bit.add(x, y, {val, x * val, y * val, x * y * val});
    }
    void add(int lx, int ly, int rx, int ry, T val) {
        add(lx, ly, val);
        add(lx, ry + 1, -val);
        add(rx + 1, ly, -val);
        add(rx + 1, ry + 1, val);
    }
    T sum(int x, int y) {
        RDMat cur = bit.sum(x, y);
        // (x-dx+1)(y-dy+1)
        return cur.i * (x + 1) * (y + 1) - cur.x * (y + 1) - cur.y * (x + 1) + cur.xy;
    }
    T sum(int lx, int ly, int rx, int ry) { return sum(rx, ry) - sum(rx, ly - 1) - sum(lx - 1, ry) + sum(lx - 1, ly - 1); }
};

// 区间加; 单点查sum
template <class T> struct rangeFenwick2dSingleAsk {
    fenwick2d<T> bit;
    void add_point(int lx, int ly, int rx, int ry) {
        bit.add_point(lx, ly);
        bit.add_point(lx, ry + 1);
        bit.add_point(rx + 1, ly);
        bit.add_point(rx + 1, ry + 1);
    }
    void build() { bit.build(); }
    void add(int lx, int ly, int rx, int ry, T val) { // 添加一个右下角的矩阵
        bit.add(lx, ly, val);
        bit.add(lx, ry + 1, -val);
        bit.add(rx + 1, ly, -val);
        bit.add(rx + 1, ry + 1, val);
    }
    T sum(int x, int y) { return bit.sum(x, y); }
};
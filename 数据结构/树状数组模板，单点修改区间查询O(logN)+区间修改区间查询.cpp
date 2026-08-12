/**
 * 树状数组 (Fenwick Tree / Binary Indexed Tree)
 * 支持单点更新、区间查询
 * 时间复杂度: O(log n)
 */
struct Fenwick {
    vector<long long> tree;
    int n;

    Fenwick(int _n) : n(_n) {
        tree.resize(n + 1);
    }

    // 单点增加: a[x] += v
    void add(int x, long long v) {
        for (; x <= n; x += x & -x)
            tree[x] += v;
    }

    // 前缀和: a[1] + ... + a[x]
    long long sum(int x) {
        long long res = 0;
        for (; x > 0; x -= x & -x)
            res += tree[x];
        return res;
    }

    // 区间和: a[l] + ... + a[r]
    long long query(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

/**
 * 树状数组 — 区间修改 + 区间查询
 * 使用两个树状数组维护差分
 */
struct FenwickRange {
    vector<long long> t1, t2;
    int n;

    FenwickRange(int _n) : n(_n) {
        t1.resize(n + 2);
        t2.resize(n + 2);
    }

    void _add(vector<long long>& t, int x, long long v) {
        for (; x <= n; x += x & -x) t[x] += v;
    }

    long long _sum(vector<long long>& t, int x) {
        long long res = 0;
        for (; x > 0; x -= x & -x) res += t[x];
        return res;
    }

    // 区间加: [l, r] += v
    void add(int l, int r, long long v) {
        _add(t1, l, v);
        _add(t1, r + 1, -v);
        _add(t2, l, v * (l - 1));
        _add(t2, r + 1, -v * r);
    }

    // 前缀和
    long long _prefix(int x) {
        return _sum(t1, x) * x - _sum(t2, x);
    }

    // 区间和: [l, r]
    long long query(int l, int r) {
        return _prefix(r) - _prefix(l - 1);
    }
};

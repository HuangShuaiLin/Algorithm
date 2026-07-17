#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * 线段树 (Segment Tree)
 * 支持区间修改 + 区间查询
 * 默认是区间加法和区间求和
 */

struct SegTree {
    vector<ll> tree, lazy;
    int n;

    SegTree(const vector<int>& a) {
        n = a.size();
        tree.resize(4 * n);
        lazy.resize(4 * n);
        build(1, 0, n - 1, a);
    }

    void build(int rt, int l, int r, const vector<int>& a) {
        if (l == r) {
            tree[rt] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(rt * 2, l, mid, a);
        build(rt * 2 + 1, mid + 1, r, a);
        pushUp(rt);
    }

    void pushUp(int rt) {
        tree[rt] = tree[rt * 2] + tree[rt * 2 + 1];
    }

    void pushDown(int rt, int l, int r) {
        if (lazy[rt]) {
            int mid = (l + r) / 2;
            int lenL = mid - l + 1;
            int lenR = r - mid;

            tree[rt * 2] += lazy[rt] * lenL;
            tree[rt * 2 + 1] += lazy[rt] * lenR;
            lazy[rt * 2] += lazy[rt];
            lazy[rt * 2 + 1] += lazy[rt];
            lazy[rt] = 0;
        }
    }

    // 区间加: [L, R] += val
    void update(int L, int R, ll val, int rt, int l, int r) {
        if (L <= l && r <= R) {
            tree[rt] += val * (r - l + 1);
            lazy[rt] += val;
            return;
        }
        pushDown(rt, l, r);
        int mid = (l + r) / 2;
        if (L <= mid) update(L, R, val, rt * 2, l, mid);
        if (R > mid) update(L, R, val, rt * 2 + 1, mid + 1, r);
        pushUp(rt);
    }

    void update(int L, int R, ll val) {
        update(L, R, val, 1, 0, n - 1);
    }

    // 区间查询: sum[L..R]
    ll query(int L, int R, int rt, int l, int r) {
        if (L <= l && r <= R) {
            return tree[rt];
        }
        pushDown(rt, l, r);
        int mid = (l + r) / 2;
        ll res = 0;
        if (L <= mid) res += query(L, R, rt * 2, l, mid);
        if (R > mid) res += query(L, R, rt * 2 + 1, mid + 1, r);
        return res;
    }

    ll query(int L, int R) {
        return query(L, R, 1, 0, n - 1);
    }
};

/**
 * 线段树 — 区间赋值 + 区间最值
 */
struct SegTreeAssign {
    vector<ll> mx, lazy; // lazy = -1 表示无操作
    int n;

    SegTreeAssign(const vector<int>& a) {
        n = a.size();
        mx.resize(4 * n);
        lazy.assign(4 * n, -1);
        build(1, 0, n - 1, a);
    }

    void build(int rt, int l, int r, const vector<int>& a) {
        if (l == r) {
            mx[rt] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(rt * 2, l, mid, a);
        build(rt * 2 + 1, mid + 1, r, a);
        mx[rt] = max(mx[rt * 2], mx[rt * 2 + 1]);
    }

    void pushDown(int rt) {
        if (lazy[rt] != -1) {
            mx[rt * 2] = lazy[rt];
            mx[rt * 2 + 1] = lazy[rt];
            lazy[rt * 2] = lazy[rt];
            lazy[rt * 2 + 1] = lazy[rt];
            lazy[rt] = -1;
        }
    }

    void assign(int L, int R, ll val, int rt, int l, int r) {
        if (L <= l && r <= R) {
            mx[rt] = val;
            lazy[rt] = val;
            return;
        }
        pushDown(rt);
        int mid = (l + r) / 2;
        if (L <= mid) assign(L, R, val, rt * 2, l, mid);
        if (R > mid) assign(L, R, val, rt * 2 + 1, mid + 1, r);
        mx[rt] = max(mx[rt * 2], mx[rt * 2 + 1]);
    }

    void assign(int L, int R, ll val) {
        assign(L, R, val, 1, 0, n - 1);
    }

    ll queryMax(int L, int R, int rt, int l, int r) {
        if (L <= l && r <= R) return mx[rt];
        pushDown(rt);
        int mid = (l + r) / 2;
        ll res = -1e18;
        if (L <= mid) res = max(res, queryMax(L, R, rt * 2, l, mid));
        if (R > mid) res = max(res, queryMax(L, R, rt * 2 + 1, mid + 1, r));
        return res;
    }

    ll queryMax(int L, int R) {
        return queryMax(L, R, 1, 0, n - 1);
    }
};

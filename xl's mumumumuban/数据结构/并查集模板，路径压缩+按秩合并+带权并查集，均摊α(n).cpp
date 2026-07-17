#include <bits/stdc++.h>
using namespace std;

/**
 * 并查集 (Disjoint Set Union / Union-Find)
 * 支持路径压缩和按秩合并
 */
struct DSU {
    vector<int> parent, sz;

    DSU(int n) {
        parent.resize(n + 1);
        sz.resize(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }
};

/**
 * 带权并查集 (维护到根节点的距离)
 * 常用场景：模拟链式关系、模运算
 */
struct WeightedDSU {
    vector<int> parent, sz;
    vector<long long> weight; // weight[x]: x到parent[x]的权值

    WeightedDSU(int n) {
        parent.resize(n + 1);
        sz.resize(n + 1, 1);
        weight.resize(n + 1, 0);
        iota(parent.begin(), parent.end(), 0);
    }

    // 返回 (根, x到根的权值和)
    pair<int, long long> find(int x) {
        if (parent[x] == x) return {x, 0};
        auto [root, w] = find(parent[x]);
        parent[x] = root;
        weight[x] += w;
        return {root, weight[x]};
    }

    // 合并: value[a] - value[b] = w
    bool unite(int a, int b, long long w) {
        auto [ra, wa] = find(a);
        auto [rb, wb] = find(b);
        if (ra == rb) return false;
        if (sz[ra] < sz[rb]) {
            swap(ra, rb);
            swap(wa, wb);
            w = -w;
        }
        parent[rb] = ra;
        weight[rb] = wa - wb - w;
        sz[ra] += sz[rb];
        return true;
    }
};

#include <bits/stdc++.h>
using namespace std;

/**
 * 树的基础算法
 * 包含：树的直径、树的重心、树的重链剖分
 */

// ==============================
// 1. 树的直径 (两次DFS / 树形DP)
// ==============================

// 方法1: 两次DFS (适用于边权非负)
pair<int, int> treeDiameterDFS(const vector<vector<int>>& adj, int start) {
    int n = adj.size();
    vector<int> dist(n);
    function<void(int, int, int)> dfs = [&](int u, int fa, int d) {
        dist[u] = d;
        for (int v : adj[u])
            if (v != fa) dfs(v, u, d + 1);
    };
    dfs(start, -1, 0);
    int u = max_element(dist.begin(), dist.end()) - dist.begin();
    dfs(u, -1, 0);
    int v = max_element(dist.begin(), dist.end()) - dist.begin();
    return {u, v}; // 返回直径的两个端点
}

// 方法2: 树形DP (适用于带负权边)
int treeDiameterDP(const vector<vector<pair<int, int>>>& adj) {
    int ans = 0;
    function<int(int, int)> dfs = [&](int u, int fa) {
        int d1 = 0, d2 = 0; // 最长和次长向下距离
        for (auto [v, w] : adj[u]) {
            if (v == fa) continue;
            int d = dfs(v, u) + w;
            if (d > d1) { d2 = d1; d1 = d; }
            else if (d > d2) d2 = d;
        }
        ans = max(ans, d1 + d2);
        return d1;
    };
    dfs(1, 0);
    return ans;
}

// ==============================
// 2. 树的重心
// 删除重心后，剩余最大连通块最小
// ==============================
int treeCentroid(const vector<vector<int>>& adj) {
    int n = adj.size() - 1;
    int centroid = -1, minMax = n;
    vector<int> sz(n + 1);
    function<void(int, int)> dfs = [&](int u, int fa) {
        sz[u] = 1;
        int maxSub = 0;
        for (int v : adj[u]) {
            if (v == fa) continue;
            dfs(v, u);
            sz[u] += sz[v];
            maxSub = max(maxSub, sz[v]);
        }
        maxSub = max(maxSub, n - sz[u]);
        if (maxSub < minMax) {
            minMax = maxSub;
            centroid = u;
        }
    };
    dfs(1, 0);
    return centroid;
}

// ==============================
// 3. 树链剖分 (Heavy-Light Decomposition)
// 用于路径操作、子树操作
// ==============================
struct HLD {
    int n, timer = 0;
    vector<vector<int>> adj;
    vector<int> fa, dep, sz, son;   // 树基础信息
    vector<int> top, dfn, rnk;       // 剖分信息

    HLD(int _n) : n(_n), adj(n + 1),
        fa(n + 1), dep(n + 1), sz(n + 1), son(n + 1, 0),
        top(n + 1), dfn(n + 1), rnk(n + 1) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 第一遍DFS: 求fa, dep, sz, son(重儿子)
    void dfs1(int u, int f) {
        fa[u] = f; dep[u] = dep[f] + 1;
        sz[u] = 1;
        for (int v : adj[u]) {
            if (v == f) continue;
            dfs1(v, u);
            sz[u] += sz[v];
            if (sz[v] > sz[son[u]]) son[u] = v;
        }
    }

    // 第二遍DFS: 求top, dfn(DFS序), rnk(DFS序对应节点)
    void dfs2(int u, int tp) {
        top[u] = tp;
        dfn[u] = ++timer;
        rnk[timer] = u;
        if (son[u]) dfs2(son[u], tp); // 先走重儿子保证重链 DFS 序连续
        for (int v : adj[u]) {
            if (v == fa[u] || v == son[u]) continue;
            dfs2(v, v);
        }
    }

    void build(int root = 1) {
        dfs1(root, 0);
        dfs2(root, root);
    }

    // 路径 u-v 上的操作: 对路径上所有节点做 op
    // op 作用于 dfn 序区间 [l, r] (保证 l <= r)
    void pathProcess(int u, int v, function<void(int, int)> op) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            op(dfn[top[u]], dfn[u]); // 当前链
            u = fa[top[u]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        op(dfn[u], dfn[v]);
    }

    // 子树 u 上的操作 (子树在 dfn 序上是连续的)
    void subtreeProcess(int u, function<void(int, int)> op) {
        op(dfn[u], dfn[u] + sz[u] - 1);
    }

    // LCA (使用重链剖分)
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
};

/**
 * 重链剖分配上线段树后可实现:
 * - 路径修改/查询 (O(log^2 n) 或 O(log n))
 * - 子树修改/查询 (O(log n))
 * 用法: 将区间操作委托给 HLD 的 op 函数
 */

#include <bits/stdc++.h>
using namespace std;

/**
 * LCA 最近公共祖先 (倍增法 Binary Lifting)
 * 预处理: O(n log n), 查询: O(log n)
 */
struct LCA {
    int n, LOG;
    vector<vector<int>> adj, up;
    vector<int> depth;

    LCA(int _n) : n(_n) {
        LOG = __lg(n) + 1;
        adj.resize(n + 1);
        up.assign(n + 1, vector<int>(LOG));
        depth.resize(n + 1, 0);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int fa) {
        up[u][0] = fa;
        for (int i = 1; i < LOG; i++)
            up[u][i] = up[up[u][i - 1]][i - 1];
        for (int v : adj[u]) {
            if (v == fa) continue;
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }

    void build(int root = 1) {
        dfs(root, root);
    }

    int query(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        for (int i = 0; i < LOG; i++)
            if (diff & (1 << i)) u = up[u][i];
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }

    // 两点距离
    int dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[query(u, v)];
    }

    // 从 u 向上走 k 步
    int kthAncestor(int u, int k) {
        for (int i = 0; i < LOG; i++)
            if (k & (1 << i)) u = up[u][i];
        return u;
    }

    // 路径 u->v 上第 k 个节点 (从 u 开始，k=0 是 u)
    int kthOnPath(int u, int v, int k) {
        int lca = query(u, v);
        int d1 = depth[u] - depth[lca];
        if (k <= d1) return kthAncestor(u, k);
        int d2 = depth[v] - depth[lca];
        return kthAncestor(v, d1 + d2 - k);
    }
};

/**
 * LCA — Tarjan 离线算法
 * 处理所有查询总复杂度 O(n + q) (使用并查集)
 */
struct LCA_Tarjan {
    vector<vector<int>> adj;
    vector<vector<pair<int, int>>> queries; // queries[u] = {{v, query_id}}
    vector<int> parent, ans;
    vector<bool> vis;

    LCA_Tarjan(int n) : adj(n + 1), queries(n + 1), parent(n + 1), vis(n + 1, false) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void addQuery(int u, int v, int id) {
        queries[u].push_back({v, id});
        queries[v].push_back({u, id});
    }

    void dfs(int u, int fa) {
        vis[u] = true;
        for (int v : adj[u]) {
            if (v == fa) continue;
            dfs(v, u);
            parent[v] = u; // 合并到父节点
        }
        for (auto [v, id] : queries[u]) {
            if (vis[v]) {
                ans[id] = find(v);
            }
        }
    }

    vector<int> solve(int n, int q, int root = 1) {
        ans.resize(q);
        dfs(root, root);
        return ans;
    }
};

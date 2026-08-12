#include <bits/stdc++.h>
using namespace std;

/**
 * LCA — Euler Tour + ST表 (欧拉序 + RMQ)
 * 预处理: O(n log n), 单次查询: O(1)
 * 比倍增法查询更快，适合查询量极大时使用
 * 原理: 树的欧拉序列上任意两点 u,v 的 LCA 是 u,v 首次出现位置间深度最小的节点
 */

struct LCA_ST {
    int n;
    vector<vector<int>> adj;
    vector<int> euler;      // 欧拉序
    vector<int> first;      // 每个节点在欧拉序中首次出现的位置
    vector<int> depth;      // 每个节点的深度
    vector<int> log2;

    // ST 表: st[i][j] = 欧拉序 [i, i+2^j-1] 中深度最小的节点
    vector<vector<int>> st;

    LCA_ST(int _n) : n(_n), adj(n + 1),
        first(n + 1, -1), depth(n + 1) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // DFS 生成欧拉序列
    void dfs(int u, int fa) {
        first[u] = euler.size();
        euler.push_back(u);

        for (int v : adj[u]) {
            if (v == fa) continue;
            depth[v] = depth[u] + 1;
            dfs(v, u);
            euler.push_back(u); // 回溯时也加入
        }
    }

    void build(int root = 1) {
        depth[root] = 0;
        dfs(root, 0);

        int sz = euler.size();

        // 预处理 log2
        log2.resize(sz + 1);
        log2[1] = 0;
        for (int i = 2; i <= sz; i++)
            log2[i] = log2[i / 2] + 1;

        int K = log2[sz] + 1;
        st.assign(sz, vector<int>(K));

        for (int i = 0; i < sz; i++)
            st[i][0] = euler[i];

        for (int j = 1; j < K; j++) {
            for (int i = 0; i + (1 << j) - 1 < sz; i++) {
                int a = st[i][j - 1];
                int b = st[i + (1 << (j - 1))][j - 1];
                st[i][j] = depth[a] < depth[b] ? a : b;
            }
        }
    }

    // 查询 LCA, O(1)
    int query(int u, int v) {
        int l = first[u], r = first[v];
        if (l > r) swap(l, r);     // [l, r] 区间
        int k = log2[r - l + 1];
        int a = st[l][k];
        int b = st[r - (1 << k) + 1][k];
        return depth[a] < depth[b] ? a : b;
    }
};

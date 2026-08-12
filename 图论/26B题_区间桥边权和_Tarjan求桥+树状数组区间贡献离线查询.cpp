#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

/**
 * ***26省赛第B题 - 区间桥边权和***
 * 题目：给定无向图+边权+m条边编号1..m，q个查询[l,r]，
 *       求仅保留该区间内边时，所有桥的权值和 (mod 2^64)
 * 算法：Tarjan求桥 + 树状数组离线区间贡献
 * n ≤ 500, m,q ≤ 10^5
 *
 * 核心思路：
 * 1. n 很小 → 可对整体图跑 Tarjan 得到所有桥
 * 2. 对每条桥边 i，找让它"不再是桥"的最小区间
 * 3. 转换为二维数点：每条桥边对包含它且不含破坏边的区间有贡献
 * 4. 离线 BIT：树状数组维护区间贡献
 */

// 树状数组 — 单点更新、区间查询 O(log n)
struct Fenwick {
    vector<ull> tree; int n;
    Fenwick(int _n) : n(_n) { tree.resize(n + 1); }
    void add(int x, ull v) {
        for (; x <= n; x += x & -x) tree[x] += v;
    }
    ull sum(int x) {
        ull res = 0;
        for (; x > 0; x -= x & -x) res += tree[x];
        return res;
    }
    ull query(int l, int r) { return sum(r) - sum(l - 1); }
};

// Tarjan 求桥 — 边从 1..m 编号
struct Bridge {
    int n, timer = 0;
    vector<vector<pair<int,int>>> adj; // {to, edge_id}
    vector<int> dfn, low;
    vector<bool> isBridge; // isBridge[e] = 边e是否为桥

    Bridge(int _n, int m) : n(_n), adj(n + 1),
        dfn(n + 1), low(n + 1), isBridge(m + 1, false) {}

    void addEdge(int u, int v, int eid) {
        adj[u].push_back({v, eid});
        adj[v].push_back({u, eid});
    }

    void dfs(int u, int faEdge) {
        dfn[u] = low[u] = ++timer;
        for (auto [v, eid] : adj[u]) {
            if (eid == faEdge) continue;
            if (!dfn[v]) {
                dfs(v, eid);
                low[u] = min(low[u], low[v]);
                if (low[v] > dfn[u]) isBridge[eid] = true;
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }

    void solve() {
        for (int i = 1; i <= n; i++)
            if (!dfn[i]) dfs(i, -1);
    }
};
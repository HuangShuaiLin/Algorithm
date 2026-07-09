#include <bits/stdc++.h>
using namespace std;

/**
 * Kosaraju 算法 — 求有向图强连通分量 (SCC)
 * 思路:
 *   1. 对原图 DFS，记录出栈顺序 (post-order)
 *   2. 逆序遍历出栈顺序，在反图上 DFS，每次遍历到的节点属于同一个 SCC
 * 时间复杂度: O(n + m)
 *
 * 与 Tarjan 对比: Kosaraju 需要两次 DFS + 反图，常数略大
 *   但逻辑更直观，容易理解和实现
 */

// ==============================================
// 版本1: 仅求 SCC 个数和每个节点所属分量
// ==============================================
struct Kosaraju {
    int n;
    vector<vector<int>> adj, radj; // 原图和反图
    vector<int> comp;  // comp[i] = 节点 i 所属的 SCC 编号
    vector<bool> vis;
    vector<int> order; // dfs 出栈序

    Kosaraju(int _n) : n(_n), adj(n + 1), radj(n + 1),
        comp(n + 1), vis(n + 1) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        radj[v].push_back(u); // 反图
    }

    // 第一次 DFS: 在原图上求拓扑序
    void dfs1(int u) {
        vis[u] = true;
        for (int v : adj[u])
            if (!vis[v]) dfs1(v);
        order.push_back(u); // 出栈时记录
    }

    // 第二次 DFS: 在反图上标记 SCC
    void dfs2(int u, int sccId) {
        comp[u] = sccId;
        for (int v : radj[u])
            if (!comp[v]) dfs2(v, sccId);
    }

    // 返回 SCC 个数
    int solve() {
        // Step 1
        for (int i = 1; i <= n; i++)
            if (!vis[i]) dfs1(i);

        // Step 2: 逆序遍历
        int sccCnt = 0;
        for (int i = n - 1; i >= 0; i--) {
            int u = order[i];
            if (!comp[u]) dfs2(u, ++sccCnt);
        }
        return sccCnt;
    }

    // 判断整个图是否强连通
    bool isStronglyConnected() {
        int cnt = solve();
        return cnt == 1;
    }
};

// ==============================================
// 版本2: SCC 缩点 + DAG 最长路 DP
// 先求 SCC，将每个 SCC 缩成一个点，在新 DAG 上 DP
// ==============================================
struct Kosaraju_Shrink {
    int n;
    vector<vector<int>> adj, radj;
    vector<int> comp, w; // w: 每个节点的点权
    vector<bool> vis;
    vector<int> order;

    Kosaraju_Shrink(int _n) : n(_n), adj(n + 1), radj(n + 1),
        comp(n + 1), w(n + 1), vis(n + 1) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        radj[v].push_back(u);
    }

    void dfs1(int u) {
        vis[u] = true;
        for (int v : adj[u])
            if (!vis[v]) dfs1(v);
        order.push_back(u);
    }

    void dfs2(int u, int sccId) {
        comp[u] = sccId;
        for (int v : radj[u])
            if (!comp[v]) dfs2(v, sccId);
    }

    // 返回 SCC 个数，comp 存储每个节点的 SCC 编号
    int solve() {
        for (int i = 1; i <= n; i++)
            if (!vis[i]) dfs1(i);

        int sccCnt = 0;
        for (int i = n - 1; i >= 0; i--) {
            int u = order[i];
            if (!comp[u]) dfs2(u, ++sccCnt);
        }
        return sccCnt;
    }

    // DAG 缩点后的 DP (求最长路/最大权值)
    // compW[sccId] = SCC内所有节点的权值之和
    vector<int> shrinkAndDP() {
        int sccCnt = solve();

        // compW[i] = 第 i 个 SCC 的总权值
        vector<int> compW(sccCnt + 1, 0);
        for (int i = 1; i <= n; i++)
            compW[comp[i]] += w[i];

        // 建 DAG: 对每条原图的边，若两端不在同一 SCC 则连边
        vector<vector<int>> dag(sccCnt + 1);
        vector<int> indeg(sccCnt + 1, 0);
        set<pair<int, int>> added; // 去重 (可能有多条边连接同一对 SCC)

        for (int u = 1; u <= n; u++) {
            for (int v : adj[u]) {
                if (comp[u] != comp[v] &&
                    !added.count({comp[u], comp[v]})) {
                    dag[comp[u]].push_back(comp[v]);
                    indeg[comp[v]]++;
                    added.insert({comp[u], comp[v]});
                }
            }
        }

        // 拓扑序 DP
        vector<int> dp = compW;
        queue<int> q;
        for (int i = 1; i <= sccCnt; i++)
            if (indeg[i] == 0) q.push(i);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : dag[u]) {
                dp[v] = max(dp[v], dp[u] + compW[v]);
                if (--indeg[v] == 0) q.push(v);
            }
        }

        return dp; // dp[i] = 以 SCC i 结尾的最大路径权值和
    }
};

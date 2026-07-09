#include <bits/stdc++.h>
using namespace std;

/**
 * 拓扑排序 (Kahn算法 / BFS)
 * 返回拓扑序，若存在环则返回空vector
 */
vector<int> toposort(int n, const vector<vector<int>>& adj) {
    vector<int> indeg(n + 1, 0);
    for (int u = 1; u <= n; u++)
        for (int v : adj[u])
            indeg[v]++;

    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (indeg[i] == 0) q.push(i);

    vector<int> order;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : adj[u]) {
            if (--indeg[v] == 0)
                q.push(v);
        }
    }
    // 如果 order.size() < n，说明有环
    if ((int)order.size() < n) return {};
    return order;
}

/**
 * 拓扑排序 — DFS实现
 */
void dfs(int u, const vector<vector<int>>& adj, vector<int>& vis, vector<int>& order, bool& hasCycle) {
    vis[u] = 1; // 正在访问
    for (int v : adj[u]) {
        if (vis[v] == 1) hasCycle = true;
        else if (vis[v] == 0) dfs(v, adj, vis, order, hasCycle);
    }
    vis[u] = 2; // 已访问
    order.push_back(u);
}

vector<int> toposortDFS(int n, const vector<vector<int>>& adj) {
    vector<int> vis(n + 1, 0), order;
    bool hasCycle = false;
    for (int i = 1; i <= n && !hasCycle; i++)
        if (vis[i] == 0) dfs(i, adj, vis, order, hasCycle);
    if (hasCycle) return {};
    reverse(order.begin(), order.end());
    return order;
}

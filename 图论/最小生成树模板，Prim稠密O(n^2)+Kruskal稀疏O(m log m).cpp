#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * Prim 最小生成树 (邻接矩阵, O(n^2))
 * 适用于稠密图
 */
ll prim(int n, const vector<vector<ll>>& g) {
    // g[i][j] 为边权，INF 表示无边
    const ll INF = 1e18;
    vector<ll> mn(n + 1, INF);
    vector<bool> vis(n + 1, false);
    mn[1] = 0;
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        int u = -1;
        for (int v = 1; v <= n; v++)
            if (!vis[v] && (u == -1 || mn[v] < mn[u]))
                u = v;
        if (mn[u] == INF) return -1; // 图不连通
        vis[u] = true;
        ans += mn[u];
        for (int v = 1; v <= n; v++)
            if (!vis[v] && g[u][v] < mn[v])
                mn[v] = g[u][v];
    }
    return ans;
}

/**
 * Kruskal 最小生成树 (边排序 + 并查集, O(m log m))
 * 适用于稀疏图
 */
struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

ll kruskal(int n, vector<Edge> edges) {
    sort(edges.begin(), edges.end());
    // 需要并查集模板
    vector<int> parent(n + 1), sz(n + 1, 1);
    iota(parent.begin(), parent.end(), 0);
    function<int(int)> find = [&](int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    };
    auto unite = [&](int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    };

    ll ans = 0;
    int cnt = 0;
    for (auto [u, v, w] : edges) {
        if (unite(u, v)) {
            ans += w;
            cnt++;
            if (cnt == n - 1) break;
        }
    }
    return cnt == n - 1 ? ans : -1; // -1 表示不连通
}

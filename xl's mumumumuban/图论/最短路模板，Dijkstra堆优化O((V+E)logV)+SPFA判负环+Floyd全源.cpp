#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;

/**
 * Dijkstra 最短路 (堆优化)
 * 适用于非负权边
 * 时间复杂度: O((V+E) log V)
 */
vector<ll> dijkstra(int n, const vector<vector<pair<int, int>>>& adj, int s) {
    vector<ll> dist(n + 1, INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

/**
 * SPFA (Shortest Path Faster Algorithm)
 * 可处理负权边，判断负环
 * 平均快，最坏 O(VE)
 */
vector<ll> spfa(int n, const vector<vector<pair<int, int>>>& adj, int s) {
    vector<ll> dist(n + 1, INF);
    vector<bool> inq(n + 1, false);
    vector<int> cnt(n + 1, 0); // 入队次数用于判负环
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    inq[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        inq[u] = false;
        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                    if (++cnt[v] > n) {
                        // 存在负环
                        return {}; // 返回空vector表示负环
                    }
                }
            }
        }
    }
    return dist;
}

/**
 * Floyd-Warshall 全源最短路
 * 时间复杂度: O(n^3)
 */
vector<vector<ll>> floyd(const vector<vector<ll>>& d) {
    // d[i][i] = 0, d[i][j] = INF 表示无边
    auto dist = d;
    int n = dist.size() - 1;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (dist[i][k] != INF && dist[k][j] != INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    return dist;
}

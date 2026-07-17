#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;

/**
 * Dinic 最大流算法
 * 时间复杂度: O(V^2 * E)，实际通常很快
 */
struct Dinic {
    struct Edge {
        int to, rev;
        ll cap;
    };

    int n;
    vector<vector<Edge>> adj;
    vector<int> level, ptr;

    Dinic(int _n) : n(_n), adj(_n + 1), level(_n + 1), ptr(_n + 1) {}

    void addEdge(int u, int v, ll cap) {
        adj[u].push_back({v, (int)adj[v].size(), cap});
        adj[v].push_back({u, (int)adj[u].size() - 1, 0}); // 反向边
    }

    // 添加无向边(两个方向各cap)
    void addUndirectedEdge(int u, int v, ll cap) {
        adj[u].push_back({v, (int)adj[v].size(), cap});
        adj[v].push_back({u, (int)adj[u].size() - 1, cap});
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto& e : adj[u]) {
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    ll dfs(int u, int t, ll flow) {
        if (u == t) return flow;
        for (int& i = ptr[u]; i < (int)adj[u].size(); i++) {
            auto& e = adj[u][i];
            if (e.cap > 0 && level[e.to] == level[u] + 1) {
                ll pushed = dfs(e.to, t, min(flow, e.cap));
                if (pushed > 0) {
                    e.cap -= pushed;
                    adj[e.to][e.rev].cap += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    ll maxFlow(int s, int t) {
        ll flow = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (ll pushed = dfs(s, t, INF))
                flow += pushed;
        }
        return flow;
    }
};

/**
 * 最小费用最大流 (MCMF) — SPFA版
 */
struct MCMF {
    struct Edge {
        int to, rev;
        ll cap, cost;
    };

    int n;
    vector<vector<Edge>> adj;

    MCMF(int _n) : n(_n), adj(_n + 1) {}

    void addEdge(int u, int v, ll cap, ll cost) {
        adj[u].push_back({v, (int)adj[v].size(), cap, cost});
        adj[v].push_back({u, (int)adj[u].size() - 1, 0, -cost});
    }

    // 返回 {最大流量, 最小费用}
    pair<ll, ll> minCostMaxFlow(int s, int t) {
        ll flow = 0, cost = 0;
        vector<ll> dist(n + 1);
        vector<int> preV(n + 1), preE(n + 1);
        vector<bool> inq(n + 1);

        while (true) {
            fill(dist.begin(), dist.end(), INF);
            fill(inq.begin(), inq.end(), false);
            dist[s] = 0;
            queue<int> q;
            q.push(s);
            inq[s] = true;

            while (!q.empty()) {
                int u = q.front(); q.pop();
                inq[u] = false;
                for (int i = 0; i < (int)adj[u].size(); i++) {
                    auto& e = adj[u][i];
                    if (e.cap > 0 && dist[e.to] > dist[u] + e.cost) {
                        dist[e.to] = dist[u] + e.cost;
                        preV[e.to] = u;
                        preE[e.to] = i;
                        if (!inq[e.to]) {
                            q.push(e.to);
                            inq[e.to] = true;
                        }
                    }
                }
            }

            if (dist[t] == INF) break; // 无法增广

            ll pushed = INF;
            for (int v = t; v != s; v = preV[v])
                pushed = min(pushed, adj[preV[v]][preE[v]].cap);

            for (int v = t; v != s; v = preV[v]) {
                auto& e = adj[preV[v]][preE[v]];
                e.cap -= pushed;
                adj[v][e.rev].cap += pushed;
            }

            flow += pushed;
            cost += pushed * dist[t];
        }
        return {flow, cost};
    }
};

/**
 * 二分图最大匹配 — 匈牙利算法
 * 时间复杂度: O(VE)
 */
struct Hungarian {
    int n, m; // 左部点数, 右部点数
    vector<vector<int>> adj;
    vector<int> match;
    vector<bool> vis;

    Hungarian(int _n, int _m) : n(_n), m(_m),
        adj(n + 1), match(m + 1, 0), vis(m + 1) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            if (vis[v]) continue;
            vis[v] = true;
            if (!match[v] || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
        return false;
    }

    int solve() {
        int res = 0;
        for (int i = 1; i <= n; i++) {
            fill(vis.begin(), vis.end(), false);
            if (dfs(i)) res++;
        }
        return res;
    }
};

/**
 * 二分图最大匹配 — Dinic (跑得更快)
 * 直接使用上面的Dinic，建立二分图: S->左部->右部->T
 */

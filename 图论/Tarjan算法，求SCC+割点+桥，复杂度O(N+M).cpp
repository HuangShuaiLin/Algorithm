#include <bits/stdc++.h>
using namespace std;

/**
 * Tarjan 算法合集
 * 包含：强连通分量(SCC)、割点、桥
 */

// 1. 强连通分量 (SCC) — Tarjan
struct TarjanSCC {
    int n, timer = 0, sccCnt = 0;
    vector<vector<int>> adj;
    vector<int> dfn, low, belong;
    vector<bool> instk;
    stack<int> st;

    TarjanSCC(int _n) : n(_n), adj(n + 1),
        dfn(n + 1, 0), low(n + 1, 0),
        belong(n + 1, 0), instk(n + 1, false) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void dfs(int u) {
        dfn[u] = low[u] = ++timer;
        st.push(u); instk[u] = true;
        for (int v : adj[u]) {
            if (!dfn[v]) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (instk[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            sccCnt++;
            int v;
            do {
                v = st.top(); st.pop();
                instk[v] = false;
                belong[v] = sccCnt;
            } while (v != u);
        }
    }

    void solve() {
        for (int i = 1; i <= n; i++)
            if (!dfn[i]) dfs(i);
    }
};

// 2. 割点 (Articulation Point)
struct CutPoint {
    int n, timer = 0;
    vector<vector<int>> adj;
    vector<int> dfn, low;
    vector<bool> isCut;

    CutPoint(int _n) : n(_n), adj(n + 1),
        dfn(n + 1, 0), low(n + 1, 0), isCut(n + 1, false) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int fa) {
        dfn[u] = low[u] = ++timer;
        int child = 0;
        for (int v : adj[u]) {
            if (v == fa) continue;
            if (!dfn[v]) {
                dfs(v, u);
                child++;
                low[u] = min(low[u], low[v]);
                if (fa != u && low[v] >= dfn[u])
                    isCut[u] = true;
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (fa == u && child >= 2)
            isCut[u] = true;
    }

    void solve() {
        for (int i = 1; i <= n; i++)
            if (!dfn[i]) dfs(i, i);
    }
};

// 3. 桥 (Bridge)
struct Bridge {
    int n, timer = 0;
    vector<vector<int>> adj;
    vector<int> dfn, low;
    vector<pair<int, int>> bridges; // 存储所有桥

    Bridge(int _n) : n(_n), adj(n + 1),
        dfn(n + 1, 0), low(n + 1, 0) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int fa) {
        dfn[u] = low[u] = ++timer;
        for (int v : adj[u]) {
            if (v == fa) continue;
            if (!dfn[v]) {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > dfn[u])
                    bridges.push_back({u, v});
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }

    void solve() {
        for (int i = 1; i <= n; i++)
            if (!dfn[i]) dfs(i, i);
    }
};

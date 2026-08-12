#include <bits/stdc++.h>
using namespace std;

/**
 * 2-SAT 模板 (2-Satisfiability)
 * 判断布尔变量约束是否有解
 * 建图: 每个变量 x 拆成两个点 (x 和 x+n)
 *   合取范式 (a ∨ b): 连边 ¬a→b, ¬b→a
 * 用 Tarjan SCC 判强连通分量: 若 x 与 ¬x 在同一 SCC 中则无解
 * 时间复杂度: O(N + E)
 * 参考题目: HDU3062
 */

struct TwoSAT {
    int n, timer = 0, sccCnt = 0;
    vector<vector<int>> adj;
    vector<int> dfn, low, belong;
    vector<bool> instk;
    stack<int> st;

    TwoSAT(int _n) : n(_n), adj(2 * _n + 1),
        dfn(2 * _n + 1), low(2 * _n + 1),
        belong(2 * _n + 1), instk(2 * _n + 1) {}

    // 添加约束 (a = valA) ∨ (b = valB)
    // val 为 1 表示 true, 0 表示 false
    void addClause(int a, bool valA, int b, bool valB) {
        // 变量编码: true -> i, false -> i+n
        a = valA ? a : a + n;
        b = valB ? b : b + n;
        // ¬a → b
        adj[notVar(a)].push_back(b);
        // ¬b → a
        adj[notVar(b)].push_back(a);
    }

    // 强制 a (即 ¬a → a)
    void setTrue(int a) {
        adj[notVar(a)].push_back(a);
    }

    // a 和 b 不能同时为真 (即 ¬a ∨ ¬b)
    void addNAND(int a, int b) {
        addClause(a, 0, b, 0);
    }

    int notVar(int x) {
        return x > n ? x - n : x + n;
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

    // 返回是否有解
    bool solve() {
        for (int i = 1; i <= 2 * n; i++)
            if (!dfn[i]) dfs(i);
        for (int i = 1; i <= n; i++)
            if (belong[i] == belong[i + n])
                return false; // 无解
        return true;
    }

    // 获取一组可行赋值 (solve() 返回 true 后才可调用)
    vector<bool> getAssignment() {
        vector<bool> res(n + 1);
        for (int i = 1; i <= n; i++)
            res[i] = belong[i] < belong[i + n]; // 选拓扑序大的(SCC编号小的)
        return res;
    }
};

// 使用示例:
// TwoSAT sat(5);  // 5个变量
// sat.addClause(1, 1, 2, 0);  // x1=true 或 x2=false
// sat.addClause(2, 1, 3, 1);  // x2=true 或 x3=true
// if (sat.solve()) {
//     auto ans = sat.getAssignment();
// }

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * ***26省赛第A题 - Company R调度问题 ***
 * 题目：树(n≤5e5) 每个节点有类型A(工作a小时)或B(工作b小时, a<b)。
 *       分配开始时间s_i，一个员工satisfied当且仅当：
 *       存在邻居开始时间严格更早 AND 存在邻居结束时间严格更晚。
 *       最小化 dissatisfied 人数。
 *
 * 算法：树的DFS + 贪心——沿直径/最长链阶梯式分配时间
 *
 * 关键观察：
 * - 链首第一人和链尾最后一人必不满(无更早/更晚邻居)
 * - 最少 dissatisfied ≥ 2 (n>1时)
 * - 沿BFS/DFS的最长路径阶梯分配时间即可达到最小 dissatisfaction
 * - 工人类别 B 工作更久 → 安排在路径末端让结束时间更晚
 */

// ===== 树的DFS遍历 (沿直径方向分配时间) =====
void dfsAssign(int u, int fa, const vector<vector<int>>& adj,
               const string& type, int a, int b,
               vector<ll>& startTime, ll& curTime) {
    int workHours = (type[u] == 'A') ? a : b;
    startTime[u] = curTime;
    curTime += workHours; // 下一个人开始得更晚

    for (int v : adj[u]) {
        if (v == fa) continue;
        dfsAssign(v, u, adj, type, a, b, startTime, curTime);
    }
}

// 两次BFS求直径端点，再沿直径DFS分配
pair<int,int> treeDiameter(const vector<vector<int>>& adj, int start) {
    int n = adj.size();
    vector<int> dist(n);
    queue<int> q;
    q.push(start); dist[start] = 0;
    int far = start;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (v != 0 && dist[v] == 0 && v != start) {
                dist[v] = dist[u] + 1;
                q.push(v);
                if (dist[v] > dist[far]) far = v;
            }
        }
    }
    return {far, dist[far]};
}

// 求树的直径端点(简化版BFS)
int bfsFarthest(const vector<vector<int>>& adj, int start) {
    int n = adj.size();
    vector<int> dist(n, -1);
    queue<int> q;
    q.push(start); dist[start] = 0;
    int far = start;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
                if (dist[v] > dist[far]) far = v;
            }
        }
    }
    return far;
}
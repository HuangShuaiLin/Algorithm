#include <bits/stdc++.h>
using namespace std;

/**
 * ***26省赛第E题 - 交互猜图，判断独立集找边***
 * 题目：交互题。每轮询问一个顶点集S是否为独立集(无内部边)。
 *       用 ≤ n + m(2 + ceil(log2 n)) 次询问找出所有边。
 *       n ≤ 500, 图是自适应的。
 *
 * 算法：二分/分治定位每条边
 *       1. 先用 n 次询问确定每个点的邻居候选集
 *       2. 对每个点 i，用二分在 {i+1, ..., n} 中找邻居
 *       3. 询问集合 {i, mid} 间是否有边 → 二分收缩范围
 *
 * 核心技巧：
 * - 询问独立集：返回1表示集合内无边
 * - 问 {i, j}：返回0说明 i-j 有边
 * - 用二分在候选集中逐条定位边: 类似"找第一个1"的二分
 * - 总询问次数: 每个点花 O(log n) 二分, 总共 O(n log n)
 */

// 交互框架 (需要根据实际交互库调整)
// 每次询问: ? k v1 v2 ... vk → 返回1(独立集)或0(不是)
// 回答: ! m u1 v1 u2 v2 ... um vm

// 伪代码模板:
/*
int n; cin >> n;

// 策略: 对每个点 i, 找出它和 i+1..n 中的哪些点有边
vector<pair<int,int>> edges;

vector<int> candidates;
for (int j = 1; j <= n; j++) candidates.push_back(j);

for (int i = 1; i <= n; i++) {
    // 二分找 i 的所有大于它的邻居
    int lo = i + 1, hi = n;
    while (lo <= hi) {
        // 询问 {i} ∪ {lo..mid}
        int mid = (lo + hi) / 2;
        vector<int> query = {i};
        for (int x = lo; x <= mid; x++) query.push_back(x);
        // ask(query) ...
        bool hasEdge = !ask(query);
        if (hasEdge) {
            // 收缩找具体边
            // ...
            edges.push_back({i, mid});
        }
        lo = mid + 1;
    }
}
*/

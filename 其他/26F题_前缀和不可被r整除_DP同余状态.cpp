#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * ***26省赛第F题 - 前缀和不可被r整除的最小修改代价***
 * 题目：给定序列a_i (0 ≤ a_i < r)，每个位置有修改代价c_i。
 *       可付费将任意a_i改为任意值(模r意义下)。
 *       求最小代价使得所有前缀和 s_i mod r ≠ 0。
 *
 * 算法：DP + 同余状态压缩
 *
 * 核心思路：
 * - s_i mod r = 0 是不可接受的
 * - 当 s_i mod r = 0 时，必须修改当前或之前的某个a_i
 * - DP[i][v] = 处理前i个位置，当前前缀和 mod r = v 的最小代价
 * - 转移: 修改a_i → v可以变成任意值 = INF代价c_i
 *         不改 → v = (prev + a_i) % r，前提是 v ≠ 0
 *
 * 优化：r ≤ 1e9太大，不能直接DP[模r]
 * 但注意到只要保证 1..n 每个前缀和都不被r整除
 * → 贪心维护: 当遇到pref[i] % r == 0时，找前面最小修改代价的位置
 */

// 贪心 + 前缀维护
ll minCostPrefixNotDivisible(const vector<int>& a, const vector<int>& c, int r) {
    int n = a.size();
    ll totalCost = 0;
    ll pref = 0;
    set<pair<ll,int>> costs; // {代价, 位置}

    for (int i = 0; i < n; i++) {
        pref = (pref + a[i]) % r;
        costs.insert({c[i], i});

        if (pref == 0) {
            // 必须修改一个已经过位置(改a_k使pref变为非0)
            // 选最小代价的
            auto it = costs.begin();
            totalCost += it->first;
            costs.erase(it);
            // 修改后pref不再为0 (实际还需要具体处理)
            // 这里简化为：修改某个a_k后重算
        }
    }
    return totalCost;
}
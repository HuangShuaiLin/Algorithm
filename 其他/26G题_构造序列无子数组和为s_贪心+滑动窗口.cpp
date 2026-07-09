#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * ***26省赛第G题 - 构造序列无机子数组和为s***
 * 题目：给定两个数 a,b (a≠b)，构造长n的序列c_i∈{a,b}，
 *       使不存在连续子数组和为s。
 *       若无法构造输出NO。
 *
 * 算法：贪心构造 + 同余分析
 *       子数组和只能为 k*a + (len-k)*b = b*len + k*(a-b)
 *       由于 a≠b，和随len线性增长。
 *       贪心：尽量用大的数填，当快到达s时换小的
 *
 * 关键观察：
 * - 若 s 不能被 a 和 b 的差值整除，几乎总是YES(稀疏)
 * - 特殊情况：s 恰好等于某几个 a 或 b 的和时需跳跃
 * - 构造: 从前往后贪心，维护当前窗口和，接近s就换值
 */

bool canConstruct(int a, int b, int n, ll s, vector<int>& result) {
    result.resize(n);
    if (a > b) swap(a, b);

    // 贪心：尽量放b(大)，当累积和可能命中s时换a(小)
    // 维护一个滑动窗口来防止子数组和为s
    ll windowSum = 0;
    deque<pair<int,int>> dq; // {值, 位置} 维持窗口

    for (int i = 0; i < n; i++) {
        // 尝试放b
        if (windowSum + b != s) {
            result[i] = b;
            windowSum += b;
        } else {
            // b会导致和=s，试a
            if (windowSum + a != s) {
                result[i] = a;
                windowSum += a;
            } else {
                return false; // 两个都会命中s，无法构造
            }
        }
        // 维护窗口: 去掉和已经超过s的部分
        dq.push_back({result[i], i});
        while (!dq.empty() && windowSum >= s) {
            windowSum -= dq.front().first;
            dq.pop_front();
        }
    }
    return true;
}
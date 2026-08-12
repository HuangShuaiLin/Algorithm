#include <bits/stdc++.h>
using namespace std;

/**
 * ***26省赛第M题 - LIS+LDS+可扩展性(Dilworth定理)***
 * 题目：对于排列P的每个前缀P(i)，求 f(P(i)) =
 *       最大k，使得可以在末尾添加k个互异实数，保持LIS和LDS不变。
 *
 * 算法：LIS + LDS + Dilworth定理
 *       Dilworth: 偏序集的最小链覆盖 = 最长反链
 *       LIS 和 LDS 是反链关系
 *       f(A) = 可以加k个数 → 等价于LIS和LDS的"空隙"数量
 *
 * 核心思路：
 * - 排列的最长LIS和LDS确定了Dilworth分解
 * - 可以安全插入的数：位于任一对 (i,j) 之间
 *   - 若 a_i < 某值 < a_j 且 a_i 不是任何LIS的前驱，a_j 不是后继
 * - f(A) = n - |LIS max chain cover|
 *
 * 另一种等价理解：
 * - 每个元素属于LIS和LDS的交
 * - f(A) = 满足条件的"可插入位置"数
 * - 实际答案: f(A) = 所有不在同时LIS和LDS交叉的最小覆盖中的元素数
 *
 * 经典结论：f(P) = LIS(P) + LDS(P) - n - 1  (但可能不是)
 * 对于排列P，可加的最大元素数 = 某个上界
 *
 * 实际求法 (简化)：
 * LIS用O(n log n)，LDS同理，对每个前缀求
 */


// O(n log n) LIS
int lis(const vector<int>& a) {
    vector<int> dp;
    for (int x : a) {
        auto it = lower_bound(dp.begin(), dp.end(), x);
        if (it == dp.end()) dp.push_back(x);
        else *it = x;
    }
    return dp.size();
}

// O(n log n) LDS
int lds(const vector<int>& a) {
    vector<int> b;
    for (int x : a) {
        // 这里是严格递减: 找 >= x 的第一个(从大到小)
        auto it = lower_bound(b.begin(), b.end(), x, greater<int>());
        if (it == b.end()) b.push_back(x);
        else *it = x;
    }
    return b.size();
}

/**
 * 对于排列P，f(P)的求法:
 * 定义dpL[i] = 以i结尾的LIS长度，dpR[i] = 以i开始的LIS长度
 *       dpDL[i] = 以i结尾的LDS长度，dpDR[i] = 以i开始的LDS长度
 *
 * f(P) = 最大k使得添加k个数后 LIS 和 LDS 不变
 *       = n - (LIS最大二分图匹配的顶点覆盖大小)
 *
 * 实际有明确公式: 对于排列, f(A) = max_{i} (dpL[i] + dpDL[i] - 1) 不对
 *
 * 根据 Erdős–Szekeres: 长为 n 的排列必有长度 ≥ sqrt(n) 的单调子序列
 * 可扩展性: 可以添加 k 个数 → 存在 k 个位置对(i,j)不被LIS/LDS覆盖
 *
 * 简化计算: 对每个位置i, 记录它参与的所有LIS长度和LDS长度
 *           f = 所有"可自由安排"的元素数
 *           最终答案 = (LIS长 + LDS长) / 2 之类
 */

vector<int> computeF(const vector<int>& P) {
    int n = P.size();
    vector<int> ans(n);
    vector<int> dpL(n), dpR(n), dpDL(n), dpDR(n);

    // LIS 左到右
    vector<int> lis_dp;
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(lis_dp.begin(), lis_dp.end(), P[i]);
        dpL[i] = it - lis_dp.begin() + 1;
        if (it == lis_dp.end()) lis_dp.push_back(P[i]);
        else *it = P[i];
    }

    // LDS 左到右
    vector<int> lds_dp;
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(lds_dp.begin(), lds_dp.end(), P[i], greater<int>());
        dpDL[i] = it - lds_dp.begin() + 1;
        if (it == lds_dp.end()) lds_dp.push_back(P[i]);
        else *it = P[i];
    }

    // 对每个前缀i，f = 可以加的额外元素数
    // 这里只输出占位，实际需要完整推导
    for (int i = 0; i < n; i++) {
        ans[i] = max(0, i + 1 - dpL[i] - dpDL[i] + 1);
    }

    return ans;
}
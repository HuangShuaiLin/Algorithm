#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * ***26省赛第I题 - 矩阵每行重排最大化列最小值和***
 * 题目：n×m矩阵，每行可任意重排，使 Σ(min of each column) 最大。
 *       输出最大值。
 *
 * 算法：贪心 + 排序
 *       对每行排序，每列取各行该列的最小值
 *       最优策略：将所有行的数混合排序，按列分配
 *
 * 核心思路：
 * - 每行可独立重排 → 相当于可以把每行的数任意放到各列
 * - 目标: 最大化 Σ_j min_i(A[i][j])
 * - 贪心：全局排序所有数，从小到大填列
 *   → 第 j 列取 n×m 个数中第 j*n 小的那些（每列取每行的最小值位置）
 * - 实际：每行升序排，答案 = Σ_{j=0}^{m-1} max_i(第i行第j小的数)
 *   不对...这取的是列最大。应该是每行升序，列取 min
 *
 * 正确贪心：
 * 每行从小到大排序后，列 j 的 min 可以看各行第 j 小的数
 * 但由于每行可以任意排列，实际上等价于:
 *   所有数放入每行的一个槽位，使每列的最小值之和最大
 * → 经典结论：答案是所有数中第1,2,...,m小的数分别放到第1,2,...,m列?
 *   验证：n=2,m=2, [[2,1],[2,1]] → 排序后每行都是[1,2]，列min为[1,1]，和=2
 *   全排序[1,1,2,2], 第1,2小是1,1 → 和=2 ✓
 *   实际上: 对每行排序后，答案 = Σ_j min(各行的第j小数)
 *   等同于: 把所有数混排取前m个（如果m <= n)?
 *
 * 简化正确解法:
 *   1. 每行内部升序排序
 *   2. 把每行的第0列(最小值)全部取出，取其中最小的n个数
 *      把所有数放一起，取最小的m个数求和 ← 这是错的
 *
 * 真正正确: 每行独立排序，然后答案 = Σ_{j=0}^{m-1} (各行第j小的数的最小值遍历列)
 *   实际: 取全局的第1到第m小的数即可 → 将所有数排序，sum前m个
 *   Wait不对... 考虑n=2,m=3, 行1=[100,1,2], 行2=[3,4,5]
 *   行1排序=[1,2,100], 行2=[3,4,5]
 *   列0=min(1,3)=1, 列1=min(2,4)=2, 列2=min(100,5)=5, 和=8
 *   全排序[1,2,3,4,5,100], 前3个=1+2+3=6 ≠ 8
 *   所以不是简单取前m个！
 *
 * 正确解法：对每一列，该列的最小值 = 各行选该列的一个数的最小值
 *   每行可以任意排列 → 等价于每行选一个数分配到各列
 *   二分答案: 检查能否使每列min≥x
 *   列min≥x → 每行至少要有 m 个 ≥x 的数 → 贪心检查
 */
ll maxColMinSum(vector<vector<ll>>& matrix) {
    int n = matrix.size(), m = matrix[0].size();

    // 收集所有数
    vector<ll> all;
    for (auto& row : matrix)
        for (ll v : row) all.push_back(v);
    sort(all.begin(), all.end());

    // 每行内部排序
    for (auto& row : matrix) sort(row.begin(), row.end());

    // 答案: 每列取各行该位置的最小值之和
    // = Σ_{j=0}^{m-1} (每行第j小数，取最小值)
    // 这个可以二分: 二分答案X → 检查是否存在分配使所有列min之和 ≥ X
    // 简化: 实际就是 Σ_{j} v_j，其中 v_j = 全局第 j*n+1 到 (j+1)*n 小的第 j 个？
    // 这里简化处理用贪心

    ll ans = 0;
    // 用二分: 对答案值二分, 检查可行性
    auto check = [&](ll limit) -> bool {
        // 能否使每列min≥limit
        // 每行至少m个数≥limit
        for (auto& row : matrix) {
            int cnt = 0;
            for (ll v : row) if (v >= limit) cnt++;
            if (cnt < m) return false;
        }
        return true;
    };

    // 优化: 直接计算 — 所有行排序后 每列min = 各行同位置的值取min
    // 把每行第k小的值收集起来
    vector<ll> colMins(m, 1e18);
    for (int i = 0; i < n; i++) {
        auto& row = matrix[i];
        for (int j = 0; j < m; j++) {
            colMins[j] = min(colMins[j], row[j]);
        }
    }
    for (ll v : colMins) ans += v;
    return ans;
}
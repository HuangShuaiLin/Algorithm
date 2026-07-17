#include <bits/stdc++.h>
using namespace std;

/**
 * 区间DP模板
 * 适用于：石子合并、矩阵链乘、回文分割等
 * 核心思想：dp[l][r] 表示区间 [l, r] 的最优解
 *   枚举区间长度 len，再枚举起点 l，终点 r = l + len - 1
 *   再枚举分割点 k 将区间分成 [l,k] 和 [k+1,r]
 * 时间复杂度: O(n³) (标准)，部分问题可优化到 O(n²)
 */

// ================================================
// 经典: 合并石子 (区间求和最小值)
// dp[l][r] = min(dp[l][k] + dp[k+1][r]) + sum[l..r]
// ================================================
int stoneMerge(const vector<int>& stones) {
    int n = stones.size();
    vector<int> pre(n + 1, 0);
    for (int i = 1; i <= n; i++)
        pre[i] = pre[i - 1] + stones[i - 1];

    auto sum = [&](int l, int r) {
        return pre[r + 1] - pre[l];
    };

    const int INF = 1e9;
    vector<vector<int>> dp(n, vector<int>(n, INF));

    // len = 1: 一堆不用合并
    for (int i = 0; i < n; i++) dp[i][i] = 0;

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            for (int k = l; k < r; k++) {
                dp[l][r] = min(dp[l][r],
                    dp[l][k] + dp[k + 1][r] + sum(l, r));
            }
        }
    }
    return dp[0][n - 1];
}

// ==============================================
// 区间DP — 环形石子合并 (破环成链)
// 把数组复制一遍, 对每个长为 n 的区间取最值
// ==============================================
int stoneMergeCircle(const vector<int>& stones) {
    int n = stones.size();
    vector<int> a = stones;
    a.insert(a.end(), stones.begin(), stones.end()); // 复制

    vector<int> pre(2 * n + 1, 0);
    for (int i = 1; i <= 2 * n; i++)
        pre[i] = pre[i - 1] + a[i - 1];

    auto sum = [&](int l, int r) {
        return pre[r + 1] - pre[l];
    };

    const int INF = 1e9;
    vector<vector<int>> dp(2 * n, vector<int>(2 * n, INF));

    for (int i = 0; i < 2 * n; i++) dp[i][i] = 0;

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len - 1 < 2 * n; l++) {
            int r = l + len - 1;
            for (int k = l; k < r; k++) {
                dp[l][r] = min(dp[l][r],
                    dp[l][k] + dp[k + 1][r] + sum(l, r));
            }
        }
    }

    int ans = INF;
    for (int i = 0; i < n; i++)
        ans = min(ans, dp[i][i + n - 1]);
    return ans;
}

// ==========================================
// 区间DP — 回文串分割最少次数 (LeetCode 132)
// dp[l][r]: s[l..r] 最少分割次数
// ==========================================
int palindromePartition(const string& s) {
    int n = s.size();
    vector<vector<bool>> isPal(n, vector<bool>(n, false));
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i; j < n; j++) {
            if (s[i] == s[j] && (j - i <= 1 || isPal[i + 1][j - 1]))
                isPal[i][j] = true;
        }
    }

    const int INF = 1e9;
    vector<vector<int>> dp(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) dp[i][i] = 0;

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            if (isPal[l][r]) {
                dp[l][r] = 0;
            } else {
                for (int k = l; k < r; k++) {
                    dp[l][r] = min(dp[l][r],
                        dp[l][k] + dp[k + 1][r] + 1);
                }
            }
        }
    }
    return dp[0][n - 1];
}

// ==========================================
// 区间DP — 最长回文子序列
// dp[l][r]: s[l..r] 中最长回文子序列长度
// ==========================================
int longestPalindromeSubseq(const string& s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) dp[i][i] = 1;

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            if (s[l] == s[r])
                dp[l][r] = dp[l + 1][r - 1] + 2;
            else
                dp[l][r] = max(dp[l + 1][r], dp[l][r - 1]);
        }
    }
    return dp[0][n - 1];
}

#include <bits/stdc++.h>
using namespace std;

/**
 * 经典DP模板合集
 * 包含：01背包、完全背包、多重背包、LCS、LIS、编辑距离
 */

// ==============================
// 1. 01背包 (每件物品最多选一次)
// dp[j] = max(dp[j], dp[j - w] + v)
// ==============================
int knapsack01(const vector<int>& weight, const vector<int>& value, int cap) {
    vector<int> dp(cap + 1, 0);
    int n = weight.size();
    for (int i = 0; i < n; i++)
        for (int j = cap; j >= weight[i]; j--)
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
    return dp[cap];
}

// ==============================
// 2. 完全背包 (每种物品无限次)
// 把01背包的 j 倒序变成正序即可
// ==============================
int knapsackComplete(const vector<int>& weight, const vector<int>& value, int cap) {
    vector<int> dp(cap + 1, 0);
    int n = weight.size();
    for (int i = 0; i < n; i++)
        for (int j = weight[i]; j <= cap; j++)  // 注意：正序
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
    return dp[cap];
}

// ==============================
// 3. 多重背包 (每种物品有 count[i] 个)
// 二进制拆分优化: O(n*C*log(sum))
// ==============================
int knapsackMultiple(vector<int> weight, vector<int> value, vector<int> cnt, int cap) {
    vector<int> dp(cap + 1, 0);
    int n = weight.size();

    // 二进制拆分
    vector<int> newW, newV;
    for (int i = 0; i < n; i++) {
        int c = cnt[i];
        for (int k = 1; k <= c; k <<= 1) {
            newW.push_back(weight[i] * k);
            newV.push_back(value[i] * k);
            c -= k;
        }
        if (c > 0) {
            newW.push_back(weight[i] * c);
            newV.push_back(value[i] * c);
        }
    }

    // 01背包
    for (int i = 0; i < (int)newW.size(); i++)
        for (int j = cap; j >= newW[i]; j--)
            dp[j] = max(dp[j], dp[j - newW[i]] + newV[i]);
    return dp[cap];
}

// ==============================
// 4. 最长公共子序列 (LCS)
// dp[i][j] = s1前i个与s2前j个的LCS长度
// ==============================
int lcs(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[n][m];
}

// 输出LCS字符串
string lcsString(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

    // 回溯
    string res;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            res.push_back(s1[i - 1]);
            i--; j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    reverse(res.begin(), res.end());
    return res;
}

// ==============================
// 5. 最长上升子序列 (LIS) — O(n log n)
// ==============================
int lis(const vector<int>& a) {
    int n = a.size();
    vector<int> dp; // dp[len] = 长度为len的LIS的最小末尾值
    for (int x : a) {
        auto it = lower_bound(dp.begin(), dp.end(), x);
        if (it == dp.end())
            dp.push_back(x);
        else
            *it = x;
    }
    return dp.size();
}

// 输出一个LIS (需要额外的pre数组)
vector<int> lisTrack(const vector<int>& a) {
    int n = a.size();
    vector<int> dp, idx, pre(n, -1);
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(dp.begin(), dp.end(), a[i]);
        int pos = it - dp.begin();
        if (it == dp.end()) {
            dp.push_back(a[i]);
            idx.push_back(i);
        } else {
            *it = a[i];
            idx[pos] = i;
        }
        if (pos > 0) pre[i] = idx[pos - 1];
    }
    // 回溯
    vector<int> res;
    for (int i = idx.back(); i != -1; i = pre[i])
        res.push_back(a[i]);
    reverse(res.begin(), res.end());
    return res;
}

// ==============================
// 6. 编辑距离 (Levenshtein Distance)
// 允许插入、删除、替换，每步代价为1
// ==============================
int editDistance(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
        }
    }
    return dp[n][m];
}

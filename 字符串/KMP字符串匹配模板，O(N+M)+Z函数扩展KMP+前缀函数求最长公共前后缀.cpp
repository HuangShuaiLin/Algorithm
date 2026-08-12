#include <bits/stdc++.h>
using namespace std;

/**
 * KMP 字符串匹配
 * 在文本串 s 中查找所有模式串 p 的出现位置
 * 时间复杂度: O(|s| + |p|)
 */

// 求 next 数组 (前缀函数)
// pi[i] = p[0..i]的最长公共前后缀长度
vector<int> prefixFunction(const string& p) {
    int m = p.size();
    vector<int> pi(m);
    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];
        while (j > 0 && p[i] != p[j])
            j = pi[j - 1];
        if (p[i] == p[j]) j++;
        pi[i] = j;
    }
    return pi;
}

// KMP 匹配 — 返回所有匹配的起始位置(0-indexed)
vector<int> kmp(const string& s, const string& p) {
    vector<int> pi = prefixFunction(p);
    vector<int> matches;
    int j = 0; // 已匹配的长度
    for (int i = 0; i < (int)s.size(); i++) {
        while (j > 0 && s[i] != p[j])
            j = pi[j - 1];
        if (s[i] == p[j]) j++;
        if (j == (int)p.size()) {
            matches.push_back(i - j + 1);
            j = pi[j - 1];
        }
    }
    return matches;
}

/**
 * 扩展KMP (Z函数)
 * z[i] = s 与 s[i:] 的最长公共前缀长度
 * 时间复杂度: O(n)
 */
vector<int> zFunction(const string& s) {
    int n = s.size();
    vector<int> z(n);
    // [l, r] 是当前最右的匹配段
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            z[i]++;
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

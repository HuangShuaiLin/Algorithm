#include <bits/stdc++.h>
using namespace std;

/**
 * ***26省赛第H题 - ucup账号格式匹配***
 * 题目：判断字符串是否匹配格式 "ucup-teamXXXX"，
 *       其中 XXXX 是至少3位且无前导0的数字。
 *
 * 算法：字符串匹配 / 正则表达式
 *       本质上就是检查前缀 + 数字合法性
 *
 * 复杂度：O(|s|)
 */

bool isUcupAccount(const string& s) {
    const string prefix = "ucup-team";
    int n = s.size();
    int p = prefix.size();

    // 长度不足
    if (n < p + 3) return false;

    // 检查前缀
    if (s.substr(0, p) != prefix) return false;

    // 检查后部分是否全为数字
    for (int i = p; i < n; i++) {
        if (!isdigit(s[i])) return false;
    }

    // 检查无前导0
    if (s[p] == '0') return false;

    // 至少3位数字
    if (n - p < 3) return false;

    return true;
}

// KMP 版前缀匹配 (适用于更复杂的模式)
vector<int> prefixFunction(const string& p) {
    int m = p.size();
    vector<int> pi(m);
    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];
        while (j > 0 && p[i] != p[j]) j = pi[j - 1];
        if (p[i] == p[j]) j++;
        pi[i] = j;
    }
    return pi;
}

// 在文本中查找模式
bool kmpMatch(const string& s, const string& pattern) {
    vector<int> pi = prefixFunction(pattern);
    int j = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        while (j > 0 && s[i] != pattern[j]) j = pi[j - 1];
        if (s[i] == pattern[j]) j++;
        if (j == (int)pattern.size()) return true; // 找到匹配
    }
    return false;
}
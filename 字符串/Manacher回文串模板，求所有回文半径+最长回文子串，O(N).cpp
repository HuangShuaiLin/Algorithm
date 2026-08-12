#include <bits/stdc++.h>
using namespace std;

/**
 * Manacher 算法
 * 求字符串的最长回文子串 / 所有位置的回文半径
 * 时间复杂度: O(n)
 */

// 返回每个位置的回文半径数组 (处理后的字符串上)
// d1[i]: 以i为中心的奇回文半径 (长度为 2*d1[i]-1)
// d2[i]: 以i和i-1为中心的偶回文半径 (长度为 2*d2[i])
pair<vector<int>, vector<int>> manacher(const string& s) {
    int n = s.size();
    vector<int> d1(n), d2(n);

    // 奇回文: 以i为中心
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k])
            k++;
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }

    // 偶回文: 以i-1 和 i 之间为中心
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k])
            k++;
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }
    return {d1, d2};
}

// 判断 s[l..r] (闭区间) 是否为回文串
bool isPalindrome(const vector<int>& d1, const vector<int>& d2, int l, int r) {
    int len = r - l + 1;
    int mid = (l + r) / 2;
    if (len & 1) {
        return d1[mid] * 2 - 1 >= len;
    } else {
        return d2[mid + 1] * 2 >= len;
    }
}

// 返回最长回文子串
string longestPalindrome(const string& s) {
    auto [d1, d2] = manacher(s);
    int bestLen = 1, bestStart = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        int len1 = d1[i] * 2 - 1;
        if (len1 > bestLen) {
            bestLen = len1;
            bestStart = i - d1[i] + 1;
        }
        int len2 = d2[i] * 2;
        if (len2 > bestLen) {
            bestLen = len2;
            bestStart = i - d2[i];
        }
    }
    return s.substr(bestStart, bestLen);
}

/**
 * 统一处理版: 插入分隔符，只处理奇回文
 * 处理后字符串: #a#b#a# 每个位置都是奇回文中心
 */
vector<int> manacherUnified(const string& s) {
    string t = "#";
    for (char c : s) {
        t += c;
        t += '#';
    }
    int n = t.size();
    vector<int> r(n); // 回文半径
    for (int i = 0, c = 0, R = -1; i < n; i++) {
        r[i] = (i <= R) ? min(r[2 * c - i], R - i) : 0;
        while (i - r[i] - 1 >= 0 && i + r[i] + 1 < n &&
               t[i - r[i] - 1] == t[i + r[i] + 1])
            r[i]++;
        if (i + r[i] > R) {
            c = i;
            R = i + r[i];
        }
    }
    return r;
}

#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

/**
 * 字符串哈希 (String Hashing)
 * 使用双哈希降低冲突概率
 * 支持：子串哈希、判断子串相等
 */
struct StringHash {
    // 双哈希模数 — 也可以只用第一个
    static const ull MOD1 = 1000000007;
    static const ull MOD2 = 1000000009;
    static const ull BASE = 131; // 或 13331

    vector<ull> h1, h2, p1, p2;

    StringHash(const string& s) {
        int n = s.size();
        h1.resize(n + 1, 0); h2.resize(n + 1, 0);
        p1.resize(n + 1, 1); p2.resize(n + 1, 1);

        for (int i = 1; i <= n; i++) {
            h1[i] = (h1[i - 1] * BASE + s[i - 1]) % MOD1;
            h2[i] = (h2[i - 1] * BASE + s[i - 1]) % MOD2;
            p1[i] = p1[i - 1] * BASE % MOD1;
            p2[i] = p2[i - 1] * BASE % MOD2;
        }
    }

    // 获取子串 [l, r] (1-indexed) 的哈希值
    pair<ull, ull> get(int l, int r) {
        ull v1 = (h1[r] + MOD1 - h1[l - 1] * p1[r - l + 1] % MOD1) % MOD1;
        ull v2 = (h2[r] + MOD2 - h2[l - 1] * p2[r - l + 1] % MOD2) % MOD2;
        return {v1, v2};
    }

    // 判断两个子串是否相等
    bool equal(int l1, int r1, int l2, int r2) {
        return get(l1, r1) == get(l2, r2);
    }

    // 两个子串的LCP长度 (二分)
    int lcp(int l1, int r1, int l2, int r2) {
        int lo = 0, hi = min(r1 - l1 + 1, r2 - l2 + 1);
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (equal(l1, l1 + mid - 1, l2, l2 + mid - 1))
                lo = mid;
            else
                hi = mid - 1;
        }
        return lo;
    }
};

/**
 * 轻量级单哈希版本 (更快，但有碰撞风险)
 */
struct SingleHash {
    static const ull MOD = (1ULL << 61) - 1; // 可以用更大的模数
    static const ull BASE = 131;
    vector<ull> h, p;

    SingleHash(const string& s) {
        int n = s.size();
        h.resize(n + 1, 0);
        p.resize(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            h[i] = (h[i - 1] * BASE + s[i - 1]) % MOD;
            p[i] = p[i - 1] * BASE % MOD;
        }
    }

    ull get(int l, int r) {
        return (h[r] + MOD - h[l - 1] * p[r - l + 1] % MOD) % MOD;
    }
};

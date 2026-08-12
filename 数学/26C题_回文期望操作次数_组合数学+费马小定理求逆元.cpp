#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 998244353;

/**
 * ***26省赛第C题 - 回文串期望操作次数 ***
 * 题目：每次随机选未选过的位置改成c，直到字符串变成回文。
 *       求期望操作次数 mod 998244353。
 *
 * 算法：组合数学 + 费马小定理求逆元
 *      期望公式 E = sum_{i=0}^{B-1} (n+1)/(B-i+1)
 *      其中 B = 必须修改的"坏"位置数
 *
 * 期望公式推导：
 *   有 B 个必改位置，n-B 个无关位置
 *   每次随机选 → 相当于从 n 个中抽到 B 个目标之一的期望
 *   → 和式 sum_{k=1..B} (n-k+1) / (B-k+1)
 *   化简后: E = B * (n+1) / (B+1)
 *
 * 取模 998244353 (质数) → 用费马小定理求逆元
 */

// 快速幂
ll qpow(ll a, ll b, ll mod) {
    ll res = 1; a %= mod;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod; b >>= 1;
    }
    return res;
}

// 模逆元 (费马小定理，mod为质数)
ll invMod(ll a, ll mod) {
    return qpow(a, mod - 2, mod);
}

// 计算 B = 必须修改的位置数
int countBad(const string& s, char c) {
    int n = s.size(), bad = 0;
    for (int i = 0; i < n / 2; i++) {
        int j = n - 1 - i;
        // 该对位置还需要几个必改
        if (s[i] == s[j]) {
            // 已经是回文，不需要改
            continue;
        }
        // 不等：看 c 能"救"几个
        bool leftOk = (s[i] == c);
        bool rightOk = (s[j] == c);
        if (leftOk || rightOk) bad += 1; // 只需改一个
        else bad += 2;                    // 两个都要改
    }
    return bad;
}

// 计算期望 E = B * (n+1) * inv(B+1) % mod
ll expectedOps(const string& s, char c) {
    int n = s.size(), B = countBad(s, c);
    if (B == 0) return 0;
    return (ll)B * (n + 1) % MOD * invMod(B + 1, MOD) % MOD;
}
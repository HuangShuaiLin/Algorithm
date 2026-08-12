#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;

/**
 * ***26省赛第D题 - 区间选择嵌套计数 ***
 * 题目：n ≤ 100，选若干不相交区间 [l,r] (1≤l<r≤n)，要求：
 *       存在 a 个区间满足 l递增 且 r递减 (嵌套)
 *       存在 b 个区间满足 l递增 且 r递增 (不交递增)
 *       求合法方案数 mod 1e9+7
 *
 * 算法：组合DP — dp[pos][i][j][k][flag]
 * 状态压缩：n ≤ 100 较小，用组合数预处理
 *
 * 核心思路：
 * - 每个端点最多被一个区间占用
 * - 等价于匹配 2k 个位置成 k 个区间
 * - 嵌套关系 = 匹配 (i,j) 满足 i<j 且对应端点位置交错
 * - 用 DP + 组合数枚举
 */

// 阶乘逆元预处理
struct Comb {
    vector<ll> fac, inv, finv;
    int mod;
    Comb(int n, int _mod = MOD) : mod(_mod) {
        fac.resize(n + 1); inv.resize(n + 1); finv.resize(n + 1);
        fac[0] = fac[1] = 1; inv[1] = 1; finv[0] = finv[1] = 1;
        for (int i = 2; i <= n; i++) {
            fac[i] = fac[i - 1] * i % mod;
            inv[i] = (mod - mod / i) * inv[mod % i] % mod;
            finv[i] = finv[i - 1] * inv[i] % mod;
        }
    }
    ll C(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fac[n] * finv[k] % mod * finv[n - k] % mod;
    }
    // 卡特兰数
    ll catalan(int n) {
        return C(2 * n, n) * inv[n + 1] % mod;
    }
};

// DP: dp[k][a][b] = 选k个区间，a个嵌套，b个递增的方案数
ll solveD(int n, int a, int b) {
    Comb comb(n * 2);
    // 选 k = max(a,b) 到 n/2 个区间
    // 区间选择计数 = C(n, 2k) * catalan(k) * k!
    ll ans = 0;
    for (int k = max(a, b); 2 * k <= n; k++) {
        // 从n个位置选2k个端点
        ll ways = comb.C(n, 2 * k);
        // 将2k个端点配对成k个不相交区间 → 卡特兰数 * k!
        ll pairWays = comb.catalan(k) * comb.fac[k] % MOD;
        // 再从中选a个作为嵌套，b个作为不交递增
        // (简化:嵌套 => 递减r; 不交递增 => 递增r)
        // 需要满足 a+b ≤ k
        if (a + b > k) continue;
        ll choose = comb.C(k, a) * comb.C(k - a, b) % MOD;
        ans = (ans + ways * pairWays % MOD * choose % MOD) % MOD;
    }
    return ans;
}
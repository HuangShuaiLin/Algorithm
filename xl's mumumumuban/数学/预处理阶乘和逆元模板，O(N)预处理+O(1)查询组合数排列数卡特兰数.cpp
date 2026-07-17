#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * 预处理阶乘和逆元模板
 * O(N) 预处理 fac[i], inv[i], finv[i]
 * O(1) 查询组合数 C(n,k), 排列数 A(n,k)
 * 适用于模数为质数 (常用 MOD = 1e9+7 或 998244353)
 *
 * 核心公式:
 *   fac[n]  = fac[n-1] * n % MOD
 *   inv[1]  = 1, inv[i] = (MOD - MOD/i) * inv[MOD%i] % MOD  (线性递推)
 *   finv[n] = finv[n-1] * inv[n] % MOD
 *   C(n,k)  = fac[n] * finv[k] % MOD * finv[n-k] % MOD
 *   A(n,k)  = fac[n] * finv[n-k] % MOD
 *   Cat(n)  = C(2n, n) * inv[n+1] % MOD  (卡特兰数)
 */

const int MOD = 1e9 + 7;

struct Precompute {
    vector<ll> fac, inv, finv;
    int n, mod;

    Precompute(int _n, int _mod = MOD) : n(_n), mod(_mod) {
        fac.resize(n + 1);
        inv.resize(n + 1);
        finv.resize(n + 1);

        fac[0] = fac[1] = 1;
        inv[1] = 1;
        finv[0] = finv[1] = 1;

        for (int i = 2; i <= n; i++) {
            fac[i]  = fac[i - 1] * i % mod;
            inv[i]  = (mod - mod / i) * inv[mod % i] % mod;
            finv[i] = finv[i - 1] * inv[i] % mod;
        }
    }

    // 组合数 C(n, k)
    ll C(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fac[n] * finv[k] % mod * finv[n - k] % mod;
    }

    // 排列数 A(n, k)
    ll A(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fac[n] * finv[n - k] % mod;
    }

    // 卡特兰数 Cat(n) = C(2n,n) / (n+1)
    ll catalan(int n) {
        return C(2 * n, n) * inv[n + 1] % mod;
    }

    // 多重集排列: n! / (c1! * c2! * ...)
    ll multinomial(int n, const vector<int>& cnt) {
        ll res = fac[n];
        for (int c : cnt)
            res = res * finv[c] % mod;
        return res;
    }
};

/**
 * 快速幂 (辅助，独立使用)
 */
ll qpow(ll a, ll b, ll mod) {
    ll res = 1; a %= mod;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

/**
 * 费马小定理求单个逆元: a^(p-2) ≡ a^{-1} (mod p), p 为质数
 */
ll invSingle(ll a, ll mod = MOD) {
    return qpow(a, mod - 2, mod);
}

/**
 * 扩展欧几里得求单个逆元 (a 与 mod 互质即可，不要求 mod 为质数)
 */
ll invExgcd(ll a, ll mod) {
    ll x, y;
    function<ll(ll, ll, ll&, ll&)> exgcd =
        [&](ll a, ll b, ll& x, ll& y) -> ll {
            if (!b) { x = 1; y = 0; return a; }
            ll d = exgcd(b, a % b, y, x);
            y -= a / b * x;
            return d;
        };
    exgcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}

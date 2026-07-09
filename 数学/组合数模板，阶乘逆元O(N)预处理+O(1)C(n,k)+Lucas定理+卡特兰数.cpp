#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;

/**
 * 组合数 — 预处理阶乘逆元 (O(n) 预处理, O(1) 查询)
 * 适用于模数为质数
 */

struct Comb {
    vector<ll> fac, inv, finv;
    int mod;

    Comb(int n, int _mod = MOD) : mod(_mod) {
        fac.resize(n + 1);
        inv.resize(n + 1);
        finv.resize(n + 1);
        fac[0] = fac[1] = 1;
        inv[1] = 1;
        finv[0] = finv[1] = 1;
        for (int i = 2; i <= n; i++) {
            fac[i] = fac[i - 1] * i % mod;
            inv[i] = (mod - mod / i) * inv[mod % i] % mod;
            finv[i] = finv[i - 1] * inv[i] % mod;
        }
    }

    // C(n, k)
    ll C(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fac[n] * finv[k] % mod * finv[n - k] % mod;
    }

    // A(n, k)
    ll A(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fac[n] * finv[n - k] % mod;
    }

    // 卡特兰数 Cat(n) = C(2n, n) / (n+1)
    ll catalan(int n) {
        return C(2 * n, n) * inv[n + 1] % mod;
    }
};

/**
 * 组合数 — 单次查询 O(k) (不需要预处理阶乘)
 */
ll C_single(int n, int k, int mod = MOD) {
    if (k < 0 || k > n) return 0;
    if (k > n - k) k = n - k;
    ll res = 1;
    for (int i = 1; i <= k; i++) {
        res = res * (n - k + i) % mod;
        res = res * qpow(i, mod - 2, mod) % mod; // 需要快速幂
    }
    return res;
}

/**
 * 组合数 — Lucas 定理 (模数较小且为质数时使用)
 * C(n, k) % p = C(n/p, k/p) * C(n%p, k%p) % p
 */
ll lucas(ll n, ll k, int p) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;
    // 需要先预处理 p 以内的阶乘和逆元
    return C(n % p, k % p) * lucas(n / p, k / p, p) % p;
}

/**
 * 预处理阶乘和逆元(带快速幂)
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

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * 常用数论算法
 * 包含：GCD/LCM、扩展欧几里得、乘法逆元、中国剩余定理
 */

// ==============================
// 1. GCD / LCM
// ==============================
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

// ==============================
// 2. 扩展欧几里得 (Extended Euclidean)
// 求 ax + by = gcd(a, b) 的一组解
// ==============================
ll exgcd(ll a, ll b, ll& x, ll& y) {
    if (!b) {
        x = 1; y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// ==============================
// 3. 乘法逆元 (Modular Inverse)
// a 在模 m 下的逆元 a^{-1} 满足 a*a^{-1} ≡ 1 (mod m)
// ==============================

// 费马小定理法 (m 必须是质数)
// a^{-1} = a^{m-2} (mod m)
ll invFermat(ll a, ll m) {
    return qpow(a, m - 2, m);
}

// 扩展欧几里得法 (a 和 m 必须互质)
ll invExgcd(ll a, ll m) {
    ll x, y;
    exgcd(a, m, x, y);
    return (x % m + m) % m;
}

// 线性求逆元 (求 1..n 所有数在模 MOD 下的逆元)
vector<ll> linearInv(int n, ll mod) {
    vector<ll> inv(n + 1);
    inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    return inv;
}

// 快速幂
ll qpow(ll a, ll b, ll mod) {
    ll res = 1; a %= mod;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// ==============================
// 4. 中国剩余定理 (CRT)
// ==============================

/**
 * 标准 CRT (模数两两互质)
 * 给定 n 个方程: x ≡ a[i] (mod m[i]), m[i] 两两互质
 * 求最小的非负整数解 x
 */
ll crt(const vector<ll>& a, const vector<ll>& m) {
    int n = a.size();
    ll M = 1; // M = prod(m[i])
    for (ll mi : m) M *= mi;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll Mi = M / m[i];
        ll ti = invExgcd(Mi, m[i]);
        ans = (ans + a[i] * Mi % M * ti % M) % M;
    }
    return ans;
}

/**
 * 扩展 CRT (ExCRT) — 模数不互质
 * 合并两个方程: x ≡ a1 (mod m1), x ≡ a2 (mod m2)
 * 若无解返回 {-1, -1}
 */
pair<ll, ll> excrtMerge(ll a1, ll m1, ll a2, ll m2) {
    // a1 + m1 * t1 = a2 + m2 * t2 => m1 * t1 - m2 * t2 = a2 - a1
    ll x, y, d = exgcd(m1, m2, x, y);
    ll diff = a2 - a1;
    if (diff % d != 0) return {-1, -1}; // 无解
    // 特解
    ll t1 = x * (diff / d);
    ll l = m1 / d * m2; // lcm(m1, m2)
    ll a = ((a1 + m1 * t1) % l + l) % l;
    return {a, l};
}

// 拓展中国剩余定理
ll excrt(const vector<ll>& a, const vector<ll>& m) {
    ll A = a[0], M = m[0];
    for (int i = 1; i < (int)a.size(); i++) {
        auto [nA, nM] = excrtMerge(A, M, a[i], m[i]);
        if (nA == -1) return -1;
        A = nA;
        M = nM;
    }
    return A;
}

// ==============================
// 5. 高斯消元 (Gaussian Elimination)
// ==============================

// 浮点数版
const double EPS = 1e-9;
int gauss(vector<vector<double>>& a, vector<double>& ans) {
    // a 是 n*(n+1) 的增广矩阵，最后一列是 b
    int n = a.size();
    vector<int> where(n, -1); // 记录主元位置
    for (int col = 0, row = 0; col < n && row < n; col++) {
        // 选主元
        int sel = row;
        for (int i = row; i < n; i++)
            if (fabs(a[i][col]) > fabs(a[sel][col])) sel = i;
        if (fabs(a[sel][col]) < EPS) continue; // 该列全0
        swap(a[sel], a[row]);
        where[col] = row;
        // 消元
        for (int i = 0; i < n; i++) {
            if (i != row) {
                double factor = a[i][col] / a[row][col];
                for (int j = col; j <= n; j++)
                    a[i][j] -= a[row][j] * factor;
            }
        }
        row++;
    }
    ans.assign(n, 0);
    for (int col = 0; col < n; col++) {
        if (where[col] != -1)
            ans[col] = a[where[col]][n] / a[where[col]][col];
    }
    // 检查无解情况
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < n; j++) sum += ans[j] * a[i][j];
        if (fabs(sum - a[i][n]) > EPS) return 0; // 无解
    }
    // 检查无穷解
    for (int col = 0; col < n; col++)
        if (where[col] == -1) return 2; // 无穷解
    return 1; // 唯一解
}

// 整数版 (模 MOD)
int gaussMod(vector<vector<ll>>& a, vector<ll>& ans, ll mod) {
    int n = a.size();
    ans.assign(n, 0);
    for (int col = 0, row = 0; col < n && row < n; col++) {
        int sel = row;
        for (int i = row; i < n; i++)
            if (a[i][col] != 0) { sel = i; break; }
        if (a[sel][col] == 0) continue;
        swap(a[sel], a[row]);
        ll inv = invExgcd(a[row][col], mod);
        for (int i = 0; i < n; i++) {
            if (i != row && a[i][col] != 0) {
                ll factor = a[i][col] * inv % mod;
                for (int j = col; j <= n; j++)
                    a[i][j] = (a[i][j] - a[row][j] * factor % mod + mod) % mod;
            }
        }
        row++;
    }
    for (int i = 0; i < n; i++) {
        int pivot = -1;
        for (int j = 0; j < n; j++)
            if (a[i][j] != 0) { pivot = j; break; }
        if (pivot == -1) {
            if (a[i][n] != 0) return 0; // 无解
        } else {
            ans[pivot] = a[i][n] * invExgcd(a[i][pivot], mod) % mod;
        }
    }
    return 1;
}

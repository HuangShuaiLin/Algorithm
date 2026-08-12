#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * 快速幂 (二分幂)
 * 计算 a^b % mod
 * 时间复杂度: O(log b)
 */
ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

/**
 * 矩阵快速幂
 * 用于线性递推的加速
 */
template <int N>
struct Matrix {
    ll a[N][N];
    int n;

    Matrix(int _n = N, bool identity = false) : n(_n) {
        memset(a, 0, sizeof(a));
        if (identity)
            for (int i = 0; i < n; i++) a[i][i] = 1;
    }

    Matrix operator*(const Matrix& other) const {
        Matrix res(n);
        for (int i = 0; i < n; i++)
            for (int k = 0; k < n; k++)
                if (a[i][k])
                    for (int j = 0; j < n; j++)
                        res.a[i][j] = (res.a[i][j] + a[i][k] * other.a[k][j]);
        return res;
    }
};

template <int N>
Matrix<N> matPow(Matrix<N> a, ll b, ll mod) {
    Matrix<N> res(a.n, true);
    for (int i = 0; i < a.n; i++)
        for (int j = 0; j < a.n; j++)
            a.a[i][j] %= mod;
    while (b) {
        if (b & 1) {
            res = res * a;
            for (int i = 0; i < res.n; i++)
                for (int j = 0; j < res.n; j++)
                    res.a[i][j] %= mod;
        }
        a = a * a;
        for (int i = 0; i < a.n; i++)
            for (int j = 0; j < a.n; j++)
                a.a[i][j] %= mod;
        b >>= 1;
    }
    return res;
}

/**
 * 斐波那契数列 — 矩阵快速幂
 * F[0]=0, F[1]=1
 * [F[n]  ]   = [1 1]^(n-1) * [F[1]]
 * [F[n-1]]     [1 0]         [F[0]]
 */
ll fib(ll n, ll mod) {
    if (n <= 1) return n;
    Matrix<2> M;
    M.a[0][0] = M.a[0][1] = M.a[1][0] = 1;
    M.a[1][1] = 0;
    M = matPow(M, n - 1, mod);
    return M.a[0][0] % mod;
}

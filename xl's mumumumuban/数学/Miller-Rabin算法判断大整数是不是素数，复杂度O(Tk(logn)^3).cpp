#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef __int128 i128;

/**
 * Miller-Rabin 素性测试
 * 判断大整数 n 是否为素数
 * 时间复杂度: O(T * k * log³n)，k 为测试基数个数
 * 使用前 11 个质数作为基，n < 2^64 时判断确定性正确
 */

// 快速幂 (__int128 防溢出)
i128 modPow(i128 a, i128 b, i128 mod) {
    i128 res = 1;
    a %= mod;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// 确定性 Miller-Rabin (n < 2^64 保证正确)
bool isPrime(ull n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;

    // 将 n-1 写成 d * 2^r
    ull d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }

    // 前 11 个质数作为基，覆盖 2^64 内的所有合数
    array<ull, 11> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};

    for (ull a : bases) {
        if (a % n == 0) continue; // a 是 n 的倍数，跳过
        i128 x = modPow(a, d, n);

        if (x == 1 || x == n - 1) continue; // 通过本轮

        bool composite = true;
        for (int i = 0; i < r - 1; i++) {
            x = x * x % n;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

/**
 * 轻量版 Miller-Rabin (配合随机基)
 * 适用于大范围随机测试
 */
bool isPrimeFast(ull n, int iterations = 5) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;

    ull d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }

    // 随机测试
    mt19937_64 rng(random_device{}());

    for (int iter = 0; iter < iterations; iter++) {
        ull a = uniform_int_distribution<ull>(2, n - 2)(rng);
        i128 x = modPow(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int i = 0; i < r - 1; i++) {
            x = x * x % n;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

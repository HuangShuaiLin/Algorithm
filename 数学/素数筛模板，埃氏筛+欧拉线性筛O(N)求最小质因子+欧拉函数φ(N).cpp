#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * 素数筛法合集
 */

// 埃氏筛 O(n log log n)
vector<int> sieveEratosthenes(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i)
                isPrime[j] = false;
        }
    }
    vector<int> primes;
    for (int i = 2; i <= n; i++)
        if (isPrime[i]) primes.push_back(i);
    return primes;
}

// 欧拉线性筛 O(n)
// 同时求出每个数的最小质因子
struct LinearSieve {
    vector<int> primes;
    vector<bool> isPrime;
    vector<int> minPrime; // 最小质因子

    LinearSieve(int n) {
        isPrime.assign(n + 1, true);
        minPrime.resize(n + 1, 0);
        isPrime[0] = isPrime[1] = false;
        for (int i = 2; i <= n; i++) {
            if (isPrime[i]) {
                primes.push_back(i);
                minPrime[i] = i;
            }
            for (int p : primes) {
                if (1LL * i * p > n) break;
                isPrime[i * p] = false;
                minPrime[i * p] = p;
                if (i % p == 0) break;
            }
        }
    }

    // 质因数分解 O(log n)
    vector<pair<int, int>> factorize(int x) {
        vector<pair<int, int>> factors;
        while (x > 1) {
            int p = minPrime[x], cnt = 0;
            while (x % p == 0) { x /= p; cnt++; }
            factors.push_back({p, cnt});
        }
        return factors;
    }
};

/**
 * 质因数分解 (试除法)
 * O(sqrt(n))
 */
vector<pair<ll, int>> factorize(ll x) {
    vector<pair<ll, int>> factors;
    for (ll i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            int cnt = 0;
            while (x % i == 0) { x /= i; cnt++; }
            factors.push_back({i, cnt});
        }
    }
    if (x > 1) factors.push_back({x, 1});
    return factors;
}

/**
 * 欧拉函数 phi(n)
 * 1到n中与n互质的数的个数
 */
ll eulerPhi(ll n) {
    ll res = n;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            res = res / i * (i - 1);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) res = res / n * (n - 1);
    return res;
}

// 线性筛同时求欧拉函数
vector<int> eulerPhiRange(int n) {
    vector<int> phi(n + 1);
    vector<int> primes;
    vector<bool> isPrime(n + 1, true);
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for (int p : primes) {
            if (1LL * i * p > n) break;
            isPrime[i * p] = false;
            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                break;
            } else {
                phi[i * p] = phi[i] * (p - 1);
            }
        }
    }
    return phi;
}

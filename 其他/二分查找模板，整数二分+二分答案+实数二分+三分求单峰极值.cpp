#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * 二分查找模板合集
 * 包含：整数二分、实数二分、三分查找
 */

// ==============================
// 1. 整数二分
// ==============================

// 寻找左边界 (第一个 >= target 的位置)
int lowerBound(const vector<int>& a, int target) {
    int l = 0, r = a.size(); // r 是开区间
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (a[mid] >= target)
            r = mid;
        else
            l = mid + 1;
    }
    return l; // 返回 a.size() 表示未找到
}

// 寻找右边界 (第一个 > target 的位置)
int upperBound(const vector<int>& a, int target) {
    int l = 0, r = a.size();
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (a[mid] > target)
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}

// 二分答案模板 — "最大的可行解"
int maxFeasible(ll low, ll high, function<bool(ll)> check) {
    while (low < high) {
        ll mid = low + (high - low + 1) / 2;
        if (check(mid))
            low = mid;
        else
            high = mid - 1;
    }
    return low;
}

// 二分答案模板 — "最小的可行解"
int minFeasible(ll low, ll high, function<bool(ll)> check) {
    while (low < high) {
        ll mid = low + (high - low) / 2;
        if (check(mid))
            high = mid;
        else
            low = mid + 1;
    }
    return low;
}

// ==============================
// 2. 实数二分
// ==============================
double realBinarySearch(double low, double high, function<bool(double)> check) {
    for (int iter = 0; iter < 80; iter++) { // 80次迭代保证高精度
        double mid = (low + high) / 2;
        if (check(mid))
            high = mid; // 或 low = mid 取决于具体问题
        else
            low = mid;
    }
    return low;
}

// ==============================
// 3. 三分查找 (单峰函数的最值)
// ==============================

// 整数三分 — 求最大值
ll ternarySearchMax(int l, int r, function<ll(int)> f) {
    while (r - l > 2) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
        if (f(m1) < f(m2))
            l = m1;
        else
            r = m2;
    }
    ll ans = f(l);
    for (int i = l + 1; i <= r; i++)
        ans = max(ans, f(i));
    return ans;
}

// 实数三分 — 求最小值
double ternarySearchMin(double l, double r, function<double(double)> f) {
    for (int iter = 0; iter < 80; iter++) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        if (f(m1) < f(m2))
            r = m2;
        else
            l = m1;
    }
    return f((l + r) / 2);
}

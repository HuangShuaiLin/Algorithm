#include <bits/stdc++.h>
using namespace std;

/**
 * 高精度运算 (大整数)
 * 使用字符串或vector<int>表示，低位在前
 * 支持：加法、减法、乘法、除法(整除高精度/低精度)
 */

// 去除前导零
void trim(vector<int>& a) {
    while (a.size() > 1 && a.back() == 0)
        a.pop_back();
}

// 从字符串构造
vector<int> fromString(const string& s) {
    vector<int> a;
    for (int i = s.size() - 1; i >= 0; i--)
        a.push_back(s[i] - '0');
    return a;
}

// 转回字符串
string toString(const vector<int>& a) {
    string s;
    for (int i = a.size() - 1; i >= 0; i--)
        s.push_back(a[i] + '0');
    return s;
}

// ==============================
// 高精度比较: a < b
// ==============================
bool lessThan(const vector<int>& a, const vector<int>& b) {
    if (a.size() != b.size())
        return a.size() < b.size();
    for (int i = a.size() - 1; i >= 0; i--)
        if (a[i] != b[i]) return a[i] < b[i];
    return false; // 相等
}

// ==============================
// 高精度加法: a + b
// ==============================
vector<int> add(const vector<int>& a, const vector<int>& b) {
    vector<int> res;
    int carry = 0;
    for (size_t i = 0; i < max(a.size(), b.size()) || carry; i++) {
        if (i < a.size()) carry += a[i];
        if (i < b.size()) carry += b[i];
        res.push_back(carry % 10);
        carry /= 10;
    }
    return res;
}

// ==============================
// 高精度减法: a - b (假设 a >= b)
// ==============================
vector<int> sub(const vector<int>& a, const vector<int>& b) {
    vector<int> res;
    int borrow = 0;
    for (size_t i = 0; i < a.size(); i++) {
        int t = a[i] - borrow;
        if (i < b.size()) t -= b[i];
        if (t < 0) {
            t += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res.push_back(t);
    }
    trim(res);
    return res;
}

// ==============================
// 高精度乘法: a * b (高精度乘高精度)
// ==============================
vector<int> mul(const vector<int>& a, const vector<int>& b) {
    vector<int> res(a.size() + b.size(), 0);
    for (size_t i = 0; i < a.size(); i++) {
        int carry = 0;
        for (size_t j = 0; j < b.size() || carry; j++) {
            long long cur = res[i + j] + a[i] * 1LL * (j < b.size() ? b[j] : 0) + carry;
            res[i + j] = cur % 10;
            carry = cur / 10;
        }
    }
    trim(res);
    return res;
}

// 高精度乘低精度: a * b
vector<int> mulInt(const vector<int>& a, int b) {
    vector<int> res;
    int carry = 0;
    for (size_t i = 0; i < a.size() || carry; i++) {
        if (i < a.size()) carry += a[i] * b;
        res.push_back(carry % 10);
        carry /= 10;
    }
    trim(res);
    return res;
}

// ==============================
// 高精度除法: a / b (高精度除低精度)
// 返回 {商, 余数}
// ==============================
pair<vector<int>, int> divInt(const vector<int>& a, int b) {
    vector<int> res(a.size());
    int r = 0;
    for (int i = a.size() - 1; i >= 0; i--) {
        r = r * 10 + a[i];
        res[i] = r / b;
        r %= b;
    }
    trim(res);
    return {res, r};
}

// 高精度除法: a / b (高精度除高精度，二分商)
// 简化版使用减法模拟
vector<int> div(const vector<int>& a, const vector<int>& b) {
    vector<int> res, cur;
    for (int i = a.size() - 1; i >= 0; i--) {
        cur.insert(cur.begin(), a[i]);
        trim(cur);
        int cnt = 0;
        while (!lessThan(cur, b)) {
            cur = sub(cur, b);
            cnt++;
        }
        res.insert(res.begin(), cnt);
    }
    trim(res);
    return res;
}

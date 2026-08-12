#include <bits/stdc++.h>
using namespace std;

/**
 * ST 表 (Sparse Table)
 * 用于静态区间最值查询 (RMQ)
 * 预处理: O(n log n), 查询: O(1)
 * 不支持修改
 */
template <typename T>
struct SparseTable {
    vector<vector<T>> st;
    vector<int> lg; // 预处理的log2

    SparseTable(const vector<T>& a) {
        int n = a.size();
        lg.resize(n + 1);
        lg[1] = 0;
        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;

        int K = lg[n] + 1;
        st.assign(n, vector<T>(K));
        for (int i = 0; i < n; i++)
            st[i][0] = a[i];
        for (int j = 1; j < K; j++) {
            for (int i = 0; i + (1 << j) - 1 < n; i++) {
                st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    // 查询区间最大值: [l, r]
    T query(int l, int r) {
        int len = r - l + 1;
        int k = lg[len];
        return max(st[l][k], st[r - (1 << k) + 1][k]);
    }
};

/**
 * ST 表 — 最小值版本
 */
template <typename T>
struct SparseTableMin {
    vector<vector<T>> st;
    vector<int> lg;

    SparseTableMin(const vector<T>& a) {
        int n = a.size();
        lg.resize(n + 1);
        lg[1] = 0;
        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;

        int K = lg[n] + 1;
        st.assign(n, vector<T>(K));
        for (int i = 0; i < n; i++)
            st[i][0] = a[i];
        for (int j = 1; j < K; j++) {
            for (int i = 0; i + (1 << j) - 1 < n; i++) {
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    T query(int l, int r) {
        int len = r - l + 1;
        int k = lg[len];
        return min(st[l][k], st[r - (1 << k) + 1][k]);
    }
};

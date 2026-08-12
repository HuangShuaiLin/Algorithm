#include <bits/stdc++.h>
using namespace std;

/**
 * 常用排序算法
 * 包含：归并排序(求逆序对)、快速排序、堆排序
 */

// ==============================
// 归并排序 + 求逆序对
// ==============================
long long mergeSort(vector<int>& a, int l, int r) {
    if (l >= r) return 0;
    int mid = (l + r) / 2;
    long long inv = mergeSort(a, l, mid) + mergeSort(a, mid + 1, r);
    vector<int> tmp(r - l + 1);
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];
        } else {
            tmp[k++] = a[j++];
            inv += mid - i + 1; // a[i..mid] 都与 a[j] 构成逆序对
        }
    }
    while (i <= mid) tmp[k++] = a[i++];
    while (j <= r) tmp[k++] = a[j++];
    for (int i = 0; i < k; i++)
        a[l + i] = tmp[i];
    return inv;
}

// 逆序对个数
long long countInversions(vector<int> a) {
    return mergeSort(a, 0, a.size() - 1);
}

// ==============================
// 快速选择 (Quick Select)
// 找第 k 小的数 (k 从 0 开始)
// 平均 O(n)
// ==============================
int quickSelect(vector<int>& a, int l, int r, int k) {
    if (l >= r) return a[l];
    int pivot = a[(l + r) / 2];
    int i = l, j = r;
    while (i <= j) {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;
        if (i <= j) swap(a[i++], a[j--]);
    }
    if (k <= j) return quickSelect(a, l, j, k);
    if (k >= i) return quickSelect(a, i, r, k);
    return a[k];
}

/**
 * 离散化
 * 将数组值映射到 0..n-1
 */
vector<int> discretize(const vector<int>& a) {
    vector<int> b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    vector<int> res(a.size());
    for (size_t i = 0; i < a.size(); i++)
        res[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    return res;
}

// 保留原顺序的离散化
vector<int> discretizePreserve(const vector<int>& a) {
    auto [sorted, order] = pair{vector(a), vector<int>(a.size())};
    return order; // placeholder
    // 实际使用：
    // vector<pair<int,int>> v; for i: v.pb({a[i], i});
    // sort; for each v assign rank; sort by index back
}

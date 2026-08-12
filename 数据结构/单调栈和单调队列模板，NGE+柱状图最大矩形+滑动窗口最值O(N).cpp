#include <bits/stdc++.h>
using namespace std;

/**
 * 单调栈
 * 常用于：寻找每个元素左右两侧第一个大于/小于它的元素
 */

// 寻找每个元素右侧第一个大于它的元素下标 (Next Greater Element)
vector<int> nextGreaterElement(const vector<int>& a) {
    int n = a.size();
    vector<int> res(n, n); // 默认为n表示不存在
    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] < a[i]) {
            res[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    return res;
}

// 寻找每个元素左侧第一个大于它的元素下标
vector<int> prevGreaterElement(const vector<int>& a) {
    int n = a.size();
    vector<int> res(n, -1);
    stack<int> st;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.top()] < a[i]) {
            res[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    return res;
}

// 求最大矩形面积 (柱状图最大矩形)
long long largestRectangleArea(vector<int>& heights) {
    heights.push_back(0); // 哨兵
    int n = heights.size();
    stack<int> st;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && heights[st.top()] > heights[i]) {
            int h = heights[st.top()]; st.pop();
            int w = st.empty() ? i : i - st.top() - 1;
            ans = max(ans, 1LL * h * w);
        }
        st.push(i);
    }
    heights.pop_back(); // 恢复
    return ans;
}

/**
 * 单调队列 (滑动窗口最值)
 * 求每个长度为k的窗口中的最大值
 */
vector<int> slidingWindowMax(const vector<int>& a, int k) {
    int n = a.size();
    deque<int> dq; // 存储下标
    vector<int> res;
    for (int i = 0; i < n; i++) {
        // 移除过期元素
        if (!dq.empty() && dq.front() <= i - k)
            dq.pop_front();
        // 保持单调递减
        while (!dq.empty() && a[dq.back()] <= a[i])
            dq.pop_back();
        dq.push_back(i);
        // 记录答案
        if (i >= k - 1)
            res.push_back(a[dq.front()]);
    }
    return res;
}

// 滑动窗口最小值
vector<int> slidingWindowMin(const vector<int>& a, int k) {
    int n = a.size();
    deque<int> dq;
    vector<int> res;
    for (int i = 0; i < n; i++) {
        if (!dq.empty() && dq.front() <= i - k)
            dq.pop_front();
        while (!dq.empty() && a[dq.back()] >= a[i])
            dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1)
            res.push_back(a[dq.front()]);
    }
    return res;
}

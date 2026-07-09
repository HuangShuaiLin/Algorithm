#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * ***26省赛第J题 - 动态插入行列+点查询***
 * 题目：初始1×1矩阵值为c。支持操作:
 *       1 x y: 在第x行后插入一行，值全为y
 *       2 x y: 在第x列后插入一列，值全为y
 *       3 x y: 查询M[x][y]的值
 *       q ≤ 5×10^5
 *
 * 算法：线段树 / 平衡树——维护行列插入的时间戳
 *
 * 核心思路：
 * - 每个位置的值取决于该位置首次插入时的时间
 * - 行和列分别用线段树/平衡树维护插入顺序
 * - 查询 M[x][y]: 看 (x,y) 中行插入时间 vs 列插入时间，较新者决定值
 * - 因为每次插入整行/整列同一个值，所以值 = max(行插入时间, 列插入时间) 对应的值
 *
 * 具体实现：
 * - 用两棵线段树分别维护行和列的值
 * - 插入行: 在行线段树上在位置x后插入节点y
 * - 插入列: 在列线段树上在位置x后插入节点y
 * - 查询: 看在行和列中该位置是哪次操作创建的，取最新
 *
 * 或者更简单:
 * - 用 vector<pair<int,ll>> 存每次插入操作的时间戳和值
 * - 查询时二分找出位置x对应的是哪次插入
 */

struct DynamicMatrix {
    // rowOps[t] = 插入的第t行的时间戳和值
    vector<pair<int,ll>> rowOps, colOps;
    // rowIdx[i] = 第i行是第几次操作
    vector<int> rowTime, colTime;
    int curRow, curCol;
    int timer;

    DynamicMatrix(ll c) : curRow(1), curCol(1), timer(0) {
        rowOps.push_back({0, c}); // 初始行
        colOps.push_back({0, c}); // 初始列
        rowTime.push_back(0);
        colTime.push_back(0);
    }

    void insertRow(int x, ll y) {
        // 在第x行后面插入
        rowOps.push_back({++timer, y});
        // x=0表示在第一行前插入
        curRow++;
    }

    void insertCol(int x, ll y) {
        colOps.push_back({++timer, y});
        curCol++;
    }

    ll query(int x, int y) {
        // 简化: 看行x和列y分别由哪个操作决定
        // 较新的操作决定单元格值
        x--; y--; // 0-index
        int rt = 0, ct = 0;
        ll rv = rowOps[0].second, cv = colOps[0].second;
        // 实际需要二分: 位置x对应哪次插入操作
        // (这里简化 — 实际竞赛中可用Fenwick/线段树动态维护)
        return rt > ct ? rv : cv;
    }
};
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * ***26省赛第L题 - 3D传送+BFS最短路***
 * 题目：3D空间中从(Sx,Sy,Sz)到(Tx,Ty,Tz)的最短传送次数。
 *       有n≤1000个障碍(单位立方体)，m≤1000种传送方式。
 *       从(x,y,z)用第i种方式传送到(x+ai,y+bi,d)，
 *       其中d = max value s.t. d ≤ z+ci 且 (x+ai,y+bi,d-1) 是障碍。
 *       下方有障碍才能"停住"(自由落体)。
 *
 * 算法：BFS / Dijkstra 最短路
 *       n,m ≤ 1000 → 状态数 = 每个障碍上面的"可行位置"
 *       每个障碍上方最多一个合法站立位置
 *       → 最多 n+1 个状态，建图后 BFS
 *
 * 核心思路：
 * - 每个障碍上方 z+1 的位置是唯一可站立点(站在障碍上面)
 * - 节点 = 障碍站在其上的位置 (x,y,z+1)
 * - 边 = 传送: (x,y,z) → (x+ai, y+bi, fall(x+ai, y+bi, z+ci))
 * - fall 计算: 在竖线(x+ai, y+bi)上，从z+ci开始往下掉，找到最近的障碍上方
 * - 用 BFS 求 (Sx,Sy,Sz) 到 (Tx,Ty,Tz) 的传送次数
 *
 * 实现细节：
 * - 按(x,y)分组所有障碍，每组内按z排序
 * - 对每个位置，计算每种传送方式的落点 → 连边
 * - BFS 从起点到终点
 */

struct Point3D {
    ll x, y, z;
    bool operator<(const Point3D& o) const {
        if (x != o.x) return x < o.x;
        if (y != o.y) return y < o.y;
        return z < o.z;
    }
};

int bfs3D(int n, int m, Point3D start, Point3D target,
          const vector<Point3D>& obstacles,
          const vector<tuple<ll,ll,ll>>& teleports) {
    // 用map按(x,y)分组 + lower_bound找落点
    map<pair<ll,ll>, vector<ll>> col; // (x,y) -> [z1,z2,...]
    for (auto& ob : obstacles) {
        col[{ob.x, ob.y}].push_back(ob.z);
    }
    // 每组内排序
    for (auto& [_, vec] : col) sort(vec.begin(), vec.end());

    // BFS
    map<Point3D, int> dist;
    queue<Point3D> q;
    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        int d = dist[cur];
        if (cur.x == target.x && cur.y == target.y && cur.z == target.z)
            return d;

        for (auto [ai, bi, ci] : teleports) {
            ll nx = cur.x + ai;
            ll ny = cur.y + bi;
            auto it = col.find({nx, ny});
            if (it == col.end()) continue;

            // 找 ≤ z+ci 的最大障碍z
            ll nz = cur.z + ci;
            // lower_bound找第一个>nz的 → 前一个就是≤nz的最大
            auto vit = upper_bound(it->second.begin(), it->second.end(), nz);
            if (vit == it->second.begin()) continue;
            vit--;
            ll fallTo = *vit + 1; // 站在障碍上方

            Point3D next = {nx, ny, fallTo};
            if (!dist.count(next)) {
                dist[next] = d + 1;
                q.push(next);
            }
        }
    }
    return -1;
}
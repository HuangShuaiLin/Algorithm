#include <bits/stdc++.h>
using namespace std;

/**
 * 计算几何基础模板
 * 包含：点/向量表示、叉积、点积、方向判断、凸包
 */

const double EPS = 1e-9;
const double PI = acos(-1.0);

// 符号函数
int sgn(double x) {
    if (fabs(x) < EPS) return 0;
    return x < 0 ? -1 : 1;
}

// ==============================
// 2D 点 / 向量
// ==============================
struct Point {
    double x, y;
    Point() : x(0), y(0) {}
    Point(double _x, double _y) : x(_x), y(_y) {}

    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator*(double k) const { return Point(x * k, y * k); }
    Point operator/(double k) const { return Point(x / k, y / k); }
    bool operator<(const Point& p) const {
        int c = sgn(x - p.x);
        if (c) return c < 0;
        return sgn(y - p.y) < 0;
    }
    bool operator==(const Point& p) const {
        return sgn(x - p.x) == 0 && sgn(y - p.y) == 0;
    }

    double len() const { return sqrt(x * x + y * y); }
    double len2() const { return x * x + y * y; }
    double angle() const { return atan2(y, x); }

    // 逆时针旋转弧度 rad
    Point rotate(double rad) const {
        return Point(x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad));
    }

    // 单位法向量 (逆时针旋转90度)
    Point normal() const { return Point(-y, x); }
};

// 点积
double dot(const Point& a, const Point& b) { return a.x * b.x + a.y * b.y; }

// 叉积 (a × b > 0 表示 b 在 a 的逆时针方向)
double cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }

// ==============================
// 线段相关
// ==============================
struct Segment {
    Point a, b;
    Segment() {}
    Segment(Point _a, Point _b) : a(_a), b(_b) {}
};

// 判断点是否在线段上 (包括端点)
bool onSegment(const Point& p, const Point& a, const Point& b) {
    return sgn(cross(p - a, p - b)) == 0 &&
           sgn(dot(p - a, p - b)) <= 0;
}

// 两线段是否相交 (不包括端点接触)
bool segmentsIntersect(const Point& a1, const Point& a2,
                       const Point& b1, const Point& b2) {
    double c1 = cross(a2 - a1, b1 - a1);
    double c2 = cross(a2 - a1, b2 - a1);
    double c3 = cross(b2 - b1, a1 - b1);
    double c4 = cross(b2 - b1, a2 - b1);
    return sgn(c1) * sgn(c2) < 0 && sgn(c3) * sgn(c4) < 0;
}

// 点到线段的最短距离
double pointToSegment(const Point& p, const Point& a, const Point& b) {
    if (sgn(dot(b - a, p - a)) < 0) return (p - a).len();
    if (sgn(dot(a - b, p - b)) < 0) return (p - b).len();
    return fabs(cross(b - a, p - a)) / (b - a).len();
}

// 两直线交点 (需保证不平行)
Point lineIntersection(const Point& p1, const Point& v1,
                       const Point& p2, const Point& v2) {
    double t = cross(p2 - p1, v2) / cross(v1, v2);
    return p1 + v1 * t;
}

// ==============================
// 凸包 (Andrew算法 / 单调链)
// ==============================
vector<Point> convexHull(vector<Point> pts) {
    int n = pts.size();
    if (n <= 2) return pts;
    sort(pts.begin(), pts.end());
    vector<Point> hull(n + 1);

    // 下凸壳
    int k = 0;
    for (int i = 0; i < n; i++) {
        while (k >= 2 && sgn(cross(hull[k - 1] - hull[k - 2], pts[i] - hull[k - 2])) <= 0)
            k--;
        hull[k++] = pts[i];
    }

    // 上凸壳
    int t = k + 1;
    for (int i = n - 2; i >= 0; i--) {
        while (k >= t && sgn(cross(hull[k - 1] - hull[k - 2], pts[i] - hull[k - 2])) <= 0)
            k--;
        hull[k++] = pts[i];
    }

    hull.resize(k - 1); // 去掉重复的起点
    return hull;
}

// 凸包周长
double convexHullPerimeter(const vector<Point>& hull) {
    double res = 0;
    int m = hull.size();
    for (int i = 0; i < m; i++)
        res += (hull[(i + 1) % m] - hull[i]).len();
    return res;
}

// 凸包面积 (2倍面积，用叉积)
double convexHullArea2(const vector<Point>& hull) {
    double res = 0;
    int m = hull.size();
    for (int i = 0; i < m; i++)
        res += cross(hull[i], hull[(i + 1) % m]);
    return fabs(res);
}

// 多边形面积 (2倍)
double polygonArea2(const vector<Point>& p) {
    double res = 0;
    int n = p.size();
    for (int i = 0; i < n; i++)
        res += cross(p[i], p[(i + 1) % n]);
    return fabs(res);
}

// 点是否在多边形内部 (射线法)
int pointInPolygon(const Point& p, const vector<Point>& poly) {
    int n = poly.size(), wn = 0; // winding number
    for (int i = 0; i < n; i++) {
        if (onSegment(p, poly[i], poly[(i + 1) % n]))
            return 0; // 在边上
        int k = sgn(cross(poly[(i + 1) % n] - poly[i], p - poly[i]));
        int d1 = sgn(poly[i].y - p.y);
        int d2 = sgn(poly[(i + 1) % n].y - p.y);
        if (k > 0 && d1 <= 0 && d2 > 0) wn++;
        if (k < 0 && d2 <= 0 && d1 > 0) wn--;
    }
    return wn ? 1 : -1; // 1: 内部, -1: 外部
}

// ==============================
// 最近点对 (分治法) O(n log n)
// ==============================
double closestPair(vector<Point>& pts, int l, int r) {
    if (r - l <= 3) {
        double d = 1e18;
        for (int i = l; i < r; i++)
            for (int j = i + 1; j < r; j++)
                d = min(d, (pts[i] - pts[j]).len());
        return d;
    }
    int mid = (l + r) / 2;
    double midX = pts[mid].x;
    double d = min(closestPair(pts, l, mid), closestPair(pts, mid, r));

    // 合并：选中间带状区域
    vector<Point> strip;
    for (int i = l; i < r; i++)
        if (fabs(pts[i].x - midX) < d)
            strip.push_back(pts[i]);
    sort(strip.begin(), strip.end(), [](const Point& a, const Point& b) {
        return a.y < b.y;
    });
    for (int i = 0; i < (int)strip.size(); i++)
        for (int j = i + 1; j < (int)strip.size() && strip[j].y - strip[i].y < d; j++)
            d = min(d, (strip[i] - strip[j]).len());
    return d;
}

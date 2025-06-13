#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

struct Point {
    int x, y;
};

Point p0; // 添加此行以定义 p0

// 用于确定点a、b、c的位置关系（顺时针、逆时针、共线）
int orientation(Point a, Point b, Point c) {
    long long val = ((long long)b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if (val == 0) return 0;     // 共线
    return (val > 0) ? 1 : 2;   // 顺时针或逆时针
}

// 用于比较两个点的极角
bool compare(Point a, Point b) {
    int o = orientation(p0, a, b);
    if (o == 0)
        return (a.x + a.y < b.x + b.y);
    return (o == 2);
}

// 查找最低点
int findLowestPoint(std::vector<Point>& points) {
    int lowest = 0;
    for (int i = 1; i < points.size(); i++) {
        if (points[i].y < points[lowest].y || (points[i].y == points[lowest].y && points[i].x < points[lowest].x)) {
            lowest = i;
        }
    }
    return lowest;
}

Point nextToTop(std::stack<Point>& hull) {
    Point p = hull.top();
    hull.pop();
    Point res = hull.top();
    hull.push(p);
    return res;
}

long long mult(Point a, Point b, Point c){
    long long val = ((long long)b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    return val;
}

// Graham扫描算法
std::vector<Point> convexHull(std::vector<Point>& points) {
    int n = points.size();
    int lowest = findLowestPoint(points);
    std::swap(points[0], points[lowest]);
    p0 = points[0];

    std::sort(points.begin() + 1, points.end(), compare);

    std::stack<Point> hull;
    hull.push(points[0]);
    hull.push(points[1]);

    for (int i = 2; i < n; i++) {
        while (hull.size() > 1 && orientation(nextToTop(hull), hull.top(), points[i]) != 2) {
            hull.pop();
        }
        hull.push(points[i]);
    }

    std::vector<Point> result;
    while (!hull.empty()) {
        result.push_back(hull.top());
        hull.pop();
    }
    std::reverse(result.begin(), result.end());
    return result;
}
int main() {
    std::ios::sync_with_stdio(false);
    int tt;
    std::cin >> tt;
    while(tt--) {
        int numPoints;
        std::cin >> numPoints;

        std::vector<Point> points;
        for (int i = 0; i < numPoints; ++i) {
            Point p;
            std::cin >> p.x >> p.y;
            points.push_back(p);
        }

        std::vector<Point> result = convexHull(points);
        long long S = 0;
        for (int i = 2; i < result.size(); i++) {
            S += mult(result[i], result[i - 1], result[0]);
        }
        if (S % 2 == 0) {
            printf("%lld.0\n", S / 2);
        } else {
            printf("%lld.5\n", S / 2);
        }
    }
    return 0;
}

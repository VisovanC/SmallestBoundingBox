#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

struct Point {
    double x, y;

    Point(double x, double y) : x(x), y(y) {}
};
double crossProduct(const Point& p1, const Point& p2, const Point& p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}
double distanceSquared(const Point& p1, const Point& p2) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return dx * dx + dy * dy;
}
double smallestBoundingBoxPerimeter(const std::vector<Point>& convexHull) {
    int n = convexHull.size();
    double minPerimeter = std::numeric_limits<double>::max();

    for (int i = 0; i < n; ++i) {
        int next = (i + 1) % n;
        for (int j = 0; j < n; ++j) {
            int nextJ = (j + 1) % n;

            double crossProd = crossProduct(convexHull[i], convexHull[next], convexHull[j]);
            double distSquared = distanceSquared(convexHull[i], convexHull[nextJ]);

            double perpendicularDist = std::fabs(crossProd) / std::sqrt(distSquared);

            minPerimeter = std::min(minPerimeter, 2 * (perpendicularDist + std::sqrt(distSquared)));
        }
    }

    return minPerimeter;
}

int main() {
    std::vector<Point> polygon;
    int numVertices;

    std::cout << "Enter the number of vertices: ";
    std::cin >> numVertices;

    std::cout << "Enter the vertices (x y):" << std::endl;
    for (int i = 0; i < numVertices; ++i) {
        double x, y;
        std::cin >> x >> y;
        polygon.emplace_back(x, y);
    }

    double perimeter = smallestBoundingBoxPerimeter(polygon);

    std::cout << "Smallest bounding box perimeter: " << perimeter << std::endl;

    return 0;
}

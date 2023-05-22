#include <cstdint>
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

template <typename T>
class Point {
public:
    Point() : x_(0), y_(0) {
    }
    Point(const T& x, const T& y) : x_(x), y_(y) {
    }

    Point operator-(const Point subtrahend) {
        return {x_ - subtrahend.x_, y_ - subtrahend.y_};
    }

    double Dist(Point other) {
        return sqrt(std::pow(x_ - other.x_, 2) + std::pow(y_ - other.y_, 2));
    }

    friend std::vector<Point<int64_t>> ConvexHullGraham(std::vector<Point<int64_t>>& points);
    friend void ConvexHullPrint(std::vector<Point<int64_t>> hull);
    template <typename U>
    friend U S(Point<U> x, Point<U> y, Point<U> z);
    void SetX(const T& x) {
        x_ = x;
    }
    void SetY(const T& y) {
        y_ = y;
    }

private:
    T x_;
    T y_;
};

template <typename T>
T S(Point<T> x, Point<T> y, Point<T> z) {
    return (y - x).x_ * (z - x).y_ - (y - x).y_ * (z - x).x_;
}

std::vector<Point<int64_t>> ConvexHullGraham(std::vector<Point<int64_t>>& points) {
    Point<int64_t> p_start = points[0];
    for (Point<int64_t> p : points) {
        if (p_start.x_ > p.x_ || (p.x_ == p_start.x_ && p.y_ < p_start.y_)) {
            p_start = p;
        }
    }

    std::vector<Point<int64_t>> hull;

    std::sort(points.begin(), points.end(), [&](Point<int64_t> a, Point<int64_t> b) {
        return (a - p_start).x_ * (b - p_start).y_ - (a - p_start).y_ * (b - p_start).x_ < 0 ||
               ((a - p_start).x_ * (b - p_start).y_ - (a - p_start).y_ * (b - p_start).x_ == 0 &&
                p_start.Dist(a) > p_start.Dist(b));
    });

    for (auto p : points) {
        while (hull.size() >= 2) {
            Point<int64_t> ver_prev = *hull.rbegin() - hull[hull.size() - 2];
            Point<int64_t> ver_new = p - *hull.rbegin();
            if ((ver_new.x_ * ver_prev.y_ - ver_new.y_ * ver_prev.x_) <= 0) {
                hull.pop_back();
            } else {
                break;
            }
        }

        hull.push_back(p);
    }
    return hull;
}
void ConvexHullPrint(std::vector<Point<int64_t>> hull) {
    int64_t s = 0;
    std::cout << hull.size() << "\n";
    std::cout << hull.rbegin()->x_ << " " << hull.rbegin()->y_ << "\n";

    for (size_t i = 0; i < hull.size() - 1; ++i) {
        std::cout << hull[i].x_ << " " << hull[i].y_ << "\n";
    }

    for (size_t i = 1; i < hull.size() - 1; ++i) {
        s += S(hull[0], hull[i + 1], hull[i]);
    }
    double answer = static_cast<double>(s) / 2;
    std::cout << std::setprecision(1) << std::fixed << answer << "\n";
}
int main() {
    int n = 0;
    std::cin >> n;
    std::vector<Point<int64_t>> points;
    int64_t x = 0;
    int64_t y = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> x >> y;
        points.emplace_back(x, y);
    }

    auto hull = ConvexHullGraham(points);
    ConvexHullPrint(hull);
    return 0;
}
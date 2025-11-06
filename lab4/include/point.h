#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <concepts>
#include <memory>

template<typename T>
concept Scalar = std::is_scalar_v<T>;

template<Scalar T>
class Point {
private:
    T x_, y_;

public:
    Point() : x_(0), y_(0) {}
    Point(T x, T y) : x_(x), y_(y) {}

    T x() const { return x_; }
    T y() const { return y_; }

    void set_x(T x) { x_ = x; }
    void set_y(T y) { y_ = y; }

    bool operator==(const Point& other) const {
        return x_ == other.x_ && y_ == other.y_;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << "(" << p.x_ << ", " << p.y_ << ")";
    }

    friend std::istream& operator>>(std::istream& is, Point& p) {
        return is >> p.x_ >> p.y_;
    }
};

#endif
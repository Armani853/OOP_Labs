#ifndef SHAPES_H
#define SHAPES_H

#include "figure.h"
#include <cmath>
#include <concepts>
#include <algorithm>

template<Scalar T>
class Rectangle : public Figure<T> {
public:
    Point<T> geometric_center() const override {
        if (this->vertices.size() != 4) return Point<T>();
        T center_x = (this->vertices[0]->x() + this->vertices[2]->x()) / 2;
        T center_y = (this->vertices[0]->y() + this->vertices[2]->y()) / 2;
        return Point<T>(center_x, center_y);
    }

    double area() const override {
        if (this->vertices.size() != 4) return 0;
        T width = std::abs(this->vertices[1]->x() - this->vertices[0]->x());
        T height = std::abs(this->vertices[2]->y() - this->vertices[1]->y());
        return static_cast<double>(width * height);
    }

    void read_from_stream(std::istream& is) override {
        this->vertices.clear();
        T x1, y1, x2, y2;
        is >> x1 >> y1 >> x2 >> y2;
        
        this->vertices.push_back(std::make_unique<Point<T>>(x1, y1));
        this->vertices.push_back(std::make_unique<Point<T>>(x2, y1));
        this->vertices.push_back(std::make_unique<Point<T>>(x2, y2));
        this->vertices.push_back(std::make_unique<Point<T>>(x1, y2));
    }

    void print_to_stream(std::ostream& os) const override {
        os << "Rectangle vertices: ";
        for (const auto& vertex : this->vertices) {
            os << *vertex << " ";
        }
        os << "| Center: " << geometric_center() << " | Area: " << area();
    }
};

template<Scalar T>
class Trapezoid : public Figure<T> {
public:
    Point<T> geometric_center() const override {
        if (this->vertices.size() != 4) return Point<T>();
        T center_x = 0, center_y = 0;
        for (const auto& vertex : this->vertices) {
            center_x += vertex->x();
            center_y += vertex->y();
        }
        return Point<T>(center_x / 4, center_y / 4);
    }

    double area() const override {
        if (this->vertices.size() != 4) return 0;
        
        T bottom_base = std::abs(this->vertices[1]->x() - this->vertices[0]->x());
        T top_base = std::abs(this->vertices[2]->x() - this->vertices[3]->x());
        T height = std::abs(this->vertices[0]->y() - this->vertices[3]->y());
        
        return static_cast<double>((bottom_base + top_base) * height / 2);
    }

    void read_from_stream(std::istream& is) override {
        this->vertices.clear();
        T x1, y1, x2, y2, x3, y3, x4, y4;
        is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        
        this->vertices.push_back(std::make_unique<Point<T>>(x1, y1));
        this->vertices.push_back(std::make_unique<Point<T>>(x2, y2));
        this->vertices.push_back(std::make_unique<Point<T>>(x3, y3));
        this->vertices.push_back(std::make_unique<Point<T>>(x4, y4));
    }

    void print_to_stream(std::ostream& os) const override {
        os << "Trapezoid vertices: ";
        for (const auto& vertex : this->vertices) {
            os << *vertex << " ";
        }
        os << "| Center: " << geometric_center() << " | Area: " << area();
    }
};

template<Scalar T>
class Rhombus : public Figure<T> {
public:
    Point<T> geometric_center() const override {
        if (this->vertices.size() != 4) return Point<T>();
        T center_x = (this->vertices[0]->x() + this->vertices[2]->x()) / 2;
        T center_y = (this->vertices[0]->y() + this->vertices[2]->y()) / 2;
        return Point<T>(center_x, center_y);
    }

    double area() const override {
        if (this->vertices.size() != 4) return 0;
        
        T d1 = std::sqrt(std::pow(this->vertices[1]->x() - this->vertices[3]->x(), 2) +
                         std::pow(this->vertices[1]->y() - this->vertices[3]->y(), 2));
        T d2 = std::sqrt(std::pow(this->vertices[0]->x() - this->vertices[2]->x(), 2) +
                         std::pow(this->vertices[0]->y() - this->vertices[2]->y(), 2));
        
        return static_cast<double>(d1 * d2 / 2);
    }

    void read_from_stream(std::istream& is) override {
        this->vertices.clear();
        T x1, y1, x2, y2, x3, y3, x4, y4;
        is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        
        this->vertices.push_back(std::make_unique<Point<T>>(x1, y1));
        this->vertices.push_back(std::make_unique<Point<T>>(x2, y2));
        this->vertices.push_back(std::make_unique<Point<T>>(x3, y3));
        this->vertices.push_back(std::make_unique<Point<T>>(x4, y4));
    }

    void print_to_stream(std::ostream& os) const override {
        os << "Rhombus vertices: ";
        for (const auto& vertex : this->vertices) {
            os << *vertex << " ";
        }
        os << "| Center: " << geometric_center() << " | Area: " << area();
    }
};

#endif
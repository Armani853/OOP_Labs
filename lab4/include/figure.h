#ifndef FIGURE_H
#define FIGURE_H

#include "point.h"
#include <iostream>
#include <memory>
#include <vector>

template<Scalar T>
class Figure {
protected:
    std::vector<std::unique_ptr<Point<T>>> vertices;

public:
    virtual ~Figure() = default;
    Figure() = default;

    Figure(const Figure&) = delete;
    Figure& operator=(const Figure&) = delete;
    
    Figure(Figure&&) = default;
    Figure& operator=(Figure&&) = default;

    virtual Point<T> geometric_center() const = 0;
    virtual double area() const = 0;
    virtual void read_from_stream(std::istream& is) = 0;
    virtual void print_to_stream(std::ostream& os) const = 0;

    explicit operator double() const {
        return area();
    }

    bool operator==(const Figure& other) const {
        return area() == other.area();
    }

    bool operator<(const Figure& other) const {
        return area() < other.area();
    }

    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
        fig.print_to_stream(os);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Figure<T>& fig) {
        fig.read_from_stream(is);
        return is;
    }
};

#endif
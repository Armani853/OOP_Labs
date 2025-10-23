#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <vector>
#include <memory>

class Figure {
public:
    virtual ~Figure() = default;
    
    virtual double calculateArea() const = 0;
    virtual std::pair<double, double> calculateCenter() const = 0;
    virtual void printVertices(std::ostream& os) const = 0;
    virtual void readVertices(std::istream& is) = 0;
    
    virtual std::unique_ptr<Figure> clone() const = 0;
    
    friend std::ostream& operator<<(std::ostream& os, const Figure& figure);
    friend std::istream& operator>>(std::istream& is, Figure& figure);
    virtual bool operator==(const Figure& other) const = 0;
    
    virtual explicit operator double() const;
};

std::ostream& operator<<(std::ostream& os, const Figure& figure);
std::istream& operator>>(std::istream& is, Figure& figure);

#endif
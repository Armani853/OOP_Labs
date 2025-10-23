#ifndef TRAPEZE_H
#define TRAPEZE_H

#include "Figure.h"
#include <array>

class Trapeze : public Figure {
private:
    std::array<std::pair<double, double>, 4> vertices;
    
public:
    Trapeze() = default;
    Trapeze(const std::array<std::pair<double, double>, 4>& verts);
    
    Trapeze(const Trapeze& other);
    
    Trapeze(Trapeze&& other) noexcept;
    
    Trapeze& operator=(const Trapeze& other);
    Trapeze& operator=(Trapeze&& other) noexcept;
    
    double calculateArea() const override;
    std::pair<double, double> calculateCenter() const override;
    void printVertices(std::ostream& os) const override;
    void readVertices(std::istream& is) override;
    std::unique_ptr<Figure> clone() const override;
    bool operator==(const Figure& other) const override;
    
    bool isValidTrapeze() const;
};

#endif
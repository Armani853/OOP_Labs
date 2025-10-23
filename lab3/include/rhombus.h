#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Figure.h"
#include <array>

class Rhombus : public Figure {
private:
    std::array<std::pair<double, double>, 4> vertices;
public:
    Rhombus() = default;
    Rhombus(const std::array<std::pair<double, double>, 4>& verts);
    
    Rhombus(const Rhombus& other);
    Rhombus(Rhombus&& other) noexcept;
    Rhombus& operator=(const Rhombus& other);
    Rhombus& operator=(Rhombus&& other) noexcept;
    
    double calculateArea() const override;
    std::pair<double, double> calculateCenter() const override;
    void printVertices(std::ostream& os) const override;
    void readVertices(std::istream& is) override;
    std::unique_ptr<Figure> clone() const override;
    bool operator==(const Figure& other) const override;
    
    bool isValidRhombus() const;
};

#endif
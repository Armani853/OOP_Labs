#ifndef PENTAGON_H
#define PENTAGON_H

#include "Figure.h"
#include <array>

class Pentagon : public Figure {
private:
    std::array<std::pair<double, double>, 5> vertices;
    
public:
    Pentagon() = default;
    Pentagon(const std::array<std::pair<double, double>, 5>& verts);
    
    Pentagon(const Pentagon& other);
    Pentagon(Pentagon&& other) noexcept;
    Pentagon& operator=(const Pentagon& other);
    Pentagon& operator=(Pentagon&& other) noexcept;
    
    double calculateArea() const override;
    std::pair<double, double> calculateCenter() const override;
    void printVertices(std::ostream& os) const override;
    void readVertices(std::istream& is) override;
    std::unique_ptr<Figure> clone() const override;
    bool operator==(const Figure& other) const override;
    
    bool isValidPentagon() const;
};

#endif
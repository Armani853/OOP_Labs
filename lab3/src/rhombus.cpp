#include "../include/rhombus.h"
#include <cmath>
#include <sstream>

Rhombus::Rhombus(const std::array<std::pair<double, double>, 4>& verts) 
    : vertices(verts) {}

Rhombus::Rhombus(const Rhombus& other) : vertices(other.vertices) {}
Rhombus::Rhombus(Rhombus&& other) noexcept : vertices(std::move(other.vertices)) {}

Rhombus& Rhombus::operator=(const Rhombus& other) {
    if (this != &other) vertices = other.vertices;
    return *this;
}

Rhombus& Rhombus::operator=(Rhombus&& other) noexcept {
    if (this != &other) vertices = std::move(other.vertices);
    return *this;
}

double Rhombus::calculateArea() const {
    double d1 = std::sqrt(std::pow(vertices[0].first - vertices[2].first, 2) +
                         std::pow(vertices[0].second - vertices[2].second, 2));
    double d2 = std::sqrt(std::pow(vertices[1].first - vertices[3].first, 2) +
                         std::pow(vertices[1].second - vertices[3].second, 2));
    return (d1 * d2) / 2.0;
}

std::pair<double, double> Rhombus::calculateCenter() const {
    double centerX = 0.0, centerY = 0.0;
    for (const auto& vertex : vertices) {
        centerX += vertex.first;
        centerY += vertex.second;
    }
    return {centerX / 4.0, centerY / 4.0};
}

void Rhombus::printVertices(std::ostream& os) const {
    os << "Вершины ромба: ";
    for (const auto& vertex : vertices) {
        os << "(" << vertex.first << ", " << vertex.second << ") ";
    }
}

void Rhombus::readVertices(std::istream& is) {
    std::string line;
    std::getline(is, line);
    std::istringstream iss(line);
    
    for (int i = 0; i < 4; ++i) {
        char ch;
        iss >> ch;
        iss >> vertices[i].first;
        iss >> ch;
        iss >> vertices[i].second;
        iss >> ch;
    }
}

std::unique_ptr<Figure> Rhombus::clone() const {
    return std::make_unique<Rhombus>(*this);
}

bool Rhombus::operator==(const Figure& other) const {
    const Rhombus* otherRhombus = dynamic_cast<const Rhombus*>(&other);
    if (!otherRhombus) return false;
    return vertices == otherRhombus->vertices;
}

bool Rhombus::isValidRhombus() const {
    auto dist = [](const std::pair<double, double>& a, 
                   const std::pair<double, double>& b) {
        return std::sqrt(std::pow(a.first - b.first, 2) + 
                        std::pow(a.second - b.second, 2));
    };
    
    double side1 = dist(vertices[0], vertices[1]);
    double side2 = dist(vertices[1], vertices[2]);
    double side3 = dist(vertices[2], vertices[3]);
    double side4 = dist(vertices[3], vertices[0]);
    
    return std::abs(side1 - side2) < 1e-9 && 
           std::abs(side2 - side3) < 1e-9 &&
           std::abs(side3 - side4) < 1e-9;
}
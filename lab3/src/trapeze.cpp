#include "../include/trapeze.h"
#include <cmath>
#include <sstream>

Trapeze::Trapeze(const std::array<std::pair<double, double>, 4>& verts) 
    : vertices(verts) {}

Trapeze::Trapeze(const Trapeze& other) : vertices(other.vertices) {}

Trapeze::Trapeze(Trapeze&& other) noexcept : vertices(std::move(other.vertices)) {}

Trapeze& Trapeze::operator=(const Trapeze& other) {
    if (this != &other) {
        vertices = other.vertices;
    }
    return *this;
}

Trapeze& Trapeze::operator=(Trapeze&& other) noexcept {
    if (this != &other) {
        vertices = std::move(other.vertices);
    }
    return *this;
}

double Trapeze::calculateArea() const {
    double area = 0.0;
    for (int i = 0; i < 4; ++i) {
        int j = (i + 1) % 4;
        area += vertices[i].first * vertices[j].second;
        area -= vertices[j].first * vertices[i].second;
    }
    return std::abs(area) / 2.0;
}

std::pair<double, double> Trapeze::calculateCenter() const {
    double centerX = 0.0, centerY = 0.0;
    for (const auto& vertex : vertices) {
        centerX += vertex.first;
        centerY += vertex.second;
    }
    return {centerX / 4.0, centerY / 4.0};
}

void Trapeze::printVertices(std::ostream& os) const {
    os << "Вершины трапеции: ";
    for (const auto& vertex : vertices) {
        os << "(" << vertex.first << ", " << vertex.second << ") ";
    }
}

void Trapeze::readVertices(std::istream& is) {
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

std::unique_ptr<Figure> Trapeze::clone() const {
    return std::make_unique<Trapeze>(*this);
}

bool Trapeze::operator==(const Figure& other) const {
    const Trapeze* otherTrapeze = dynamic_cast<const Trapeze*>(&other);
    if (!otherTrapeze) return false;
    
    return vertices == otherTrapeze->vertices;
}

bool Trapeze::isValidTrapeze() const {
    double y1 = vertices[0].second;
    double y2 = vertices[1].second;
    double y3 = vertices[2].second;
    double y4 = vertices[3].second;
    
    if (std::abs(y1 - y2) > 1e-9) return false;
    if (std::abs(y3 - y4) > 1e-9) return false;
    
    return true;
}
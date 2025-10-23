#include "../include/pentagon.h"
#include <cmath>
#include <sstream>

Pentagon::Pentagon(const std::array<std::pair<double, double>, 5>& verts) 
    : vertices(verts) {}

Pentagon::Pentagon(const Pentagon& other) : vertices(other.vertices) {}
Pentagon::Pentagon(Pentagon&& other) noexcept : vertices(std::move(other.vertices)) {}

Pentagon& Pentagon::operator=(const Pentagon& other) {
    if (this != &other) vertices = other.vertices;
    return *this;
}

Pentagon& Pentagon::operator=(Pentagon&& other) noexcept {
    if (this != &other) vertices = std::move(other.vertices);
    return *this;
}

double Pentagon::calculateArea() const {
    double area = 0.0;
    for (int i = 0; i < 5; ++i) {
        int j = (i + 1) % 5;
        area += vertices[i].first * vertices[j].second;
        area -= vertices[j].first * vertices[i].second;
    }
    return std::abs(area) / 2.0;
}

std::pair<double, double> Pentagon::calculateCenter() const {
    double centerX = 0.0, centerY = 0.0;
    for (const auto& vertex : vertices) {
        centerX += vertex.first;
        centerY += vertex.second;
    }
    return {centerX / 5.0, centerY / 5.0};
}

void Pentagon::printVertices(std::ostream& os) const {
    os << "Вершины пятиугольника: ";
    for (const auto& vertex : vertices) {
        os << "(" << vertex.first << ", " << vertex.second << ") ";
    }
}

void Pentagon::readVertices(std::istream& is) {
    std::string line;
    std::getline(is, line);
    std::istringstream iss(line);
    
    for (int i = 0; i < 5; ++i) {
        char ch;
        iss >> ch;
        iss >> vertices[i].first;
        iss >> ch;
        iss >> vertices[i].second;
        iss >> ch;
    }
}

std::unique_ptr<Figure> Pentagon::clone() const {
    return std::make_unique<Pentagon>(*this);
}

bool Pentagon::operator==(const Figure& other) const {
    const Pentagon* otherPentagon = dynamic_cast<const Pentagon*>(&other);
    if (!otherPentagon) return false;
    return vertices == otherPentagon->vertices;
}

bool Pentagon::isValidPentagon() const {
    for (int i = 0; i < 5; ++i) {
        for (int j = i + 1; j < 5; ++j) {
            if (std::abs(vertices[i].first - vertices[j].first) < 1e-9 &&
                std::abs(vertices[i].second - vertices[j].second) < 1e-9) {
                return false;
            }
        }
    }
    return true;
}
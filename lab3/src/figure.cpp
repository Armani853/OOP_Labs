#include "../include/figure.h"

Figure::operator double() const {
    return calculateArea();
}

std::ostream& operator<<(std::ostream& os, const Figure& figure) {
    figure.printVertices(os);
    return os;
}

std::istream& operator>>(std::istream& is, Figure& figure) {
    figure.readVertices(is);
    return is;
}
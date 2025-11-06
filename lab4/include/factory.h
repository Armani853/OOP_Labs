#ifndef FACTORY_H
#define FACTORY_H

#include "shapes.h"
#include <memory>
#include <string>

template<Scalar T>
std::unique_ptr<Figure<T>> create_figure(const std::string& type, std::istream& is = std::cin) {
    std::unique_ptr<Figure<T>> figure;
    
    if (type == "rectangle") {
        figure = std::make_unique<Rectangle<T>>();
    } else if (type == "trapezoid") {
        figure = std::make_unique<Trapezoid<T>>();
    } else if (type == "rhombus") {
        figure = std::make_unique<Rhombus<T>>();
    } else {
        return nullptr;
    }
    
    is >> *figure;
    return figure;
}

#endif
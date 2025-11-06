#include <iostream>
#include <iomanip>
#include <limits>
#include "include/array.h"
#include "include/factory.h"



template<typename T>
double total_area(const Array<std::unique_ptr<T>>& figures) {
    double total = 0;
    for (const auto& figure : figures) {
        total += static_cast<double>(*figure);
    }
    return total;
}

template<typename T>
void print_figures_info(const Array<std::unique_ptr<T>>& figures) {
    std::cout << "\n=== Information about all figures ===\n";
    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << "Figure " << i + 1 << ": " << *figures[i] << std::endl;
    }
}

int main() {
    std::cout << "=== Demonstration with Array<std::unique_ptr<Figure<int>>> ===\n";
    
    Array<std::unique_ptr<Figure<int>>> figures;

    std::cout << "\nAdding figures...\n";
    
    auto rect = std::make_unique<Rectangle<int>>();
    std::cout << "Enter rectangle coordinates (x1 y1 x2 y2): ";
    std::cin >> *rect;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    figures.push_back(std::move(rect));

    auto trap = std::make_unique<Trapezoid<int>>();
    std::cout << "Enter trapezoid coordinates (4 points x1 y1 x2 y2 x3 y3 x4 y4): ";
    std::cin >> *trap;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    figures.push_back(std::move(trap));

    auto rhomb = std::make_unique<Rhombus<int>>();
    std::cout << "Enter rhombus coordinates (4 points x1 y1 x2 y2 x3 y3 x4 y4): ";
    std::cin >> *rhomb;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    figures.push_back(std::move(rhomb));

    print_figures_info(figures);
    
    std::cout << "\nTotal area of all figures: " << total_area(figures) << std::endl;

    std::cout << "\n=== Removing figure at index 1 ===\n";
    figures.remove_at(1);
    print_figures_info(figures);
    std::cout << "Total area after removal: " << total_area(figures) << std::endl;

    std::cout << "\n=== Demonstration with Array<std::unique_ptr<Rectangle<int>>> ===\n";
    Array<std::unique_ptr<Rectangle<int>>> rectangles;
    
    auto rect1 = std::make_unique<Rectangle<int>>();
    auto rect2 = std::make_unique<Rectangle<int>>();
    
    std::cout << "Enter first rectangle: ";
    std::cin >> *rect1;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter second rectangle: ";
    std::cin >> *rect2;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    rectangles.push_back(std::move(rect1));
    rectangles.push_back(std::move(rect2));
    
    std::cout << "\nRectangles array:\n";
    for (size_t i = 0; i < rectangles.size(); ++i) {
        std::cout << "Rectangle " << i + 1 << ": " << *rectangles[i] << std::endl;
    }

    return 0;
}
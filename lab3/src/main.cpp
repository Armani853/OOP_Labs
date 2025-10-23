#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "../include/figure.h"
#include "../include/trapeze.h"
#include "../include/rhombus.h"
#include "../include/pentagon.h"

class FigureArray {
private:
    std::vector<std::unique_ptr<Figure>> figures;

public:
    void addFigure(std::unique_ptr<Figure> figure) {
        figures.push_back(std::move(figure));
    }
    
    bool removeFigure(int index) {
        if (index < 0 || index >= figures.size()) {
            return false;
        }
        figures.erase(figures.begin() + index);
        return true;
    }
    
    void printAllFigures() const {
        for (size_t i = 0; i < figures.size(); ++i) {
            std::cout << "Фигура " << i << ":\n";
            std::cout << "  Тип: ";
            if (dynamic_cast<Trapeze*>(figures[i].get())) {
                std::cout << "Трапеция\n";
            } else if (dynamic_cast<Rhombus*>(figures[i].get())) {
                std::cout << "Ромб\n";
            } else if (dynamic_cast<Pentagon*>(figures[i].get())) {
                std::cout << "Пятиугольник\n";
            }
            
            auto center = figures[i]->calculateCenter();
            double area = figures[i]->calculateArea();
            
            std::cout << "  Центр: (" << center.first << ", " << center.second << ")\n";
            std::cout << "  Площадь: " << area << "\n";
            std::cout << "  Вершины: " << *figures[i] << "\n\n";
        }
    }
    
    double totalArea() const {
        double total = 0.0;
        for (const auto& figure : figures) {
            total += figure->calculateArea();
        }
        return total;
    }
    
    size_t size() const {
        return figures.size();
    }
};

int main() {
    FigureArray figureArray;
    std::string command;
    
    std::cout << "Введите одну из команд!\n";
    std::cout << "Команды: add, remove, print, area, exit\n\n";
    
    while (true) {
        std::cout << "> ";
        std::cin >> command;
        
        if (command == "add") {
            std::string figureType;
            std::cout << "Введите тип фигуры (trapeze/rhombus/pentagon): ";
            std::cin >> figureType;
            std::cin.ignore(); 
            
            std::unique_ptr<Figure> figure;
            
            if (figureType == "trapeze") {
                figure = std::make_unique<Trapeze>();
            } else if (figureType == "rhombus") {
                figure = std::make_unique<Rhombus>();
            } else if (figureType == "pentagon") {
                figure = std::make_unique<Pentagon>();
            } else {
                std::cout << "Неизвестный тип фигуры!\n";
                continue;
            }
            
            std::cout << "Введите координаты вершин (в виде: (x1,y1) (x2,y2) ...): ";
            std::cin >> *figure;
            
            figureArray.addFigure(std::move(figure));
            std::cout << "Фигура успешно добавлена!\n";
            
        } else if (command == "remove") {
            int index;
            std::cout << "Введите индекс для удаления: ";
            std::cin >> index;
            
            if (figureArray.removeFigure(index)) {
                std::cout << "Фигура успешно удалена!\n";
            } else {
                std::cout << "Неизвестный индекс!\n";
            }
            
        } else if (command == "print") {
            if (figureArray.size() == 0) {
                std::cout << "В массиве нет фигур.\n";
            } else {
                figureArray.printAllFigures();
            }
            
        } else if (command == "area") {
            std::cout << "Общая площадь всех фигур: " << figureArray.totalArea() << "\n";
            
        } else if (command == "exit") {
            break;
            
        } else {
            std::cout << "Неизвестная команда!\n";
        }
    }
    
    return 0;
}
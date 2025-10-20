#include <iostream>
#include "twelve.h"

void twelve_ex() {
    std::cout << "Проверка работы с 12-ричными числами" << std::endl;
    try {
        Twelve a("579");
        Twelve b("247");

        std::cout << "a: " << a.to_str() << std::endl;
        std::cout << "b: " << b.to_str() << std::endl;

        std::cout << "\nПопробуем сравнения" << std::endl;
        std::cout << "a == b:" << (a.equal(b) ? "да" : "нет") << std::endl;
        std::cout << "a > b:" << (a.greater(b) ? "да" : "нет") << std::endl;
        std::cout << "a < b:" << (a.less(b) ? "да" : "нет") << std::endl;

        std::cout << "\nПопробуем сложить и вычесть" << std::endl;

        Twelve s = a.add(b);
        std::cout << a.to_str() << " + " << b.to_str() << " = " << s.to_str() << std::endl;

        Twelve d = a.sub(b);
        std::cout << a.to_str() << " - " << b.to_str() << " = " << d.to_str() << std::endl;

    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void easy_ex() {
    std::cout << "Демонстрация работы конструкторов:" << std::endl;

    Twelve zero_val;
    std::cout << "1. Twelve() (По умолчанию): " << zero_val.to_str() << std::endl; 
    
    Twelve three_B(4, 11); 
    std::cout << "2. Twelve(4, B): " << three_B.to_str() << std::endl; 
    
    Twelve list_val = {1, 0, 0}; 
    std::cout << "3. Twelve({1, 0, 0}): " << list_val.to_str() << std::endl; 

    Twelve copy_of_list = list_val;
    std::cout << "4. Копия (list_val): " << copy_of_list.to_str() << std::endl;
    
    std::cout << "\nПокажем еще немного примеров арифметики" << std::endl;
    
    Twelve x("B");
    Twelve y("3");
    Twelve z = x.add(y);
    std::cout << "B + 3 = " << z.to_str() << std::endl;

    Twelve p("19");
    Twelve q("7");
    Twelve r = p.sub(q);
    std::cout << "19 - 7 = " << r.to_str() << std::endl;
}

int main() {
    std::cout << "Покажу работу программы" << std::endl;
    twelve_ex();
    easy_ex();
    return 0;
}
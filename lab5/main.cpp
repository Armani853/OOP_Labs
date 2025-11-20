#include "include/list_resource.h"
#include "include/pmr_vector.h"
#include <iostream>
#include <string>

struct ComplexData {
    int id;
    double value;
    std::pmr::string name;

    ComplexData(int i, double v, const std::string& n, std::pmr::memory_resource* mr) 
        : id(i), value(v), name(n, mr) {
        std::cout << "  [ComplexData] Constructed ID: " << id << "\n";
    }

    ~ComplexData() {
        std::cout << "  [ComplexData] Destroyed ID: " << id << "\n";
    }
    
    ComplexData(ComplexData&& other) noexcept
        : id(other.id), value(other.value), name(std::move(other.name)) {
        other.id = -1;
    }
};

void run_test_simple(UniqueListResource& resource) {
    std::cout << "\n--- ТЕСТ 1: Простой тип (int) ---\n";
    
    pmr_vector<int> vec(&resource);

    std::cout << "Добавление 4 элементов:\n";
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);
    
    std::cout << "Текущий размер: " << vec.size() << "\n";

    std::cout << "Элементы (через итератор): ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}

void run_test_complex(UniqueListResource& resource) {
    std::cout << "\n--- ТЕСТ 2: Сложный тип (ComplexData) ---\n";
    
    pmr_vector<ComplexData> vec(&resource);

    std::cout << "Добавление 3 сложных элементов:\n";
    vec.push_back({1, 1.1, "Alpha", vec.get_allocator().resource()});
    vec.push_back({2, 2.2, "Beta", vec.get_allocator().resource()});
    vec.push_back({3, 3.3, "Gamma", vec.get_allocator().resource()});
    
    std::cout << "Текущий размер: " << vec.size() << "\n";

    std::cout << "Элементы (через оператор[]): ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << "{" << vec[i].id << ":" << vec[i].name << "} ";
    }
    std::cout << "\n";
    
}

void run_test_reuse_and_leak(UniqueListResource& resource) {
    std::cout << "\n--- ТЕСТ 3: Переиспользование и утечка (leak) ---\n";
    
    {
        pmr_vector<int> v1(&resource);
        v1.push_back(1);
        v1.push_back(2);
    } 
    std::cout << "Вектор v1 уничтожен. Его память доступна для переиспользования.\n";

    {
        pmr_vector<int> v2(&resource);
        std::cout << "Добавление элементов в v2 (ожидается переиспользование):\n";
        v2.push_back(100);
        v2.push_back(200);
        v2.push_back(300);
        
        int* leaked_ptr = (int*)resource.allocate(sizeof(int), alignof(int));
        std::cout << "Создан 'утеченный' блок: " << leaked_ptr << " (будет удален в ~UniqueListResource)\n";
        *leaked_ptr = 999;
    }
    std::cout << "Вектор v2 уничтожен. Его память снова доступна для переиспользования.\n";

}

int main() {
    std::cout << "Начало работы программы.\n";
    
    UniqueListResource my_resource;

    run_test_simple(my_resource);
    run_test_complex(my_resource);
    run_test_reuse_and_leak(my_resource);
    
    std::cout << "\nКонец работы тестов. Вызов ~UniqueListResource() для очистки.\n";
    
    return 0;
}
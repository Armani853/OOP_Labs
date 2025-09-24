#include <iostream>
#include <string>
#include "find_numbers.h"

int main() {
    std::cout << "Введите, пожалуйста, строку" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::string numbers = find_numbers_in_string(input);
    std::cout << numbers << std::endl;
    return 0;
}

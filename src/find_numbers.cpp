#include "find_numbers.h"

std::string find_numbers_in_string(const std::string& input) {
    std::string result;
    std::string Num;
    for (char c : input) {
        if (c >= '0' && c <= '9') {
            Num += c;
        } else {
            if (!Num.empty()) {
                result += Num + " ";
                Num.clear();
            }
        }
    }
    if (!Num.empty()) {
        result += Num;
    }
    return result;
}
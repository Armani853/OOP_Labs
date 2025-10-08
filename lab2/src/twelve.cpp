#include "twelve.h"
#include <stdexcept>

Twelve::Twelve() : len(1) {
    nums = new unsigned char [1];
    nums[0] = 0;
}

Twelve::Twelve(const size_t& n, unsigned char b) : len(n) {
    if (n == 0) {
        throw std::invalid_argument("Число не может быть пустым");
    } 
    if (b > 11) {
        throw std::invalid_argument("Число не может содержать цифры больше 11");
    }
    nums = new unsigned char[n];
    for (size_t i = 0; i < n; i++) {
        nums[i] = b;
    }
    delete_zeros();
}

Twelve::Twelve(const std::initializer_list<unsigned char>& els) {
    len = els.size();
    if (len == 0) {
        throw std::invalid_argument("Список не может быть пустым");
    }
    nums = new unsigned char[len];
    size_t ind = 0;
    for (auto i = els.end() - 1; i >= els.begin(); i--) {
        unsigned char b = *i;
        if (b > 11) {
            delete[] nums;
            throw std::invalid_argument("Не может быть числа больше 11");
        }
        nums[ind++] = b;
        if (ind >= len) {
            break;
        }
    }
    delete_zeros();
}

Twelve::Twelve(const std::string& s) {
    if (s.empty()) {
        throw std::invalid_argument("Строка не может быть пустой");
    }
    len = s.size();
    nums = new unsigned char[len];
    for (size_t i = 0; i < len; i++) {
        char c = s[i];
        unsigned char m;
        if (c >= '0' && c <= '9') {
            m = c - '0';
        } else if (c == 'A' || c == 'a') {
            m = 10;
        } else if (c == 'B' || c == 'b') {
            m = 11;
        } else  {
            delete [] nums;
            throw std::invalid_argument("Некорректный символ в строке");
        }
        nums[len - 1 - i] = m;
    }
    delete_zeros();
}

Twelve::Twelve(const Twelve& other) : len(other.len){
    nums = new unsigned char[len];
    for (size_t i = 0; i < len; i++) {
        nums[i] = other.nums[i];
    }
}

Twelve::Twelve(Twelve&& other) noexcept : nums(other.nums), len(other.len) {
    other.nums = nullptr;
    other.len = 0;
}

Twelve::~Twelve() noexcept {
    delete[] nums;
}

void Twelve::delete_zeros() {
    size_t new_len = len;
    while (new_len > 1 && nums[new_len - 1] == 0) {
        new_len--;
    }

    if (new_len != len) {
        unsigned char* new_nums = new unsigned char[new_len];
        for (size_t i = 0; i < new_len; i++) {
            new_nums[i] = nums[i];
        }
        delete[] nums;
        nums = new_nums;
        len = new_len;
    }
}

size_t Twelve::length() const {
        return len;
    }
unsigned char* Twelve::getnums() const {
    unsigned char* copy = new unsigned char[len];
    for (size_t i = 0; i < len; i++) {
        copy[i] = nums[i];
    }
    return copy;
}

bool Twelve::equal(const Twelve& other) const {
    if (len != other.len) {
        return false;
    }
    for (size_t i = 0; i < len; i++) {
        if (nums[i] != other.nums[i]) {
            return false;
        }
    }
    return true;
}

bool Twelve::greater(const Twelve& other) const {
    if (len > other.len) {
        return true;
    } else if (len < other.len) { 
        return false;
    }
    for (int i = len - 1; i >= 0; i--) {
        if (nums[i] > other.nums[i]) {
            return true;
        }
        if (nums[i] < other.nums[i]) {
            return false;
        }
    }
    return false;
}

bool Twelve::less(const Twelve& other) const {
    if (!greater(other) && !equal(other)) {
        return true;
    } else {
        return false;
    }
}

Twelve Twelve::add(const Twelve& other) const{
    size_t max_len;
    if (len >= other.len) {
        max_len = len + 1;
    } else {
        max_len = other.len + 1;
    }
    std::vector<unsigned char> res(max_len, 0);
    unsigned char of = 0;
    for (size_t i = 0; i < max_len; i++) {
        unsigned char sum = of;
        if (i < len) {
            sum += nums[i];
        }
        if (i < other.len) {
            sum += other.nums[i];
        }
        res[i] = sum % 12;
        of = sum / 12;
    }
    std::string a;
    for (int i = res.size() - 1; i >= 0; i--) {
        if (res[i] < 10) {
            a += '0' + res[i];
        } else if (res[i] == 10) {
            a += 'A';
        } else if(res[i] == 11) {
            a += 'B';
        }
    }
    size_t start = a.find_first_not_of('0');
    if (start == std::string::npos) {
        return Twelve("0");
    }
    return Twelve(a.substr(start));
}

Twelve Twelve::sub(const Twelve& other) const {
    if (less(other)) {
        throw std::invalid_argument("Нельзя вычитать большее число");
    }
    std::vector <unsigned char> res(len, 0);
    int borr = 0;
    for (size_t i = 0; i < len; i++) {
        int diff = nums[i] - borr;
        if (i < other.len) {
            diff -= other.nums[i];
        }
        if (diff < 0) {
            diff += 12;
            borr = 1;
        } else {
            borr = 0;
        }
        res[i] = diff;
    }
    std::string a;
    for (int i = res.size() - 1; i >= 0; i--) {
        if (res[i] < 10) {
            a += '0' + res[i];
        } else if (res[i] == 10) {
            a += 'A';
        } else if(res[i] == 11) {
            a += 'B';
        }
    }
    size_t start = a.find_first_not_of('0');
    if (start == std::string::npos) {
        return Twelve("0");
    }
    return Twelve(a.substr(start));
}

std::string Twelve::to_str() const {
    std::string a;
    for (int i = len - 1; i >= 0; i--) {
        if (nums[i] < 10) {
            a += '0' + nums[i];
        } else if (nums[i] == 10) {
            a += 'A';
        } else if(nums[i] == 11) {
            a += 'B';
        }
    }
    return a;
}

Twelve& Twelve::operator=(const Twelve& other) {
    if (this != &other) {
        delete[] nums;
        len = other.len;
        nums = new unsigned char[len];
        for (size_t i = 0; i < len; i++) {
            nums[i] = other.nums[i];
        }
    }
    return *this;
}

Twelve& Twelve::operator=(Twelve&& other) noexcept {
    if (this != &other) {
        delete[] nums;
        nums = other.nums;
        len = other.len;
        other.nums = nullptr;
        other.len = 0;
    }
    return *this;
}


#ifndef TWELVE_H
#define TWELVE_H
#include <iostream>
#include <vector>

class Twelve {
private:
    unsigned char* nums;
    size_t len;
    
    void delete_zeros();
public:
    Twelve();
    Twelve(const size_t& n, unsigned char b = 0);
    Twelve(const std::initializer_list<unsigned char>& els);
    Twelve(const std::string& st);
    Twelve(const Twelve& other);
    Twelve(Twelve&& other) noexcept;

    ~Twelve() noexcept;

    size_t length() const;
    unsigned char* getnums() const;

    bool equal(const Twelve& other) const;
    bool greater(const Twelve& other) const;
    bool less(const Twelve& other) const;

    Twelve add(const Twelve& other) const;
    Twelve sub(const Twelve& other) const;

    std::string to_str() const;

    Twelve& operator=(const Twelve& other);
    Twelve& operator=(Twelve&& other) noexcept;
};


#endif
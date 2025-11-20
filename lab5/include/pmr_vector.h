#ifndef PMR_VECTOR_H
#define PMR_VECTOR_H

#include <memory_resource>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <iostream>

template<typename T>
using PMRAllocator = std::pmr::polymorphic_allocator<T>;


template <typename T>
class PMRVectorIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;

private:
    pointer ptr_;

public:
    explicit PMRVectorIterator(pointer ptr = nullptr) : ptr_(ptr) {}

    reference operator*() const { return *ptr_; }
    pointer operator->() const { return ptr_; }
    
    PMRVectorIterator& operator++() {
        ++ptr_;
        return *this;
    }
    PMRVectorIterator operator++(int) {
        PMRVectorIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    friend bool operator==(const PMRVectorIterator& a, const PMRVectorIterator& b) {
        return a.ptr_ == b.ptr_;
    }
    friend bool operator!=(const PMRVectorIterator& a, const PMRVectorIterator& b) {
        return a.ptr_ != b.ptr_;
    }
};


template <typename T>
class pmr_vector {
public:
    using value_type      = T;
    using size_type       = size_t;
    using difference_type = std::ptrdiff_t;
    using reference       = T&;
    using const_reference = const T&;
    using pointer         = T*;
    using iterator        = PMRVectorIterator<T>;
    using const_iterator  = PMRVectorIterator<const T>;
    using allocator_type  = PMRAllocator<T>;

private:
    allocator_type alloc_;
    pointer data_ = nullptr;
    size_type size_ = 0;
    size_type capacity_ = 0;

    static constexpr size_type INITIAL_CAPACITY = 4;
    

    pointer allocate_buffer(size_type count) {
        return alloc_.allocate(count);
    }
    
    void deallocate_buffer(pointer p, size_type count) {
        if (p) {
            alloc_.deallocate(p, count);
        }
    }

    void destroy_elements(pointer first, pointer last) {
        for (; first != last; ++first) {
            std::allocator_traits<allocator_type>::destroy(alloc_, first);
        }
    }

    void reallocate(size_type new_capacity) {
        if (new_capacity <= capacity_) return;

        pointer new_data = allocate_buffer(new_capacity);
        
        if (data_) {
            for (size_type i = 0; i < size_; ++i) {
                alloc_.construct(new_data + i, std::move(data_[i]));
                std::allocator_traits<allocator_type>::destroy(alloc_, data_ + i);
            }
            deallocate_buffer(data_, capacity_);
        }

        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
    explicit pmr_vector(std::pmr::memory_resource* mr = std::pmr::get_default_resource())
        : alloc_(mr) {
        reallocate(INITIAL_CAPACITY);
    }

    ~pmr_vector() {
        destroy_elements(data_, data_ + size_);
        deallocate_buffer(data_, capacity_);
    }
    

    allocator_type get_allocator() const noexcept {
        return alloc_;
    }
    
    size_type size() const noexcept { return size_; }
    
    reference operator[](size_type index) {
        if (index >= size_) {
            throw std::out_of_range("pmr_vector index out of range");
        }
        return data_[index];
    }
    
    void push_back(const T& value) {
        if (size_ == capacity_) {
            reallocate(capacity_ * 2);
        }
        alloc_.construct(data_ + size_, value);
        size_++;
    }

    void push_back(T&& value) {
        if (size_ == capacity_) {
            reallocate(capacity_ * 2);
        }
        alloc_.construct(data_ + size_, std::move(value));
        size_++;
    }
    
    iterator begin() noexcept {
        return iterator(data_);
    }

    iterator end() noexcept {
        return iterator(data_ + size_);
    }
    
    const_iterator begin() const noexcept {
        return const_iterator(data_);
    }

    const_iterator end() const noexcept {
        return const_iterator(data_ + size_);
    }
};

#endif 
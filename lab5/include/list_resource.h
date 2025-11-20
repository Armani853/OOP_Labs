#ifndef UNIQUE_LIST_RESOURCE_H
#define UNIQUE_LIST_RESOURCE_H

#include <list>
#include <memory_resource>
#include <cstddef>
#include <iostream>

class UniqueListResource : public std::pmr::memory_resource {
private:
    struct FreeBlock {
        void* ptr;
        size_t size;
        size_t alignment;

        bool operator==(const void* p) const {
            return ptr == p;
        }
    };

    std::list<FreeBlock> allocated_blocks_; 
    

    void* allocate_new_block(size_t bytes, size_t alignment) {
        void* p = ::operator new(bytes, std::align_val_t(alignment)); 
        
        if (!p) {
            throw std::bad_alloc();
        }

        allocated_blocks_.push_front({p, bytes, alignment});
        
        return p;
    }

protected:
    void* do_allocate(size_t bytes, size_t alignment) override {
        for (auto it = allocated_blocks_.begin(); it != allocated_blocks_.end(); ++it) {
            
            if (it->size >= bytes && it->alignment == 0) {
                void* p = it->ptr;
                it->alignment = alignment;
                return p;
            }
        }

        return allocate_new_block(bytes, alignment);
    }

    void do_deallocate(void* p, size_t bytes, size_t alignment) override {
        if (!p) return;

        for (auto& block : allocated_blocks_) {

            if (block.ptr == p && block.size >= bytes) {

                block.alignment = 0; 
                return;
            }
        }
        
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }

public:
    UniqueListResource() = default;
    
    ~UniqueListResource() override {
        size_t leaked_count = 0;
        for (const auto& block : allocated_blocks_) {
            if (block.alignment > 0) { 
                leaked_count++;
            }
            

            size_t effective_alignment = block.alignment > 0 ? block.alignment : 1;
            
            ::operator delete(block.ptr, block.size, std::align_val_t(effective_alignment));
        }
        if (leaked_count > 0) {
            std::cout << " [PMR CLEANUP] Обнаружено и удалено неосвобожденных блоков: " 
                    << leaked_count << "\n";
        }
    }
};

#endif 
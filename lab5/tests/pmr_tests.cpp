#include "gtest/gtest.h"
#include "../include/list_resource.h" 
#include "../include/pmr_vector.h"

#include <string>
#include <vector>
#include <memory>

struct PMRTestStruct {
    int id;
    std::pmr::string name;
    
    PMRTestStruct(int i, const char* n, std::pmr::memory_resource* mr)
        : id(i), name(n, mr) {}

    PMRTestStruct(PMRTestStruct&& other) noexcept
        : id(other.id), value(other.value), name(std::move(other.name)) {
        other.id = -1;
    }

    bool operator==(const PMRTestStruct& other) const {
        return id == other.id && name == other.name;
    }
    
    double value; 
};


TEST(UniqueListResourceTest, AllocationAndDeallocation) {
    UniqueListResource resource;
    
    size_t size1 = 16;
    size_t size2 = 32;

    void* p1 = resource.allocate(size1, alignof(int));
    void* p2 = resource.allocate(size2, alignof(long long));

    ASSERT_NE(p1, nullptr);
    ASSERT_NE(p2, nullptr);
    
    resource.deallocate(p1, size1, alignof(int));
    
    void* p3 = resource.allocate(10, alignof(int));
    
    ASSERT_EQ(p3, p1);

    resource.deallocate(p3, 10, alignof(int));
    resource.deallocate(p2, size2, alignof(long long));
}

TEST(UniqueListResourceTest, LeakCleanupOnDestruction) {
    auto resource_ptr = std::make_unique<UniqueListResource>();
    
    size_t size = 64;
    void* p_leak = resource_ptr->allocate(size, alignof(double));

    resource_ptr.reset(); 
}


TEST(PMRVectorTest, BasicIntFunctionality) {
    UniqueListResource resource;
    pmr_vector<int> vec(&resource);
    
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    ASSERT_EQ(vec.size(), 3);
    ASSERT_EQ(vec[0], 10);
    ASSERT_EQ(vec[2], 30);
}

TEST(PMRVectorTest, ReallocationAndCleanup) {
    UniqueListResource resource;
    pmr_vector<int> vec(&resource);

    for (int i = 0; i < 5; ++i) {
        vec.push_back(i); 
    }
    
    ASSERT_EQ(vec.size(), 5);
    ASSERT_EQ(vec[4], 4);
}

TEST(PMRVectorTest, PMRStringCorrectness) {
    UniqueListResource resource;
    pmr_vector<PMRTestStruct> vec(&resource);
    
    auto mr = vec.get_allocator().resource();

    vec.push_back(PMRTestStruct(1, "DataA", mr));
    vec.push_back(PMRTestStruct(2, "DataB", mr));

    ASSERT_EQ(vec.size(), 2);
    ASSERT_EQ(vec[0].name, "DataA");
    ASSERT_EQ(vec[1].id, 2);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
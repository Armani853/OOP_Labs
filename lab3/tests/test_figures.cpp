#include "gtest/gtest.h"
#include "../include/figure.h"
#include "../include/trapeze.h"
#include "../include/rhombus.h"
#include "../include/pentagon.h"
#include <cmath>
void EXPECT_NEAR_PAIR(const std::pair<double, double>& expected, const std::pair<double, double>& actual, double abs_error) {
    EXPECT_NEAR(expected.first, actual.first, abs_error);
    EXPECT_NEAR(expected.second, actual.second, abs_error);
}


TEST(TrapezeTest, CalculatesAreaCorrectly) {

    std::array<std::pair<double, double>, 4> verts = {{{0, 0}, {4, 0}, {3, 3}, {1, 3}}};
    Trapeze t(verts);
    
    EXPECT_NEAR(9.0, static_cast<double>(t), 1e-9);
    
    EXPECT_NEAR(9.0, t.calculateArea(), 1e-9);
}

TEST(TrapezeTest, CalculatesCenterCorrectly) {
    std::array<std::pair<double, double>, 4> verts = {{{0, 0}, {4, 0}, {3, 3}, {1, 3}}};
    Trapeze t(verts);
    
    EXPECT_NEAR_PAIR({2.0, 1.5}, t.calculateCenter(), 1e-9);
}


TEST(RhombusTest, CalculatesAreaCorrectly) {
    std::array<std::pair<double, double>, 4> verts = {{{0, 3}, {4, 0}, {0, -3}, {-4, 0}}};
    Rhombus r(verts);
    
    EXPECT_NEAR(24.0, r.calculateArea(), 1e-9);
}

TEST(RhombusTest, CalculatesCenterCorrectly) {
    std::array<std::pair<double, double>, 4> verts = {{{0, 3}, {4, 0}, {0, -3}, {-4, 0}}};
    Rhombus r(verts);
    
    EXPECT_NEAR_PAIR({0.0, 0.0}, r.calculateCenter(), 1e-9);
}


TEST(PentagonTest, CalculatesAreaAndCenterCorrectly) {
    double R = 1.701301617; 
    double A = 0.5 * 5 * R * R * std::sin(2 * M_PI / 5.0); // 5 * Area_Triangle
    
    std::array<std::pair<double, double>, 5> verts = {
        {{R, 0.0}, 
         {R * std::cos(2 * M_PI / 5.0), R * std::sin(2 * M_PI / 5.0)},
         {R * std::cos(4 * M_PI / 5.0), R * std::sin(4 * M_PI / 5.0)},
         {R * std::cos(6 * M_PI / 5.0), R * std::sin(6 * M_PI / 5.0)},
         {R * std::cos(8 * M_PI / 5.0), R * std::sin(8 * M_PI / 5.0)}}
    };
    Pentagon p(verts);
    
    EXPECT_NEAR_PAIR({0.0, 0.0}, p.calculateCenter(), 1e-5); 
    
    EXPECT_NEAR(6.8819, p.calculateArea(), 1e-4);
}


TEST(PolymorphismTest, CloneAndEqualityWorks) {
    std::array<std::pair<double, double>, 4> verts_t = {{{0, 0}, {4, 0}, {3, 3}, {1, 3}}};
    Trapeze t1(verts_t);
    
    std::unique_ptr<Figure> t2_ptr = t1.clone();
    
    EXPECT_TRUE(t1 == *t2_ptr);
    
    Trapeze* t2_concrete = dynamic_cast<Trapeze*>(t2_ptr.get());
    ASSERT_NE(t2_concrete, nullptr);
    
    Rhombus r;
    EXPECT_FALSE(t1 == r); 
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
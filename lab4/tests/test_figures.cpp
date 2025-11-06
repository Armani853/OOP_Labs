#include "gtest/gtest.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <memory>
#include "../include/point.h"
#include "../include/figure.h"
#include "../include/shapes.h"
#include "../include/array.h"

using namespace std;

const double EPSILON = 1e-6;


TEST(PointTest, BasicPointOperations) {
    Point<int> p(5, 10);
    EXPECT_EQ(p.x(), 5);
    EXPECT_EQ(p.y(), 10);

    Point<double> p2(1.5, 2.5);
    stringstream ss;
    ss << p2;
    EXPECT_EQ(ss.str(), "(1.5, 2.5)");

    Point<int> p3;
    stringstream ss_in("10 20");
    ss_in >> p3;
    EXPECT_EQ(p3, Point<int>(10, 20));
}

TEST(RectangleTest, AreaAndCenter) {
    Rectangle<int> rect;
    stringstream ss_in("0 0 3 2");
    ss_in >> rect;

    EXPECT_NEAR(rect.area(), 6.0, EPSILON);


    Rectangle<double> rect_d;
    stringstream ss_d("0.0 0.0 3.0 2.0");
    ss_d >> rect_d;
    EXPECT_EQ(rect_d.geometric_center().x(), 1.5);
    EXPECT_EQ(rect_d.geometric_center().y(), 1.0);
}

TEST(TrapezoidTest, AreaAndCenter) {
    Trapezoid<double> trap;
    stringstream ss_in("1.0 0.0 5.0 0.0 4.0 2.0 2.0 2.0");
    ss_in >> trap;

    EXPECT_NEAR(trap.area(), 6.0, EPSILON);
    EXPECT_EQ(trap.geometric_center().x(), 3.0); 
    EXPECT_EQ(trap.geometric_center().y(), 1.0);
}

TEST(RhombusTest, AreaAndCenter) {
    Rhombus<int> rhomb;
    stringstream ss_in("0 5 3 0 6 5 3 10");
    ss_in >> rhomb;

    EXPECT_NEAR(rhomb.area(), 30.0, EPSILON); 
    EXPECT_EQ(rhomb.geometric_center().x(), 3);
    EXPECT_EQ(rhomb.geometric_center().y(), 5);
}

TEST(ArrayTest, StoresNonCopyableObjects) {
    Array<Rectangle<int>> rectangles;
    Rectangle<int> r1;
    Rectangle<int> r2;
    
    stringstream ss1("0 0 3 2");
    ss1 >> r1;
    
    stringstream ss2("20 20 22 21");
    ss2 >> r2;

    rectangles.push_back(std::move(r1));
    rectangles.push_back(std::move(r2));

    EXPECT_EQ(rectangles.size(), 2);
    EXPECT_NEAR(rectangles[0].area(), 6.0, EPSILON);
    EXPECT_NEAR(rectangles[1].area(), 2.0, EPSILON);

    rectangles.remove_at(0); 
    EXPECT_EQ(rectangles.size(), 1);
    EXPECT_NEAR(rectangles[0].area(), 2.0, EPSILON);
}

template<typename T>
double total_area(const Array<T>& figures) {
    double total = 0;
    for (const auto& figure : figures) {
        total += static_cast<double>(*figure); 
    }
    return total;
}

TEST(PolymorphismTest, TotalAreaCalculation) {
    Array<std::shared_ptr<Figure<int>>> figures;

    auto rect = std::make_shared<Rectangle<int>>();
    stringstream ss_rect("0 0 3 2");
    ss_rect >> *rect;
    figures.push_back(rect);

    auto trap = std::make_shared<Trapezoid<int>>();
    stringstream ss_trap("0 0 8 0 6 3 2 3"); 
    ss_trap >> *trap;
    figures.push_back(trap);
    
    auto rhomb = std::make_shared<Rhombus<int>>();
    stringstream ss_rhomb("0 5 3 0 6 5 3 10");
    ss_rhomb >> *rhomb;
    figures.push_back(rhomb);

    EXPECT_NEAR(total_area(figures), 54.0, EPSILON);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
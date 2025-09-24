#include "gtest/gtest.h" 


TEST(MyProgramTests, TrueAssertion) {
    EXPECT_TRUE(true);
}

TEST(MyProgramTests, AdditionTest) {
    int a = 5;
    int b = 7;
    
    ASSERT_EQ(a + b, 12);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
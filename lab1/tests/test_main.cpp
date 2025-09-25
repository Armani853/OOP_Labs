#include "gtest/gtest.h"
#include "../src/find_numbers.h" 
TEST(FindNumbersTest, FindsSingleNumber) {
    EXPECT_EQ("123", find_numbers_in_string("abc123def"));
}

TEST(FindNumbersTest, FindsMultipleNumbers) {
    EXPECT_EQ("10 20 30", find_numbers_in_string("a10b20c30d"));
}

TEST(FindNumbersTest, HandlesNoNumbers) {
    EXPECT_EQ("", find_numbers_in_string("abcdefg"));
}

TEST(FindNumbersTest, HandlesMixedCharacters) {
    EXPECT_EQ("789", find_numbers_in_string("!@#$789%^&*"));
}

TEST(FindNumbersTest, HandlesEmptyString) {
    EXPECT_EQ("", find_numbers_in_string(""));
}
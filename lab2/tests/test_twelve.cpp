#include "gtest/gtest.h"
#include "../src/twelve.h" 

TEST(TwelveConstructorTest, HandlesStringBase12) {
    Twelve t("1B"); 
    EXPECT_EQ("1B", t.to_str());
    
    Twelve t2("A0"); 
    EXPECT_EQ("A0", t2.to_str());
}

TEST(TwelveConstructorTest, HandlesLeadingZeros) {
    Twelve t("001A"); 
    EXPECT_EQ("1A", t.to_str());

    Twelve t2("000"); 
    EXPECT_EQ("0", t2.to_str());
}

TEST(TwelveConstructorTest, HandlesZero) {
    Twelve t; 
    EXPECT_EQ("0", t.to_str());
}

TEST(TwelveConstructorTest, ThrowsOnInvalidCharacter) {
    EXPECT_THROW(Twelve("1C"), std::invalid_argument);
    EXPECT_THROW(Twelve("2G"), std::invalid_argument);
}

TEST(TwelveComparisonTest, HandlesEqual) {
    Twelve a("1A");
    Twelve b("1A");
    Twelve c("1B");
    EXPECT_TRUE(a.equal(b));
    EXPECT_FALSE(a.equal(c));
}

TEST(TwelveComparisonTest, HandlesGreater) {
    Twelve a("100"); 
    Twelve b("B");   
    Twelve c("10");  

    EXPECT_TRUE(a.greater(b));     
    EXPECT_TRUE(a.greater(c));
    EXPECT_FALSE(c.greater(a));
    EXPECT_FALSE(c.greater(c));    
}

TEST(TwelveComparisonTest, HandlesGreaterSameLength) {
    Twelve a("9B"); 
    Twelve b("B9"); 
    
    EXPECT_TRUE(b.greater(a));
    EXPECT_FALSE(a.greater(b));
}

TEST(TwelveComparisonTest, HandlesLess) {
    Twelve a("1A");
    Twelve b("20");
    
    EXPECT_TRUE(a.less(b));
    EXPECT_FALSE(b.less(a));
    EXPECT_FALSE(a.less(a)); 
}

TEST(TwelveAddTest, SimpleAddition) {
    Twelve a("5");
    Twelve b("3");
    Twelve result = a.add(b);
    EXPECT_EQ("8", result.to_str());
}

TEST(TwelveAddTest, AdditionWithCarry) {
    Twelve a("B");
    Twelve b("1");
    Twelve result = a.add(b);
    EXPECT_EQ("10", result.to_str()); 
}

TEST(TwelveAddTest, AdditionWithMultipleCarry) {
    Twelve a("BB");
    Twelve b("1");
    Twelve result = a.add(b);
    EXPECT_EQ("100", result.to_str());
}

TEST(TwelveAddTest, AdditionWithLengthIncrease) {
    Twelve a("A0");
    Twelve b("30");
    Twelve result = a.add(b);
    EXPECT_EQ("110", result.to_str()); 
}

TEST(TwelveSubTest, SimpleSubtraction) {
    Twelve a("9");
    Twelve b("4");
    Twelve result = a.sub(b);
    EXPECT_EQ("5", result.to_str());
}

TEST(TwelveSubTest, SubtractionWithBorrow) {
    Twelve a("10");
    Twelve b("1");
    Twelve result = a.sub(b);
    EXPECT_EQ("B", result.to_str());
}

TEST(TwelveSubTest, SubtractionResultsInZero) {
    Twelve a("1A");
    Twelve b("1A");
    Twelve result = a.sub(b);
    EXPECT_EQ("0", result.to_str());
}

TEST(TwelveSubTest, SubtractionRemovesLeadingZeros) {
    Twelve a("200");
    Twelve b("1");
    Twelve result = a.sub(b);
    EXPECT_EQ("1BB", result.to_str());
}

TEST(TwelveSubTest, ThrowsOnInvalidSubtraction) {
    Twelve a("10");
    Twelve b("11"); 
    EXPECT_THROW(a.sub(b), std::invalid_argument); 
}
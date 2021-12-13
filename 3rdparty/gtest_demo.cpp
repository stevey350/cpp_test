#include <gtest/gtest.h>

int add(int a,int b)
{
    return a+b;
}

// 宏TEST原型：TEST(TestSuiteName, TestName)
TEST(TestSuit1, add_test)
{
    EXPECT_EQ(add(2,3), 5);
}

// Demonstrate some basic assertions.
TEST(TestSuit1, BasicAssertions_test)
{
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

int main(int argc,char*argv[])
{
   testing::InitGoogleTest(&argc,argv);
   return RUN_ALL_TESTS();
}

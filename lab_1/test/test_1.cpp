#include <gtest/gtest.h>
#include "../include/counter.h"

TEST(test_01, basic_test_set)
{
    int a = 1;
    int b = 1;
    int result = counter(a, b);
    ASSERT_TRUE(result==1);
}

TEST(test_02, basic_test_set)
{
    int a = 2;
    int b = 7;
    int result = counter(a, b);
    ASSERT_TRUE(result==11);
}

TEST(test_03, basic_test_set)
{
    int a = 1;
    int b = 18;
    int result = counter(a, b);
    ASSERT_TRUE(result==37);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
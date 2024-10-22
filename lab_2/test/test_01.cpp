#include <gtest/gtest.h>
#include "../include/decimal.h"
#include <string>

TEST(Decimal_test, Default_constructor)
{
    Decimal obj;
    size_t size = obj.get_size();
    unsigned char *data = obj.get_all_data();
    ASSERT_TRUE(size == 0);
    ASSERT_TRUE(data == nullptr);
}

TEST(Decimal_test, set_def_constructor)
{
    size_t n = 7;
    unsigned char t = '7';
    Decimal obj(n, t);
    size_t size = obj.get_size();
    unsigned char *data = obj.get_all_data();

    ASSERT_TRUE(size == n);
    for (size_t i = 0; i < size; ++i)
    {
        ASSERT_TRUE(data[i] == t);
    }
}

TEST(Decimal_test, lst_constructor)
{
    std::initializer_list<unsigned char> lst = {'7', '2', '1', '5', '3', '7', '4'};
    Decimal obj(lst);
    size_t size = obj.get_size();
    unsigned char *data = obj.get_all_data();

    ASSERT_TRUE(size == lst.size());
    size_t c = 0;
    for (unsigned char i: lst)
    {
        ASSERT_TRUE(data[c] == i);
        ++c;
    }
}

TEST(Decimal_test, constructor_with_string)
{

    std::string st = "1234567890";
    Decimal b(st);

    size_t size = b.get_size();
    unsigned char *data = b.get_all_data();
    ASSERT_TRUE(size ==st.size());
    for (size_t i = 0; i < size; ++i)
    {
        ASSERT_TRUE(data[i] == st[i]);
    }
}

TEST(Decimal_test, constructor_with_copy){
    Decimal obj_1("7777");
    Decimal obj_2(obj_1);
    for (size_t i = 0; i < obj_1.get_size(); ++i){
        ASSERT_TRUE(obj_1.get_all_data()[i] == obj_2.get_all_data()[i]);
    }
}
TEST(Decimal_test, get_size_method){
    Decimal obj("1234567890");
    ASSERT_TRUE(obj.get_size() == 10);
}
TEST(Decimal_test, Operator_of_assign)
{
    std::initializer_list<unsigned char> lst = {'7', '2', '1', '5', '3', '7', '4'};
    Decimal obj_1(lst);
    Decimal obj_2;
    obj_2 = obj_1;
    ASSERT_TRUE(obj_2.get_size() == obj_1.get_size());
    auto data_1 = obj_1.get_all_data();
    auto data_2 = obj_2.get_all_data();
    for (int i = 0; i < obj_2.get_size(); ++i)
    {
        ASSERT_TRUE(data_1[i] == data_2[i]);
    }
}

TEST(Decimal_test, equal_operator)
{

    Decimal obj_1("777");
    Decimal obj_2("666");
    Decimal obj_3("111");

    EXPECT_FALSE(obj_1 == obj_2);
    EXPECT_FALSE(obj_1 == obj_3);
    obj_2 += obj_3;
    ASSERT_TRUE(obj_1 == obj_2);
}

TEST(Decimal_test, Operator_of_not_equality)
{
    Decimal obj_1("777");
    Decimal obj_2("666");
    Decimal obj_3("111");

    EXPECT_TRUE(obj_1 != obj_2);
    EXPECT_TRUE(obj_1 != obj_3);
    obj_2 += obj_3;
    ASSERT_FALSE(obj_1 != obj_2);
}

TEST(Decimal_test, substraction)
{

    Decimal obj_1("5678");
    Decimal obj_2("1234");
    obj_1 -= obj_2;
    std::string ans = "4444";
    ASSERT_TRUE(obj_1.get_size() == 4);
    for (size_t i = 0; i < obj_1.get_size(); ++i)
    {
        ASSERT_TRUE(obj_1.get_all_data()[i] == ans[i]);
    }
}

TEST(Decimal_test, less_oper)
{
    Decimal obj_1("1333");
    Decimal obj_2("777");
    EXPECT_TRUE(obj_1 > obj_2);
    EXPECT_FALSE(obj_2 > obj_1);
}

TEST(Decimal_test, greater_oper)
{
    Decimal obj_1("1234");
    Decimal obj_2("5678");
    EXPECT_TRUE(obj_2 > obj_1);
    EXPECT_FALSE(obj_2 < obj_1);
}
TEST(Decimal_test, Operator_of_addition)
{
    Decimal obj_1("1234");
    Decimal obj_2("5678");
    obj_1 += obj_2;
    ASSERT_TRUE(obj_1.get_size() == 4);
    auto ch = obj_1.get_all_data();
    std::string ch_st = "6912";
    for (size_t i = 0; i < obj_1.get_size(); ++i){
        ASSERT_TRUE(ch[i] == ch_st[i]);
    }
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#include <iostream>
#include "include/decimal.h"

int main()
{
    try
    {
        std::string first_num, second_num;
        std::cout << "Enter first number: ";
        std::cin >> first_num;
        std::cout << "Enter second number: ";
        std::cin >> second_num;
        Decimal first(first_num);
        Decimal second(second_num);
        first -= second;
        std::cout << "result of subtraction: ";
        for (size_t i = 0; i < first.get_size(); ++i)
        {
            std::cout << first.get_all_data()[i];
        }
        std::cout << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }
    try
    {
        std::initializer_list<unsigned char> first_one {'1', '2', '3'};
        std::initializer_list<unsigned char> second_two {'1', '2', '1'};
        Decimal new_first(first_one);
        Decimal new_second(second_two);
        Decimal result("123");
        result += new_second;
        std::cout << "result of addition: ";
        for (size_t i = 0; i < result.get_size(); ++i)
        {
            std::cout << result.get_all_data()[i];
        }
        std::cout << std::endl;
        if (new_first != new_second){
            std::cout << "123 and 121 are not equal" << std::endl;
        }
        Decimal just_two("2");
        new_second += just_two;
        new_first.print(std::cout);
        std::cout << std::endl;
        new_second.print(std::cout);
        std::cout << std::endl;
        if (new_first == new_second){
            std::cout << "now they are equal because 123 = 123" << std::endl;
        }

    }
    catch (const std::exception &ex)
    {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }
    return 0;
}
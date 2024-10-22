#pragma once
#include <iostream>
#include <string>
#include <initializer_list>


void checking_digit(unsigned char digit);
class Decimal
{
public:
    Decimal();
    Decimal(const size_t &n, unsigned char t);
    Decimal(const std::initializer_list<unsigned char> &t);
    Decimal(const std::string &t);
    Decimal(const Decimal &other);
    Decimal(Decimal &&other) noexcept;
    ~Decimal() noexcept;

    size_t get_size();
    unsigned char* get_all_data() const;

    bool operator==(const Decimal &other) const;
    bool operator!=(const Decimal &other) const;
    Decimal& operator+=(const Decimal &other);
    Decimal& operator-=(const Decimal &other);
    Decimal& operator=(const Decimal &other);
    Decimal& operator=(Decimal &&other) noexcept;
    bool operator>(const Decimal& other) const;
    bool operator<(const Decimal& other) const;

    std::ostream &print(std::ostream &os);

private:
    size_t _size;
    unsigned char* _array;
    void checking_digit(unsigned char digit);
};



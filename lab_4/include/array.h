#pragma once
#include <memory>
#include <stdexcept>

template <typename T>
class Array
{
public:
    Array();
    Array(const Array &other);
    Array(Array &&other) noexcept;
    size_t get_size() const;
    void push_back(std::shared_ptr<T> element);
    void remove(size_t index);
    Array &operator=(Array &&other) noexcept;
    Array &operator=(const Array &other);
    std::shared_ptr<T> &operator[](size_t index);
    const std::shared_ptr<T>& operator[](size_t index) const;

private:
    size_t size;
    size_t capacity;
    std::unique_ptr<std::shared_ptr<T>[]> data;
    void resize(size_t newCapacity);
};
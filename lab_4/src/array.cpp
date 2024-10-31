#include "../include/array.h"

template <typename T>
Array<T>::Array(){
    size = 0;
    capacity = 10;
    data = std::make_unique<std::shared_ptr<T>[]>(capacity);
    }

template <typename T>
Array<T>::Array(const Array &other)
{
    size = other.size;
    capacity = other.capacity;
    data = std::make_unique<std::shared_ptr<T>[]>(other.capacity);
    for (size_t i = 0; i < size; ++i){
        data[i] = std::make_shared<T>(*other.data[i]);
    }
}

template <typename T>
Array<T>::Array(Array &&other) noexcept{
    size = other.size;
    capacity = other.capacity;
    data = std::move(other.data);
    other.size = 0;
    other.capacity = 0;
}

template <typename T>
Array<T> &Array<T>::operator=(Array &&other) noexcept{
    if (this != &other)
    {
        size = other.size;
        capacity = other.capacity;
        data = std::move(other.data);
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}

template <typename T>
const std::shared_ptr<T>& Array<T>::operator[](size_t index) const {
    return data[index];
}

template <typename T>
Array<T> &Array<T>::operator=(const Array &other){
    if (this != &other)
    {
        size = other.size;
        capacity = other.capacity;
        data = std::make_unique<std::shared_ptr<T>[]>(other.capacity);
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = std::make_shared<T>(*other.data[i]);
        }
    }
    return *this;
}

template <typename T>
size_t Array<T>::get_size() const{
    return size;
}

template <typename T>
void Array<T>::push_back(std::shared_ptr<T> elem_to_push){
    if (size == capacity)
    {
        resize(capacity * 2);
    }
    data[size++] = std::move(elem_to_push);
}

template <typename T>
void Array<T>::remove(size_t index_of_deleting){
    if (index_of_deleting >= size)
    {
        throw std::invalid_argument("Index out of range");
    }
    for (size_t i = index_of_deleting; i < size - 1; ++i)
    {
        data[i] = std::move(data[i + 1]);
    }
    --size;
}

template <typename T>
std::shared_ptr<T> &Array<T>::operator[](size_t index)
{
    if (index >= size)
    {
        throw std::invalid_argument("Index out of range");
    }
    return data[index];
}

template <typename T>
void Array<T>::resize(size_t new_size)
{
    auto new_elems = std::make_unique<std::shared_ptr<T>[]>(new_size);
    for (size_t i = 0; i < size; ++i)
    {
        new_elems[i] = std::move(data[i]);
    }
    data = std::move(new_elems);
    capacity = new_size;
}
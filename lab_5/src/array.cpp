#include "../include/Array.h"
#include <algorithm>

template <typename T>
Array<T>::Array(size_t capacity)
    : size(0), capacity(capacity), data(nullptr) {
    reserve_data(capacity);
}

template <typename T>
Array<T>::~Array() {
    clear();
    alloc.deallocate(data, capacity);
}

template <typename T>
T* Array<T>::begin() {
    return data;
}

template <typename T>
T* Array<T>::end() {
    return data + size;
}

template <typename T>
const T* Array<T>::cbegin() const {
    return data;
}

template <typename T>
const T* Array<T>::cend() const {
    return data + size;
}

template <typename T>
bool Array<T>::is_empty() const {
    return size == 0;
}

template <typename T>
size_t Array<T>::get_size() const {
    return size;
}

template <typename T>
size_t Array<T>::get_capacity() const {
    return capacity;
}

template <typename T>
const T& Array<T>::operator[](size_t i) const {
    if (i >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

template <typename T>
T& Array<T>::operator[](size_t i) {
    if (i >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

template <typename T>
void Array<T>::swap(Array<T>& other) noexcept {
    std::swap(data, other.data);
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(alloc, other.alloc);
}

template <typename T>
T* Array<T>::erase(T* pos) {
    if (pos < data || pos >= data + size) {
        throw std::out_of_range("Iterator out of range");
    }
    std::move(pos + 1, data + size, pos);
    --size;
    std::allocator_traits<std::allocator<T>>::destroy(alloc, &data[size]);
    return pos;
}

template <typename T>
T* Array<T>::erase(T* start, T* end) {
    if (start < data || end > data + size || start >= end) {
        throw std::out_of_range("Iterator out of range");
    }
    std::move(end, data + size, start);
    size -= (end - start);
    for (T* ptr = data + size; ptr != data + capacity; ++ptr) {
        std::allocator_traits<std::allocator<T>>::destroy(alloc, ptr);
    }
    return start;
}

template <typename T>
T* Array<T>::insert(T* pos, const T& value) {
    if (pos < data || pos > data + size) {
        throw std::out_of_range("Iterator out of range");
    }
    
    size_t offset = pos - data;
    if (size == capacity) {
        reserve_data(capacity * 2);
        pos = data + offset;
    }

    std::move_backward(pos, data + size, data + size + 1);
    std::allocator_traits<std::allocator<T>>::construct(alloc, pos, value);
    ++size;
    return pos;
}

template <typename T>
T* Array<T>::insert(T* pos, const T& value, size_t count) {
    if (pos < data || pos > data + size) {
        throw std::out_of_range("Iterator out of range");
    }

    size_t offset = pos - data;
    if (size + count > capacity) {
        reserve_data(std::max(capacity * 2, size + count));
        pos = data + offset;
    }

    std::move_backward(pos, data + size, data + size + count);
    for (size_t j = 0; j < count; ++j) {
        std::allocator_traits<std::allocator<T>>::construct(alloc, pos + j, value);
    }
    size += count;
    return pos;
}

template <typename T>
T* Array<T>::insert(T* pos, T* start, T* end) {
    if (pos < data || pos > data + size) {
        throw std::out_of_range("Iterator out of range");
    }

    size_t count = end - start;
    size_t offset = pos - data;
    if (size + count > capacity) {
        reserve_data(std::max(capacity * 2, size + count));
        pos = data + offset;
    }

    std::move_backward(pos, data + size, data + size + count);
    std::uninitialized_copy(start, end, pos);
    size += count;
    return pos;
}

template <typename T>
void Array<T>::push_back(const T& value) {
    if (size == capacity) {
        reserve_data(capacity * 2);
    }
    std::allocator_traits<std::allocator<T>>::construct(alloc, &data[size], value);
    ++size;
}

template <typename T>
void Array<T>::pop_back() {
    if (size > 0) {
        --size;
        std::allocator_traits<std::allocator<T>>::destroy(alloc, &data[size]);
    } else {
        throw std::out_of_range("Array is empty");
    }
}

template <typename T>
void Array<T>::clear() {
    for (size_t i = 0; i < size; ++i) {
        std::allocator_traits<std::allocator<T>>::destroy(alloc, &data[i]);
    }
    size = 0;
}

template <typename T>
void Array<T>::reserve_data(size_t new_capacity) {
    T* new_data = alloc.allocate(new_capacity);
    if (data) {
        std::uninitialized_move(data, data + size, new_data);
        alloc.deallocate(data, capacity);
    }
    data = new_data;
    capacity = new_capacity;
}
#pragma once

template <typename T>
class Iterator {
public:
    explicit Iterator(T *pointer) : iter_ptr(pointer) {}

    T &operator*() const {
        return *iter_ptr;
    }

    T *operator->() const {
        return iter_ptr;
    }

    bool operator==(const Iterator &other_iter) const {
        return iter_ptr == other_iter.iter_ptr;
    }

    bool operator!=(const Iterator &other_iter) const {
        return iter_ptr != other_iter.iter_ptr;
    }

    Iterator &operator++() {
        ++iter_ptr;
        return *this;
    }

    

    Iterator operator+(size_t n) const {
        return Iterator(iter_ptr + n);
    }

    Iterator &operator+=(size_t n) {
        iter_ptr += n;
        return *this;
    }

    Iterator operator-(size_t n) const {
        return Iterator(iter_ptr - n);
    }

    Iterator &operator-=(size_t n) {
        iter_ptr -= n;
        return *this;
    }

    size_t operator-(const Iterator &other_iter) const {
        return iter_ptr - other_iter.iter_ptr;
    }
    Iterator &operator--() {
        --iter_ptr;
        return *this;
    }
private:
    T *iter_ptr;
};
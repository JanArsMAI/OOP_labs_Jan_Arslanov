#pragma once

template <typename T>
class ConstIterator {
public:
    explicit ConstIterator(const T *pointer) : iter_ptr(pointer) {}

    const T &operator*() const {
        return *iter_ptr;
    }

    const T *operator->() const {
        return iter_ptr;
    }

    bool operator==(const ConstIterator &other_iter) const {
        return iter_ptr == other_iter.iter_ptr;
    }

    bool operator!=(const ConstIterator &other_iter) const {
        return iter_ptr != other_iter.iter_ptr;
    }

    ConstIterator &operator++() {
        ++iter_ptr;
        return *this;
    }

    

    ConstIterator operator+(size_t n) const {
        return ConstIterator(iter_ptr + n);
    }

    ConstIterator &operator+=(size_t n) {
        iter_ptr += n;
        return *this;
    }

    ConstIterator operator-(size_t n) const {
        return ConstIterator(iter_ptr - n);
    }

    ConstIterator &operator-=(size_t n) {
        iter_ptr -= n;
        return *this;
    }

    size_t operator-(const ConstIterator &other_iter) const {
        return iter_ptr - other_iter.iter_ptr;
    }
    ConstIterator &operator--() {
        --iter_ptr;
        return *this;
    }

private:
    const T *iter_ptr;
};
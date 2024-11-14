#include <memory> 
#include <stdexcept> 
#include <algorithm> 

template <typename T>
class Array {
public:
    Array(size_t capacity);
    ~Array();

    T* begin();
    T* end();
    const T* cbegin() const;
    const T* cend() const;
    bool is_empty() const;
    size_t get_size() const;
    size_t get_capacity() const;
    const T& operator[](size_t i) const;
    T& operator[](size_t i);
    void swap(Array<T>& other) noexcept;
    T* erase(T* pos);
    T* erase(T* start, T* end);
    T* insert(T* pos, const T& value);
    T* insert(T* pos, const T& value, size_t count);
    T* insert(T* pos, T* start, T* end);
    void push_back(const T& value);
    void pop_back();
    void clear();
    void reserve_data(size_t new_capacity);

private:

    std::allocator<T> alloc;
    size_t size;
    size_t capacity;
    T* data;
};
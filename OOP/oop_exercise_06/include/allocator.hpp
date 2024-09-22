#ifndef CONT_ALLOCATOR_HPP
#define CONT_ALLOCATOR_HPP

#include <exception>
#include "stack.hpp"

template<typename T, size_t ALLOC_SIZE>
class allocator {
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using is_always_equal = std::false_type;

    template<class V>
    struct rebind {
        using other = allocator<V, ALLOC_SIZE>;
    };

    allocator(const allocator&) = delete;
    allocator(allocator&&) = delete;

    allocator() {
        size_t object_count = ALLOC_SIZE / sizeof(T);
        memory = reinterpret_cast<char*>(operator new(sizeof(T) * object_count));
        for(size_t i = 0; i < object_count; ++i) {
            free_blocks.push(memory + sizeof(T) * i);
        }
    }
    ~allocator() {
        operator delete(memory);
    }

    T* allocate(size_t size) {
        if (size > 1) {
            throw std::logic_error("This allocator cant do that");
        }
        if (free_blocks.empty()) {
            throw std::bad_alloc();
        }
        T* temp = reinterpret_cast<T*>(free_blocks.top());
        free_blocks.pop();
        return temp;
    }

    void deallocate(T* ptr, size_t size) {
        if (size > 1) {
            throw std::logic_error("This allocator cant do that");
        }
        free_blocks.push(reinterpret_cast<char*>(ptr));
    }

private:
    cont::stack<char*> free_blocks;
    char* memory;
};

#endif

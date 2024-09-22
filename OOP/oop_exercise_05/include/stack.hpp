#ifndef CONT_STACK_HPP
#define CONT_STACK_HPP

#include <exception>
#include <memory>

namespace cont {
    template<class T>
    class stack {
    private:
        class stack_node;
        std::shared_ptr<stack_node> head;
        std::shared_ptr<stack_node> tail;
    public:
        class iterator;
        class const_iterator;
        stack();
        stack(const stack&) = delete;
        stack& operator =(const stack&) = delete;

        bool empty() const;
        void push(const T&);
        void pop();
        T& top();
        size_t size() const;

        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;

        void insert(iterator, const T&);
        void erase(iterator);
    };

    template<typename T>
    struct stack<T>::stack_node {
        stack_node() = default;
        stack_node(T new_value) : value(new_value) {}

        T value;
        std::shared_ptr<stack_node> next = nullptr;
        std::weak_ptr<stack_node> prev;
    };

    template<typename T>
    stack<T>::stack() {
        head = std::make_shared<stack_node>();
        tail = head;
    }

    template<typename T>
    bool stack<T>::empty() const {
        return head == tail;
    }

    template<typename T>
    void stack<T>::push(const T& value) {
        std::shared_ptr<stack_node> new_elem = std::make_shared<stack_node>(value);
        if(empty()) {
            head = new_elem;
            head->next = tail;
            tail->prev = head;
        } else {
            new_elem->next = head;
            head->prev = new_elem;
            head = new_elem;
        }
    }

    template<typename T>
    void stack<T>::pop() {
        if(empty()) {
            throw std::out_of_range("Pop from empty stack");
        }
        head = head->next;
    }

    template<typename T>
    T& stack<T>::top() {
        return head->value;
    }

    template<typename T>
    size_t stack<T>::size() const {
        size_t size = 0;
        for(auto i : *this) {
            ++size;
        }
        return size;
    }

    template<typename T>
    typename stack<T>::iterator stack<T>::begin() {
        return iterator(head, this);
    }
    template<typename T>
    typename stack<T>::iterator stack<T>::end() {
        return iterator(tail, this);
    }
    template<typename T>
    typename stack<T>::const_iterator stack<T>::begin() const {
        return const_iterator(head, this);
    }
    template<typename T>
    typename stack<T>::const_iterator stack<T>::end() const {
        return const_iterator(tail, this);
    }

    template<typename T>
    void stack<T>::insert(iterator it, const T& value) {
        if(it.collection != this) {
            throw std::runtime_error("Iterator does not belong to this collection");
        }
        std::shared_ptr<stack_node> it_ptr = it.node.lock();
        if(!it_ptr) {
            throw std::runtime_error("Iterator is corrupted");
        }
        if(it == begin()) {
            push(value);
            return;
        }
        std::shared_ptr<stack_node> new_elem = std::make_shared<stack_node>(value);
        if(it == end()) {
            it_ptr->prev.lock()->next = new_elem;
            new_elem->prev = it_ptr->prev;
            new_elem->next = it_ptr;
            it_ptr->prev = new_elem;
        } else {
            std::shared_ptr<stack_node> next_ptr = it_ptr->next;
            std::weak_ptr<stack_node> prev_ptr = it_ptr;
            new_elem->next = next_ptr;
            next_ptr->prev = new_elem;
            new_elem->prev = prev_ptr;
            prev_ptr.lock()->next = new_elem;
        }
    }

    template<typename T>
    void stack<T>::erase(iterator it) {
        if(it.collection != this) {
            throw std::runtime_error("Iterator does not belong to this collection");
        }
        std::shared_ptr<stack_node> it_ptr = it.node.lock();
        if(!it_ptr) {
            throw std::runtime_error("Iterator is corrupted");
        }
        if(it == end()) {
            throw std::runtime_error("Erase of end iterator");
        }
        if(it == begin()) {
            pop();
        } else {
            std::shared_ptr<stack_node> next_ptr = it_ptr->next;
            std::weak_ptr<stack_node> prev_ptr = it_ptr->prev;
            next_ptr->prev = prev_ptr;
            prev_ptr.lock()->next = next_ptr;
        }
    }

    template<typename T>
    class stack<T>::iterator {
        friend stack<T>;
    public:
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator(std::shared_ptr<stack_node> init_ptr, const stack<T>* ptr) : node(init_ptr), collection(ptr) {}
        iterator(const iterator& other) : node(other.node), collection(other.collection) {}

        iterator& operator =(const iterator&);
        bool operator ==(const iterator&) const;
        bool operator !=(const iterator&) const;
        iterator& operator ++();
        iterator operator ++(int);
        T& operator *() const;
    private:
        std::weak_ptr<stack_node> node;
        const stack<T>* collection;
    };

    template<typename T>
    typename stack<T>::iterator& stack<T>::iterator::operator =(const iterator& other) {
        node = other.node;
        return *this;
    }
    template<typename T>
    bool stack<T>::iterator::operator ==(const iterator& other) const {
        auto lhs = node.lock();
        auto rhs = other.node.lock();
        if (lhs && rhs) {
            return lhs.get() == rhs.get();
        }
        return false;
    }
    template<typename T>
    bool stack<T>::iterator::operator !=(const iterator& other) const {
        return !(*this == other);
    }
    template<typename T>
    typename stack<T>::iterator& stack<T>::iterator::operator ++() {
        std::shared_ptr<stack_node> tmp = node.lock();
        if(tmp) {
            if(tmp->next == nullptr) {
                throw std::out_of_range("Going out of container boundaries");
            }
            tmp = tmp->next;
            node = tmp;
            return *this;
        } else {
            throw std::runtime_error("Element pointed by this iterator doesnt exist anymore");
        }
    }
    template<typename T>
    typename stack<T>::iterator stack<T>::iterator::operator ++(int) {
        iterator result(*this);
        ++(*this);
        return result;
    }

    template<typename T>
    T& stack<T>::iterator::operator *() const {
        std::shared_ptr<stack_node> tmp = node.lock();
        if(tmp) {
            if(tmp->next == nullptr) {
                throw std::runtime_error("Dereferencing of end iterator");
            }
            return tmp->value;
        } else {
            throw std::runtime_error("Element pointed by this iterator doesnt exist anymore");
        }
    }

    template<typename T>
    class stack<T>::const_iterator {
    private:
        std::weak_ptr<stack_node> node;
        const stack<T>* collection;
    public:
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        const_iterator(std::shared_ptr<stack_node> init_ptr, const stack<T>* ptr) : node(init_ptr), collection(ptr) {}
        const_iterator(const const_iterator& other) : node(other.node), collection(other.collection) {}

        const_iterator& operator =(const const_iterator&);
        bool operator ==(const const_iterator&) const;
        bool operator !=(const const_iterator&) const;
        const_iterator& operator ++();
        const_iterator operator ++(int);
        T& operator *() const;
    };

    template<typename T>
    typename stack<T>::const_iterator& stack<T>::const_iterator::operator =(const const_iterator& other) {
        node = other.node;
        return *this;
    }
    template<typename T>
    bool stack<T>::const_iterator::operator ==(const const_iterator& other) const {
        auto lhs = node.lock();
        auto rhs = other.node.lock();
        if (lhs && rhs) {
            return lhs.get() == rhs.get();
        }
        return false;
    }
    template<typename T>
    bool stack<T>::const_iterator::operator !=(const const_iterator& other) const {
        return !(*this == other);
    }
    template<typename T>
    typename stack<T>::const_iterator& stack<T>::const_iterator::operator ++() {
        std::shared_ptr<stack_node> tmp = node.lock();
        if(tmp) {
            if(tmp->next == nullptr) {
                throw std::out_of_range("Going out of container boundaries");
            }
            tmp = tmp->next;
            node = tmp;
            return *this;
        } else {
            throw std::runtime_error("Element pointed by this iterator doesnt exist anymore");
        }
    }
    template<typename T>
    typename stack<T>::const_iterator stack<T>::const_iterator::operator ++(int) {
        const_iterator result(*this);
        ++(*this);
        return result;
    }

    template<typename T>
    T& stack<T>::const_iterator::operator *() const {
        std::shared_ptr<stack_node> tmp = node.lock();
        if(tmp) {
            if(tmp->next == nullptr) {
                throw std::runtime_error("Dereferencing of end iterator");
            }
            return tmp->value;
        } else {
            throw std::runtime_error("Element pointed by this iterator doesnt exist anymore");
        }
    }
}

#endif

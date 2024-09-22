#ifndef T_POINT_HPP
#define T_POINT_HPP

#include <iostream>

template<typename T>
struct point {
    T x;
    T y;
    point<T> operator +(point<T>&);
    point<T> operator -(point<T>&);
};

template<typename T>
point<T> point<T>::operator +(point<T>& other) {
    return {x + other.x, y + other.y};
}

template<typename T>
point<T> point<T>::operator -(point<T>& other) {
    return {x - other.x, y - other.y};
}

template<typename T>
std::ostream& operator <<(std::ostream& os, const point<T>& p) {
    os << p.x << " " << p.y;
    return os;
}

template<typename T>
std::istream& operator >>(std::istream& is, point<T>& p) {
    is >> p.x >> p.y;
    return is;
}

#endif

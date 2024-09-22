#ifndef T_HEXAGON_HPP
#define T_HEXAGON_HPP

#include <iostream>
#include <exception>

#include "point.hpp"

template<typename T>
class hexagon {
public:
    hexagon() = default;
    hexagon(point<T>&, point<T>&, point<T>&, point<T>&, point<T>&, point<T>&);
    point<double> center() const;
    double area() const;
    void write(std::ostream&) const;
    void read(std::istream&);
private:
    point<T> p1, p2, p3, p4, p5, p6;
};

template<typename T>
hexagon<T>::hexagon(point<T>& p1_, point<T>& p2_, point<T>& p3_, point<T>& p4_, point<T>& p5_, point<T>& p6_)
            : p1(p1_), p2(p2_), p3(p3_), p4(p4_), p5(p5_), p6(p6_) {};

template<typename T>
point<double> hexagon<T>::center() const {
    point<double> res;
    res.x = double(p1.x + p2.x + p3.x + p4.x + p5.x + p6.x) / 6;
    res.y = double(p1.y + p2.y + p3.y + p4.y + p5.y + p6.y) / 6;
    return res;
}

template<typename T>
double hexagon<T>::area() const {
    double A = (p1.x * p2.y + p2.x * p3.y + p3.x * p4.y + p4.x * p5.y + p5.x * p6.y + p6.x * p1.y)
        - (p2.x * p1.y + p3.x * p2.y + p4.x * p3.y + p5.x * p4.y + p6.x * p5.y) - (p1.x * p6.y);
    return A >= 0 ? (A * 0.5) : (-A * 0.5);
}

template<typename T>
void hexagon<T>::write(std::ostream& os) const {
    os << "Hexagon p1: " << p1 << ", p2: "<< p2 << ", p3: "<< p3 << ", p4: "<< p4 << ", p5: "<< p5 << ", p6: "<< p6;
}

template<typename T>
void hexagon<T>::read(std::istream& is) {
    point<T> p1_, p2_, p3_, p4_, p5_, p6_;
    is >> p1_ >> p2_ >> p3_ >> p4_ >> p5_ >> p6_;
    *this = hexagon(p1_, p2_, p3_, p4_, p5_, p6_);
}

template<typename T>
std::ostream& operator <<(std::ostream& os, const hexagon<T>& hex) {
    hex.write(os);
    return os;
}

template<typename T>
std::istream& operator >>(std::istream& is, hexagon<T>& hex) {
    hex.read(is);
    return is;
}

#endif

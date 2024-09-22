#ifndef T_TRIANGLE_HPP
#define T_TRIANGLE_HPP

#include "point.hpp"
#include "figure.hpp"

template<typename T>
class triangle : public figure {
public:
    triangle() = default;
    triangle(point<T>&, point<T>&, point<T>&);
    int get_size() const override;
    double area() override;
    point<double> center() override;
    void write(std::ostream&) const override;
    void read(std::istream&) override;
private:
    point<T> p1, p2, p3;
};

template<typename T>
triangle<T>::triangle(point<T>& p1_, point<T>& p2_, point<T>& p3_)
            : p1(p1_), p2(p2_), p3(p3_) {};

template<typename T>
int triangle<T>::get_size() const {
    return 3;
}

template<typename T>
double triangle<T>::area() {
    point<T> points[3] = {p1, p2, p3};
    return polygon_area(points, 3);
}

template<typename T>
point<double> triangle<T>::center() {
    point<T> points[3] = {p1, p2, p3};
    return polygon_center(points, 3);
}

template<typename T>
void triangle<T>::write(std::ostream& os) const {
    os << "triangle " << p1 << " " << p2 << " " << p3;
}

template<typename T>
void triangle<T>::read(std::istream& is) {
    point<T> p1_, p2_, p3_;
    is >> p1_ >> p2_ >> p3_;
    *this = triangle(p1_, p2_, p3_);
}

template<typename T>
std::ostream& operator <<(std::ostream& os, const triangle<T>& tri) {
    tri.write(os);
    return os;
}

template<typename T>
std::istream& operator >>(std::istream& is, triangle<T>& tri) {
    tri.read(is);
    return is;
}

#endif

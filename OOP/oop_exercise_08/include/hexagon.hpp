#ifndef T_HEXAGON_HPP
#define T_HEXAGON_HPP

#include "point.hpp"
#include "figure.hpp"

template<typename T>
class hexagon : public figure {
public:
    hexagon() = default;
    hexagon(point<T>&, point<T>&, point<T>&, point<T>&, point<T>&, point<T>&);
    int get_size() const override;
    double area() override;
    point<double> center()  override;
    void write(std::ostream&) const override;
    void read(std::istream&) override;
private:
    point<T> p1, p2, p3, p4, p5, p6;
};

template<typename T>
hexagon<T>::hexagon(point<T>& p1_, point<T>& p2_, point<T>& p3_, point<T>& p4_, point<T>& p5_, point<T>& p6_)
            : p1(p1_), p2(p2_), p3(p3_), p4(p4_), p5(p5_), p6(p6_) {};

template<typename T>
int hexagon<T>::get_size() const {
    return 6;
}

template<typename T>
double hexagon<T>::area() {
    point<T> points[6] = {p1, p2, p3, p4, p5, p6};
    return polygon_area(points, 6);
}

template<typename T>
point<double> hexagon<T>::center() {
    point<T> points[6] = {p1, p2, p3, p4, p5, p6};
    return polygon_center(points, 6);
}

template<typename T>
void hexagon<T>::write(std::ostream& os) const {
    os << "hexagon "<< p1 << " " << p2 << " " << p3 << " " << p4 << " " << p5 << " " << p6;
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

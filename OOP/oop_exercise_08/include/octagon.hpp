#ifndef T_OCTAGON_HPP
#define T_OCTAGON_HPP

#include "point.hpp"
#include "figure.hpp"

template<typename T>
class octagon : public figure {
public:
    octagon() = default;
    octagon(point<T>&, point<T>&, point<T>&, point<T>&, point<T>&, point<T>&, point<T>&, point<T>&);
    int get_size() const override;
    double area() override;
    point<double> center() override;
    void write(std::ostream&) const override;
    void read(std::istream&) override;
private:
    point<T> p1, p2, p3, p4, p5, p6, p7, p8;
};

template<typename T>
octagon<T>::octagon(point<T>& p1_, point<T>& p2_, point<T>& p3_, point<T>& p4_, point<T>& p5_, point<T>& p6_, point<T>& p7_, point<T>& p8_)
            : p1(p1_), p2(p2_), p3(p3_), p4(p4_), p5(p5_), p6(p6_), p7(p7_), p8(p8_) {};

template<typename T>
int octagon<T>::get_size() const {
    return 8;
}

template<typename T>
double octagon<T>::area() {
    point<T> points[8] = {p1, p2, p3, p4, p5, p6, p7, p8};
    return polygon_area(points, 8);
}

template<typename T>
point<double> octagon<T>::center() {
    point<T> points[8] = {p1, p2, p3, p4, p5, p6, p7, p8};
    return polygon_center(points, 8);
}

template<typename T>
void octagon<T>::write(std::ostream& os) const {
    os << "octagon " << p1 << " " << p2 << " " << p3 << " " << p4 << " " << p5 << " " << p6 << " " << p7 << " " << p8;
}

template<typename T>
void octagon<T>::read(std::istream& is) {
    point<T> p1_, p2_, p3_, p4_, p5_, p6_, p7_, p8_;
    is >> p1_ >> p2_ >> p3_ >> p4_ >> p5_ >> p6_ >> p7_ >> p8_;
    *this = octagon(p1_, p2_, p3_, p4_, p5_, p6_, p7_, p8_);
}

template<typename T>
std::ostream& operator <<(std::ostream& os, const octagon<T>& oct) {
    oct.write(os);
    return os;
}

template<typename T>
std::istream& operator >>(std::istream& is, octagon<T>& oct) {
    oct.read(is);
    return is;
}

#endif

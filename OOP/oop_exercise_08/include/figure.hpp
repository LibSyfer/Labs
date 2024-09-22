#ifndef T_FIGURE_HPP
#define T_FIGURE_HPP

#include <iostream>
#include "point.hpp"

class figure {
public:
    figure() {};
    virtual ~figure() {};

    virtual int get_size() const = 0;

    virtual void read(std::istream&) = 0;
    virtual void write(std::ostream&) const = 0;

    virtual double area() = 0;
    virtual point<double> center() = 0;
protected:
    template<typename T>
    static double polygon_area(const point<T>*, const int);
    template<typename T>
    static point<double> polygon_center(const point<T>*, const int);
};

template<typename T>
double figure::polygon_area(const point<T>* peaks, const int size) {
    //std::cout << "Size = " << Size << "\n";
    double A = 0.0;
    if(size < 3) {
        return A;
    }
    for(int i = 0; i < size - 1; ++i) {
        A = A + (peaks[i].x * peaks[i + 1].y);
    }
    A = A + (peaks[size-1].x * peaks[0].y);
    for(int i = 0; i < size - 1; ++i) {
        A = A - (peaks[i+1].x * peaks[i].y);
    }
    A = A - (peaks[0].x * peaks[size-1].y);
    return A >= 0 ? (A * 0.5) : (-A * 0.5);
}

template<typename T>
point<double> figure::polygon_center(const point<T>* peaks, const int size) {
    point<double> res;
    double x = 0;
    double y = 0;
    for(int i = 0; i < size; ++i) {
        x = x + peaks[i].x;
        y = y + peaks[i].y;
    }
    res.x = x / size;
    res.y = y / size;
    return res;
}

std::istream& operator >>(std::istream& is, figure& f) {
    f.read(is);
    return is;
}
std::ostream& operator <<(std::ostream& os, figure& f) {
    f.write(os);
    return os;
}

#endif

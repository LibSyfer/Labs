#ifndef D_TRAPEZOID_H_
#define D_TRAPEZOID_H_

#include <iostream>
#include <assert.h>
#include "vertex.h"

template<class T>
struct Trapezoid {
    Trapezoid(std::istream &is);
    int IsCorrect() const;

    vertex<double> Center() const;
    void Print() const;
    double Area() const;

private:
    vertex<T> one,two,three,four;
};

template<class T>
Trapezoid<T>::Trapezoid(std::istream &is){
    is >> one >> two >> three >> four;
    assert(IsCorrect());
}

template<class T>
int Trapezoid<T>::IsCorrect() const {
    T vec1_x = four.x - one.x;
    T vec1_y = four.y - one.y;

    T vec2_x = three.x - two.x;
    T vec2_y = three.y - two.y;

    T vec3_x = two.x - one.x;
    T vec3_y = two.y - one.y;

    T vec4_x = three.x - four.x;
    T vec4_y = three.y - four.y;
    
    if ((vec1_x / vec2_x == vec1_y / vec2_y) || (vec3_x / vec4_x == vec3_y / vec4_y) || //отношение соответствующих координат
            (vec1_x == 0 && vec2_x == 0) || (vec1_y == 0 && vec2_y == 0) || (vec3_x == 0 && vec4_x == 0) || (vec3_y == 0 && vec4_y == 0)) {
        return 1;
    }
    return 0;
}

template<class T>
vertex<double> Trapezoid<T>::Center() const {
    vertex<double> center;

    center = one + two + three + four;
    center /= 4;
    
    return center;
}

template<class T>
void Trapezoid<T>::Print() const {
    std::cout << one << " " << two << " " << three << " " << four << '\n';
}

template<class T>
double Trapezoid<T>::Area() const {

    const T area1 = 0.5 * abs((three.x - two.x) * (four.y - two.y) - (four.x - two.x) * (three.y - two.y));
    const T area2 = 0.5 * abs((one.x - two.x) * (four.y - two.y) - (four.x - two.x) * (one.y - two.y));
    
    return area1 + area2;
}

#endif
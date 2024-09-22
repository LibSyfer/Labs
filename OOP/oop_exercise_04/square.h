#ifndef D_SQUARE_H_
#define D_SQUARE_H_

#include <iostream>
#include <assert.h>
#include <math.h>

#include "vertex.h"

template<class T>
struct Square {
    Square(std::istream &is);
    int IsCorrect() const;

    vertex<double> Center() const;
    void Print() const;
    double Area() const;

private:
    vertex<T> one,two,three,four;
};

template<class T>
Square<T>::Square(std::istream &is){
    is >> one >> two >> three >> four;
    assert(IsCorrect());
}

template<class T>
int Square<T>::IsCorrect() const {
    const T vec1_x = two.x - one.x;
    const T vec1_y = two.y - one.y;

    const T vec2_x = three.x - two.x;
    const T vec2_y = three.y - two.y;

    const T vec3_x = four.x - one.x;
    const T vec3_y = four.y - one.y;

    const T vec4_x = four.x - three.x;
    const T vec4_y = four.y - three.y;

    const T dotProduct1 = vec1_x * vec2_x + vec1_y * vec2_y;
    const T dotProduct2 = vec3_x * vec1_x + vec3_y * vec1_y;
    const T dotProduct3 = vec3_x * vec4_x + vec3_y * vec4_y;

    const T vec1_length = sqrt(vec1_x * vec1_x + vec1_y * vec1_y);
    const T vec2_length = sqrt(vec2_x * vec2_x + vec2_y * vec2_y);

    if (dotProduct1 == 0 && dotProduct2 == 0 && dotProduct3 == 0 && vec1_length == vec2_length) {
        return 1;
    }
    return 0;
}

template<class T>
vertex<double> Square<T>::Center() const {
    vertex<double> center;
    center.x = (one.x + three.x) / 2;
    center.y = (one.y + three.y) / 2;
    return center;
}

template<class T>
void Square<T>::Print() const {
    std::cout << one << " " << two << " " << three << " " << four << '\n';
}

template<class T>
double Square<T>::Area() const {
    const T vecX = two.x - one.x;
    const T vecY = two.y - one.y;

    return vecX * vecX + vecY * vecY;
}

#endif
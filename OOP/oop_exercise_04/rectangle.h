#ifndef D_RECTANGLE_H_
#define D_RECTANGLE_H_

#include <iostream>
#include <assert.h>
#include <math.h>

#include "vertex.h"

template<class T>
struct Rectangle {
    Rectangle(std::istream &is);
    int IsCorrect() const;

    vertex<double> Center() const;
    void Print() const;
    double Area() const;

private:
    vertex<T> one,two,three,four;
};

template<class T>
Rectangle<T>::Rectangle(std::istream &is){
    is >> one >> two >> three >> four;
    assert(IsCorrect());
}

template<class T>
int Rectangle<T>::IsCorrect() const {
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

    if (dotProduct1 == 0 && dotProduct2 == 0 && dotProduct3 == 0) {
        return 1;
    }
    return 0;
}

template<class T>
vertex<double> Rectangle<T>::Center() const {
    vertex<double> center;
    center.x = (one.x + three.x) / 2;
    center.y = (one.y + three.y) / 2;
    return center;
}

template<class T>
void Rectangle<T>::Print() const {
    std::cout << one << " " << two << " " << three << " " << four << '\n';
}

template<class T>
double Rectangle<T>::Area() const {
    const T xHeight = two.x - one.x;
    const T yHeight = two.y - one.y;

    const T xWidth = three.x - two.x;
    const T yWidth = three.y - two.y;

    return sqrt(xHeight * xHeight + yHeight * yHeight) * sqrt(xWidth * xWidth + yWidth * yWidth);
}

#endif
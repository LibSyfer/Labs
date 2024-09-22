#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <iostream>
#include "Figure.hpp"

class Triangle : public Figure {
private:
    Point Peaks[3];
    const int Size = 3;
public:
    Triangle() {};
    ~Triangle() {};

    int GetSize() const override;

    void ReadFigure(std::istream&) override;
    void WriteFigure(std::ostream&) const override;

    double FigureArea() override;
    virtual Point GeomCenter() override;
};

std::istream& operator >>(std::istream&, Triangle&);
std::ostream& operator <<(std::ostream&, Triangle&);

#endif

#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include <iostream>
#include "Figure.hpp"

class Hexagon : public Figure {
private:
    Point Peaks[6];
    const int Size = 6;
public:
    Hexagon() {};
    ~Hexagon() {};

    int GetSize() const override;

    void ReadFigure(std::istream&) override;
    void WriteFigure(std::ostream&) const override;

    double FigureArea() override;
    virtual Point GeomCenter() override;
};

std::istream& operator >>(std::istream&, Hexagon&);
std::ostream& operator <<(std::ostream&, Hexagon&);

#endif

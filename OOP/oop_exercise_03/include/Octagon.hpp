#ifndef OCTAGON_HPP
#define OCTAGON_HPP

#include <iostream>
#include "Figure.hpp"

class Octagon : public Figure {
private:
    Point Peaks[8];
    const int Size = 8;
public:
    Octagon() {};
    ~Octagon() {};

    int GetSize() const override;

    void ReadFigure(std::istream&) override;
    void WriteFigure(std::ostream&) const override;

    double FigureArea() override;
    virtual Point GeomCenter() override;
};

std::istream& operator >>(std::istream&, Octagon&);
std::ostream& operator <<(std::ostream&, Octagon&);

#endif

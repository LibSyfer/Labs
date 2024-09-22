#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <iostream>

struct Point {
    double X;
    double Y;
};
std::istream& operator >>(std::istream&, Point&);
std::ostream& operator <<(std::ostream&, Point&);

class Figure {
public:
    Figure() {};
    ~Figure() {};

    virtual int GetSize() const = 0;

    virtual void ReadFigure(std::istream&) = 0;
    virtual void WriteFigure(std::ostream&) const = 0;

    virtual double FigureArea() = 0;
    virtual Point GeomCenter() = 0;
protected:
    static double PolygonArea(const Point*, const int);
    static Point PolygonCenter(const Point*, const int);
};

std::istream& operator >>(std::istream&, Figure&);
std::ostream& operator <<(std::ostream&, Figure&);

#endif

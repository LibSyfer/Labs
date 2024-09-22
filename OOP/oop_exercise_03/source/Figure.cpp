#include "../include/Figure.hpp"

std::istream& operator >>(std::istream& is, Point& p) {
    is >> p.X >> p.Y;
    return is;
}
std::ostream& operator <<(std::ostream& os, Point& p) {
    os << "(" << p.X << ", " << p.Y << ")";
    return os;
}

double Figure::PolygonArea(const Point* Peaks, const int Size) {
    //std::cout << "Size = " << Size << "\n";
    double A = 0.0;
    if(Size < 3) {
        return A;
    }
    for(int i = 0; i < Size - 1; ++i) {
        A = A + (Peaks[i].X * Peaks[i + 1].Y);
    }
    A = A + (Peaks[Size-1].X * Peaks[0].Y);
    for(int i = 0; i < Size - 1; ++i) {
        A = A - (Peaks[i+1].X * Peaks[i].Y);
    }
    A = A - (Peaks[0].X * Peaks[Size-1].Y);
    return A >= 0 ? (A * 0.5) : (-A * 0.5);
}
Point Figure::PolygonCenter(const Point* Peaks, const int Size) {
    Point res;
    double x = 0;
    double y = 0;
    for(int i = 0; i < Size; ++i) {
        x = x + Peaks[i].X;
        y = y + Peaks[i].Y;
    }
    res.X = x / Size;
    res.Y = y / Size;
    return res;
}

std::istream& operator >>(std::istream& is, Figure& f) {
    f.ReadFigure(is);
    return is;
}
std::ostream& operator <<(std::ostream& os, Figure& f) {
    f.WriteFigure(os);
    return os;
}

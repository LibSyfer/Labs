#include "../include/Triangle.hpp"

int Triangle::GetSize() const {
    return Size;
}

void Triangle::ReadFigure(std::istream& is) {
    for(int i = 0; i < Size; ++i) {
        is >> Peaks[i].X;
        is >> Peaks[i].Y;
    }
}
void Triangle::WriteFigure(std::ostream& os) const {
    for(int i = 0; i < Size; ++i) {
        os << "(" << Peaks[i].X << ", " << Peaks[i].Y << ")";
    }
}

double Triangle::FigureArea() {
    return PolygonArea(Peaks, Size);
}
Point Triangle::GeomCenter() {
    return PolygonCenter(Peaks, Size);
}

std::istream& operator >>(std::istream& is, Triangle& t) {
    t.ReadFigure(is);
    return is;
}
std::ostream& operator <<(std::ostream& os, Triangle& t) {
    t.WriteFigure(os);
    return os;
}

#include "../include/Hexagon.hpp"

int Hexagon::GetSize() const {
    return Size;
}

void Hexagon::ReadFigure(std::istream& is) {
    for(int i = 0; i < Size; ++i) {
        is >> Peaks[i].X;
        is >> Peaks[i].Y;
    }
}
void Hexagon::WriteFigure(std::ostream& os) const {
    for(int i = 0; i < Size; ++i) {
        os << "(" << Peaks[i].X << ", " << Peaks[i].Y << ")";
    }
}

double Hexagon::FigureArea() {
    return PolygonArea(Peaks, Size);
}
Point Hexagon::GeomCenter() {
    return PolygonCenter(Peaks, Size);
}

std::istream& operator >>(std::istream& is, Hexagon& x) {
    x.ReadFigure(is);
    return is;
}
std::ostream& operator <<(std::ostream& os, Hexagon& x) {
    x.WriteFigure(os);
    return os;
}

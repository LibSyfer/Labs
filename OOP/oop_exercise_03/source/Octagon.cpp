#include "../include/Octagon.hpp"

int Octagon::GetSize() const {
    return Size;
}

void Octagon::ReadFigure(std::istream& is) {
    for(int i = 0; i < Size; ++i) {
        is >> Peaks[i].X;
        is >> Peaks[i].Y;
    }
}
void Octagon::WriteFigure(std::ostream& os) const {
    for(int i = 0; i < Size; ++i) {
        os << "(" << Peaks[i].X << ", " << Peaks[i].Y << ")";
    }
}

double Octagon::FigureArea() {
    return PolygonArea(Peaks, Size);
}
Point Octagon::GeomCenter() {
    return PolygonCenter(Peaks, Size);
}

std::istream& operator >>(std::istream& is, Octagon& oc) {
    oc.ReadFigure(is);
    return is;
}
std::ostream& operator <<(std::ostream& os, Octagon& oc) {
    oc.WriteFigure(os);
    return os;
}

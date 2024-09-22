#include "../include/main.hpp"

int main(int argc, char* argv[]) {
    Hexagon hex;
    Octagon oct;
    Triangle tri;
    Point p;

    Figure* fig;
    std::vector<Figure*> v;
    int key = 0;
    char buff[50];

    while(key < 5 && key >= 0) {
        std::cout << "============================\n";
        std::cout << "1)Add\n2)Functions\n3)Remove\n4)Test\n5)Exit\n";
        std::cout << "----------------------------\n";
        std::cin >> key;
        if(key == 1) {
            std::cout << "----------------------------\n";
            std::cout << "1)Hexagon\n2)Octagon\n3)Triangle\n";
            std::cout << "----------------------------\n";
            std::cin >> key;
            if(key == 1) {
                fig = new Hexagon;
            } else if(key == 2) {
                fig = new Octagon;
            } else if(key == 3) {
                fig = new Triangle;
            } else {
                continue;
            }
            std::cin >> *fig;
            v.push_back(fig);
        } else if(key == 2) {
            if(v.size() == 0) {
                std::cout << "----------------------------\n";
                std::cout << "Empty vector.\n";
            }
            for(int i = 0; i < v.size(); ++i) {
                p = v[i]->GeomCenter();
                std::cout << "----------------------------\n";
                std::cout << "Фигура: " << *(v[i]) << "\n";
                std::cout << "Геометрический центр: " << p << "\n";
                std::cout << "Площадь: " << v[i]->FigureArea() << "\n";
            }
        } else if(key == 3) {
            std::cout << "----------------------------\n";
            std::cout << "Index: ";
            std::cin >> key;
            if(key >= 0 && key < v.size()) {
                delete v[key];
                v.erase(v.begin() + key);
            }
        } else if(key == 4) {
            std::cin >> buff;
            std::ifstream fin(buff);
            if(!fin.is_open()) {
                continue;
            }
            fin >>  hex;
            fin >> oct;
            fin >> tri;
            std::cout << "----------------------------\n";
            std::cout << "Фигура: " << hex << "\n";
            p = hex.GeomCenter();
            std::cout << "Геометрический центр: " << p << "\n";
            std::cout << "Площать: " << hex.FigureArea() << "\n";
            std::cout << "----------------------------\n";
            std::cout << "Фигура: " << oct << "\n";
            p = oct.GeomCenter();
            std::cout << "Геометрический центр: " << p << "\n";
            std::cout << "Площать: " << oct.FigureArea() << "\n";
            std::cout << "----------------------------\n";
            std::cout << "Фигура: " << tri << "\n";
            p = tri.GeomCenter();
            std::cout << "Геометрический центр: " << p << "\n";
            std::cout << "Площать: " << tri.FigureArea() << "\n";

            fin.close();
        } else if(key == 5) {
            break;
        }
    }
    for(int i = 0; i < v.size(); ++i) {
        delete v[i];
    }
    return 0;
}

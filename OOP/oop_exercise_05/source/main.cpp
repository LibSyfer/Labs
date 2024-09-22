#include <iostream>
#include <string>
#include <algorithm>

#include "../include/hexagon.hpp"
#include "../include/stack.hpp"

int main() {
    std::string command;
    cont::stack<hexagon<int>> figures;
    while(std::cin >> command) {
        if (command == "menu") {
            std::cout << "1) add\n";
            std::cout << "2) erase\n";
            std::cout << "3) size\n";
            std::cout << "4) print\n";
            std::cout << "5) count\n";
            std::cout << "6) exit\n";
        } else if (command == "help") {
            std::cout << "1) add - add a figure by index\n \t example: add 0 1 1 1 1 1 1 1 1 1 1 1 1\n    It means: add hexagon {{1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1}} to position 0\n";
            std::cout << "2) erase - erase a figure by index\n\t example: erase 0\n    It means: erase shape from position 0\n";
            std::cout << "3) size - print size of stack\n";
            std::cout << "4) print - print all shapes in a stack and their area\n";
            std::cout << "5) count - print the number of figures with a given area\n";
        } else if (command == "add") {
            size_t position;
            std::cin >> position;
            auto it = figures.begin();
            try {
                it = std::next(it, position);
            } catch(std::exception& ex) {
                std::cout << "Position is too big\n";
                continue;
            }
            hexagon<int> new_figure;
            try {
                std::cin >> new_figure;
            } catch(std::exception& ex) {
                std::cout << ex.what() << "\n";
            }
            figures.insert(it, new_figure);
            std::cout << new_figure << "\n";
        } else if (command == "erase") {
            size_t index;
            std::cin >> index;
            auto it = figures.begin();
            try {
                it = std::next(it, index);
                figures.erase(it);
            } catch(...) {
                std::cout << "Index is too big\n";
                continue;
            }
        } else if (command == "size") {
            std::cout << figures.size() << "\n";
        } else if (command == "print") {
            std::for_each(figures.begin(), figures.end(), [](const hexagon<int>& fig) {
                std::cout << fig << "\n";
                std::cout << "Center: " << fig.center() << "\n";
                std::cout << "Area: " << fig.area() << "\n";
            });
        } else if (command == "count") {
            size_t required_area;
            std::cin >> required_area;
            std::cout << std::count_if(figures.begin(), figures.end(), [&required_area] (const hexagon<int>& fig) {
                return fig.area() < required_area;
            });
            std::cout << "\n";
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Incorrect command\n";
            std::cin.ignore(32767, '\n');
        }
    }
    return 0;
}

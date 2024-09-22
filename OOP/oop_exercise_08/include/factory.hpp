#ifndef T_FACTORY_HPP
#define T_FACTORY_HPP

#include <iostream>
#include <string>

#include "figure.hpp"
#include "hexagon.hpp"
#include "octagon.hpp"
#include "triangle.hpp"

class factory {
public:
    factory() {};
    ~factory() {};
    figure* build(std::istream& is) const {
        figure* fig = nullptr;
        std::string command;
        is >> command;
        while(command != "1" && command != "hexagon" &&
              command != "2" && command != "octagon" &&
              command != "3" && command != "triangle" &&
              command != "4" && command != "exit") {
            std::cout << "1) hexagon\n";
            std::cout << "2) octagon\n";
            std::cout << "3) triangle\n";
            is >> command;
        }
        if(command == "1" || command == "hexagon") {
            fig = new hexagon<int>;
        } else if(command == "2" || command == "octagon") {
            fig = new octagon<int>;
        } else if(command == "3" || command == "triangle") {
            fig = new triangle<int>;
        } else {
            return fig;
        }
        is >> *fig;
        return fig;
    }
};

#endif

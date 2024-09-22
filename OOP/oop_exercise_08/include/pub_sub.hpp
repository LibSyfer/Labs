#ifndef T_PUB_SUB_HPP
#define T_PUB_SUB_HPP

#include <iostream>
#include <fstream>

#include "stack.hpp"
#include "figure.hpp"

namespace PubSub {
    class observer {
    public:
        virtual ~observer() = default;
        virtual void handle_event(cont::stack<figure*>&) = 0;
    };
    class writer_observer : public observer {
    public:
        writer_observer() {}
        ~writer_observer() {}
        void handle_event(cont::stack<figure*>& figures) override {
            for(auto fig : figures) {
                std::cout << *fig << " ";
            }
            std::cout << "\n";
        }
    };
    class file_observer : public observer {
    public:
        file_observer() {}
        ~file_observer() {}

        void handle_event(cont::stack<figure*>& figures) override {
            static int iterations = 0;
            std::string file_name("../fig/figure_stack_");
            std::string ending = std::to_string(iterations);
            file_name += ending;
            file_name += ".txt";
            std::fstream fin(file_name, std::ios_base::out);
            if(!fin.is_open()) {
                return;
            }
            for(auto fig : figures) {
                fin << *fig << " ";
            }
            fin << "\n";
            fin.close();
            ++iterations;
        }
    };
}

#endif

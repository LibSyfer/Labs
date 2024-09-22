#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>

#include "include/pub_sub.hpp"
#include "include/stack.hpp"

#include "include/factory.hpp"

#include "include/figure.hpp"
#include "include/hexagon.hpp"
#include "include/octagon.hpp"
#include "include/triangle.hpp"


void handle(cont::stack<figure*>& figures, int buff_length, std::condition_variable& cv_mtx1, std::condition_variable& cv_mtx2, std::mutex& mtx, bool& stop_thrd) {
    std::unique_lock<std::mutex> lock(mtx);
    cv_mtx2.notify_all();

    cont::stack<PubSub::observer*> observers;

    observers.push(new PubSub::writer_observer());
    observers.push(new PubSub::file_observer());
    while(!(stop_thrd)) {
        cv_mtx1.wait(lock);
        if(figures.size() != 0) {
            for(auto i : observers) {
                i->handle_event(figures);
            }
        }
        while(figures.size() != 0) {
            delete figures.top();
            figures.pop();
        }
        cv_mtx2.notify_all();
    }
    for(auto i : observers) {
        delete i;
    }
    return;
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        return 1;
    }

    factory fact;

    cont::stack<figure*> figures;
    int buff_length = std::stoi(argv[1]);

    std::string command;
    std::string action;

    std::condition_variable cv_mtx1;
    std::condition_variable cv_mtx2;
    std::mutex mtx;
    bool stop_thrd = false;

    std::unique_lock<std::mutex> lock(mtx);

    std::thread handler(handle, std::ref(figures), buff_length, std::ref(cv_mtx1), std::ref(cv_mtx2), std::ref(mtx), std::ref(stop_thrd));
    cv_mtx2.wait(lock);
    
    while(std::cin >> action) {
        while(action != "add" && action != "1" && action != "exit" && action != "2") {
            if(action == "help") {
                std::cout << "1) add\n";
                std::cout << "2) exit\n";
            } else {
                std::cout << "Unknown command. Type help\n";
            }
            std::cin >> action;
        }
        if(action == "add"  || action == "1") {
            while(figures.size() != buff_length) {
                figure* fig = fact.build(std::cin);
                if(fig != nullptr) {
                    figures.push(fig);
                }
            }
            cv_mtx1.notify_all();
            cv_mtx2.wait(lock);
        } else {
            break;
        }
    }
    stop_thrd = true;
    cv_mtx1.notify_all();
    lock.unlock();
    handler.join();
    // for(auto i : figures) {
    //     delete i;
    // }
    return 0;
}

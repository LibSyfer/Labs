#include <iostream>
#include <string>

#include "include/document_new.hpp"

int main(int argc, char* argv[]) {
    editor::document doc;
    std::string command;
    while(std::cin >> command) {
        if(command == "help") {
            std::cout << "1) create\n";
            std::cout << "2) delete\n";
            std::cout << "3) load\n";
            std::cout << "4) save\n";
            std::cout << "5) print\n";
            std::cout << "6) undo\n";
            std::cout << "7) exit\n";
        } else if(command == "create" || command == "1") {
            doc.create_doc(std::cin, std::cout);
        } else if(command == "delete" || command == "2") {
            doc.delete_doc(std::cin, std::cout);
        } else if(command == "load" || command == "3") {
            doc.load_doc(std::cin, std::cout);
        } else if(command == "save" || command == "4") {
            doc.save_doc(std::cin, std::cout);
        } else if(command == "print" || command == "5") {
            doc.print_doc(std::cout);
        } else if(command == "undo" || command == "6") {
            doc.undo();
        } else if(command == "exit" || command == "7") {
            break;
        } else {
            std::cout << "Unknown command\n";
        }
    }
    return 0;
}

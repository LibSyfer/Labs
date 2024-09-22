#ifndef T_DOCUMENT_HPP
#define T_DOCUMENT_HPP

#include <iostream>
#include <fstream>

#include <string>

#include "stack.hpp"

#include "factory.hpp"
#include "figure.hpp"

#include "hexagon.hpp"
#include "octagon.hpp"
#include "triangle.hpp"

namespace editor {
    class operation {
    public:
        virtual ~operation() {}
        virtual void undo(figure**) {}
    };
    class operation_load : public operation {
    public:
        operation_load() {
            fig = nullptr;
        }
        ~operation_load() {
            if(fig != nullptr) {
                delete fig;
            }
        }
        void undo(figure** current_figure) override {
            delete *current_figure;
            *current_figure = fig;
            fig = nullptr;
        }
        void set_figure(figure* f) {
            if(fig == nullptr) {
                fig = f;
            }
        }
    private:
        figure* fig;
    };
    class operation_save : public operation {
    public:
        operation_save() {}
        ~operation_save() {}
        void undo(figure** current_figure) override {
            remove(file_name.c_str());
        }
        void set_filename(const std::string& f_name) {
            file_name = f_name;
        }
    private:
        std::string file_name;
    };
    class operation_create : public operation {
    public:
        operation_create() {
            fig = nullptr;
        }
        ~operation_create() {
            if(fig != nullptr) {
                delete fig;
            }
        }
        void undo(figure** current_figure) override {
            delete *current_figure;
            *current_figure = fig;
            fig = nullptr;
        }
        void set_figure(figure* f) {
            if(fig == nullptr) {
                fig = f;
            }
        }
    private:
        figure* fig;
    };
    class operation_delete : public operation {
    public:
        operation_delete() {
            fig = nullptr;
        }
        ~operation_delete() {
            if(fig != nullptr) {
                delete fig;
            }
        }
        void undo(figure** current_figure) override {
            *current_figure = fig;
            fig = nullptr;
        }
        void set_figure(figure* f) {
            if(fig == nullptr) {
                fig = f;
            }
        }
    private:
        figure* fig;
    };

    class document {
    public:
        document() {
            current_figure = nullptr;
        };
        ~document() {
            if(operations.size() != 0) {
                for(auto elem : operations) {
                    delete elem;
                }
            }
            if(current_figure != nullptr) {
                delete current_figure;
            }
        }
        void load_doc(const std::string& file_name) {
            factory fact;
            operation_load* oper_load = new operation_load();

            if(current_figure != nullptr) {
                oper_load->set_figure(current_figure);
            }
            std::fstream fin(file_name, std::ios_base::binary | std::ios_base::in);
            if(!fin.is_open()) {
                std::cout << "Error opening file\n";
                delete oper_load;
                return;
            }
            current_figure = fact.build(fin);
            operations.push(oper_load);
            fin.close();
        }
        void save_doc(const std::string& file_name) {
            operation_save* oper_save = new operation_save();
            oper_save->set_filename(file_name);

            std::fstream fout(file_name, std::ios_base::binary | std::ios_base::out);
            if(!fout.is_open()) {
                std::cout << "Error opening file\n";
                delete oper_save;
                return;
            }
            operations.push(oper_save);
            fout << *current_figure << "\n";
            fout.close();
            // нужно добавить удаление файла из директории
        }
        void create_doc() {
            factory fact;
            operation_create* oper_create = new operation_create();

            if(current_figure != nullptr) {
                oper_create->set_figure(current_figure);
            }
            current_figure = fact.build(std::cin);
            operations.push(oper_create);
        }
        void delete_doc() {
            operation_delete* oper_delete = new operation_delete();

            if(current_figure != nullptr) {
                oper_delete->set_figure(current_figure);
                current_figure = nullptr;
            }
            operations.push(oper_delete);
        }
        void print_doc(std::ostream& out) {
            if(current_figure != nullptr) {
                out << *current_figure << "\n";
            }
        }
        void undo() {
            if(operations.size() != 0) {
                operation* op = operations.top();
                operations.pop();
                op->undo(&current_figure);
                delete op;
            }
        }
    private:
        cont::stack<operation*> operations;
        figure* current_figure;
    };
}

#endif

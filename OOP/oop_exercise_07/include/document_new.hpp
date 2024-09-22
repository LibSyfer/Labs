#ifndef T_DOCUMENT_HPP
#define T_DOCUMENT_HPP

#include <iostream>
#include <fstream>

#include <string>
#include <vector>

#include "stack.hpp"

#include "factory.hpp"
#include "figure.hpp"

#include "hexagon.hpp"
#include "octagon.hpp"
#include "triangle.hpp"

namespace editor {
struct document {
public:
    class operation {
    public:
        virtual ~operation() {}
        virtual void undo(std::vector<figure*>&) {}
        virtual void undo_inf() {}
    protected:
        std::vector<figure*> fig_buff;
    };
    class operation_load : public operation {
    public:
        operation_load(std::vector<figure*>& _figures) {
            figures_buff.reserve(_figures.size());
            for(auto i : _figures) {
                figures_buff.push_back(i);
            }
        }
        ~operation_load() {
            if(!figures_buff.empty()) {
                for(auto i : figures_buff) {
                    delete i;
                }
                figures_buff.clear();
            }
        }
        void undo(std::vector<figure*>& f) override {
            for(auto i : f) {
                delete i;
            }
            f.clear();
            f.reserve(figures_buff.size());
            for(auto i : figures_buff) {
                f.push_back(i);
            }
            figures_buff.clear();
        }
        void undo_inf() {
            std::cout << "[undo] operation_load\n";
        }
    private:
        std::vector<figure*> figures_buff;
    };
    class operation_save : public operation {
    public:
        operation_save(std::string& _file_name) {
            file_name = _file_name;
        }
        ~operation_save() {}
        void undo(std::vector<figure*>& f) override {
            remove(file_name.c_str());
        }
        void undo_inf() {
            std::cout << "[undo] operation_save\n";
        }
    private:
        std::string file_name;
    };
    class operation_create : public operation {
    public:
        operation_create() {}
        ~operation_create() {}
        void undo(std::vector<figure*>& f) override {
            delete f.back();
            f.pop_back();
        }
        void undo_inf() {
            std::cout << "[undo] operation_create\n";
        }
    };
    class operation_delete : public operation {
    public:
        operation_delete(size_t _index, figure* _fig) {
            index = _index;
            fig = _fig;
        }
        ~operation_delete() {
            if(fig != nullptr) {
                delete fig;
            }
        }
        void undo(std::vector<figure*>& f) override {
            f.insert(f.begin() + index, fig);
            fig = nullptr;
        }
        void undo_inf() {
            std::cout << "[undo] operation_delete\n";
        }
    private:
        size_t index;
        figure* fig;
    };
public:
    document() {}
    ~document() {
        for(auto i : operations) { // Освобождаем память, выделенную под операции
            delete i;
        }
        for(auto i : figures) { // Освобождаем память, выделенную под фигуры
            delete i;
        }
    }
    void load_doc(std::istream& is, std::ostream& os) {
        factory fact;
        std::string file_name;
        if(!figures.empty()) {
            std::string command;
            os << "Документ не пустой.\n";
            os << "Сохранить в файл?\n";
            is >> command;
            if(command == "Да" || command == "Yes") {
                os << "Имя файла: ";
                is >> file_name;
                std::fstream fin(file_name, std::ios_base::binary | std::ios_base::out);
                if(fin.is_open()) {
                    os << "Сохранение...\n";
                    for(auto i : figures) {
                        fin << *i << "\n";
                    }
                    fin.close();
                } else {
                    os << "Не удалось сохранить файл\n";
                }
            }
        }
        operation_load* oper_load = new operation_load(figures);
        figures.clear();
        os << "Имя файла: ";
        is >> file_name;
        std::fstream fin(file_name, std::ios_base::binary | std::ios_base::in);
        if(fin.is_open()) {
            figure* curr_figure = nullptr;
            while((curr_figure = fact.build(fin)) != nullptr) {
                figures.push_back(curr_figure);
            }
            operations.push_back(oper_load);
            fin.close();
        }
    }
    void save_doc(std::istream& is, std::ostream& os) {
        std::string file_name;
        if(!figures.empty()) {
            os << "Имя файла: ";
            is >> file_name;
            std::fstream fin(file_name, std::ios_base::binary | std::ios_base::out);
            if(fin.is_open()) {
                os << "Сохранение...\n";
                for(auto i : figures) {
                    fin << *i << "\n";
                }
                operation_save* oper_save = new operation_save(file_name);
                operations.push_back(oper_save);
                fin.close();
            }
        }
    }
    void create_doc(std::istream& is, std::ostream& os) {
        factory fact;
        figure* curr_figure;
        if((curr_figure = fact.build(is)) != nullptr) {
            figures.push_back(curr_figure);
            operation_create* oper_create = new operation_create();
            operations.push_back(oper_create);
        }
    }
    void delete_doc(std::istream& is, std::ostream& os) {
        if(!figures.empty()) {
            size_t index = figures.size()-1;
            is >> index;
            if(index < 0 || index >= figures.size()) {
                index = figures.size()-1;
            }
            operation_delete* oper_delete = new operation_delete(index, figures[index]);
            figures.erase(figures.begin() + index);
            operations.push_back(oper_delete);
        }
    }
    void print_doc(std::ostream& os) {
        if(figures.empty()) {
            os << "Нет не одной фигуры\n";
        }
        for(auto i : figures) {
            os << *i << "\n";
        }
    }
    void undo() {
        for(auto i : operations) {
            i->undo_inf();
        }
        if(!operations.empty()) {
            operations.back()->undo(figures);
            delete operations.back();
            operations.pop_back();
        }
    }
private:
    std::vector<operation*> operations;
    std::vector<figure*> figures;
};
}

#endif

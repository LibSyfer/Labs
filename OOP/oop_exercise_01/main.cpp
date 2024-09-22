#include <iostream>
#include <fstream>
#include "bigString.hpp"

void separator();
void meny();
unsigned long long get_num_in_file(std::ifstream& fin);

int main(int argc, char* argv[]) {
    int key;
    int shift;
    unsigned long long n1;
    unsigned long long n2;
    BigString str1;
    BigString str2;

    if (argc > 1) {
        std::ifstream fin(argv[1], std::ios_base::in);
        if (!fin.is_open()) {
            std::cout << "Нельзя отрыть файл!\n";
            return 2;
        }

        n1 = get_num_in_file(fin);
        n2 = get_num_in_file(fin);
        str1.set_lstring(n1);
        str1.set_rstring(n2);

        n1 = get_num_in_file(fin);
        n2 = get_num_in_file(fin);
        str2.set_lstring(n1);
        str2.set_rstring(n2);

        fin.close();
    }
    else {
            std::cin >> n1 >> n2;
            str1.set_lstring(n1);
            str1.set_rstring(n2);

            std::cin >> n1 >> n2;
            str2.set_lstring(n1);
            str2.set_rstring(n2);
    }

    meny();

    std::cin >> key;
    switch(key) {
        case 1:
            std::cout << "shift: ";
            std::cin >> shift;
            str1.print_bits();
            str1.shift_left(shift);
            str1.print_bits();
            break;
        case 2:
            std::cout << "shift: ";
            std::cin >> shift;
            str1.print_bits();
            str1.shift_right(shift);
            str1.print_bits();
            break;
        case 3:
            str1.print_bits();
            str2.print_bits();
            str1.bs_and(str2).print_bits();
            break;
        case 4:
            str1.print_bits();
            str2.print_bits();
            str1.bs_or(str2).print_bits();
            break;
        case 5:
            str1.print_bits();
            str2.print_bits();
            str1.bs_xor(str2).print_bits();
            break;
        case 6:
            str1.print_bits();
            str1.bs_not().print_bits();
            break;
        case 7:
            str1.print_bits();
            str2.print_bits();
            std::cout << "num_of_units :" << str1.num_of_units() <<std::endl;
            std::cout << "num_of_units :" << str2.num_of_units() <<std::endl;
            break;
        case 8:
            str1.print_bits();
            str2.print_bits();
            std::cout << "comparison \n";
            str1.comparison(str2)->print_bits();
            break;
        case 9:
            str1.print_bits();
            str2.print_bits();
            if (str1.is_include(str2)) {
                std::cout << "Yes\n";
            }
            else {
                std::cout << "No\n";
            }
            break;
        default:
            std::cout << "error" << std::endl;
            break;
    }
    return 0;
}

void separator() {
    std::cout <<"==============";
    for(int i = 0; i < 128; ++i) {
        std::cout << "=";
    }
    std::cout << std::endl;
}

void meny() {
    std::cout << "1)shiftLeft" << std::endl;
    std::cout << "2)shiftLeft" << std::endl;
    std::cout << "3)AND" << std::endl;
    std::cout << "4)OR" << std::endl;
    std::cout << "5)XOR" << std::endl;
    std::cout << "6)NOT" << std::endl;
    std::cout << "7)num_of_units" << std::endl;
    std::cout << "8)comparison" << std::endl;
    std::cout << "9)is_include" << std::endl;

}

unsigned long long get_num_in_file(std::ifstream& fin) {
    unsigned long long num = 0;
    char ch;
    while(fin.get(ch)) {
        if (ch != ' ' && ch != '\n' && ch != EOF) {
            num = num * 10 + (ch - '0');
        }
        else {
            break;
        }
    }
    return num;
}

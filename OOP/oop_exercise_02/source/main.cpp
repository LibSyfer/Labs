#include <iostream>
#include <fstream>
#include "../includes/bigString.hpp"

void separator();
void meny();
unsigned long long get_num_in_file(std::ifstream& fin);

int main(int argc, char* argv[]) {
    BigString str1;
    BigString str2;
    int key;
    std::cout << "Ввод:\n\t1)Консоль\n\t2)Файл\n";
    std::cin >> key;
    std::cout << "========================================\n";
    if(key == 1) {
        std::cout << "Первая строка: ";
        str1.ReadBS(std::cin);
        std::cout << "Вторая строка: ";
        str2.ReadBS(std::cin);
    } else if(key == 2) {
        if(argc < 2) {
            std::cout << "Не указан файл!\n";
            return 1;
        }
        std::ifstream fin(argv[1]);
        if(!fin.is_open()) {
            std::cout << "Не удалось отрыть файл!\n";
            return 2;
        }
        str1.ReadBS(fin);
        str2.ReadBS(fin);
        fin.close();
    } else {
        std::cout << "Стандартное действие\n\t1)---0XF800000000000000\n\t2)---0X1800000000000000\n";
        str1.set_lstring(0XF800000000000000);
        str1.set_rstring(0X1800000000000000);
        str2.set_lstring(0XF800000000000000);
        str2.set_rstring(0X1800000000000000);
    }
    char R = '!';
    int shift = 0;
    std::cout << "========================================\n";
    while(R != EOF) {
        meny();
        std::cout << "========================================\n";
        std::cin >> R;
        if(R == '1') {
            str1.WriteBS(std::cout);
        } else if(R == '2') {
            str2.WriteBS(std::cout);
        } else if(R == '3') {
            std::cin >> shift;
            str1 >> shift;
            str1.WriteBS(std::cout);
            str2 >> shift;
            str2.WriteBS(std::cout);
        } else if(R == '4') {
            str1 << shift;
            str1.WriteBS(std::cout);
            str2 << shift;
            str2.WriteBS(std::cout);
        } else if(R == '5') {
            str1.WriteBS(std::cout);
            str2.WriteBS(std::cout);
            (str1 & str2).WriteBS(std::cout);
        } else if(R == '6') {
            (str1 | str2).WriteBS(std::cout);
        } else if(R == '7') {
            (str1 ^ str2).WriteBS(std::cout);
        } else if(R == '8') {
            (!str1).WriteBS(std::cout);
            (!str2).WriteBS(std::cout);
        } else if(R == '9') {
            std::cout << "str1 :" << str1.num_of_units();
        } else if(R == 'A') {
            (str1.comparison(str2))->WriteBS(std::cout);
        } else if(R == 'B') {
            if(str1.is_include(str2)) {
                std::cout << "str1 включено в str2\n";
            } else {
                std::cout << "str1 не включено в str2\n";
            }
        } else if(R == 'C') {
            if(str1 == str2) {
                std::cout << "Равны\n";
            } else {
                std::cout << "Не равны\n";
            }
        } else if(R == 'D') {
            if(str1 != str2) {
                std::cout << "Не равны\n";
            } else {
                std::cout << "Равны\n";
            }
        } else if(R == 'E') {
            if(str1 > str2) {
                std::cout << "str1 блольше str2\n";
            } else {
                std::cout << "str1 не блольше str2\n";
            }
        } else if(R == 'F') {
            if(str1 < str2) {
                std::cout << "str1 меньше str2\n";
            } else {
                std::cout << "str1 не меньше str2\n";
            }
        } else if(R == 'G') {
            std::cout << "Введите 2 числа:\n";
            std::cin >> str1;
            std::cout << str1 << std::endl;
        } else {
            break;
        }
        std::cout << "========================================\n";
    }
    return 0;
}

void meny() {
    std::cout << "1)Print str1" << std::endl;
    std::cout << "2)Print str2" << std::endl;
    std::cout << "3)shiftLeft" << std::endl;
    std::cout << "4)shiftLeft" << std::endl;
    std::cout << "5)AND" << std::endl;
    std::cout << "6)OR" << std::endl;
    std::cout << "7)XOR" << std::endl;
    std::cout << "8)NOT" << std::endl;
    std::cout << "9)num_of_units" << std::endl;
    std::cout << "A)comparison" << std::endl;
    std::cout << "B)is_include" << std::endl;
    std::cout << "C)==" << std::endl;
    std::cout << "D)!=" << std::endl;
    std::cout << "E)>" << std::endl;
    std::cout << "F)<" << std::endl;
    std::cout << "G) std::cin >> str1 и std:cout << str1" << std::endl;
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

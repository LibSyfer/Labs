#include <iostream>
#include "bigString.hpp"

BigString::BigString():lString(0), rString(0){}

BigString::BigString(unsigned long long n1, unsigned long long n2):lString(n1), rString(n2){}

BigString::~BigString(){}

void BigString::set_lstring(unsigned long long n) {
    this->lString = n;
}

void BigString::set_rstring(unsigned long long n) {
    this->rString = n;
}

unsigned long long BigString::get_lstring() const {
    return this->lString;
}

unsigned long long BigString::get_rstring() const {
    return this->rString;
}

void BigString::print_bits() {
    unsigned long long Mask_firstBit = 0x8000000000000000; // первый бит 1 остальные 0
    unsigned long long num = this->lString;
    for(int i = 0; i < 64; ++i) {
        if (num&Mask_firstBit) {
            std::cout << "1";
        }
        else {
            std::cout << "0";
        }
        num = num << 1;
    }
    num = this->rString;
    for(int i = 0; i < 64; ++i) {
        if (num&Mask_firstBit) {
            std::cout << "1";
        }
        else {
            std::cout << "0";
        }
        num = num << 1;
    }
    std::cout << "\n";
}

void BigString::shift_left(int shift) {
    unsigned long long Mask_firstBit = 0x8000000000000000; // первый бит 1 остальные 0
    int bit;
    for(int i = 0; i < shift; ++i) {
        if(this->rString & Mask_firstBit) {
            bit = 1;
        }
        else {
            bit  = 0;
        }
        this->rString = this->rString << 1;
        this->lString = this->lString << 1;
        this->lString = this->lString | bit;
    }
}

void BigString::shift_right(int shift) {
    unsigned long long Mask_lastBit = 1; // последний бит 1 остальные 0
    int bit;
    for(int i = 0; i < shift; ++i) {
        if (this->lString & Mask_lastBit) {
            bit = 1;
        }
        else {
            bit = 0;
        }
        this->lString = this->lString >> 1;
        this->rString = this->rString >> 1;
        if (bit) {
            this->rString= this->rString | 0x8000000000000000;
        }
    }
}

BigString BigString::bs_and(const BigString& s) {
    BigString res;
    res.set_lstring(this->lString & s.get_lstring());
    res.set_lstring(this->rString & s.get_rstring());
    return res;
}

BigString BigString::bs_or(const BigString& s) {
    BigString res;
    res.set_lstring(this->lString | s.get_lstring());
    res.set_rstring(this->rString | s.get_rstring());
    return res;
}
///

BigString BigString::bs_xor(const BigString& s) {
    BigString res;
    res.set_lstring(this->lString ^ s.get_lstring());
    res.set_rstring(this->rString ^ s.get_rstring());
    return res;
}

BigString BigString::bs_not() {
    BigString res;
    res.set_lstring(~(this->lString));
    res.set_rstring(~(this->rString));
    return res;
}

int BigString::num_of_units() const {
    unsigned long long mask = 0x8000000000000000;
    int counter = 0;
    for(int i = 0; i < 64; ++i) {
        if (this->lString & mask) {
            counter++;
        }
        mask = mask >> 1;
    }
    mask = 0x8000000000000000;
    for(int i = 0; i < 64; ++i) {
        if (this->rString & mask) {
            counter++;
        }
        mask = mask >> 1;
    }
    return counter;
}

BigString* BigString::comparison(BigString& s) {
    int value1 = this->num_of_units();
    int value2 = s.num_of_units();
    if (value1 >= value2) {
        return this;
    }
    else {
        return &s;
    }
}

int BigString::is_include(const BigString& s) const {
    if(((this->lString & s.get_lstring()) == this->get_lstring()) || ((this->rString & s.get_rstring()) == this->get_rstring())) {
        return 1;
    }
    else {
        return 0;
    }
}

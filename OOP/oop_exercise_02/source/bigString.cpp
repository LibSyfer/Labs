#include "../includes/bigString.hpp"

BigString::BigString():lString(0), rString(0){}

BigString::BigString(unsigned long long n1, unsigned long long n2):lString(n1), rString(n2){}

BigString::BigString(const BigString& s) {
    this->lString = s.get_lstring();
    this->rString = s.get_rstring();
    std::cout << "Конструктор копирования\n";
}

BigString::~BigString(){}

void BigString::ReadBS(std::istream& in) {
    in >> this->lString;
    in >> this->rString;
}
void BigString::WriteBS(std::ostream& out) {
    out << "Bits: ";
    for(int i = 0; i < 128; ++i) {
        out << this->get_bit(i);
    }
    out << "\n";
    out << "Первое поле числа: ";
    out << this->lString;
    out << "  ";
    out << "Второе поле поле числа: ";
    out << this->rString;
    out << "\n";
}

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

char BigString::get_bit(int index) const{
    char bit = '0';
    if(index >= 0 && index < 128) {
        unsigned long long mask = 0x8000000000000000; // первый бит 1 остальные 0
        if(index < 64) {
            mask = mask >> index;
            if(this->lString & mask) {
                bit = '1';
            } else {
                bit = '0';
            }
        } else {
            mask = mask >> (index - 64);
            if(this->rString & mask) {
                bit = '1';
            } else {
                bit = '0';
            }
        }
    }
    return bit;
}
void BigString::print_all_bits() const{
    for(int i = 0; i < 128; ++i) {
        std::cout << this->get_bit(i);
    }
    std::cout << "\n";
}

BigString BigString::operator &(const BigString& s) const{
    BigString res;
    res.set_lstring(this->lString & s.get_lstring());
    res.set_rstring(this->rString & s.get_rstring());
    return res;
}
BigString BigString::operator |(const BigString& s) const{
    BigString res;
    res.set_lstring(this->lString | s.get_lstring());
    res.set_rstring(this->rString | s.get_rstring());
    return res;
}
BigString BigString::operator ^(const BigString& s) const{
    BigString res;
    res.set_lstring(this->lString ^ s.get_lstring());
    res.set_rstring(this->rString ^ s.get_rstring());
    return res;
}
BigString BigString::operator !() const{
    BigString res;
    res.set_lstring(~(this->lString));
    res.set_rstring(~(this->rString));
    return res;
}
BigString BigString::operator<<(int shift) const{
    unsigned long long mask = 0x8000000000000000; // первый бит 1 остальные 0
    BigString res = *this;
    int bit;
    for(int i = 0; i < shift; ++i) {
        if(res.rString & mask) {
            bit = 1;
        }
        else {
            bit  = 0;
        }
        res.rString = res.rString << 1;
        res.lString = res.lString << 1;
        res.lString = res.lString | bit;
    }
    return res;
}
BigString BigString::operator>>(int shift) const{
    unsigned long long mask = 1; // последний бит 1 остальные 0
    BigString res = *this;
    int bit;
    for(int i = 0; i < shift; ++i) {
        if (res.lString & mask) {
            bit = 1;
        }
        else {
            bit = 0;
        }
        res.lString = res.lString >> 1;
        res.rString = res.rString >> 1;
        if (bit) {
            res.rString= res.rString | 0x8000000000000000;
        }
    }
    return res;
}
bool BigString::operator ==(const BigString& s) const{
    return this->lString == s.get_lstring() && this->rString == s.get_rstring();
}
bool BigString::operator !=(const BigString& s) const{
    return !(this->lString == s.get_lstring() && this->rString == s.get_rstring());
}
bool BigString::operator >(const BigString& s) const{
    if(this->lString > s.get_lstring()) {
        return true;
    } else if(this->lString == s.get_lstring()) {
        if(this->rString > s.get_rstring()) {
            return true;
        }
    }
    return false;
}
bool BigString::operator <(const BigString& s) const{
    if(this->rString < s.get_rstring()) {
        return true;
    } else if(this->rString == s.get_rstring()) {
        if(this->lString < s.get_lstring()) {
            return true;
        }
    }
    return false;
}
const BigString& BigString::operator =(const BigString& s) {
    this->lString = s.get_lstring();
    this->rString = s.get_rstring();
    return s;
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

bool BigString::is_include(const BigString& s) const {
    if(((this->lString & s.get_lstring()) == this->get_lstring()) || ((this->rString & s.get_rstring()) == this->get_rstring())) {
        return true;
    }
    else {
        return false;
    }
}

std::istream& operator >>(std::istream& is, BigString& s) {
    unsigned long long n = 0;
    is >> n;
    s.set_lstring(n);
    is >> n;
    s.set_rstring(n);
    return is;
}
std::ostream& operator <<(std::ostream& os, const BigString& s) {
    for(int i = 0; i < 128; ++i) {
        os << s.get_bit(i);
    }
    return os;
}

unsigned long long pow_m(int a, int b) {
    unsigned long long res = 0;
    for(int i = 0; i < b; ++i) {
        if(res == 0) {
            res = 1;
        }
        res = res*a;
    }
    return res;
}

BigString operator ""_0XtoBS(const char* str, size_t size) {
    BigString res;
    if(size != 37) {
        std::cout << "не то1\n";
        return res;
    }
    char sym;
    unsigned long long n = 0;
    int k = 15;
    for(int i = 0; i < 37; ++i) {
        std::cout << "k: " << k << std::endl;
        sym = str[i];
        std::cout << i << ") Sym : " << sym << std::endl;
        if((sym >= '0' && sym <= '9')) {
            n = n + (sym - '0') * pow_m(16, k);
            --k;
        } else if(sym == 'A') {
            n = n + 10 * pow_m(16, k);
            --k;
        } else if(sym == 'B') {
            n = n + 11 * pow_m(16, k);
            --k;
        } else if(sym == 'C') {
            n = n + 12 * pow_m(16, k);
            --k;
        } else if(sym == 'D') {
            n = n + 13 * pow_m(16, k);
            --k;
        } else if(sym == 'E') {
            n = n + 14 * pow_m(16, k);
            --k;
        } else if(sym == 'F') {
            n = n + 15 * pow_m(16, k);
            --k;
        } else if(sym == ' ') {
            res.set_lstring(n);
            k = 15;
        } else if(sym == 'X') {
            n = 0;
            k = 15;
        } else {
            res.set_lstring(0);
            res.set_rstring(0);
            return res;
        }
    }
    res.set_rstring(n);
    return res;
}

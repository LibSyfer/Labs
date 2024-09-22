#ifndef BIGSTRING_HPP
#define BIGSTRING_HPP

struct BigString{
    BigString();
    BigString(unsigned long long n1, unsigned long long n2);
    ~BigString();

    void set_lstring(unsigned long long n);
    void set_rstring(unsigned long long n);
    unsigned long long get_lstring() const;
    unsigned long long get_rstring() const;

    void print_bits();

    void shift_left(int shift);
    void shift_right(int shift);

    BigString bs_and(const BigString& s);
    BigString bs_or(const BigString& s);
    BigString bs_xor(const BigString& s);
    BigString bs_not();

    int num_of_units() const;
    BigString* comparison(BigString& s);
    int is_include(const BigString& s) const;

private:
    unsigned long long lString;
    unsigned long long rString;
};

#endif

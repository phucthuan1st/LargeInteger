#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#define ZERO 48

using namespace std;

class LargeInteger
{
private:
    vector<char> digits;

    void cleanup();

public:
    LargeInteger();
    LargeInteger(unsigned long long);
    LargeInteger(const LargeInteger &other);
    LargeInteger(string &);
    LargeInteger(string);

    void parse(string &);
    string to_str();

    int digitNum() { return this->digits.size(); }

    bool isNull() { return this->digits.size() == 0; }

    LargeInteger multiply_pow_10(unsigned long long n);

    friend istream &operator>>(istream &, LargeInteger);
    friend ostream &operator<<(ostream &, LargeInteger);

    friend bool operator<(LargeInteger first, LargeInteger second);
    friend bool operator>(LargeInteger first, LargeInteger second);
    friend bool operator>=(LargeInteger first, LargeInteger second);
    friend bool operator<=(LargeInteger first, LargeInteger second);
    friend bool operator==(LargeInteger first, LargeInteger second);
    friend bool operator!=(LargeInteger first, LargeInteger second);

    friend bool operator<(LargeInteger first, unsigned long long second);
    friend bool operator>(LargeInteger first, unsigned long long second);
    friend bool operator>=(LargeInteger first, unsigned long long second);
    friend bool operator<=(LargeInteger first, unsigned long long second);
    friend bool operator==(LargeInteger first, unsigned long long second);
    friend bool operator!=(LargeInteger first, unsigned long long second);

    friend bool operator<(unsigned long long first, LargeInteger second);
    friend bool operator>(unsigned long long first, LargeInteger second);
    friend bool operator>=(unsigned long long first, LargeInteger second);
    friend bool operator<=(unsigned long long first, LargeInteger second);
    friend bool operator==(unsigned long long first, LargeInteger second);
    friend bool operator!=(unsigned long long first, LargeInteger second);

    LargeInteger &operator=(LargeInteger second);

    friend LargeInteger operator+(LargeInteger first, LargeInteger second);
    friend LargeInteger operator-(LargeInteger first, LargeInteger second);
    friend LargeInteger operator*(LargeInteger first, LargeInteger second);
    friend LargeInteger operator/(LargeInteger dividend, LargeInteger divisor);
    friend LargeInteger operator%(LargeInteger dividend, LargeInteger divisor);

    friend LargeInteger operator+(LargeInteger first, unsigned long long second);
    friend LargeInteger operator-(LargeInteger first, unsigned long long second);
    friend LargeInteger operator*(LargeInteger first, unsigned long long second);
    friend LargeInteger operator/(LargeInteger dividend, unsigned long long second);
    friend LargeInteger operator%(LargeInteger dividend, unsigned long long second);

    friend LargeInteger operator+(unsigned long long first, LargeInteger second);
    friend LargeInteger operator-(unsigned long long first, LargeInteger second);
    friend LargeInteger operator*(unsigned long long first, LargeInteger second);
    friend LargeInteger operator/(unsigned long long dividend, LargeInteger divisor);
    friend LargeInteger operator%(unsigned long long dividend, LargeInteger divisor);
};

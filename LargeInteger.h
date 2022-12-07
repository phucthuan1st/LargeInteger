#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

// order of '0'
#define ZERO 48

#define LONG_LONG_MAX LargeInteger("18446744073709551615")

using namespace std;

class LargeInteger
{
private:
    vector<char> digits;
    void cleanup();

public:
    LargeInteger();
    LargeInteger(long long);
    LargeInteger(const LargeInteger &other);
    LargeInteger(string);
    LargeInteger &operator=(LargeInteger other);

    //---------------------- UTILITIES ----------------------//
    // parse a string to large integer
    void parse(string &);

    // get string representation of your large integer
    string to_str();

    // get number of digit of your number
    int digitNum() { return this->digits.size(); }

    // check if your number is NULL
    bool isNull() { return this->digits.size() == 0; }

    // is Even
    bool isEven() { return (this->digits.at(0) - ZERO) % 2 == 0; }

    // is Negative
    bool isNegative() { return (this->digits.at(this->digits.size() - 1)) == '-'; }

    // multiply your number by 10^n
    LargeInteger multiply_pow_10(unsigned long long n);

    // get abs of the number
    LargeInteger abs();

    // get negative form of the number
    LargeInteger negative();

    //---------------------- INPUT & OUTPUT ----------------------//

    friend istream &operator>>(istream &, LargeInteger &);
    friend ostream &operator<<(ostream &, LargeInteger);

    //---------------------- COMPARISION ----------------------//

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

    //---------------------- ARITHMETIC ----------------------//

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

LargeInteger pow(LargeInteger base, LargeInteger expo);
LargeInteger pow(LargeInteger base, LargeInteger expo, LargeInteger mod);
LargeInteger gcd(LargeInteger a, LargeInteger b);

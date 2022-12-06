#include "LargeInteger.h"

void LargeInteger::cleanup()
{
    while (this->digitNum() > 1 && this->digits[this->digits.size() - 1] == '0')
    {
        this->digits.pop_back();
    }
}

void LargeInteger::parse(string &digits)
{
    this->digits = {};
    for (auto &digit : digits)
    {
        this->digits.push_back(digit);
    }

    reverse(this->digits.begin(), this->digits.end());
}

string LargeInteger::to_str()
{
    string digits;

    vector<char> int_digits = this->digits;

    for (auto &digit : this->digits)
    {
        digits += digit;
    }

    reverse(digits.begin(), digits.end());

    return digits;
}

LargeInteger LargeInteger::multiply_pow_10(unsigned long long n)
{
    for (unsigned int i = 0; i < n; i++)
    {
        this->digits.insert(this->digits.begin(), '0');
    }

    return *this;
}

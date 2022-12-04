#include "LargeInteger.h"

LargeInteger::LargeInteger()
{
    this->digits = {};
}

LargeInteger::LargeInteger(unsigned long long value)
{
    if (value == 0)
    {
        this->digits = {ZERO};
    }
    else
    {
        bool sign = false;

        if (value < 0)
        {
            value = -value;
            sign = true;
        }

        while (value > 0)
        {
            this->digits.push_back(value % 10 + ZERO);
            value = value / 10;
        }

        if (sign == true)
        {
            this->digits.push_back('-');
        }
    }
}

LargeInteger::LargeInteger(string digits)
{
    for (auto &digit : digits)
    {
        this->digits.push_back(digit);
    }

    reverse(this->digits.begin(), this->digits.end());
}

LargeInteger::LargeInteger(string &digits)
{
    for (auto &digit : digits)
    {
        this->digits.push_back(digit);
    }

    reverse(this->digits.begin(), this->digits.end());
}

LargeInteger::LargeInteger(const LargeInteger &other)
{
    this->digits = vector<char>(other.digits);
}

void LargeInteger::cleanup()
{
    while (this->digits[this->digits.size() - 1] == '0' && this->digitNum() > 1)
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

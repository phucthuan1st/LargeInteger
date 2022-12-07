#include "LargeInteger.h"

LargeInteger::LargeInteger()
{
    this->digits = {};
}

LargeInteger::LargeInteger(long long value)
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
    if (digits.at(0) == '-')
    {
        this->digits.push_back(digits.at(0));
        digits.erase(digits.begin());
    }

    for (auto &digit : digits)
    {
        if ((digit >= '0' && digit <= '9'))
            this->digits.push_back(digit);
        else
            throw("Invalid input");
    }

    reverse(this->digits.begin(), this->digits.end());
}

LargeInteger::LargeInteger(const LargeInteger &other)
{
    this->digits = vector<char>(other.digits);
}

LargeInteger &LargeInteger::operator=(LargeInteger other)
{
    this->digits = other.digits;
    return *this;
}
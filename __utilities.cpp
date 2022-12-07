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

// fast gcd using Stein's algorithm
LargeInteger gcd(LargeInteger a, LargeInteger b)
{
    // MARK: Special cases:
    // if the two are null, just null result
    if (a.isNull() || b.isNull())
        return LargeInteger();

    if (a == 0)
        return b;

    if (b == 0)
        return a;
    // MARK: End Special cases!

    // make sure a >=b in all cases
    if (b > a)
        return gcd(b, a);

    LargeInteger zero(0);
    LargeInteger two(2);
    LargeInteger g(1);

    LargeInteger t;

    while (a.isEven() && b.isEven())
    {
        a = a / two;
        b = b / two;
        g = g * two;
    }

    while (a > 0)
    {

        while (a.isEven())
        {
            a = a / two;
        }

        while (b.isEven())
        {
            b = b / two;
        }

        LargeInteger sub = (a > b) ? (a - b) : (b - a);
        t = sub / two;

        if (a >= b)
        {
            a = t;
        }
        else
        {
            b = t;
        }
    }

    g = g * b;

    return g;
}
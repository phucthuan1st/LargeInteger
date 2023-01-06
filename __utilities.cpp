#include "LargeInteger.h"
#include "Randomizer.h"

void LargeInteger::cleanup()
{
    int n = this->digits.size();

    if (n < 2) 
        return;
    
    bool sign = (this->digits[n - 1] == '-');

    if (sign) {
        this->digits.pop_back();
        n = n - 1;
    }

    while(n > 1 && this->digits[n - 1] == ZERO) {
        this->digits.pop_back(),
        n--;
    }

    if (sign) {
        this->digits.push_back('-');
    }
}

void LargeInteger::parse(string &digits)
{
    int n = digits.size();
    this->digits = vector<char>(n, ZERO);
    int end = 0;

    for (int i = n - 1; i >= 1; i--)
    {
        if (isdigit(digits[end]))
            this->digits[end++] = digits[i];
        else 
            throw("Invalid string for int: digit must be a number");
    }

    if (digits[0] == '-' || isdigit(digits[0])) {
        this->digits[end] = digits[0];
    }
    else {
        throw("Invalid string for int: digit must be a number");
    }
    cleanup();
}

string LargeInteger::to_str()
{
    int n = this->digits.size();
    string digits(n, '0');
    int end = 0;

    for (int i = n - 1; i >= 0; i--) {
        digits[i] = this->digits[end++];
    }

    return digits;
}

LargeInteger LargeInteger::abs()
{
    LargeInteger result = *this;
    if (result.isNegative())
    {
        result.digits.pop_back();
    }

    return result;
}

LargeInteger LargeInteger::negative()
{
    LargeInteger result = *this;
    if (!result.isNegative())
    {
        result.digits.push_back('-');
    }

    return result;
}

// fast gcd using Stein's algorithm
LargeInteger gcd(LargeInteger a, LargeInteger b)
{
    // MARK: Special cases:
    // if the two are null, just null result
    if (a.isNull() || b.isNull())
        return LargeInteger();

    if (a == constant::zero)
        return b;

    if (b == constant::zero)
        return a;
    // MARK: End Special cases!

    // make sure a >=b in all cases
    if (b > a)
        return gcd(b, a);

    LargeInteger g(constant::one);

    LargeInteger t;

    while (a.isEven() && b.isEven())
    {
        a = a / 2;
        b = b / 2;
        g = g * constant::two;
    }

    while (a > constant::zero)
    {

        while (a.isEven())
        {
            a = a / 2;
        }

        while (b.isEven())
        {
            b = b / 2;
        }

        LargeInteger sub = (a > b) ? (a - b) : (b - a);
        t = sub / 2;

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

string LargeInteger::binary()
{
    string result;
    LargeInteger clone(*this);

    while (clone != constant::zero)
    {
        if (clone.isEven())
        {
            result.append("0");
        }
        else
        {
            result.append("1");
        }

        clone = clone / 2;
    }

    return result;
}
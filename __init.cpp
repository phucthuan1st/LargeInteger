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
        string digits = to_string(value);
        int n = digits.length();
        this->digits = vector<char>(n, ZERO);
        int end = 0;

        for (int i = n - 1; i >= 0; i--)
        {
            this->digits[end++] = digits[i];
        }
    }
}

LargeInteger::LargeInteger(string digits)
{
    int n = digits.size();
    this->digits = vector<char>(n, ZERO);
    int end = 0;

    for (int i = n - 1; i >= 1; i--)
    {
        if (isdigit(digits[i]))
            this->digits[end++] = digits[i];
        else 
            throw("Invalid string for int: digit must be a number");
    }

    if (digits[0] == '-' || isdigit(digits[0])) {
        this->digits[end] = digits[0];
    }
    else {
        cout << "DEBUG: Your string is: " << digits << endl;
        throw("Invalid string for int: digit must be a number");
    }
    cleanup();
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
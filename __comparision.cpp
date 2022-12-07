#include "LargeInteger.h"

bool operator<(LargeInteger first, LargeInteger second)
{
    first.cleanup();
    second.cleanup();

    // handle negative case
    if (first.isNegative() && second.isNegative())
    {
        return first.abs() > second.abs();
    }

    if (first.isNegative())
        return true;

    if (second.isNegative())
        return false;

    int n = first.digitNum();
    int m = second.digitNum();

    if (n != m)
    {
        return n < m;
    }

    while (n--)
    {
        if (first.digits[n] > second.digits[n])
        {
            return false;
        }

        if (first.digits[n] < second.digits[n])
        {
            return true;
        }
    }

    return false;
}

bool operator>(LargeInteger first, LargeInteger second)
{
    first.cleanup();
    second.cleanup();

    // handle negative case
    if (first.isNegative() && second.isNegative())
    {
        return first.abs() < second.abs();
    }

    if (first.isNegative())
        return false;

    if (second.isNegative())
        return true;

    int n = first.digitNum();
    int m = second.digitNum();

    if (n != m)
    {
        return n > m;
    }

    while (n--)
    {

        if (first.digits[n] < second.digits[n])
        {
            return false;
        }

        if (first.digits[n] > second.digits[n])
        {
            return true;
        }
    }

    return false;
}

bool operator==(LargeInteger first, LargeInteger second)
{
    return first.digits == second.digits;
}

bool operator!=(LargeInteger first, LargeInteger second)
{
    return !(first == second);
}

bool operator<=(LargeInteger first, LargeInteger second)
{
    return !(first > second);
}

bool operator>=(LargeInteger first, LargeInteger second)
{
    return !(first < second);
}

bool operator<(LargeInteger first, unsigned long long second)
{
    return first < LargeInteger(second);
}

bool operator>(LargeInteger first, unsigned long long second)
{
    return first > LargeInteger(second);
}

bool operator==(LargeInteger first, unsigned long long second)
{
    return first == LargeInteger(second);
}

bool operator!=(LargeInteger first, unsigned long long second)
{
    return first != LargeInteger(second);
}

bool operator<=(LargeInteger first, unsigned long long second)
{
    return first <= LargeInteger(second);
}

bool operator>=(LargeInteger first, unsigned long long second)
{
    return first >= LargeInteger(second);
}

bool operator<(unsigned long long first, LargeInteger second)
{
    return LargeInteger(first) < second;
}

bool operator>(unsigned long long first, LargeInteger second)
{
    return LargeInteger(first) > second;
}

bool operator<=(unsigned long long first, LargeInteger second)
{
    return LargeInteger(first) <= second;
}

bool operator>=(unsigned long long first, LargeInteger second)
{
    return LargeInteger(first) >= second;
}

bool operator==(unsigned long long first, LargeInteger second)
{
    return LargeInteger(first) == second;
}

bool operator!=(unsigned long long first, LargeInteger second)
{
    return LargeInteger(first) != second;
}
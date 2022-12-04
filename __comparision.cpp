#include "LargeInteger.h"

bool operator<(LargeInteger first, LargeInteger second)
{
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
#include "LargeInteger.h"

ostream &operator<<(ostream &out, LargeInteger big_int)
{
    string digits = big_int.to_str();

    out << digits;

    return out;
}

istream &operator>>(istream &in, LargeInteger &&big_int)
{
    string digits;
    in >> digits;

    big_int.parse(digits);

    return in;
}
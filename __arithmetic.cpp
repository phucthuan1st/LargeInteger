#include "LargeInteger.h"

LargeInteger operator+(LargeInteger first, LargeInteger second)
{
    if (first.isNull() || second.isNull())
        return LargeInteger();

    if (first == constant::zero) {
        return second;
    }

    if (second == constant::zero) {
        return first;
    }

    LargeInteger result;

    if (first.isNegative() && second.isNegative())
    {
        result = first.abs() + second.abs();
        result = result.negative();
        return result;
    }

    if (first.isNegative())
    {
        return second - first.abs();
    }

    if (second.isNegative())
    {
        return first - second.abs();
    }

    int n = first.digitNum();
    int m = second.digitNum();

    if (m > n) {
        for (int i = 0; i < m - n; i++) {
            first.digits.push_back(ZERO);
        }
    }
    n = first.digitNum();
    result.digits = vector<char>(n, '0');

    int t = 0, s;

    for (int i = 0; i < n; i++) {
        if (i < m) 
            s = (first.at(i) + second.at(i)) + t;
        else 
            s = first.at(i) + t;

        t = s / 10;
        result.digits[i] = char((s % 10) + ZERO);
    }

    if (t > 0) {
        result.digits.push_back(t + ZERO);
    }

    result.cleanup();
    return result;
}

LargeInteger operator-(LargeInteger first, LargeInteger second)
{
    if (first.isNull() || second.isNull())
        return LargeInteger();

    if (first == 0)
    {
        return second.negative();
    }

    if (second == 0)
    {
        return first;
    }

    LargeInteger result;
    LargeInteger first_abs = first.abs();
    LargeInteger second_abs = second.abs();

    if (first.isNegative() && second.isNegative())
    {
        if (first_abs > second_abs)
        {
            result = first_abs - second_abs;
            result = result.negative();
        }
        else
        {
            result = second_abs - first_abs;
        }

        return result;
    }

    if (first.isNegative())
    {
        result = first_abs + second;
        result = result.negative();
        return result;
    }

    if (second.isNegative())
    {
        return first + second_abs;
    }

    if (second > first)
    {
        result = second - first;
        return result.negative();
    }

    int m = second.digitNum();
    int n = first.digitNum();

    int t = 0, s;
    result.digits = vector<char>(n, ZERO);
    for (int i = 0; i < n; i++) {
        if (i < m) 
            s = first.at(i) - second.at(i) + t;
        else
            s = first.at(i) + t;

        if (s < 0) {
            s += 10;
            t = -1;
        }
        else {
            t = 0;
        }
        result.digits.at(i) = char(s + ZERO);
    }

    result.cleanup();
    return result;
}

LargeInteger operator*(LargeInteger first, LargeInteger second)
{
    if (first.isNull() || second.isNull())
        return LargeInteger();
    if (first == 0 || second == 0)
    {
        return constant::zero;
    }

    if (first == 1)
    {
        return second;
    }

    if (second == 1)
    {
        return first;
    }

    if (first.isNegative() && second.isNegative())
    {
        return first.abs() * second.abs();
    }

    if (first.isNegative())
    {
        LargeInteger result = first.abs() * second;
        return result.negative();
    }

    if (second.isNegative())
    {
        LargeInteger result = first * second.abs();
        return result.negative();
    }

    int f = first.digitNum();
    int s = second.digitNum();

    if (f == 1 && s == 1)
    {
        int value = int(first.digits[0] - ZERO) * int(second.digits[0] - ZERO);
        return LargeInteger(value);
    }

    int n = f + s;
    vector<int> v(n, 0);
    
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < s; j++) {
            v.at(i + j) += first.at(i) * second.at(j);
        }
    }

    LargeInteger result;
    result.digits = vector<char>(v.size(), ZERO);
    int t = 0, save;
    for (int i = 0; i < n; i++) {
        save = t + v[i];
        result.digits.at(i) = char(save % 10 + ZERO);
        t = save / 10;
    }

    result.cleanup();
    return result;
}

LargeInteger operator/(LargeInteger dividend, LargeInteger divisor)
{
    
    if (dividend.isNull() || divisor.isNull()) {
        return LargeInteger();
    }

    if (dividend.isNegative() && divisor.isNegative())
    {
        return dividend.abs() / divisor.abs();
    }

    if (dividend.isNegative())
    {
        LargeInteger result = dividend.abs() / divisor;
        return result.negative();
    }

    if (divisor.isNegative())
    {
        LargeInteger result = dividend / divisor.abs();
        return result.negative();
    }

    if (divisor == constant::zero)
    {
        throw("Division by zero");
    }

    if (divisor > dividend)
    {
        return constant::zero;
    }

    if (dividend == divisor)
    {
        return constant::one;
    }

    int i, log = 0, qt;
    int n = dividend.digitNum();
    vector<int> prod(n, 0);
    LargeInteger t(0);

    for (i = n - 1; t * 10 + dividend.at(i) < divisor; i--) {
        t = t * 10 + dividend.at(i);
    }

    while (i >= 0) {
        t = t * 10 + dividend.at(i--);

        for (qt = 9; qt * divisor > t; qt--);

        t = t - qt * divisor;
        prod.at(log++) = qt;
    }

    LargeInteger result;   
    result.digits = vector<char>(log, ZERO);
    for (int i = 0; i < log; i++) {
        result.digits[i] = char(prod[log - i - 1] + ZERO);
    }

    result.cleanup();
    return result;
}

LargeInteger operator%(LargeInteger dividend, LargeInteger divisor)
{
    if (divisor.isNegative())
    {
        return dividend % divisor.abs();
    }

    if (dividend.isNegative())
    {
        LargeInteger result = dividend.abs() % divisor;
        result = divisor - result;
        return result;
    }

    if (divisor == constant::zero)
    {
        throw("Division by zero");
    }

    if (divisor > dividend)
    {
        return dividend;
    }

    if (dividend == divisor)
    {
        return constant::zero;
    }

    int i, log = 0, qt;
    int n = dividend.digitNum();
    LargeInteger t(0);

    for (i = n - 1; t * 10 + dividend.at(i) < divisor; i--) {
        t = t * 10 + dividend.at(i);
    }

    while (i >= 0) {
        t = t * 10 + dividend.at(i--);

        for (qt = 9; qt * divisor > t; qt--);

        t = t - qt * divisor;
    }

    t.cleanup();
    return t;
}

LargeInteger operator+(LargeInteger first, unsigned long long second)
{
    return first + LargeInteger(second);
}

LargeInteger operator-(LargeInteger first, unsigned long long second)
{
    return first - LargeInteger(second);
}

LargeInteger operator*(LargeInteger first, unsigned long long second)
{
    return first * LargeInteger(second);
}

LargeInteger operator/(LargeInteger first, unsigned long long second)
{
    return first / LargeInteger(second);
}

LargeInteger operator%(LargeInteger first, unsigned long long second)
{
    return first % LargeInteger(second);
}

LargeInteger operator+(unsigned long long first, LargeInteger second)
{
    return LargeInteger(first) + second;
}

LargeInteger operator-(unsigned long long first, LargeInteger second)
{
    return LargeInteger(first) - second;
}

LargeInteger operator*(unsigned long long first, LargeInteger second)
{
    return LargeInteger(first) * second;
}

LargeInteger operator/(unsigned long long first, LargeInteger second)
{
    return LargeInteger(first) / second;
}

LargeInteger operator%(unsigned long long first, LargeInteger second)
{
    return LargeInteger(first) % second;
}

// fast pow
LargeInteger pow(LargeInteger base, LargeInteger expo)
{
    LargeInteger result(constant::one);

    if (expo == constant::zero)
    {
        return result;
    }

    string bitset = expo.binary();

    if (bitset.at(0) == '1')
    {
        result = base;
    }

    for (int i = 1; i < bitset.size(); i++)
    {
        base = base * base;

        if (bitset.at(i) == '1')
        {
            result = result * base;
        }
    }

    return result;
}

// calculate base^expo % mod
LargeInteger pow(LargeInteger base, LargeInteger expo, LargeInteger mod)
{
    LargeInteger result(constant::one);
    if (expo == constant::zero)
    {
        return result;
    }

    string bitset = expo.binary();
    base = base % mod;

    if (bitset.at(0) == '1')
    {
        result = base;
    }

    for (int i = 1; i < bitset.size(); i++)
    {
        base = base * base % mod;

        if (bitset.at(i) == '1')
        {
            result = result * base % mod;
        }
    }

    return result;
}

LargeInteger sqrt(LargeInteger x) {
    LargeInteger left(1), right(x / 2), mid(0);
    LargeInteger v(1), prod;

    while (left <= right) {
        mid = (left + right) / constant::two;
        
        prod = mid * mid;
        if (prod <= x) {
            v = mid;
            mid = mid + constant::one;
            left = mid;
        }
        else {
            mid = mid - constant::one;
            right = mid;
        }
    }

    return v;
}

LargeInteger LargeInteger::multiply_pow_10(unsigned long long n)
{
    int start = this->digits.size();
    vector<char> digits(n + start, ZERO);

    for (int i = 0; i < start; i++) {
        digits[i] = this->digits[i];
    }

    this->digits = digits;

    return *this;
}

LargeInteger LargeInteger::divide_by_10() {
    if (*this == constant::zero)
    {
        return constant::zero;
    }

    if (this->isNegative())
    {
        return this->abs().divide_by_10().negative();
    }

    string digits = this->to_str();
    if (digits.length() > 1)
    {
        digits.pop_back();
    }
    return LargeInteger(digits);
}
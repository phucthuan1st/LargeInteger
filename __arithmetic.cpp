#include "LargeInteger.h"

LargeInteger operator+(LargeInteger first, LargeInteger second)
{
    LargeInteger result;
    int n = second.digitNum();
    int m = first.digitNum();

    int minNum = min(m, n);
    int maxNum = max(m, n);

    int save = 0;

    for (int i = 0; i < minNum; i++)
    {
        int temp = (first.digits[i] - ZERO) + (second.digits[i] - ZERO) + save;

        result.digits.push_back(temp % 10 + ZERO);
        temp /= 10;
        save = temp % 10;
    }

    vector<char> bigger = (m > n) ? first.digits : second.digits;

    for (int i = minNum; i < maxNum; i++)
    {
        int temp = (bigger[i] - ZERO) + save;

        result.digits.push_back(temp % 10 + ZERO);
        temp /= 10;
        save = temp % 10;
    }

    if (save == 1)
        result.digits.push_back('1');

    return result;
}

LargeInteger operator-(LargeInteger first, LargeInteger second)
{
    if (first < second)
    {
        throw("Under Zero Subtraction");
    }
    LargeInteger result;
    int n = second.digitNum();
    int m = first.digitNum();

    int minNum = min(m, n);
    int maxNum = max(m, n);

    int save = 0;

    for (int i = 0; i < minNum; i++)
    {
        int temp = (first.digits[i]) - (second.digits[i]) - save;

        if (temp < 0)
        {
            temp = temp + 10;
            save = 1;
        }
        else
        {
            save = 0;
        }

        result.digits.push_back(temp + ZERO);
    }

    vector<char> bigger = (m > n) ? first.digits : second.digits;

    for (int i = minNum; i < maxNum; i++)
    {
        int temp = (bigger[i] - ZERO) - save;

        if (temp < 0)
        {
            temp = temp + 10;
            save = 1;
        }
        else
        {
            save = 0;
        }

        result.digits.push_back(temp + ZERO);
    }

    result.cleanup();

    return result;
}

LargeInteger operator*(LargeInteger first, LargeInteger second)
{

    if (first.isNull() || second.isNull())
        return LargeInteger();

    int f = first.digitNum();
    int s = second.digitNum();

    if (f == 1 && s == 1)
    {
        int value = (first.digits[0] - ZERO) * (second.digits[0] - ZERO);
        return LargeInteger(value);
    }

    int n = f + s;

    vector<int> pow_sum(n, 0);
    for (unsigned int i = 0; i < f; i++)
    {
        for (unsigned int j = 0; j < s; j++)
        {
            int first_digit = (first.digits[i] - ZERO);
            int second_digit = (second.digits[j] - ZERO);

            pow_sum[i + j] += first_digit * second_digit;
        }
    }

    vector<LargeInteger> pow_sum_large;

    for (int i = 0; i < pow_sum.size(); i++)
    {
        LargeInteger num = LargeInteger(pow_sum[i]);
        num.multiply_pow_10(i);
        pow_sum_large.push_back(num);
    }

    LargeInteger result(0);

    for (auto &sum : pow_sum_large)
    {
        result = result + sum;
    }

    result.cleanup();

    return result;
}

LargeInteger operator/(LargeInteger dividend, LargeInteger divisor)
{
    LargeInteger zero(0);
    LargeInteger one(1);

    if (divisor == zero)
    {
        throw("Division by zero");
    }

    if (divisor > dividend)
    {
        return zero;
    }

    if (dividend == divisor)
    {
        return one;
    }

    int digit_pos = dividend.digitNum() - 1;
    LargeInteger result;

    // temporary/sub dividend
    LargeInteger dv;

    while (digit_pos > 0)
    {
        // get as much as posible digit for sub-dividsend
        while (dv.isNull() || dv < divisor)
        {
            dv.digits.insert(dv.digits.begin(), dividend.digits[digit_pos--]);

            if (dv < divisor)
            {
                result.digits.insert(result.digits.begin(), '0');
            }
        }

        // multiplying and subtracting
        LargeInteger quotient = one;
        LargeInteger save = quotient * divisor;

        while (save <= dv)
        {
            quotient = quotient + one;
            save = quotient * divisor;
        }

        quotient = quotient - one;
        dv = dv - quotient * divisor;

        for (auto &digit : quotient.digits)
        {
            result.digits.insert(result.digits.begin(), digit);
        }
    }

    result.cleanup();

    return result;
}

LargeInteger operator%(LargeInteger dividend, LargeInteger divisor)
{
    LargeInteger zero(0);
    LargeInteger one(1);

    if (divisor == zero)
    {
        throw("Division by zero");
    }

    if (divisor > dividend)
    {
        return dividend;
    }

    if (dividend == divisor)
    {
        return zero;
    }

    int digit_pos = dividend.digitNum() - 1;

    // temporary/sub dividend
    LargeInteger dv;

    while (digit_pos > 0)
    {
        // get as much as posible digit for sub-dividsend
        while (dv.isNull() || dv < divisor)
        {
            dv.digits.insert(dv.digits.begin(), dividend.digits[digit_pos--]);
        }

        // multiplying and subtracting
        LargeInteger quotient = one;
        LargeInteger save = quotient * divisor;

        while (save <= dv)
        {
            quotient = quotient + one;
            save = quotient * divisor;
        }

        quotient = quotient - one;
        dv = dv - quotient * divisor;
    }

    return dv;
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

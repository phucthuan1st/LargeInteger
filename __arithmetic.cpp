#include "LargeInteger.h"

LargeInteger operator+(LargeInteger first, LargeInteger second)
{
    if (first.isNull() || second.isNull())
        return LargeInteger();

    if (first == 0)
    {
        return second;
    }

    if (second == 0)
    {
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

    for (int i = minNum; i < m; i++)
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

// slow multiplying
LargeInteger operator*(LargeInteger first, LargeInteger second)
{
    if (first.isNull() || second.isNull())
        return LargeInteger();
    if (first == 0 || second == 0)
    {
        return LargeInteger(0);
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

    int digit_pos = dividend.digitNum() - 1;
    LargeInteger result;

    // temporary/sub dividend
    LargeInteger dv;

    while (digit_pos >= 0)
    {
        // get as much as posible digit for sub-dividsend
        while (digit_pos >= 0 && (dv.isNull() || dv < divisor))
        {
            dv.digits.insert(dv.digits.begin(), dividend.digits[digit_pos--]);

            if (dv < divisor)
            {
                result.digits.insert(result.digits.begin(), '0');
            }
        }

        dv.cleanup();
        if (dv < divisor)
        {
            result.cleanup();
            return result;
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
        save = quotient * divisor;
        dv = dv - save;

        for (auto &digit : quotient.digits)
        {
            result.digits.insert(result.digits.begin(), digit);
        }

        if (dv == 0)
        {
            dv.digits = {};
        }
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

    while (digit_pos >= 0)
    {
        // get as much as posible digit for sub-dividsend
        if (dv == 0)
        {
            dv.digits = {};
        }
        while (digit_pos >= 0 && (dv.isNull() || dv < divisor))
        {
            dv.digits.insert(dv.digits.begin(), dividend.digits[digit_pos--]);
        }
        dv.cleanup();

        if (dv < divisor)
        {
            return dv;
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
        save = quotient * divisor;
        dv = dv - save;
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

LargeInteger pow(LargeInteger base, LargeInteger expo)
{
    if (expo == 0)
    {
        return LargeInteger(1);
    }

    LargeInteger result = pow(base, expo.divide_by_2());
    if (expo.isEven())
    {
        return result * result;
    }
    else
    {
        return result * result * base;
    }
}

// calculate base^expo % mod
LargeInteger pow(LargeInteger base, LargeInteger expo, LargeInteger mod)
{
    LargeInteger zero(0);
    LargeInteger result(1);

    base = base % mod;

    while (expo > zero)
    {
        if (!expo.isEven())
        {
            result = multiply(result, base, mod);
        }

        base = multiply(base, base, mod);
        expo = expo.divide_by_2();
    }

    return result;
}

string BinaryAdd(string first, string second)
{
    while (first.length() < second.length())
    {
        first.append("0");
    }

    while (first.length() > second.length())
    {
        second.append("0");
    }

    string result;
    int n = first.length();
    int carry = 0;

    for (int i = 0; i < n; i++)
    {
        int firstBit = first[i] - ZERO;
        int secondBit = second[i] - ZERO;

        // sum by using xor
        int sum = (firstBit ^ secondBit ^ carry);

        // cast sum to char and add to result
        result = result + (char(ZERO + sum));

        carry = (firstBit & secondBit) | (secondBit & carry) | (firstBit & carry);
    }

    if (carry)
        result = result + '1';

    return result;
}

LargeInteger BinaryMultiply(string first_bin, string second_bin)
{
    while (first_bin.length() < second_bin.length())
    {
        first_bin.append("0");
    }

    while (first_bin.length() > second_bin.length())
    {
        second_bin.append("0");
    }

    int n = first_bin.length();
    if (n == 0)
    {
        return 0;
    }

    if (n == 1)
    {
        int result = (first_bin.at(0) - ZERO) * (second_bin.at(0) - ZERO);
        return LargeInteger(result);
    }

    int first_half = n / 2;
    int second_half = n - first_half;

    string first_right = first_bin.substr(0, second_half);
    string first_left = first_bin.substr(second_half, first_half);

    string second_right = second_bin.substr(0, second_half);
    string second_left = second_bin.substr(second_half, first_half);

    LargeInteger P1 = BinaryMultiply(first_left, second_left);
    LargeInteger P2 = BinaryMultiply(first_right, second_right);
    LargeInteger P3 = BinaryMultiply(BinaryAdd(first_left, first_right), BinaryAdd(second_left, second_right));

    LargeInteger power = pow(2, second_half);

    LargeInteger result = P1 * pow(power, 2) + (P3 - P1 - P2) * power + P2;
    return result;
}

LargeInteger fastMultiply(LargeInteger first, LargeInteger second)
{
    if (first.isNull() || second.isNull())
        return LargeInteger();

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

    // ------------- MARK: Karatsuba Algorithm ----------------
    string first_bin = first.binary();
    string second_bin = second.binary();

    return BinaryMultiply(first_bin, second_bin);
}

LargeInteger multiply(LargeInteger first, LargeInteger second, LargeInteger mod)
{
    string binary = second.binary();
    LargeInteger two(2);

    LargeInteger result = (binary.at(0) == '1') ? first : 0;

    for (int i = 1; i < binary.size(); i++)
    {
        first = (two * first) % mod;

        if (binary.at(i) == '1')
        {
            result = (result + first) % mod;
        }
    }

    return result;
}

LargeInteger LargeInteger::divide_by_2()
{
    LargeInteger result;
    if (this->isNegative())
    {
        result = this->abs().divide_by_2().negative();
    }
    else
    {
        string resultStr = "";
        string num_str = this->to_str();
        int n = num_str.length();
        int carry = 0;
        int step = 15;

        for (int i = 0; i < n; i += step)
        {
            string chunk = to_string(carry) + num_str.substr(i, 15);
            long long num = stoll(chunk);
            long long temp = num / 2;
            int carry = num & 1;

            resultStr = resultStr + to_string(temp);
        }

        result = LargeInteger(resultStr);
    }

    return result;
}

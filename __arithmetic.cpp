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

    vector<int> result(n, 0);

    int i_n1 = 0;
    int i_n2 = 0;

    // Go from right to left in first
    for (int i = 0; i <= f - 1; i++)
    {
        int carry = 0;
        int n1 = first.digits[i] - ZERO;

        // To shift position to left after every multiplication of a digit in second number
        i_n2 = 0;

        // Go from right to left in second
        for (int j = 0; j <= s - 1; j++)
        {
            // Take current digit of second number
            int n2 = second.digits[j] - ZERO;

            // Multiply with current digit of first number
            // and add result to previously stored result
            // at current position.
            int sum = n1 * n2 + result[i_n1 + i_n2] + carry;

            // Carry for next iteration
            carry = sum / 10;

            // Store result
            result[i_n1 + i_n2] = sum % 10;

            i_n2++;
        }

        // store carry in next cell
        if (carry > 0)
            result[i_n1 + i_n2] += carry;

        // To shift position to left after every
        // multiplication of a digit in num1.
        i_n1++;
    }

    int i = result.size() - 1;
    while (i >= 0 && result[i] == '0')
        i--;

    string str = "";
    while (i >= 0)
    {
        str = str + to_string(result[i--]);
    }

    LargeInteger res(str);
    res.cleanup();

    return res;
}

LargeInteger operator/(LargeInteger dividend, LargeInteger divisor)
{

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
        LargeInteger quotient = constant::one;
        LargeInteger save = quotient * divisor;

        while (save <= dv)
        {
            quotient = quotient + constant::one;
            save = quotient * divisor;
        }

        quotient = quotient - constant::one;
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
        LargeInteger quotient = constant::one;
        LargeInteger save = quotient * divisor;

        while (save <= dv)
        {
            quotient = quotient + constant::one;
            save = quotient * divisor;
        }

        quotient = quotient - constant::one;
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
        base = multiply(base, base, mod);

        if (bitset.at(i) == '1')
        {
            result = multiply(result, base, mod);
        }
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

// multiplication with modulo
LargeInteger multiply(LargeInteger first, LargeInteger second, LargeInteger mod)
{
    string binary = second.binary();

    LargeInteger result = (binary.at(0) == '1') ? first : 0;

    for (int i = 1; i < binary.size(); i++)
    {
        first = constant::two * first % mod;

        if (binary.at(i) == '1')
        {
            result = (result + first) % mod;
        }
    }

    return result;
}

LargeInteger schonhageStrassenMultiplication(LargeInteger x, LargeInteger y)
{
    int n = x.digitNum();
    int m = y.digitNum();

    LargeInteger linearConvolution[n + m - 1];
    for (int i = 0; i < (n + m - 1); i++)
        linearConvolution[i] = 0;

    LargeInteger p = x;
    for (int i = 0; i < m; i++)
    {
        x = p;
        for (int j = 0; j < n; j++)
        {
            linearConvolution[i + j] = linearConvolution[i + j] + y.last_digit() * x.last_digit();
            x = x.divide_by_10();
        }
        y = y.divide_by_10();
    }

    LargeInteger product(0);
    LargeInteger nextCarry(0), base(1);

    for (int i = 0; i < n + m - 1; i++)
    {
        linearConvolution[i] = linearConvolution[i] + nextCarry;
        product = product + (base * (linearConvolution[i].last_digit()));
        nextCarry = linearConvolution[i].divide_by_10();
        base = base.multiply_pow_10(1);
    }

    if (nextCarry != 0)
    {
        for (auto &digit : nextCarry.digits)
        {
            product.digits.push_back(digit);
        }
    }

    return product;
}
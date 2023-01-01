#include "LargeInteger.h"
#include "Randomizer.h"

void LargeInteger::cleanup()
{
    while (this->digitNum() > 1 && this->digits[this->digits.size() - 1] == '0')
    {
        this->digits.pop_back();
    }
}

void LargeInteger::parse(string &digits)
{
    if (digits.at(0) == '-')
    {
        this->digits.push_back(digits.at(0));
        digits.erase(digits.begin());
    }

    for (auto &digit : digits)
    {
        if ((digit >= '0' && digit <= '9'))
            this->digits.push_back(digit);
        else
            throw("Invalid input");
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
        a = a.divide_by_2();
        b = b.divide_by_2();
        g = g * constant::two;
    }

    while (a > constant::zero)
    {

        while (a.isEven())
        {
            a = a.divide_by_2();
        }

        while (b.isEven())
        {
            b = b.divide_by_2();
        }

        LargeInteger sub = (a > b) ? (a - b) : (b - a);
        t = sub.divide_by_2();

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
        // cout << "Clone = " << clone << endl;
        if (clone.isEven())
        {
            result.append("0");
        }
        else
        {
            result.append("1");
        }

        clone = clone.divide_by_2();
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
        int step = 18;

        for (int i = 0; i < n; i += step)
        {
            string chunk = to_string(carry) + num_str.substr(i, step);

            long long num = stoll(chunk);
            long long temp = num / 2;
            carry = num & 1;

            string nonZeroDigits = to_string(temp);
            string zeroDigits(chunk.size() - nonZeroDigits.size() - 1, '0');
            resultStr = resultStr + zeroDigits + nonZeroDigits;
        }

        result = LargeInteger(resultStr);
    }

    result.cleanup();

    return result;
}

LargeInteger LargeInteger::divide_by_10()
{
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

int LargeInteger::last_digit()
{
    return int(this->digits.at(0)) - ZERO;
}

// using little Fermat to check if n is Prime number method with k tries
bool checkPrimeFermat(LargeInteger n, int k)
{

    if (n < 1 || n == 4)
        return false;

    if (n <= 3)
        return true;

    LargeInteger step = pow(2, k + 1);
    LargeInteger min(constant::two);
    // try k times if n if satisfied a^(n-1) congruent with n
    while (k > 0)
    {
        LargeInteger a;
        a = Randomizer::randomizer()->next(min, n / step);

        // make sure n>4
        LargeInteger _gcd = gcd(n, a);
        if (_gcd != constant::one)
        {
            return false;
        }

        auto start = clock();
        LargeInteger powMod = pow(a, n - 1, n);
        auto end = clock();
        double time = double(end - start) / CLOCKS_PER_SEC;

        cout << "PowMod = " << powMod << " Finished in " << time << "seconds" << endl;
        if (powMod != constant::one)
        {
            return false;
        }

        k = k - 1;
        min = n / step;
        step = step.divide_by_2();
    }
    return true;
}
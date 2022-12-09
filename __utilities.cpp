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

    if (a == 0)
        return b;

    if (b == 0)
        return a;
    // MARK: End Special cases!

    // make sure a >=b in all cases
    if (b > a)
        return gcd(b, a);

    LargeInteger zero(0);
    LargeInteger two(2);
    LargeInteger g(1);

    LargeInteger t;

    while (a.isEven() && b.isEven())
    {
        a = a.divide_by_2();
        b = b.divide_by_2();
        g = g * two;
    }

    while (a > 0)
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
    LargeInteger two(2);
    LargeInteger zero(0);
    string result;
    LargeInteger clone(*this);

    while (clone != zero)
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

// using little Fermat to check if n is Prime number method with k tries
bool checkPrimeFermat(LargeInteger n, LargeInteger k)
{
    LargeInteger one(1);
    LargeInteger zero(0);

    if (n < 1 || n == 4)
        return false;

    if (n <= 3)
        return true;

    // try k times if n if satisfied a^(n-1) congruent with n
    while (k > 0)
    {
        LargeInteger a;
        a = Randomizer::randomizer()->next(2, n - 4);
        cout << "Try number: " << a << endl;

        // make sure n>4
        LargeInteger _gcd = gcd(n, a);
        cout << "gcd: " << _gcd << endl;

        if (_gcd != one)
        {
            return false;
        }

        LargeInteger powMod = pow(a, n - 1, n);
        cout << "powMod: " << powMod << endl;

        if (powMod != one)
        {
            return false;
        }

        k = k - one;
    }
    return true;
}
#include "LargeInteger.h"
#include "Randomizer.h"

void LargeInteger::cleanup()
{
    int n = this->digits.size();

    if (n < 2) 
        return;
    
    bool sign = (this->digits[n - 1] == '-');

    if (sign) {
        this->digits.pop_back();
        n = n - 1;
    }

    while(n > 1 && this->digits[n - 1] == ZERO) {
        this->digits.pop_back(),
        n--;
    }

    if (sign) {
        this->digits.push_back('-');
    }
}

void LargeInteger::parse(string &digits)
{
    int n = digits.size();
    this->digits = vector<char>(n, ZERO);
    int end = 0;

    for (int i = n - 1; i >= 1; i--)
    {
        if (isdigit(digits[end]))
            this->digits[end++] = digits[i];
        else 
            throw("Invalid string for int: digit must be a number");
    }

    if (digits[0] == '-' || isdigit(digits[0])) {
        this->digits[end] = digits[0];
    }
    else {
        throw("Invalid string for int: digit must be a number");
    }
    cleanup();
}

string LargeInteger::to_str()
{
    int n = this->digits.size();
    string digits(n, '0');
    int end = 0;

    for (int i = n - 1; i >= 0; i--) {
        digits[i] = this->digits[end++];
    }

    return digits;
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
        a = a / 2;
        b = b / 2;
        g = g * constant::two;
    }

    while (a > constant::zero)
    {

        while (a.isEven())
        {
            a = a / 2;
        }

        while (b.isEven())
        {
            b = b / 2;
        }

        LargeInteger sub = (a > b) ? (a - b) : (b - a);
        t = sub / 2;

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
        if (clone.isEven())
        {
            result.append("0");
        }
        else
        {
            result.append("1");
        }

        clone = clone / 2;
    }

    return result;
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
    LargeInteger max(constant::zero);
    // try k times if n if satisfied a^(n-1) congruent with n
    while (k > 0)
    {
        LargeInteger a;
        max = n / step;
        cout << "-----------------------------" << endl;
        cout << k << "th try" << endl;
        a = Randomizer::randomizer()->next(min, max);

        cout << "n = " << n << endl;
        cout << "Step = " << step << endl;
        cout << "a = " << a << endl;

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
        step = step / 2;
        min = max;
    }
    return true;
}

bool isPrime(LargeInteger n) {
    if (n < constant::two) {
        return false;
    }

    auto start = clock();
    LargeInteger squareRoot = sqrt(n);
    // cout << "Sqrt = " << squareRoot << endl;
    // LargeInteger half = n / 2 - constant::one;
    // cout << "DEBUG: HALF = " << half << endl;

    for (LargeInteger i = constant::two; i < squareRoot; i = i + constant::one) {
        cout << n << "%" << i << " = " << n % i << endl;
        
        if (n % i == constant::zero) {
            return false;
        }
    }
    auto end = clock();
    double time = (end - start) / CLOCKS_PER_SEC * 1000;
    cout << "Check finished in " << time << "ms" << endl;

    return true;
}
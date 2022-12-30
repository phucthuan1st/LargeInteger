#include "LargeInteger.h"
#include "Randomizer.h"
using namespace std;

// LargeInteger karat(LargeInteger first, LargeInteger second)
// {
//     if (first.digitNum() == 1 || second.digitNum() == 1)
//     {
//         return first * second;
//     }
//     else
//     {
//         LargeInteger m = max(first.digitNum(), second.digitNum());
//         LargeInteger m2 = m / 2;
//         LargeInteger a = pow(first / 10, m2);
//         LargeInteger b = pow(first % 10, m2);
//         LargeInteger c = pow(second / 10, m2);
//         LargeInteger d = pow(second % 10, m2);
//         LargeInteger z0 = karat(b, d);
//         cout << z0 << endl;
//         LargeInteger z1 = karat(a + b, c + d);
//         cout << z0 << endl;
//         LargeInteger z2 = karat(a, c);
//         return pow(z2 * 10, 2 * m2) + pow((z1 - z2 - z0) * 10, m2) + z0;
//     }
// }

void modRandom(LargeInteger &p, LargeInteger &q, int size)
{
    if (size == 2048)
    {
        p = Randomizer::randomizer()->next();
        q = Randomizer::randomizer()->next();

        p = p * p;
        q = q * q;
    }
    else
    {
        LargeInteger upper_limit;

        if (size == 512)
        {
            upper_limit = constant::quarterMaxLargeInt;
        }
        else if (size == 1024)
        {
            upper_limit = constant::halfMaxLargeInt;
        }

        LargeInteger lower_limit = upper_limit.divide_by_2();

        p = Randomizer::randomizer()->next(lower_limit, upper_limit);
        q = Randomizer::randomizer()->next(lower_limit, upper_limit);

        p = p * p;
        q = p * p;
    }
}

LargeInteger getN(LargeInteger &p, LargeInteger &q)
{
    return p * q;
}

LargeInteger getPhi(LargeInteger &p, LargeInteger &q)
{
    return (p - 1) * (q - 1);
}

LargeInteger getE(LargeInteger Phi)
{
    for (LargeInteger e = 100; e < 1000000; e = e + 1)
    {
        if (gcd(e, Phi) == 1)
        {
            return e;
        }
    }

    return LargeInteger(0);
}

LargeInteger gcdExtend(LargeInteger a, LargeInteger b, LargeInteger &x, LargeInteger &y)
{
    if (b == 0)
    {
        x = LargeInteger(1);
        y = LargeInteger(0);
        return a;
    }

    LargeInteger x1, y1;
    LargeInteger d = gcdExtend(b, a % b, x1, y1);

    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

LargeInteger getD(LargeInteger e, LargeInteger Phi)
{
    LargeInteger x, y;
    gcdExtend(e, Phi, x, y);
    LargeInteger D = x % Phi;
    return D;
}

void RSA_generate()
{
    int check = 1;
    cout << "Select the size of the RSA key you want to generate: " << endl;
    cout << "1. 512 bits" << endl;
    cout << "2. 1024 bits" << endl;
    cout << "3. 2048 bits" << endl;
    cout << "4. Quit" << endl;
    do
    {
        LargeInteger p(2386421887), q(4238399051), l;
        int k;
        cout << "-----------" << endl
             << "Your choice: ";
        cin >> check;

        if (check == 1)
            modRandom(p, q, 512);
        else if (check == 2)
            modRandom(p, q, 1024);
        else if (check == 3)
            modRandom(p, q, 2048);
        else
            continue;

        if (p.isEven())
            p = p + 1;

        if (q.isEven())
            q = q + 1;

        while (checkPrimeFermat(p) == 0)
        {
            p = p + 2;
        }
        while (checkPrimeFermat(q) == 0)
        {
            q = q + 2;
        }

        LargeInteger n = getN(p, q);
        LargeInteger phi = getPhi(p, q);
        LargeInteger e = getE(phi);
        LargeInteger d = getD(e, phi);

        cout << "p = " << p << endl;
        cout << "q = " << q << endl;
        cout << "n = " << n << endl;
        cout << "phi = " << phi << endl;
        cout << "e = " << e << endl;
        cout << "d = " << d << endl;
    } while (check != 4);
}

int main()
{
    auto start = clock();
    RSA_generate();
    auto end = clock();

    double time = double(end - start) / CLOCKS_PER_SEC;
    cout << "Finished in " << time << "seconds" << endl;

    return 0;
}

#include "LargeInteger.h"
#include <ctime>

// unsigned int russianPeasant(unsigned int n, unsigned int m)
// {
//     int result = 0;
//     while (m > 0)
//     {
//         if (m & 1)
//             result = result + n;
//         n = n << 1;
//         cout << "n = " << n << endl;
//         m = m >> 1;
//         cout << "m = " << m << endl;
//     }
//     return result;
// }

int main()
{
    LargeInteger first("33154354547656395467544442444213444324444764444765000670087876787987909809243212317676586780980958567657657536059");
    LargeInteger second("5435465365365665439809804324320648797213219887997898231312321359454770931231312982435464");
    auto start = clock();
    cout << multiply(first, second) << endl;
    auto end = clock();

    double time = (double)(end - start) / CLOCKS_PER_SEC;
    cout << time << endl;

    start = clock();
    cout << first * second << endl;
    end = clock();

    time = (double)(end - start) / CLOCKS_PER_SEC;
    cout << time << endl;

    return 0;
}
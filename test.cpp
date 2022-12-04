#include "LargeInteger.h"
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    auto start = clock();
    LargeInteger base(2);
    LargeInteger expo(2048);
    LargeInteger mod(1747);
    // cout << two_pow(2048) << endl;
    cout << pow(base, expo, mod) << endl;
    auto end = clock();

    double time = double(end - start) / CLOCKS_PER_SEC;
    cout << "Finished in " << time << "seconds" << endl;
    return 0;
}
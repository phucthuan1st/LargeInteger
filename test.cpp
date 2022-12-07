#include "LargeInteger.h"
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    LargeInteger a(-7);
    LargeInteger b(5);

    auto start = clock();
    cout << a % b << endl;
    auto end = clock();

    double time = double(end - start) / CLOCKS_PER_SEC;
    cout << "Finished in " << time << "seconds" << endl;
    return 0;
}
#include "LargeInteger.h"
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    auto start = clock();
    // cout << two_pow(2048) << endl;
    cout << LargeInteger("76231376437686732423") % 12433642376 << endl;
    auto end = clock();

    double time = double(end - start) / CLOCKS_PER_SEC;
    cout << "Finished in " << time << "seconds" << endl;
    return 0;
}
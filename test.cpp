#include "LargeInteger.h"
#include "RSA.h"
#include <ctime>

int main()
{
    // menu();
    auto start = clock();
    cout << LargeInteger("4960165696392") % 2 << endl;
    auto end = clock();
    double time = (end - start) / CLOCKS_PER_SEC * 1000;
    cout << "finished in " << time << " ms" << endl;
    return 0;
}
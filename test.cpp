#include "Randomizer.h"
#include "LargeInteger.h"

using namespace std;

int main()
{
    LargeInteger mod(17);

    auto start = clock();
    cout << LargeInteger(7) - LargeInteger(145) << endl;
    auto end = clock();
    double time = double(end - start) / CLOCKS_PER_SEC;
    cout << "Slow multiply finished in " << time << "seconds" << endl;
    return 0;
}
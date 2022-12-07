#include "Randomizer.h"
#include "LargeInteger.h"

using namespace std;

int main()
{
    auto start = clock();
    cout << Randomizer::randomizer()->next() << endl;
    auto end = clock();

    double time = double(end - start) / CLOCKS_PER_SEC;
    cout << "Finished in " << time << "seconds" << endl;
    return 0;
}
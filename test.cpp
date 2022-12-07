#include "Randomizer.h"
#include "LargeInteger.h"

using namespace std;

int main()
{
    auto start = clock();
    for (int i = 0; i < 50; i++)
        cout << i + 1 << ". " << Randomizer::randomizer()->next(10, 100) << endl;
    auto end = clock();

    double time = double(end - start) / CLOCKS_PER_SEC;
    cout << "Finished in " << time << "seconds" << endl;
    return 0;
}
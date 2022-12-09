// #include "Randomizer.h"
// #include "LargeInteger.h"

// using namespace std;

// int main()
// {
//     LargeInteger mod(17);

//     auto start = clock();
//     for (int i = 0; i < 10; i++)
//         cout << Randomizer::randomizer()->next(1, 100) << endl;
//     auto end = clock();
//     double time = double(end - start) / CLOCKS_PER_SEC;
//     cout << "Slow multiply finished in " << time << "seconds" << endl;

//     // start = clock();
//     // cout << multiply(constant::maxLargeInt, constant::maxLargeInt, constant::diff) << endl;
//     // end = clock();
//     // time = double(end - start) / CLOCKS_PER_SEC;
//     // cout << "Fast multiply finished in " << time << "seconds" << endl;

//     return 0;
// }
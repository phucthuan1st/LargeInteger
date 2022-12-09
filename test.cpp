// #include "Randomizer.h"
// #include "LargeInteger.h"

// using namespace std;

// int main()
// {
//     LargeInteger mod(17);

//     auto start = clock();
//     cout << constant::maxLargeInt * constant::maxLargeInt << endl;
//     auto end = clock();
//     double time = double(end - start) / CLOCKS_PER_SEC;
//     cout << "Slow multiply finished in " << time << "seconds" << endl;

//     start = clock();
//     cout << multiply(constant::maxLargeInt, constant::maxLargeInt, constant::diff) << endl;
//     end = clock();
//     time = double(end - start) / CLOCKS_PER_SEC;
//     cout << "Fast multiply finished in " << time << "seconds" << endl;

//     return 0;
// }
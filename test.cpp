// #include "LargeInteger.h"
// #include <iostream>
// #include <ctime>

// using namespace std;

// int fastExp(int b, int e, int m)
// {
//     cout << "Start: base  = " << b << ", Exponent = " << e << ", mod = " << m << endl;
//     int result = 1;
//     if (1 & e)
//         result = b;
//     while (1)
//     {
//         cout << "Start loop: base  = " << b << ", Exponent = " << e << ", Result = " << result << endl;
//         if (!e)
//             break;
//         e >>= 1;
//         b = (b * b) % m;
//         if (e & 1)
//             result = (result * b) % m;

//         cout << "End loop: base  = " << b << ", Exponent = " << e << ", Result = " << result << endl;
//     }
//     return result;
// }

// int main()
// {
//     LargeInteger base(4906);
//     LargeInteger expo(11026);
//     LargeInteger mod(11027);

//     auto start = clock();
//     cout << pow(base, expo, mod) << endl;
//     auto end = clock();

//     double time = double(end - start) / CLOCKS_PER_SEC;
//     cout << "Finished in " << time << "seconds" << endl;

//     start = clock();
//     cout << fastExp(4906, 11026, 11027) << endl;
//     end = clock();

//     time = double(end - start) / CLOCKS_PER_SEC;
//     cout << "Finished in " << time << "seconds" << endl;
//     return 0;
// }
// #include "LargeInteger.h"
// #include <ctime>

// int main()
// {
//     LargeInteger first("787564354765454958357463523545324434113232143574546566453445654534567687890898767654345374635454676536475869787465245364764444765000670087876787987909809243212317676586780980958567657657536059");
//     LargeInteger second("543546536536566509804324320648797213219887997898231312321359454770931231312982435464");
//     LargeInteger mod("654634666547657536543636");
//     auto start = clock();
//     try {
//         cout << pow(first, second, mod) << endl;
//     }
//     catch(const char* err) {
//         cout << err << endl;
//     }
//     auto end = clock();

//     double time = (double)(end - start) / CLOCKS_PER_SEC;
//     cout << time * 1000 << "ms" << endl;

//     // start = clock();
//     // end = clock();

//     // time = (double)(end - start) / CLOCKS_PER_SEC;
//     // cout << time * 1000 << "ms" << endl;

//     return 0;
// }
#include <iostream>
#include <ctime>
#include "LargeInteger.h"
#include "Randomizer.h"

using namespace std;

// using little Fermat to check if n is Prime number method with k tries
bool checkPrimeFermat(LargeInteger n, LargeInteger k)
{
	LargeInteger one(1);
	LargeInteger zero(0);

	if (n < 1 || n == 4)
		return false;

	if (n <= 3)
		return true;

	// try k times if n if satisfied a^(n-1) congruent with n
	while (k > 0)
	{
		LargeInteger a;
		a = Randomizer::randomizer()->next(2, n - 4);
		cout << "Try number: " << a << endl;

		// make sure n>4
		LargeInteger _gcd = gcd(n, a);
		cout << "gcd: " << _gcd << endl;

		if (_gcd != one)
		{
			return false;
		}

		LargeInteger powMod = pow(a, n - 1, n);
		cout << "powMod: " << powMod << endl;

		if (powMod != one)
		{
			return false;
		}

		k = k - one;
	}
	return true;
}

// int main()
// {
// 	LargeInteger n("89884656743115795386465259539451236680898848947115328636715040578866337902750481566354238661203768010560056939935696678829394884407208311246423715319737062188883946712432742638151109800623047059726541476042502884419075341171231440736956555270413618581675255342293149119973622969239858152417678164812112122095"),
// 		k(10);

// 	auto start = clock();
// 	if (checkPrimeFermat(n, k) == true)
// 	{
// 		cout << n << " is a Prime number." << endl;
// 	}
// 	else
// 	{
// 		cout << n << " is not a Prime number." << endl;
// 	}
// 	auto end = clock();
// 	double time = double(end - start) / CLOCKS_PER_SEC;
// 	cout << "Fermat running time: " << time << endl;

// 	return 0;
// }
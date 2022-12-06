#include <iostream>
#include <ctime>
#include "LargeInteger.h"
#include "Randomizer.h"

using namespace std;

LargeInteger gcd(LargeInteger a, LargeInteger b)
{
	if (b == 0)
	{
		return a;
	}

	return gcd(b, a % b);
}

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
		cout << k << "th Try number is: " << a << endl;

		// make sure n>4
		LargeInteger _gcd = gcd(n, a);

		cout << "GCD = " << _gcd << endl;
		if (_gcd != one)
		{
			return false;
		}

		LargeInteger powMod = pow(a, n - 1, n);
		cout << "PowMod = " << powMod << endl;

		if (powMod != one)
		{
			return false;
		}

		k = k - one;
	}
	return true;
}
// check if n is Prime number using Miller-Rabin method
bool millerRabin(LargeInteger n, LargeInteger k)
{
	LargeInteger a = 2 + rand() % (n - 4);
	LargeInteger b = pow(a, n, k);

	if (b == 1 || b == n - 1)
		return true;
	while (k != n - 1)
	{
		b = (b * b) % n;
		k = k * 2;
		if (b == 1)
			return false;
		if (b == n - 1)
			return true;
	}
	return false;
}
bool checkPrimeMillerRabin(LargeInteger n, LargeInteger k)
{
	if (n < 1 || n == 4)
		return false;
	if (n <= 3)
		return true;
	// Find c that n = 2^k * c + 1, r >= 1
	LargeInteger c = n - 1;
	while (c % 2 == 0)
	{
		c = c / 2;
	}
	while (k > 0)
	{
		if (!millerRabin(c, n))
			return false;
	}
	return true;
}

int main()
{
	LargeInteger n(11027), k(1000);

	auto start = clock();
	if (checkPrimeFermat(n, k) == true)
	{
		cout << n << " is a Prime number." << endl;
	}
	else
	{
		cout << n << " is not a Prime number." << endl;
	}
	auto end = clock();
	double time = double(end - start) / CLOCKS_PER_SEC;
	cout << "Fermat running time: " << time << endl;

	// if (checkPrimeMillerRabin(n, k) == true)
	// {
	// 	cout << n << " is a Prime number." << endl;
	// }
	// else
	// 	cout << n << " is not a Prime number." << endl;
	return 0;
}
#include <iostream>
using namespace std;


unsigned int powMod(unsigned int a, unsigned int b, unsigned int n) {
	unsigned int result = 1;
	while (b > 0) {
		if (b & 1) {
			result = (result * a) % n;
		}
		b >>= 1;
		a = (a * a) % n;
	}
	return result;
}

bool millerRabinTest(unsigned int n, unsigned int l)
{
	if (n % 2 == 0) return false;

	unsigned int k = 0, m = n - 1;
	while (m % 2 == 0)
	{
		k += 1;
		m /= 2;
	}

	srand(time(0));
	for (int i = 0; i < l; i++)
	{
		unsigned int a = rand() % (n - 2 - 2 + 1) + 2;
		unsigned int b = powMod(a, m, n);

		if (b == 1) {
			return true;
		}

		for (int i = 0; i < k; i++)
		{
			if (b == n - 1) {
				return true;
			}
			b = (b * b) % n;
		}

	}

	return false;
}


void MillerRabin()
{
	unsigned int n = 0, k = 0;
	cout << "Enter n: ";
	cin >> n;
	cout << "Enter number of loops: ";
	cin >> k;

	cout << n << " is a " << (millerRabinTest(n, k) ? "prime" : "composite") << "\n";
}
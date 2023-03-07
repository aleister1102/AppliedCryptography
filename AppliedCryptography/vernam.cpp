#include <ctime>
#include <iostream>
using namespace std;

string keyGenerate(int size)
{
	string key = "";
	for (int i = 0; i < size; i++)
	{
		char c = rand() % (26) + 97;
		key += c;
	}
	return key;
}

string vernamEncrypt(string plaintext, string key)
{
	string ciphertext = "";

	for (int i = 0; i < plaintext.length(); i++)
	{
		char c = int(plaintext[i]) ^ int(key[i]);
		ciphertext += c;
	}

	return ciphertext;
}

string vernamDecrypt(string ciphertext, string key)
{
	string plaintext = "";

	for (int i = 0; i < ciphertext.length(); i++)
	{
		char c = int(ciphertext[i]) ^ int(key[i]);
		plaintext += c;
	}

	return plaintext;
}

int main()
{
	srand(time(NULL));
	string p = "helloworld", c = "", k = "";
	for (int i = 0; i < 20; i++)
	{
		k = keyGenerate(10);
		c = vernamEncrypt("helloworld", k); cout << "ciphertext[" << i << "]:\t" << c << endl;
		p = vernamEncrypt(c, k); cout << "plaintext[" << i << "]:\t" << p << endl << endl;
	}
	return 0;
}
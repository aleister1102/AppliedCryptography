#include <iostream>
#include "Header.h"
using namespace std;


void main() {
	int option = 0;
	while (true)
	{
		do
		{
			cout << "\nAPPLIED CRYPTOGRAPHY\n";
			cout << "0. Exit\n";
			cout << "1. Vigenere\n";
			cout << "2. Vernam\n";
			cout << "3. DES (IP, FP and PC)\n";
			cout << "4. AES\n";
			cout << "5. Miller-Rabin\n";
			cout << "6. Hash (Padding)\n";
			cout << "Your option is: ";
			cin >> option;
		} while (option < 0 || option > 6);

		switch (option)
		{
		case 0:
			return;
		case 1:
			Vigenere();
			system("pause");
			break;
		case 2:
			Vernam();
			system("pause");

			break;
		case 3:
			DES();
			system("pause");

			break;
		case 4:
			AES();
			system("pause");

			break;
		case 5:
			MillerRabin();
			system("pause");

			break;
		case 6:
			Hash();
			system("pause");

			break;
		default:
			break;
		}
	}
}
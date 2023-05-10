#include <ctime>
#include <iostream>
using namespace std;

/*
Huffman tree:
														1
												0.6(1)		a4(0) 
										0.3(0)		a3(1)        
								0.15(0)		a6(1)               
						0.09(1)		a5(0)                      
				0.05(1)		a1(0)                             
		0.02(0)		a8(1)                                    
 a2(0)		a7(1)                                           

Prefix-code:
| a1  | 10010   |
| a2  | 1001100 |
| a3  | 11      |
| a4  | 0       |
| a5  | 1000    |
| a6  | 101     |
| a7  | 1001101 |
| a8  | 100111  |

Độ dài trung bình:
l(f) = 0.04*5 + 0.01*7 + 0.3*2 + 0.4*1 + 0.06*4 + 0.15*3 + 0.01*7 + 0.03*6 = 2.21

Entropy:
-E = 0.04*log2(0.04) + 0.01 +0.3*log2(0.3) +0.4*log2(0.4) +0.06*log2(0.06) +0.15*log2(0.15) +0.01*log2(0.01) +0.03*log2(0.03) 
- E = -0.1858 - 0.0664 - 0.5211 - 0.5288 - 0.2435 - 0.4105 - 0.0664 - 0.1518 = -2,1743 
=> E = 2.1743
*/

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
	string p = "toanquandatquangthanh", c = "", k = "";
	for (int i = 0; i < 20; i++)
	{
		k = keyGenerate(p.length()); cout << "key[" << i << "]:\t" << k << endl;
		c = vernamEncrypt(p, k); cout << "ciphertext[" << i << "]:\t" << c << endl;
		p = vernamEncrypt(c, k); cout << "plaintext[" << i << "]:\t" << p << endl << endl;
	}
	return 0;
}

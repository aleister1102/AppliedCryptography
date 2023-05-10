#include <iostream>
using namespace std;

struct
{
	short IP[64] = {
		58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6,
		64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17, 9, 1,
		59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5,
		63, 55, 47, 39, 31, 23, 15, 7};

	short FP[64] = {
		40, 8, 48, 16, 56, 24, 64, 32,
		39, 7, 47, 15, 55, 23, 63, 31,
		38, 6, 46, 14, 54, 22, 62, 30,
		37, 5, 45, 13, 53, 21, 61, 29,
		36, 4, 44, 12, 52, 20, 60, 28,
		35, 3, 43, 11, 51, 19, 59, 27,
		34, 2, 42, 10, 50, 18, 58, 26,
		33, 1, 41, 9, 49, 17, 57, 25};

	short PC1[64] = {
		57, 49, 41, 33, 25, 17, 9,
		1, 58, 50, 42, 34, 26, 18,
		10, 2, 59, 51, 43, 35, 27,
		19, 11, 3, 60, 52, 44, 36,
		63, 55, 47, 39, 31, 23, 15,
		7, 62, 54, 46, 38, 30, 22,
		14, 6, 61, 53, 45, 37, 29,
		21, 13, 5, 28, 20, 12, 4};
} TABLES;

int getBit(unsigned char p[], int pos)
{
	int byte = pos / 8;
	int bit = pos % 8;

	int res = (p[byte] >> (7 - bit)) & 1;
	return res;
}

void setBit(unsigned char p[], int pos, int val)
{
	int byte = pos / 8;
	int bit = pos % 8;

	if (val)
		p[byte] |= (1 << (7 - bit));
	else
		p[byte] &= (~(1 << (7 - bit)));
}

void IP(unsigned char p[])
{
	int len = sizeof(*p) * 8;
	unsigned char *res = new unsigned char[len + 1]{0};

	for (int i = 0; i < 64; i++)
	{
		int srcPos = TABLES.IP[i] - 1;
		int srcBit = getBit(p, srcPos);
		setBit(res, i, srcBit);
	}

	memcpy(p, res, len);
}

void FP(unsigned char p[])
{
	int len = sizeof(*p) * 8;
	unsigned char *res = new unsigned char[len + 1]{0};

	for (int i = 0; i < 64; i++)
	{
		int srcPos = TABLES.FP[i] - 1;
		int srcBit = getBit(p, srcPos);
		setBit(res, i, srcBit);
	}

	memcpy(p, res, len);
}

void PC1(unsigned char p[])
{
	int len = sizeof(*p) * 8;
	unsigned char *res = new unsigned char[len + 1]{0};

	for (int i = 0; i < 56; i++)
	{
		int val = TABLES.PC1[i];
		int q = val / 8;
		TABLES.PC1[i] = val - q;
	}

	for (int i = 0; i < 64; i++)
	{
		int srcPos = TABLES.PC1[i] - 1;
		int srcBit = getBit(p, srcPos);
		setBit(res, i, srcBit);
	}

	memcpy(p, res, len);
}

void DES()
{
	unsigned char p[] = "abcdefgh";

	printf("Plain-text:\t\t");
	for (size_t i = 0; i < sizeof(p) - 1; i++)
		printf("%02x ", p[i]);
	printf("\n");

	IP(p);
	printf("IP(Plain-text):\t\t");
	for (size_t i = 0; i < sizeof(p) - 1; i++)
		printf("%02x ", p[i]);
	printf("\n");

	FP(p);
	printf("FP(Plain-text):\t\t");
	for (size_t i = 0; i < sizeof(p) - 1; i++)
		printf("%02x ", p[i]);
	printf("\n");

	PC1(p);
	printf("PC1(Plain-text):\t");
	for (size_t i = 0; i < sizeof(p) - 1; i++)
		printf("%02x ", p[i]);
}

#include <iostream>

typedef unsigned char byte;

short SBOX[256] = {
	//0		1	  2      3     4		5     6      7      8		9     A      B	  C     D      E      F
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

int C[11] = {
	0x00000000,
	0x01000000,
	0x02000000,
	0x04000000,
	0x08000000,
	0x10000000,
	0x20000000,
	0x40000000,
	0x80000000,
	0x1b000000,
	0x36000000,
};

int* toInts(byte bytes[])
{
	int* ints = new int[4] {0};

	for (int i = 0; i < 4; i++)
	{
		ints[i] = bytes[4 * i] << 24 |
			bytes[4 * i + 1] << 16 |
			bytes[4 * i + 2] << 8 |
			bytes[4 * i + 3];
	}

	return ints;
}

byte* toBytes(int ints[4])
{
	byte* bytes = new byte[16]{ 0 };

	for (int i = 0; i < 4; i++)
	{
		bytes[4 * i] = (byte)(ints[i] >> 24);
		bytes[4 * i + 1] = (byte)(ints[i] >> 16);
		bytes[4 * i + 2] = (byte)(ints[i] >> 8);
		bytes[4 * i + 3] = (byte)(ints[i]);
	}

	return bytes;
}

byte sbox(byte b)
{
	return SBOX[b];
}

int sbox(int c)
{
	byte bytes[4] = { 0 }; memcpy(bytes, &c, 4);

	for (int i = 0; i < 4; i++)
		bytes[i] = SBOX[bytes[i]];

	int res = 0; memcpy(&res, bytes, 4);

	return res;
}

int getBit(int p, int pos)
{
	int res = (p >> (31 - pos)) & 1;
	return res;
}

void setBit(int& p, int pos, int val)
{
	if (val)
		p |= (1 << (31 - pos));
	else
		p &= (~(1 << (31 - pos)));
}

int rotate(int n)
{
	for (int i = 0; i < 8; i++)
	{
		int bit = getBit(n, 0);
		n <<= 1;
		setBit(n, 31, bit);
	}

	return n;
}

byte** keyExpand(byte K0[])
{
	byte* K = new byte[16]{ 0 }; memcpy(K, K0, 16);
	byte** subkeys = new byte * [10];

	int* Ki = toInts(K);

	for (int i = 1; i <= 10; i++)
	{
		Ki[0] = Ki[0] ^ sbox(rotate(Ki[3])) ^ C[i];
		Ki[1] = Ki[1] ^ Ki[0];
		Ki[2] = Ki[2] ^ Ki[1];
		Ki[3] = Ki[3] ^ Ki[2];

		subkeys[i - 1] = toBytes(Ki);
	}

	return subkeys;
}

void addRoundKey(byte state[], byte subKey[])
{
	for (int i = 0; i < 16; i++)
		state[i] ^= subKey[i];
}

void subBytes(byte state[])
{
	for (int i = 0; i < 16; i++)
		state[i] = sbox(state[i]);
}

void shiftRow(byte state[])
{
	byte temp[16] = { 0 };
	memcpy(temp, state, 16);

	temp[0] = state[0];
	temp[1] = state[5];
	temp[2] = state[10];
	temp[3] = state[15];
	temp[4] = state[4];
	temp[5] = state[9];
	temp[6] = state[14];
	temp[7] = state[3];
	temp[8] = state[8];
	temp[9] = state[13];
	temp[10] = state[2];
	temp[11] = state[7];
	temp[12] = state[12];
	temp[13] = state[1];
	temp[14] = state[6];
	temp[15] = state[11];

	memcpy(state, temp, 16);
}

// Reference: https://en.wikipedia.org/wiki/Rijndael_MixColumns#Implementation_example
void mixSingleColumn(byte col[])
{
	unsigned char a[4];
	unsigned char b[4];
	unsigned char c;
	unsigned char h;

	for (c = 0; c < 4; c++) {
		a[c] = col[c];

		h = (unsigned char)((signed char)col[c] >> 7);

		b[c] = col[c] << 1;
		b[c] ^= 0x1B & h;
	}
	col[0] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1]; /* 2 * a0 + a3 + a2 + 3 * a1 */
	col[1] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2]; /* 2 * a1 + a0 + a3 + 3 * a2 */
	col[2] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3]; /* 2 * a2 + a1 + a0 + 3 * a3 */
	col[3] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0]; /* 2 * a3 + a2 + a1 + 3 * a0 */
}

void mixColumns(byte state[])
{
	byte* temp = new byte[4];

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			temp[j] = state[4 * i + j];
		}

		mixSingleColumn(temp);

		for (int j = 0; j < 4; ++j)
		{
			state[4 * i + j] = temp[j];
		}
	}
}

void printBlock(byte state[])
{
	for (int i = 0; i < 16; i++)
	{
		printf("%02x ", state[i]);
		//printf("%d ", state[i]);
	}
	printf("\n");
}

void encrypt(byte key[], byte message[])
{
	//? Key expansion: checked
	byte** subKeys = keyExpand(key);
	//for (int i = 0; i < 10; i++)
	//{
	//	printBlock(subKeys[i]);
	//}

	//? Add round key: checked
	addRoundKey(message, key);
	printf("C[0]:\t");
	printBlock(message);

	for (int i = 1; i <= 10; i++)
	{
		//? SBOX: checked
		subBytes(message);
		//printf("After SBOX:\n");
		//printBlock(message);

		//? Shift rows: checked
		shiftRow(message);
		//printf("After shift rows:\n");
		//printBlock(message);

		if (i < 10)
		{
			//? Mix columns : checked
			mixColumns(message);
			//printf("After mix columns:\n");
			//printBlock(message);
		}

		//? Add round key
		addRoundKey(message, subKeys[i - 1]);
		printf("C[%d]:\t", i);
		printBlock(message);
	}
}

int main()
{
	byte K0[] = "Thats my Kung Fu";
	printf("K0:\t");
	printBlock(K0);

	byte M[] = "Two One Nine Two";
	printf("M:\t");
	printBlock(M);

	encrypt(K0, M);

	return 0;
}
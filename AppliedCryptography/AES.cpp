﻿#include <iostream>
#define BLOCK_SIZE 16
#define ROUNDS 10
typedef unsigned char byte;


short SBOX[256] = {
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

short INV_SBOX[256] = {
	0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
	0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
	0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
	0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
	0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
	0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
	0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
	0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
	0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
	0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
	0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
	0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
	0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
	0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
	0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D,
};

int RC[11] = {
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

int getBit(int n, int pos)
{
	int res = (n >> (31 - pos)) & 1;
	return res;
}

void setBit(int& n, int pos, int val)
{
	if (val)
		n |= (1 << (31 - pos));
	else
		n &= (~(1 << (31 - pos)));
}

int rotate(int n, int val)
{
	for (int i = 0; i < val; i++)
	{
		int bit = getBit(n, 0);
		n <<= 1;
		setBit(n, 31, bit);
	}

	return n;
}

int* bytesToFourInts(byte* bytes)
{
	int ints[4]{ 0 };

	for (int i = 0; i < 4; i++)
	{
		ints[i] = bytes[4 * i] << 24 |
			bytes[4 * i + 1] << 16 |
			bytes[4 * i + 2] << 8 |
			bytes[4 * i + 3];
	}

	return ints;
}

byte* fourIntsToBytes(int ints[4])
{
	byte* bytes = new byte[BLOCK_SIZE + 1]{ 0 };

	for (int i = 0; i < 4; i++)
	{
		bytes[4 * i] = (byte)(ints[i] >> 24);
		bytes[4 * i + 1] = (byte)(ints[i] >> 16);
		bytes[4 * i + 2] = (byte)(ints[i] >> 8);
		bytes[4 * i + 3] = (byte)(ints[i]);
	}

	return bytes;
}

void printBlock(byte* state)
{
	size_t size = strlen((char*)state);

	for (size_t i = 0; i < size; i++)
	{
		printf("%02x ", state[i]);
		//printf("%d ", state[i]);
	}

	printf("\n");
}


int sbox(int c, short box[])
{
	byte temp[4]{ 0 }; memcpy(temp, &c, 4);

	for (int i = 0; i < 4; i++)
		temp[i] = box[temp[i]];

	int res = 0; memcpy(&res, temp, 4);

	return res;
}

byte** keyExpand(byte* K)
{
	byte** subkeys = new byte * [10] { 0 };

	int* Ki = bytesToFourInts(K);
	for (int i = 1; i <= ROUNDS; i++)
	{
		Ki[0] = Ki[0] ^ sbox(rotate(Ki[3], 8), SBOX) ^ RC[i];
		Ki[1] = Ki[1] ^ Ki[0];
		Ki[2] = Ki[2] ^ Ki[1];
		Ki[3] = Ki[3] ^ Ki[2];

		subkeys[i - 1] = fourIntsToBytes(Ki);
	}

	return subkeys;
}

byte* XOR(byte* a, byte* b)
{
	byte* res = new byte[BLOCK_SIZE + 1]{ 0 };

	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		res[i] = a[i] ^ b[i];
		//printf("%02x ", res[i]);
	}

	return res;
}

void addRoundKey(byte* state, byte* subKey)
{
	for (int i = 0; i < BLOCK_SIZE; i++)
		state[i] ^= subKey[i];
}

void subBytes(byte* state, short* box)
{
	for (int i = 0; i < 16; i++)
		state[i] = box[state[i]];
}

void shiftRow(byte* state)
{
	byte temp[16]{ 0 }; memcpy(temp, state, 16);

	temp[0] = state[0];  temp[1] = state[5]; temp[2] = state[10]; temp[3] = state[15];
	temp[4] = state[4]; temp[5] = state[9]; temp[6] = state[14]; temp[7] = state[3];
	temp[8] = state[8]; temp[9] = state[13]; temp[10] = state[2]; temp[11] = state[7];
	temp[12] = state[12]; temp[13] = state[1]; temp[14] = state[6]; temp[15] = state[11];

	memcpy(state, temp, 16);
}



//! Reference: https://en.wikipedia.org/wiki/Rijndael_MixColumns#Implementation_example
void mixSingleColumn(byte col[])
{
	byte a[4] = { 0 };
	byte b[4] = { 0 };
	byte c, h;

	for (c = 0; c < 4; c++) {
		a[c] = col[c];

		h = (byte)((signed char)col[c] >> 7);

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
	byte temp[4] = { 0 };

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

byte* encrypt(byte key[], byte message[])
{
	//? Checked
	byte** subKeys = keyExpand(key);
	//for (int i = 0; i < 10; i++)
	//{
	//	printBlock(subKeys[i]);
	//}

	//? Checked
	addRoundKey(message, key);
	//printf("C[0]:\t");
	//printBlock(message);

	for (int i = 1; i <= 10; i++)
	{
		//? Checked
		subBytes(message, SBOX);
		//printf("After SBOX:\n");
		//printBlock(message);

		//? Checked
		shiftRow(message);
		//printf("After shift rows:\n");
		//printBlock(message);

		if (i < 10)
		{
			//? Checked
			mixColumns(message);
			//printf("After mix columns:\n");
			//printBlock(message);
		}

		addRoundKey(message, subKeys[i - 1]);
		//printf("C[%d]:\t", i);
		//printBlock(message);
	}

	return message;
}

void invShiftRow(byte state[])
{
	byte temp[16] = { 0 };
	memcpy(temp, state, 16);

	temp[0] = state[0];
	temp[1] = state[13];
	temp[2] = state[10];
	temp[3] = state[7];
	temp[4] = state[4];
	temp[5] = state[1];
	temp[6] = state[14];
	temp[7] = state[11];
	temp[8] = state[8];
	temp[9] = state[5];
	temp[10] = state[2];
	temp[11] = state[15];
	temp[12] = state[12];
	temp[13] = state[9];
	temp[14] = state[6];
	temp[15] = state[3];

	memcpy(state, temp, 16);
}

//! Reference: https://www.samiam.org/mix-column.html
byte gmul(byte a, byte b) {
	byte p = 0;
	byte counter;
	byte hi_bit_set;

	for (counter = 0; counter < 8; counter++) {
		if ((b & 1) == 1)
			p ^= a;
		hi_bit_set = (a & 0x80);
		a <<= 1;
		if (hi_bit_set == 0x80)
			a ^= 0x1b;
		b >>= 1;
	}
	return p;
}

void invMixSingleColumn(byte col[])
{
	byte a[4] = { 0 };
	byte c;

	for (c = 0; c < 4; c++) {
		a[c] = col[c];
	}

	col[0] = gmul(a[0], 14) ^ gmul(a[3], 9) ^ gmul(a[2], 13) ^ gmul(a[1], 11);
	col[1] = gmul(a[1], 14) ^ gmul(a[0], 9) ^ gmul(a[3], 13) ^ gmul(a[2], 11);
	col[2] = gmul(a[2], 14) ^ gmul(a[1], 9) ^ gmul(a[0], 13) ^ gmul(a[3], 11);
	col[3] = gmul(a[3], 14) ^ gmul(a[2], 9) ^ gmul(a[1], 13) ^ gmul(a[0], 11);
}

void invMixColumns(byte state[])
{
	byte* temp = new byte[4]{ 0 };

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			temp[j] = state[4 * i + j];
		}

		invMixSingleColumn(temp);

		for (int j = 0; j < 4; ++j)
		{
			state[4 * i + j] = temp[j];
		}
	}
}

byte* decrypt(byte key[], byte message[])
{
	//? Key expansion: checked
	byte** subKeys = keyExpand(key);

	//? Checked
	addRoundKey(message, subKeys[9]);
	//printf("C[0]:\t");
	//printBlock(message);

	for (int i = 9; i >= 1; i--)
	{
		//? Checked
		invShiftRow(message);
		//printf("After inverse shift rows:\n");
		//printBlock(message);

		//? Checked
		subBytes(message, INV_SBOX);
		//printf("After inverse SBOX:\n");
		//printBlock(message);

		//? Checked
		addRoundKey(message, subKeys[i - 1]);
		//printf("After add round key:\n");
		//printBlock(message);

		invMixColumns(message);
		//printf("After mix columns, C[%d]:\n", i);
		//printBlock(message);
	}

	invShiftRow(message);
	subBytes(message, INV_SBOX);
	addRoundKey(message, key);

	return message;
}

byte** parseBlocks(byte M[], int n)
{
	byte** blocks = new byte * [n];

	for (int i = 0; i < n; i++)
	{
		blocks[i] = new byte[17]{ 0 };
		memcpy(blocks[i], &M[16 * i], 16);
	}

	return blocks;
}

byte* CBCRandomEnc(byte M[], byte K[])
{
	size_t size = strlen((char*)M);
	if (size % 16 != 0 || size == 0) return NULL;

	int n = size / 16;

	// Tách mảng đầu vào thành các blocks 16 byte
	byte** blocks = parseBlocks(M, n);

	byte* C = new byte[size + 1]{ 0 };
	byte* Ci = new byte[17]{ 0 };
	for (int i = 0; i < n; i++)
	{
		memcpy(Ci, encrypt(K, XOR(Ci, blocks[i])), 16);
		memcpy(C + 16 * i, Ci, 16);
	}

	return C;
}

byte* CBCRandomDec(byte C[], byte K[])
{
	size_t size = strlen((char*)C);
	if (size % 16 != 0 || size == 0) return NULL;

	int n = size / 16;

	// Tách mảng đầu vào thành các blocks 16 byte
	byte** blocks = parseBlocks(C, n);

	byte* M = new byte[size + 1]{ 0 };

	byte* Mi = new byte[17]{ 0 };
	byte* C0 = new byte[17]{ 0 };
	byte* Ci = new byte[17]{ 0 };
	for (int i = 0; i < n; i++)
	{
		byte* C0 = Ci; Ci = blocks[i];
		memcpy(Mi, XOR(decrypt(K, Ci), C0), 16);
		memcpy(M + 16 * i, Mi, 16);
	}

	return M;
}

int main()
{
	byte K[] = "Thats my Kung Fu";

	byte M[] = "Two One Nine Two";
	printf("Message:\t");
	printBlock(M);

	//byte* encrypted = encrypt(K, M);
	//printf("C:\t");
	//printBlock(encrypted);

	//byte* decrypted = decrypt(K, encrypted);
	//printf("M:\t");
	//printBlock(decrypted);

	byte* E = CBCRandomEnc(M, K);
	printf("Encrypted:\t");
	printBlock(E);

	byte* D = CBCRandomDec(E, K);
	printf("Decrypted:\t");
	printBlock(D);

	return 0;
}
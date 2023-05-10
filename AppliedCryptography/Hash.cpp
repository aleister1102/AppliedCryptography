#include <iostream>
#define BLOCK_SIZE 16
using namespace std;

string pkcs7(string m, int block_size, int m_len) {
	int pad_len = block_size - (m_len % block_size);
	if (pad_len == 0) {
		pad_len = block_size;
	}
	string res = m;
	res.resize(m_len + pad_len, (char)pad_len);
	return res;
}


void main() {
    string m[] = {
        "0", "01", "012", "0123", "01234", "012345", "0123456", "01234567", "012345678", "0123456789", "0123456789a", "0123456789ab", "0123456789abc", "0123456789abcd", "0123456789abcde", "quantoanthanhquangdat"
    };

    for (int i = 15; i >= 0; i--) {
        string message = m[i];
        string padded_message = pkcs7(message, BLOCK_SIZE, message.length());

        for (size_t j = 0; j < padded_message.length(); j++) {
            printf("%02x ", (unsigned char)padded_message[j]);
        }
        cout << endl;
    }
}

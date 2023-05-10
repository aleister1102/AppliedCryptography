#include "iostream"
using namespace std;

string vigenere_cipher_enc(string key, string message)
{
    string enc = "";
    int k = 0, m = key.length();

    for (int i = 0; i < message.length(); i++)
    {
        enc += ((message[i] - 97) + key[(k++) % m] - 97) % 26 + 97;
    }

    return enc;
}

string vigenere_cipher_dec(string key, string encrypted_message)
{
    string text = "";
    int k = 0, m = key.length();

    for (int i = 0; i < encrypted_message.length(); i++)
    {
        int c = ((encrypted_message[i]) - key[(k++) % m]);
        c = c < 0 ? c + 26 : c;
        text += c + 97;
    }
    return text;
}

void Vigenere()
{
    string m = "thiscryptosystemisnotsecure", k = "cipher", e_m ="";
    cout << "original message: " << m << endl;
    e_m = vigenere_cipher_enc(k, m);
    cout << "encrypted message: " << e_m << endl;
    m = vigenere_cipher_dec(k, e_m);
    cout << "decrypted message: " << m << endl;
}
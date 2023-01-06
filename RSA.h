#pragma once
#include "LargeInteger.h"
#include "Randomizer.h"
#include <utility>

using namespace std;

typedef pair<LargeInteger, LargeInteger> Key_Pair;

// generate secrect pair of p and q
void generateSecrectPair(LargeInteger &p, LargeInteger &q, int size = 512);

// calc get publickey n and e
Key_Pair generatePublicKey(LargeInteger &p, LargeInteger &q);

// extended Euclidean GCD
LargeInteger gcdExtend(LargeInteger a, LargeInteger b, LargeInteger &x, LargeInteger &y);

// calculate private key
LargeInteger calculatePrivateKey(LargeInteger &e, LargeInteger &phi);

// encrypt message
string encryptMessage(string plaintext, Key_Pair public_key);

// decrypt message
string decryptMessage(string ciphertext, Key_Pair public_key, LargeInteger private_key);

// encrypt a file
void encryptFile(string plain_file_path, Key_Pair public_key, string encrypted_file_path);

// decrypt a file
void decryptFile(string encrypted_file_path, string plain_file_path, Key_Pair public_key, LargeInteger private_key);

// check Prime using Fermat theory
bool checkPrimeFermat(LargeInteger n, int k = 12);

// bruteforce check prime
bool isPrime(LargeInteger n);

void menu();
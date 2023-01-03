#include "LargeInteger.h"
#include "Randomizer.h"
#include "RSA.h"

void generateSecrectPair(LargeInteger &p, LargeInteger &q, int size)
{
    if (size == 2048)
    {
        p = Randomizer::randomizer()->next();
        q = Randomizer::randomizer()->next();

        p = p * p;
        q = q * q;
    }
    else
    {
        LargeInteger upper_limit;

        if (size == 512)
        {
            upper_limit = constant::quarterMaxLargeInt;
        }
        else if (size == 1024)
        {
            upper_limit = constant::halfMaxLargeInt;
        }

        LargeInteger lower_limit = upper_limit.divide_by_2();

        p = Randomizer::randomizer()->next(lower_limit, upper_limit);
        q = Randomizer::randomizer()->next(lower_limit, upper_limit);

        p = p * p;
        q = p * p;
    }

    cout << "DEBUG:\np = " << p << endl << "q = " << q << endl;

    if (!p.isEven()) {
        p = p + constant::one;
    }
    if (!q.isEven()) {
        q = q + constant::one;
    }

    while (!isPrime(p)) {
        p = p + constant::two;
    }
    while (!isPrime(q)) {
        q = q + constant::two;
    }
}

Key_Pair generatePublicKey(LargeInteger &p, LargeInteger &q) {
    LargeInteger n = p * q;

    LargeInteger e = pow(constant::two, n % 100);
    LargeInteger phi = (p - constant::one) * (q - constant::one);

    while (gcd(e, phi) != 1) {
        e = e + constant::one;
    }

    auto result = make_pair(e, n);
    return result;
}

LargeInteger gcdExtend(LargeInteger a, LargeInteger b, LargeInteger &x, LargeInteger &y)
{
    if (b == 0)
    {
        x = constant::one;
        y = constant::zero;
        return a;
    }

    LargeInteger x1, y1;
    LargeInteger d = gcdExtend(b, a % b, x1, y1);

    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

LargeInteger calculatePrivateKey(LargeInteger &e, LargeInteger &phi)
{
    LargeInteger x, y;
    gcdExtend(e, phi, x, y);
    LargeInteger D = x % phi;

    return D;
}

LargeInteger encode(string str) {
    string joined_str;
    string num_part;
    for (char &character : str) {
        int num = int(character);
        if (num < 100) {
            num_part = '0' + to_string(num);
        }
        else 
            num_part = to_string(num);

        joined_str += num_part;
    }

    LargeInteger result(joined_str);
    return result;
}

string decode(LargeInteger num) {
    string num_str = num.to_str();
    constexpr int chunk_size = 3;

    string decoded_str;

    for (int i = 0; i < num_str.length(); i+= chunk_size) {
        string num_chunks = num_str.substr(i, chunk_size);
        char ch = char(stoi(num_chunks));

        decoded_str += ch;
    }

    return decoded_str;
}

LargeInteger encryptMessage(string plaintext, Key_Pair public_key) {
    LargeInteger encoded_plaintext = encode(plaintext);

    LargeInteger ciphertext = pow(encoded_plaintext, public_key.first, public_key.second);

    return ciphertext;
}

string decryptMessage(LargeInteger ciphertext, Key_Pair public_key, LargeInteger private_key) {
    LargeInteger encoded_plaintext  = pow(ciphertext, private_key, public_key.second);

    string plaintext = decode(encoded_plaintext);
    return plaintext;
}

void encryptFile(string plain_file_path, Key_Pair public_key, string encrypted_file_path) {
    fstream plain_file(plain_file_path, ios::in);
    fstream encrypted_file(encrypted_file_path, ios::out);

    string plaintext;
    getline(plain_file, plaintext);
    plain_file.close();

    LargeInteger ciphertext = encryptMessage(plaintext, public_key);
    encrypted_file << ciphertext;
    encrypted_file.close();
}

void decryptFile(string encrypted_file_path, string plain_file_path, Key_Pair public_key, LargeInteger private_key) {
    fstream plain_file(plain_file_path, ios::in);
    fstream encrypted_file(encrypted_file_path, ios::out);

    string ciphertext;
    getline(encrypted_file, ciphertext);
    encrypted_file.close();

    string plaintext = decryptMessage(ciphertext, public_key, private_key);
    plain_file << plaintext;
    plain_file.close();
}

int info() {
    system("clear");
    cout << "1. Encrypt a file" << endl;
    cout << "2. Decrypt a file" << endl;
    cout << "3. Encrypt a message" << endl;
    cout << "4. Decrypt a ciphertext" << endl;
    cout << "5. Change your private key" << endl;
    cout << "0. Quit" << endl;
    cout << "------------------" << endl;

    return 5;
}

void menu() {
    int choose;
    string key_choose;
    LargeInteger private_key, p(0), q(0);
    Key_Pair public_key;

    cout << "Using your private key or let system decide?[user/sys]: " << endl;
    do {
        cout << ">>>>>>> ";
        cin >> key_choose;
    } while (key_choose != "sys" && key_choose != "user");

    if (key_choose == "sys") {
        cout << "System generating..." << endl;
        generateSecrectPair(p, q);
        cout << "DEBUG: Your secret pair is: " << p << " --and-- " << q << endl;
    }
    else {
        cout << "Enter your private secrect prime numbers p and q:" << endl;
        do {
            cout << "p = ";
            cin >> p;               
        } while (!isPrime(p));

        do {
            cout << "q = ";
            cin >> q;               
        } while (!isPrime(q));
    }

    public_key = generatePublicKey(p, q);
    LargeInteger phi = (p - constant::one)*(q - constant::one);
    private_key = calculatePrivateKey(public_key.first, phi);

    do {
        int n_choices = info();
        do {
            cout << ">>>>>>> ";
            cin >> choose;
        } while (choose > n_choices);

        if (choose == 1) {
        }
        else if (choose == 2) {

        }
        else if (choose == 3) {

        }
        else if (choose == 4) {

        }
        else if (choose == 5) {

        }

    }
    while (choose != 0);

}
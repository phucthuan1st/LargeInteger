#include "LargeInteger.h"
#include "Randomizer.h"
#include "RSA.h"

// using little Fermat to check if n is Prime number method with k tries
bool checkPrimeFermat(LargeInteger n, int k)
{
    if (n < 1 || n == 4)
        return false;

    if (n <= 3)
        return true;

    LargeInteger a;

    for (int i = 0; i < k/4; i++) {
        a = Randomizer::randomizer()->next(2, 100);
        if (gcd(n, a) != constant::one) 
            return false;

        if (pow(a, n - 1, n) != constant::one) 
            return false;
    }

    for (int i = 0; i < k/4; i++) {
        a = Randomizer::randomizer()->next(100, n / 1024);
        if (gcd(n, a) != constant::one) 
            return false;

        if (pow(a, n - 1, n) != constant::one) 
            return false;
    }

    for (int i = 0; i < k/4; i++) {
        a = Randomizer::randomizer()->next(n / 1024, n / 512);
        if (gcd(n, a) != constant::one) 
            return false;

        if (pow(a, n - 1, n) != constant::one) 
            return false;
    }

    for (int i = 0; i < k/4; i++) {
        a = Randomizer::randomizer()->next(n / 512, sqrt(n));
        if (gcd(n, a) != constant::one) 
            return false;

        if (pow(a, n - 1, n) != constant::one) 
            return false;
    }

    return true;
}

bool isPrime(LargeInteger n) {
    if (n < constant::two) {
        return false;
    }

    LargeInteger squareRoot = sqrt(n);

    for (LargeInteger i = constant::two; i < squareRoot; i = i + constant::one) {
        if (n % i == constant::zero) {
            return false;
        }
    }

    return true;
}

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

        LargeInteger lower_limit = upper_limit / 2;

        p = Randomizer::randomizer()->next(lower_limit, upper_limit);
        q = Randomizer::randomizer()->next(lower_limit, upper_limit);

        p = p * p;
        q = p * p;
    }

    if (p.isEven()) {
        p = p + constant::one;
    }
    if (q.isEven()) {
        q = q + constant::one;
    }

    while (!checkPrimeFermat(p)) {
        p = p + constant::two;
        cout << "DEBUG: p = " << p << endl;
    }
    while (!checkPrimeFermat(q)) {
        q = q + constant::two;
        cout << "DEBUG: q = " << q << endl;
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

void setUpNewKey(LargeInteger &p, LargeInteger &q, LargeInteger &private_key, Key_Pair &public_key) {
    string key_choose;
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
}

void menu() {
    int choose;
    LargeInteger private_key, p(0), q(0);
    Key_Pair public_key;

    setUpNewKey(p, q, private_key, public_key);

    do {
        int n_choices = info();
        do {
            cout << ">>>>>>> ";
            cin >> choose;
        } while (choose > n_choices);

        if (choose == 1) {
            cout << "--------------- ENCRYPT YOUR FILE ---------------" << endl;
            string plain_file_path = "";
            string encrypted_file_path = "";
            do {
                cout << "Enter path to your plaintext file: " << endl;
                getline(cin, plain_file_path);
            } while (plain_file_path.length() <= 0);

            do {
                cout << "Enter path (or name) to save your encrypted file: " << endl;
                getline(cin, encrypted_file_path);
            } while (encrypted_file_path.length() <= 0);

            encryptFile(plain_file_path, public_key, encrypted_file_path);
        }
        else if (choose == 2) {
            cout << "--------------- DECRYPT YOUR FILE ---------------" << endl;
            string plain_file_path = "";
            string encrypted_file_path = "";

            do {
                cout << "Enter path to your encrypted file: " << endl;
                getline(cin, encrypted_file_path);
            } while (encrypted_file_path.length() <= 0);

            do {
                cout << "Enter path (or name) to save your plaintext file: " << endl;
                getline(cin, plain_file_path);
            } while (plain_file_path.length() <= 0);

            decryptFile(plain_file_path, encrypted_file_path, public_key, private_key);
        }
        else if (choose == 3) {
            cout << "--------------- ENCRYPT A MESSAGE ---------------" << endl;
            string message = "";
            do {
                cout << "Enter your message: " << endl;
                getline(cin, message);
            } while (message.length() <= 0);

            LargeInteger ciphertext = encryptMessage(message, public_key);
            cout << "Your cipher text is: " << ciphertext << endl;            
        }
        else if (choose == 4) {
            cout << "--------------- DECRYPT A MESSAGE ---------------" << endl;
            bool isValidCipherText = false;
            LargeInteger ciphertext;
            do {
                try {
                    cout << "Enter a ciphertext: " << endl;
                    cin >> ciphertext;
                    isValidCipherText = true;
                }
                catch (const char* error) {
                    cout << "Error: " << error << endl;
                }
            } while (!isValidCipherText);

            string plaintext = decryptMessage(ciphertext, public_key, private_key);
            cout << "Your plaintext is: " << plaintext << endl;
        }
        else if (choose == 5) {
            setUpNewKey(p, q, private_key, public_key);
        }

        cout << "Press Enter to continue..." << endl;
        getchar();

    }
    while (choose != 0);

}
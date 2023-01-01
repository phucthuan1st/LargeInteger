#pragma once
#define f(A, B, x) (A - B * x)
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

// order of '0'
#define ZERO 48

using namespace std;

class LargeInteger
{
private:
    vector<char> digits;
    void cleanup();

public:
    LargeInteger();
    LargeInteger(long long);
    LargeInteger(const LargeInteger &other);
    LargeInteger(string);
    LargeInteger &operator=(LargeInteger other);

    //---------------------- UTILITIES ----------------------//
    // parse a string to large integer
    void parse(string &);

    // get string representation of your large integer
    string to_str();

    // get number of digit of your number
    int digitNum() { return this->digits.size(); }

    // check if your number is NULL
    bool isNull() { return this->digits.size() == 0; }

    // is Even
    bool isEven() { return (this->digits.at(0) - ZERO) % 2 == 0; }

    // is Negative
    bool isNegative() { return (this->digits.at(this->digits.size() - 1)) == '-'; }

    // multiply your number by 10^n
    LargeInteger multiply_pow_10(unsigned long long n);

    // get abs of the number
    LargeInteger abs();

    // get negative form of the number
    LargeInteger negative();

    LargeInteger divide_by_2();
    LargeInteger divide_by_10();
    int last_digit();

    // get binary string representation
    string binary();

    //---------------------- INPUT & OUTPUT ----------------------//

    friend istream &operator>>(istream &, LargeInteger &);
    friend ostream &operator<<(ostream &, LargeInteger);

    //---------------------- COMPARISION ----------------------//

    friend bool operator<(LargeInteger first, LargeInteger second);
    friend bool operator>(LargeInteger first, LargeInteger second);
    friend bool operator>=(LargeInteger first, LargeInteger second);
    friend bool operator<=(LargeInteger first, LargeInteger second);
    friend bool operator==(LargeInteger first, LargeInteger second);
    friend bool operator!=(LargeInteger first, LargeInteger second);

    friend bool operator<(LargeInteger first, unsigned long long second);
    friend bool operator>(LargeInteger first, unsigned long long second);
    friend bool operator>=(LargeInteger first, unsigned long long second);
    friend bool operator<=(LargeInteger first, unsigned long long second);
    friend bool operator==(LargeInteger first, unsigned long long second);
    friend bool operator!=(LargeInteger first, unsigned long long second);

    friend bool operator<(unsigned long long first, LargeInteger second);
    friend bool operator>(unsigned long long first, LargeInteger second);
    friend bool operator>=(unsigned long long first, LargeInteger second);
    friend bool operator<=(unsigned long long first, LargeInteger second);
    friend bool operator==(unsigned long long first, LargeInteger second);
    friend bool operator!=(unsigned long long first, LargeInteger second);

    //---------------------- ARITHMETIC ----------------------//

    friend LargeInteger operator+(LargeInteger first, LargeInteger second);
    friend LargeInteger operator-(LargeInteger first, LargeInteger second);
    friend LargeInteger operator*(LargeInteger first, LargeInteger second);
    friend LargeInteger operator/(LargeInteger dividend, LargeInteger divisor);
    friend LargeInteger operator%(LargeInteger dividend, LargeInteger divisor);

    friend LargeInteger operator+(LargeInteger first, unsigned long long second);
    friend LargeInteger operator-(LargeInteger first, unsigned long long second);
    friend LargeInteger operator*(LargeInteger first, unsigned long long second);
    friend LargeInteger operator/(LargeInteger dividend, unsigned long long second);
    friend LargeInteger operator%(LargeInteger dividend, unsigned long long second);

    friend LargeInteger operator+(unsigned long long first, LargeInteger second);
    friend LargeInteger operator-(unsigned long long first, LargeInteger second);
    friend LargeInteger operator*(unsigned long long first, LargeInteger second);
    friend LargeInteger operator/(unsigned long long dividend, LargeInteger divisor);
    friend LargeInteger operator%(unsigned long long dividend, LargeInteger divisor);
};

LargeInteger pow(LargeInteger base, LargeInteger expo);
LargeInteger pow(LargeInteger base, LargeInteger expo, LargeInteger mod);
LargeInteger multiply(LargeInteger x, LargeInteger y);
LargeInteger multiply(LargeInteger first, LargeInteger second, LargeInteger mod);
LargeInteger gcd(LargeInteger a, LargeInteger b);
string BinaryAdd(string first, string second);
bool checkPrimeFermat(LargeInteger n, int k = 5);
LargeInteger bin2dec(string bitset);

// ------------------------- FREQUENTLY USED CONSTANT --------------------------
namespace constant
{
    const string increment = "3407892909257402499820584612747936582059323561443721764030073546976801874298166903427690318581864860508537538281194656946439";
    const string multiplying = "584612747936582059239337723561";

    // 2^256 - 1
    const string quarter_max_LargeInt = "115792089237316195423570985008687907853269984665640564039457584007913129639935";
    // 2^512 - 1
    const string half_max_LargeInt = "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084095";
    // 2^1024 - 1
    const string max_LargeInt = "179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137215";
    // 2^1023 + 1
    const string sub_max_LargeInt = "89884656743115795386465259539451236680898848947115328636715040578866337902750481566354238661203768010560056939935696678829394884407208311246423715319737062188883946712432742638151109800623047059726541476042502884419075341171231440736956555270413618581675255342293149119973622969239858152417678164812112068609";

    const LargeInteger quarterMaxLargeInt(quarter_max_LargeInt);
    const LargeInteger halfMaxLargeInt(half_max_LargeInt);
    const LargeInteger subMaxLargeInt(sub_max_LargeInt);
    const LargeInteger maxLargeInt(max_LargeInt);
    const LargeInteger A(multiplying);
    const LargeInteger B(increment);
    const LargeInteger diff = maxLargeInt - subMaxLargeInt + 1;

    const LargeInteger zero("0");
    const LargeInteger one("1");
    const LargeInteger two("2");
    const LargeInteger ten("2");
}
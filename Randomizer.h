#pragma once
#include "LargeInteger.h"
#include <ctime>

#define A LargeInteger(816744073709551516)
#define B LargeInteger(515161867449551561)

class Randomizer
{
private:
    LargeInteger seed;

    Randomizer()
    {
        seed = (LargeInteger(time(NULL)) + B) * A;
    }

    static Randomizer *instance;

public:
    LargeInteger next()
    {
        cout << "Current seed: " << seed << endl;
        LargeInteger temp = this->seed;
        this->seed = (this->seed + B) % LONG_LONG_MAX * A;
        return temp;
    }

    LargeInteger next(LargeInteger min, LargeInteger max)
    {
        return min + next() % (max - min + LargeInteger(1));
    }

    LargeInteger next(unsigned long long min, unsigned long long max)
    {
        return next(LargeInteger(min), LargeInteger(max));
    }

    static Randomizer *randomizer()
    {
        if (instance == NULL)
        {
            instance = new Randomizer();
        }

        return instance;
    }
};
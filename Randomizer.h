#pragma once
#include "LargeInteger.h"
#include <ctime>

class Randomizer
{
private:
    LargeInteger seed;

    Randomizer()
    {
        seed = (LargeInteger(time(NULL)) * constant::A + constant::B) % constant::LONG_LONG_MAX;
    }

    static Randomizer *instance;

public:
    LargeInteger next()
    {
        LargeInteger temp = this->seed;
        this->seed = (this->seed * constant::multipliment + constant::increment) % constant::LONG_LONG_MAX;
        return temp;
    }

    LargeInteger next(LargeInteger min, LargeInteger max)
    {
        return min + next() % (max - min + 1);
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
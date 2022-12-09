#pragma once
#include "LargeInteger.h"
#include <ctime>

class Randomizer
{
private:
    LargeInteger seed;

    Randomizer()
    {
        seed = LargeInteger(time(0) + clock());
        seed = constant::sub_max_LargeInt + multiply(seed + constant::B, constant::A, constant::diff);
    }

    static Randomizer *instance;

public:
    LargeInteger next()
    {
        LargeInteger temp = this->seed;
        this->seed = constant::sub_max_LargeInt + multiply(seed + constant::B, constant::A, constant::diff);
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
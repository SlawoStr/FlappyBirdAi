#pragma once
#include <random>

class RandomNumberGenerator
{
private:
    std::random_device rd;
    std::mt19937 generator;
    std::uniform_int_distribution<>intDistr;
public:
    RandomNumberGenerator(int intMin = 0, int intMax = 0) : generator(rd()), intDistr(intMin, intMax) {}
    int getRandomInt() { return intDistr(generator); }
};
#include <iostream>

inline long singleTransform(long value, long subjectNum, long divisor)
{
    value *= subjectNum;
    value %= divisor;
    return value;
}

long encrypt(long subjectNum, long loopSize, long divisor)
{
    long value = 1;
    for (auto i = 0; i < loopSize; ++i)
    {
        value = singleTransform(value, subjectNum, divisor);
    }
    return value;
}

int main()
{
    constexpr long publicKey1 = 13316116;
    constexpr long publicKey2 = 13651422;
    constexpr long subjectNumber = 7;
    constexpr long divisor = 20201227;
    auto loopSize = 0;
    long value = 1;
    while (value != publicKey1)
    {
        ++loopSize;
        value = singleTransform(value, subjectNumber, divisor);
    }
    auto encryptionKey = encrypt(publicKey2, loopSize, divisor);
    std::cout << "Part 1: " << encryptionKey << std::endl;
    return 0;
}
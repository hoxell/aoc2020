#include <algorithm>
#include <bitset>
#include <cmath>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>

#include "ioutils.hpp"

constexpr unsigned int WORDSIZE = 36;
int main()
{
    auto lines = aoc::readInput("input.txt");
    std::regex maskRegex("^(?:mask = )([0X1]+)");
    std::regex instructionRegex(R"(^mem\[(\d+)\] = (\d+)$)");
    std::smatch matches;

    std::unordered_map<unsigned long long, unsigned long long> memory;
    std::unordered_map<unsigned long long, unsigned long long> memory2;

    unsigned long long address;
    unsigned long long value;
    std::string mask;
    std::bitset<WORDSIZE> bitValue;
    std::bitset<WORDSIZE> partialAddress;
    std::bitset<WORDSIZE> targetAddress; // Target address for part 2

    for (auto instruction : lines)
    {
        if (std::regex_search(instruction, matches, maskRegex))
        {
            mask = matches[1].str();
            continue;
        }
        else if (std::regex_search(instruction, matches, instructionRegex))
        {
            address = std::strtoull(matches[1].str().c_str(), nullptr, 0);
            targetAddress = address;
            value = std::strtoull(matches[2].str().c_str(), nullptr, 0);
            bitValue = value;
        }

        int index = 0;
        for (auto it = mask.crbegin(); it != mask.crend(); ++it)
        {
            switch (*it)
            {
            case '1':
                bitValue.set(index);
                targetAddress.set(index);
                break;
            case '0':
                bitValue.reset(index);
                break;
            default:
                break;
            }
            ++index;
        }
        memory[address] = bitValue.to_ullong();

        // Get number of addresses for part 2
        auto numX = std::count(mask.cbegin(), mask.cend(), 'X');
        auto numAddresses = static_cast<int>(std::pow(2, numX) + 0.5);
        std::vector<size_t> indexes;
        size_t xIndex = mask.find('X');
        while (xIndex != std::string::npos)
        {
            indexes.push_back(mask.length() - 1 - xIndex);
            xIndex = mask.find('X', xIndex + 1);
        }

        for (unsigned int i = 0; i < numAddresses; ++i)
        {
            partialAddress = i;
            for (auto it = indexes.crbegin(); it != indexes.crend(); ++it)
            {
                targetAddress[*it] = partialAddress[it - indexes.crbegin()];
            }
            memory2[targetAddress.to_ullong()] = value;
        }
    }

    unsigned long long sum{0};
    for (auto mem : memory)
    {
        sum += mem.second;
    }
    std::cout << "Part 1: " << sum << std::endl;

    sum = 0;
    for (auto mem : memory2)
    {
        sum += mem.second;
    }
    std::cout << "Part 2: " << sum << std::endl;

    return 0;
}

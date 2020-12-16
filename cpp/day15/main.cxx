#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>

using std::chrono::high_resolution_clock;

/**
 * @brief Play the elves' game for \p nIterations and 
 * return the value of the last round
 * @param[in] nIterations The number of times to play the game
 * 
 * @return Value of last round
 */
template <typename T>
T play(const std::vector<T> inputs, const uint nIterations)
{
    // Would prefer unordered_map, but a simple vector
    // is faster
    std::vector<T> lastSpoken(nIterations, 0);
    for (auto it = inputs.cbegin(); it != inputs.cend() - 1; ++it)
    {
        lastSpoken[*it] = it - inputs.begin() + 1;
    }
    auto prev = inputs.back();
    T num{0};
    for (size_t i = inputs.size(); i < nIterations; ++i)
    {
        num = 0;
        if (lastSpoken[prev] > 0)
        {
            num = i - lastSpoken[prev];
        }
        lastSpoken[prev] = i;
        prev = num;
    }
    return prev;
}

int main()
{
    std::vector inputs{2, 0, 6, 12, 1, 3};

    auto startTime = high_resolution_clock::now();
    auto part1 = play(inputs, 2020);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(high_resolution_clock::now() - startTime).count();
    std::cout << std::setw(10) << std::left << part1 << " Time: " << duration << "microseconds" << std::endl;

    startTime = high_resolution_clock::now();
    auto part2 = play(inputs, 3e7);
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(high_resolution_clock::now() - startTime).count();
    std::cout << std::setw(10) << std::left << part2 << " Time: " << duration << "ms" << std::endl;

    return 0;
}

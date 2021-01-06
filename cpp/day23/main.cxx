#include <algorithm>
#include <array>
#include <iostream>
#include <unordered_map>

constexpr int N_CUPS_EXTRACT = 3;
using State = std::unordered_map<uint32_t, uint32_t>;
using Buffer = std::array<State::mapped_type, N_CUPS_EXTRACT>;

void play(State &state, int nIterations, State::key_type start)
{
    auto current = start;
    const auto nCups = state.size();
    auto toExtract = state[start];
    Buffer extracted{};
    for (auto i = 0; i < nIterations; ++i)
    {
        auto first = state[current];
        extracted[0] = first;
        for (auto j = 1; j < N_CUPS_EXTRACT; ++j)
        {
            extracted[j] = state[extracted[j - 1]];
        }
        auto lastExtracted = extracted.back();
        auto destination = current - 1 == 0 ? nCups : current - 1;
        while (std::find(extracted.cbegin(), extracted.cend(), destination) != extracted.cend())
        {
            destination = destination - 1 == 0 ? nCups : destination - 1;
        }

        // Can save some time by accessing once and keep the reference
        auto &afterLast = state[lastExtracted];
        state[current] = afterLast;
        current = afterLast;
        auto &afterDestination = state[destination];
        afterLast = afterDestination;
        afterDestination = first;
    }
}

int main()
{
    // State is a map keeping the id of the cup immediately clockwise of the key.
    // Similar to a linked list but with constant access time.
    const State input{{5, 2}, {2, 3}, {3, 7}, {7, 6}, {6, 4}, {4, 8}, {8, 1}, {1, 9}};
    constexpr auto startCup = 5;
    constexpr auto endCup = 9;
    State state{input};
    state[endCup] = startCup;
    play(state, 100, startCup);
    auto key = 1;
    std::cout << "Part 1: ";
    for (auto i = 0; i < state.size() - 1; ++i)
    {
        std::cout << state[key];
        key = state[key];
    }
    std::cout << std::endl;

    // Part 2
    constexpr auto nCups = 1'000'000;
    constexpr auto nRounds = 10'000'000;
    State statePart2{input};
    statePart2[endCup] = statePart2.size() + 2;
    for (auto i = statePart2.size() + 1; i < nCups; ++i)
    {
        statePart2[i] = i + 1;
    }
    statePart2[nCups] = startCup;
    play(statePart2, nRounds, startCup);
    auto next1 = statePart2[1];
    auto next2 = statePart2[next1];
    std::cout << "Part 2: " << static_cast<uint64_t>(next1) * static_cast<uint64_t>(next2) << std::endl;

    return 0;
}

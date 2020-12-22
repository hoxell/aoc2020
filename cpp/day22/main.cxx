#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <deque>

/**
 * @brief Generate a string uniquely representing the state
 */
template <typename T>
std::string compute_state(std::deque<T> player1, std::deque<T> player2)
{
    std::stringstream sstream;
    for (auto card : player1)
    {
        sstream << card << ",";
    }
    sstream << ";";
    for (auto card : player2)
    {
        sstream << card << ",";
    }
    return sstream.str();
}

/**
 * @brief Play game
 * @return true if player 1 is winner of subgame, false otherwise
 */
template <typename T>
bool subgame(std::deque<T> &player1, std::deque<T> &player2)
{
    std::set<std::string> previousStates{};

    while (!(player1.empty() || player2.empty()))
    {
        auto stateId = compute_state(player1, player2);
        if (previousStates.count(stateId))
        {
            return true;
        }
        previousStates.insert(stateId);

        auto cardPlayer1 = player1.front();
        player1.pop_front();
        auto cardPlayer2 = player2.front();
        player2.pop_front();

        bool player1Winner;
        if (cardPlayer1 <= player1.size() && cardPlayer2 <= player2.size())
        {
            std::deque<T> subsetPlayer1(player1.cbegin(), player1.cbegin() + cardPlayer1);
            std::deque<T> subsetPlayer2(player2.cbegin(), player2.cbegin() + cardPlayer2);
            player1Winner = subgame(subsetPlayer1, subsetPlayer2);
        }
        else
        {
            player1Winner = cardPlayer1 > cardPlayer2;
        }

        if (player1Winner)
        {
            player1.push_back(cardPlayer1);
            player1.push_back(cardPlayer2);
        }
        else
        {
            player2.push_back(cardPlayer2);
            player2.push_back(cardPlayer1);
        }
    }
    return !player1.empty();
}

template <typename T>
int compute_score(std::deque<T> winner)
{
    int factor = winner.size();
    int score{0};
    while (!winner.empty())
    {
        score += factor * winner.front();
        winner.pop_front();
        --factor;
    }
    return score;
}
int main()
{
    std::deque player1{14, 23, 6, 16, 46, 24, 13, 25, 17, 4, 31, 7, 1, 47, 15, 9, 50, 3, 30, 37, 43, 10, 28, 33, 32};
    std::deque player2{29, 49, 11, 42, 35, 18, 39, 40, 36, 19, 48, 22, 2, 20, 26, 8, 12, 44, 45, 21, 38, 41, 34, 5, 27};

    while (!(player1.empty() || player2.empty()))
    {
        auto p1 = player1.front();
        player1.pop_front();
        auto p2 = player2.front();
        player2.pop_front();
        if (p1 > p2)
        {
            player1.push_back(p1);
            player1.push_back(p2);
        }
        else
        {
            player2.push_back(p2);
            player2.push_back(p1);
        }
    }

    std::deque<int> winner{};
    if (player1.size() > 0)
    {
        swap(winner, player1);
    }
    else
    {
        swap(winner, player2);
    }
    std::cout << compute_score(winner) << std::endl;

    //Part 2
    player1 = {14, 23, 6, 16, 46, 24, 13, 25, 17, 4, 31, 7, 1, 47, 15, 9, 50, 3, 30, 37, 43, 10, 28, 33, 32};
    player2 = {29, 49, 11, 42, 35, 18, 39, 40, 36, 19, 48, 22, 2, 20, 26, 8, 12, 44, 45, 21, 38, 41, 34, 5, 27};
    winner.clear();
    if (subgame(player1, player2))
    {
        swap(winner, player1);
    }
    else
    {
        swap(winner, player2);
    }
    std::cout << compute_score(winner) << std::endl;
    return 0;
}

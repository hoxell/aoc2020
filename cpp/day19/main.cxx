#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "ioutils.hpp"

using std::string;
using std::unordered_map;
using std::vector;

unordered_map<string, vector<vector<string>>> getRules(const vector<string> &input)
{
    unordered_map<string, vector<vector<string>>> rules;
    std::regex ruleIndexPattern{R"(\d+(?=:))"};
    for (const auto &line : input)
    {
        std::smatch matches;
        std::regex_search(line, matches, ruleIndexPattern);
        if (matches.empty())
        {
            break;
        }
        auto idx = matches[0].str();

        std::regex ruleRegex{R"((?:(\d+)|([ab]))(?!.*:)(\s*\|)?)"};
        std::regex_iterator regexIterator{line.cbegin(), line.cend(), ruleRegex};
        std::sregex_iterator endIterator;
        vector<vector<string>> rule;
        vector<string> partialRule;
        for (; regexIterator != endIterator; ++regexIterator)
        {

            uint8_t matchIdx;
            if ((*regexIterator)[1].matched)
            {
                matchIdx = 1;
            }
            else if ((*regexIterator)[2].matched)
            {
                matchIdx = 2;
            }
            partialRule.push_back((*regexIterator)[matchIdx]);

            if ((*regexIterator)[3].matched)
            {
                rule.push_back(partialRule);
                partialRule.clear();
            }
        }
        rule.push_back(partialRule);
        rules[idx] = rule;
    }
    return rules;
}

bool containsOnlyDigits(string str)
{
    return str.find_first_not_of("0123456789") == string::npos;
}

std::string composeRegex(unordered_map<string, vector<vector<string>>> &rules, string ruleIdx)
{
    std::ostringstream regexStream;
    bool containsOr = rules[ruleIdx].size() > 1;
    bool insertBar = false;
    if (containsOr)
    {
        regexStream << "(?:";
    }

    for (const auto &alternativeRule : rules[ruleIdx])
    {
        if (insertBar)
        {
            regexStream << "|";
        }
        for (const auto &subrule : alternativeRule)
        {
            if (containsOnlyDigits(subrule))
            {
                regexStream << composeRegex(rules, subrule);
            }
            else
            {
                regexStream << subrule;
            }
        }
        insertBar = true;
    }
    if (containsOr)
    {
        regexStream << ")";
    }
    return regexStream.str();
}

int main()
{
    auto lines = aoc::readInput("input.txt");
    auto rules = getRules(lines);

    auto patternStr = composeRegex(rules, "0");
    patternStr = "^" + patternStr + "$";
    std::regex pattern{patternStr};

    auto count = 0;
    for (const auto &line : lines)
    {
        if (std::regex_match(line, pattern))
        {
            ++count;
        }
    }
    std::cout << "Part 1: " << count << std::endl;

    // Since rule 0 is "8 11", the change of rule 8 and 11 effectively
    // means you're looking for n matches of rule 42 followed by
    // m < n matches of rule 31, n = 2, 3, 4, ..., m > 0
    auto pattern42 = composeRegex(rules, "42");
    auto pattern31 = composeRegex(rules, "31");
    auto combinedPatternStr = "^" + pattern42 + "{2,}" + pattern31 + "+" + "$";
    std::regex countPattern42{pattern42 + "(?=" + pattern42 + "*" + pattern31 + "+?$" + ")"};
    std::regex countPattern31{pattern31};
    std::regex combinedPattern{combinedPatternStr};

    std::sregex_iterator iteratorEnd;

    count = 0;
    for (const auto &line : lines)
    {
        if (std::regex_match(line, combinedPattern))
        {
            string suffix;
            std::sregex_iterator iteratorRule42(line.cbegin(), line.cend(), countPattern42);
            auto count42 = 0;
            for (; iteratorRule42 != iteratorEnd; ++iteratorRule42)
            {
                suffix = (*iteratorRule42).suffix();
                ++count42;
            }
            std::regex_iterator iteratorRule31(suffix.cbegin(), suffix.cend(), countPattern31);
            auto count31 = 0;
            for (; iteratorRule31 != iteratorEnd; ++iteratorRule31)
            {
                ++count31;
            }
            if (count42 > count31)
            {
                ++count;
            }
        }
    }

    std::cout << "Part 2: " << count << std::endl;
    return 0;
}
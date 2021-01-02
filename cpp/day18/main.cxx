#include <iostream>
#include <queue>
#include <regex>
#include <stack>
#include <string>
#include <unordered_map>

#include "ioutils.hpp"

std::queue<std::string>
shuntingYard(const std::string &expression, const std::unordered_map<std::string, uint8_t> &operatorPrecedence)
{
    std::queue<std::string> output;
    std::stack<std::string> operatorStack;

    std::regex valueOrOperator{R"((\d+)|([+*])|(\()|(\)))"};
    std::sregex_iterator regexIterator{expression.cbegin(),
                                       expression.cend(),
                                       valueOrOperator};
    std::sregex_iterator endIterator;

    for (; regexIterator != endIterator; ++regexIterator)
    {
        if ((*regexIterator)[1].matched)
        {
            output.push((*regexIterator)[1].str());
        }
        else if ((*regexIterator)[2].matched)
        {
            auto extractedOperator = (*regexIterator)[2].str();
            while (!operatorStack.empty())
            {
                if (operatorStack.top() == "(")
                {
                    break;
                }
                else if (operatorPrecedence.at(operatorStack.top()) >= operatorPrecedence.at(extractedOperator))
                {
                    output.push(operatorStack.top());
                    operatorStack.pop();
                }
                else
                {
                    break;
                }
            }
            operatorStack.push(extractedOperator);
        }
        else if ((*regexIterator)[3].matched)
        {
            operatorStack.push((*regexIterator)[3].str());
        }
        else if ((*regexIterator)[4].matched)
        {
            while (operatorStack.top() != "(")
            {
                output.push(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.pop();
        }
    }

    while (!operatorStack.empty())
    {
        output.push(operatorStack.top());
        operatorStack.pop();
    }

    return output;
}

uint64_t evaluateRPN(std::queue<std::string> expression)
{
    std::stack<uint64_t> operands;
    while (!expression.empty())
    {
        auto item = expression.front();
        uint64_t tmp;
        expression.pop();
        if (std::string("+*").find(item) != std::string::npos)
        {
            auto operand1 = operands.top();
            operands.pop();
            auto operand2 = operands.top();
            operands.pop();

            if (item == "+")
            {
                tmp = operand1 + operand2;
            }
            else if (item == "*")
            {
                tmp = operand1 * operand2;
            }
            operands.push(tmp);
        }
        else
        {
            operands.push(static_cast<uint64_t>(std::stoul(item)));
        }
    }
    return operands.top();
}

int main()
{
    auto expressions = aoc::readInput("input.txt");

    const std::unordered_map<std::string, uint8_t> part1Precedence{
        {"+", 0},
        {"*", 0}};

    const std::unordered_map<std::string, uint8_t> part2Precedence{
        {"+", 1},
        {"*", 0}};

    int64_t sum1{0};
    int64_t sum2{0};
    for (const auto expression : expressions)
    {
        auto part1Notation = shuntingYard(expression, part1Precedence);
        auto result1 = evaluateRPN(part1Notation);
        sum1 += result1;
        auto part2Notation = shuntingYard(expression, part2Precedence);
        auto result2 = evaluateRPN(part2Notation);
        sum2 += result2;
    }
    std::cout << "Part 1: " << sum1 << std::endl;
    std::cout << "Part 2: " << sum2 << std::endl;
    return 0;
}
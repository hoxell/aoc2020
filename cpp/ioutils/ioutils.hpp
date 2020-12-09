/* Header-only library to handle basic IO (i.e. reading the input data) */
#pragma once
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace aoc
{
    /**
     * \brief Read file into a vector of strings
     * 
     * Each string corresponds to a line in the file.
     * The delimiter is discarded
     */
    std::vector<std::string> readInput(const std::string &filePath, char delim = '\n')
    {
        std::ifstream inputFile(filePath);
        if (!inputFile)
        {
            std::ostringstream errorMsg;
            errorMsg << "Can't open file: " << filePath;
            throw std::runtime_error(errorMsg.str());
        }
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(inputFile, line, delim))
        {
            lines.push_back(line);
        }
        return lines;
    }
} // namespace aoc
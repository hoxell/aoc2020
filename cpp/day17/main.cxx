#include <array>
#include <iostream>

using std::array;

struct Coordinates
{
    int8_t x, y, z, w;
};

constexpr uint8_t NCYCLES = 6;
constexpr uint8_t inputXDim = 8;
constexpr uint8_t inputYDim = 8;
constexpr array<array<bool, inputXDim>, inputYDim> input = {{{1, 0, 1, 1, 0, 0, 0, 0},
                                                             {0, 1, 0, 1, 0, 1, 1, 0},
                                                             {1, 1, 1, 0, 0, 0, 0, 0},
                                                             {0, 0, 0, 0, 1, 1, 0, 1},
                                                             {1, 0, 0, 0, 0, 1, 1, 1},
                                                             {0, 1, 0, 1, 0, 1, 0, 0},
                                                             {0, 1, 1, 0, 0, 0, 1, 1},
                                                             {1, 0, 0, 1, 0, 1, 1, 1}}};

template <auto xDim, auto yDim, auto zDim, auto wDim>
void printGrid(array<array<array<array<bool, xDim>, yDim>, zDim>, wDim> &grid)
{
    for (auto wIt = grid.cbegin(); wIt != grid.cend(); ++wIt)
    {
        for (auto zIt = (*wIt).cbegin(); zIt != (*wIt).cend(); ++zIt)
        {
            for (auto yIt = (*zIt).cbegin(); yIt != (*zIt).cend(); ++yIt)
            {
                for (auto xIt = (*yIt).cbegin(); xIt != (*yIt).cend(); ++xIt)
                    std::cout << *xIt << " ";
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }
}

template <auto xDim, auto yDim, auto zDim, auto wDim>
uint16_t getNumActive(array<array<array<array<bool, xDim>, yDim>, zDim>, wDim> &grid)
{
    uint16_t count{0};
    for (auto wIt = grid.cbegin(); wIt != grid.cend(); ++wIt)
    {
        for (auto zIt = (*wIt).cbegin(); zIt != (*wIt).cend(); ++zIt)
        {
            for (auto yIt = (*zIt).cbegin(); yIt != (*zIt).cend(); ++yIt)
            {
                for (auto xIt = (*yIt).cbegin(); xIt != (*yIt).cend(); ++xIt)
                {
                    if (*xIt)
                    {
                        ++count;
                    }
                }
            }
        }
    }
    return count;
}

template <auto xDim, auto yDim, auto zDim, auto wDim>
void fill4DGrid(array<array<array<array<bool, xDim>, yDim>, zDim>, wDim> &grid, bool value)
{
    for (auto &w : grid)
    {
        for (auto &z : w)
        {
            for (auto &y : z)
            {
                y.fill(value);
            }
        }
    }
}

template <auto xDim, auto yDim, auto zDim, auto wDim>
void initializeGrid(array<array<array<array<bool, xDim>, yDim>, zDim>, wDim> &grid,
                    Coordinates offset)
{
    fill4DGrid(grid, false);
    for (auto yIt = input.cbegin(); yIt != input.cend(); ++yIt)
    {
        auto yIdx = yIt - input.cbegin();
        for (auto xIt = (*yIt).cbegin(); xIt != (*yIt).cend(); ++xIt)
        {
            auto xIdx = xIt - (*yIt).cbegin();
            grid[offset.w][offset.z][offset.y + yIdx][offset.x + xIdx] = *xIt;
        }
    }
}

template <auto xDim, auto yDim, auto zDim, auto wDim>
uint8_t getNumActiveNeighbours(array<array<array<array<bool, xDim>, yDim>, zDim>, wDim> &grid, Coordinates coordinates)
{
    uint8_t count{0};
    for (auto wDiff = -1; wDiff <= 1; ++wDiff)
    {
        auto w = coordinates.w + wDiff;
        if (w < 0)
        {
            continue;
        }
        else if (w >= grid.size())
        {
            break;
        }
        for (auto zDiff = -1; zDiff <= 1; ++zDiff)
        {
            auto z = coordinates.z + zDiff;
            if (z < 0)
            {
                continue;
            }
            else if (z >= grid[w].size())
            {
                break;
            }

            for (auto yDiff = -1; yDiff <= 1; ++yDiff)
            {
                auto y = coordinates.y + yDiff;
                if (y < 0)
                {
                    continue;
                }
                else if (y >= grid[w][z].size())
                {
                    break;
                }

                for (auto xDiff = -1; xDiff <= 1; ++xDiff)
                {
                    auto x = coordinates.x + xDiff;
                    if (x < 0)
                    {
                        continue;
                    }
                    else if (x >= grid[w][z][y].size())
                    {
                        break;
                    }
                    else if (grid[w][z][y][x])
                    {
                        ++count;
                    }
                }
            }
        }
    }
    // Don't count the box itself
    if (grid[coordinates.w][coordinates.z][coordinates.y][coordinates.x])
    {
        --count;
    }
    return count;
}

template <auto xDim, auto yDim, auto zDim, auto wDim>
void runSequence(array<array<array<array<bool, xDim>, yDim>, zDim>, wDim> &grid, int nIterations)
{
    array<array<array<array<bool, xDim>, yDim>, zDim>, wDim> alternativeGrid;
    for (int i = 0; i < NCYCLES; ++i)
    {
        fill4DGrid(alternativeGrid, false);
        for (int8_t wIdx = 0; wIdx < grid.size(); ++wIdx)
        {
            for (int8_t zIdx = 0; zIdx < grid[wIdx].size(); ++zIdx)
            {
                for (int8_t yIdx = 0; yIdx < grid[wIdx][zIdx].size(); ++yIdx)
                {
                    for (int8_t xIdx = 0; xIdx < grid[wIdx][zIdx][yIdx].size(); ++xIdx)
                    {
                        auto nActiveNeighbours = getNumActiveNeighbours(grid, {xIdx, yIdx, zIdx, wIdx});
                        if (grid[wIdx][zIdx][yIdx][xIdx])
                        {
                            if (nActiveNeighbours == 2 || nActiveNeighbours == 3)
                            {
                                alternativeGrid[wIdx][zIdx][yIdx][xIdx] = true;
                            }
                        }
                        else if (nActiveNeighbours == 3)
                        {
                            alternativeGrid[wIdx][zIdx][yIdx][xIdx] = true;
                        }
                    }
                }
            }
        }

        grid.swap(alternativeGrid);
    }
}

int main()
{
    constexpr uint8_t dimX = 2 * NCYCLES + inputXDim;
    constexpr uint8_t dimY = 2 * NCYCLES + inputYDim;
    constexpr uint8_t dimZ = 2 * NCYCLES + 1;
    constexpr uint8_t dimW = dimZ;

    array<array<array<array<bool, dimX>, dimY>, dimZ>, 1> grid;
    initializeGrid(grid, {NCYCLES, NCYCLES, NCYCLES, 0});
    runSequence(grid, NCYCLES);

    std::cout << "Part 1: " << getNumActive(grid) << std::endl;

    array<array<array<array<bool, dimX>, dimY>, dimZ>, dimW> grid2;
    initializeGrid(grid2, {NCYCLES, NCYCLES, NCYCLES, NCYCLES});
    runSequence(grid2, NCYCLES);

    std::cout << "Part 2: " << getNumActive(grid2) << std::endl;
    return 0;
}
#!/usr/bin/env python3
import sys


sys.path.append("../")
from inputreader import read_input  # pylint: disable=import-error


def part1():
    data = tuple(read_input(int))
    for i, value in enumerate(data[:-1]):
        for value2 in data[i + 1 :]:
            if value + value2 == 2020:
                return value * value2


def part2():
    data = tuple(read_input(int))
    for i, value in enumerate(data[:-2]):
        for j, value2 in enumerate(data[i + 1 : -1]):
            for value3 in data[j + 1 :]:
                if value + value2 + value3 == 2020:
                    return value * value2 * value3


def main():
    print(f"part1: {part1()}")
    print(f"part2: {part2()}")


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
from collections import Counter
import sys


sys.path.append("..")
from inputreader import read_input  # pylint: disable=import-error


def transform_function(line):
    count, letter, pw = line.replace(":", "").split()
    low, high = count.split("-")
    return int(low), int(high), letter, pw


def part1(data):
    return sum(
        [
            1
            for low, high, character, pw in data
            if low <= Counter(pw)[character] <= high
        ]
    )


def part2(data):
    return sum(
        [
            1
            for low, high, character, pw in data
            if (pw[low - 1] == character) ^ (pw[high - 1] == character)
        ]
    )


def main():
    data = tuple(read_input(transform_function=transform_function))
    print(f"part1: {part1(data)}")
    print(f"part2: {part2(data)}")


if __name__ == "__main__":
    main()

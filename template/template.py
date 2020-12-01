#!/usr/bin/env python3
import sys


sys.path.append("..")
from inputreader import read_input  # pylint: disable=import-error


def transform_function(line):
    return line


def part1(data):
    pass


def part2(data):
    pass


def main():
    data = tuple(read_input(transform_function=transform_function))
    print(f"part1: {part1(data)}")
    print(f"part2: {part2(data)}")


if __name__ == "__main__":
    main()

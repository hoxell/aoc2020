#!/usr/bin/env python3
import sys
from typing import Any, Generator


sys.path.append("..")
from inputreader import read_input  # pylint: disable=import-error


def main():
    lines = read_input(transform_function=transform_function)
    data = format_input(lines)

    print(f"part1: {part1(data)}")
    print(f"part2: {part2(data)}")


def transform_function(line):
    return line


def format_input(lines: Generator[Any, None, None]) -> Any:
    """Format the lines into the expected data format"""
    return tuple(lines)


def part1(data):
    pass


def part2(data):
    pass


if __name__ == "__main__":
    main()

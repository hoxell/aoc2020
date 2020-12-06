#!/usr/bin/env python3
import os
import sys
from typing import Any, Generator


file_dir = os.path.dirname(__file__)
sys.path.append(os.path.join(file_dir, ".."))
from inputreader import read_input  # pylint: disable=import-error


def main():
    lines = read_input(transform_function=transform_function)
    data = format_input(lines)
    solve(data)


def transform_function(line):
    return line


def format_input(lines: Generator[Any, None, None]) -> Any:
    """Format lines into the appropriate data format for the task

    Returns
    -------
    list
        Nested list with outer index designating group and inner
        index designating a person within that group
        The innermost element is a set containing the question that
        person answered yes to
    """
    groups_str = "".join(lines).split("\n\n")
    groups = [
        [set(person.strip()) for person in group.split("\n")]
        for group in groups_str
    ]
    return groups


def solve(data):
    part1 = sum([len(set.union(*group)) for group in data])
    print(part1)
    part2 = sum([len(set.intersection(*group)) for group in data])
    print(part2)


if __name__ == "__main__":
    main()

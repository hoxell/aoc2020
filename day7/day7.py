#!/usr/bin/env python3
from collections import defaultdict
from queue import Queue
import os
import sys
import re
from typing import Any, Generator


file_dir = os.path.dirname(__file__)
sys.path.append(os.path.join(file_dir, ".."))
from inputreader import read_input  # pylint: disable=import-error


def main():
    lines = read_input(transform_function=transform_function)
    data = format_input(lines)

    print(f"part1: {part1(data)}")
    print(f"part2: {part2(data)}")


def transform_function(line):
    return transform_function.reg.findall(line)


# Workaround so that it doesn't get compiled for each line
transform_function.reg = re.compile(
    r"(\d+\s+)?((?:\b[a-zA-Z]+\b\s*){2})(?<!(?:no other))\s+bags?"
)


def format_input(lines: Generator[Any, None, None]) -> Any:
    """Format the lines into the expected data format"""
    return tuple(lines)


def part1(data):
    d = defaultdict(set)
    for line in data:
        containing_color = line[0][1]
        for f in line[1:]:
            c = f[1]
            d[c].add(containing_color)

    checked = set()
    valid = set()
    q = Queue()
    for color in d["shiny gold"]:
        q.put(color)
        valid.add(color)

    while not q.empty():
        c = q.get()
        for color in d[c]:
            if color not in checked:
                checked.add(color)
                valid.add(color)
                q.put(color)
    print(len(valid))


def part2(data):
    d = defaultdict(set)
    for line in data:
        # found = reg.findall(line)
        containing_color = line[0][1]
        for f in line[1:]:
            count, c = f
            count = int(count)
            d[containing_color].add((count, c))

    def num_bags(d, key, multiple):
        s = 1  # Count the bag themselves
        for count, color in d[key]:
            s += num_bags(d, color, count)
        return multiple * s

    print(num_bags(d, "shiny gold", 1) - 1)  # Subtract the gold bag itself


if __name__ == "__main__":
    main()

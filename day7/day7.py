#!/usr/bin/env python3
from collections import defaultdict
import os
from queue import Queue
import re
import sys
from typing import Any, Dict, Generator, Tuple


file_dir = os.path.dirname(__file__)
sys.path.append(os.path.join(file_dir, ".."))
from inputreader import read_input  # pylint: disable=import-error


def main():
    lines = read_input(transform_function=transform_function)
    data = format_input(lines)
    solve(data)


def transform_function(line):
    matches = transform_function.reg.findall(line)
    for i, match in enumerate(matches[1:]):
        matches[i + 1] = int(match[0]), match[1]
    return matches


# Workaround so that it doesn't get compiled for each line
transform_function.reg = re.compile(
    r"(\d+\s+)?((?:\b[a-zA-Z]+\b\s*){2})(?<!(?:no other))\s+bags?"
)


def format_input(lines: Generator[Any, None, None]) -> Any:
    """Format the lines into the expected data format"""
    return tuple(lines)


def num_bags(children: Dict[str, Tuple[int, str]], color: str, count: int):
    total = 1  # Count the bag itself
    for child_count, child_color in children[color]:
        total += num_bags(children, child_color, child_count)
    return count * total


def solve(data, color: str = "shiny gold"):
    parents = defaultdict(set)
    children = defaultdict(set)
    for line in data:
        parent_color = line[0][1]
        for child in line[1:]:
            count, child_color = child
            parents[child_color].add(parent_color)
            children[parent_color].add((count, child_color))

    candidates = set()
    queue = Queue()
    for parent in parents[color]:
        queue.put(parent)
        candidates.add(parent)

    while not queue.empty():
        child_color = queue.get()
        for parent in parents[child_color]:
            candidates.add(parent)
            queue.put(parent)

    print(f"Part 1: {len(candidates)}")
    print(f"Part 2: {num_bags(children, color, 1) - 1}")


if __name__ == "__main__":
    main()

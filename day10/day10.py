#!/usr/bin/env python3
import os
import sys
import time
from typing import Any, Generator


file_dir = os.path.dirname(__file__)
sys.path.append(os.path.join(file_dir, ".."))
from inputreader import read_input  # pylint: disable=import-error


def main():
    lines = read_input(transform_function=transform_function)
    data = format_input(lines)
    solve(data)


def transform_function(line):
    return int(line)


def format_input(lines: Generator[Any, None, None]) -> Any:
    """Format the lines into the expected data format"""
    return list(lines)


def solve(data):
    t0 = time.time()
    sorted_array = sorted(data)
    ones = 0
    threes = 0
    for a, b in zip(sorted_array[1:], sorted_array):
        if a - b == 1:
            ones += 1
        elif a - b == 3:
            threes += 1
    print(f"Part 1: {ones*threes}, time: {(time.time() - t0)*1e6:.5}µs")

    t0 = time.time()
    num_paths = [0] * len(sorted_array)
    num_paths[0] = 1
    max_idx = len(sorted_array)
    offsets = [1, 2, 3]
    for idx in range(len(sorted_array)):
        for i in offsets:
            if (
                i + idx < max_idx
                and sorted_array[i + idx] - sorted_array[idx] < 4
            ):
                num_paths[i + idx] += num_paths[idx]
    time_taken = time.time() - t0
    print(f"Part 2: {num_paths[-1]}, time: {(time_taken)*1e6:.5}µs")


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
import functools
import numpy as np
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
    array = np.fromiter(lines, dtype=np.int)
    array = np.insert(array, 0, 0)
    array = np.append(array, max(array) + 3)
    return array


def solve(data):
    t0 = time.time()
    sorted_array = np.sort(data)
    diff = np.diff(sorted_array)
    ones = np.count_nonzero(diff == 1)
    three = np.count_nonzero(diff == 3)

    print(f"Part 1: {(ones)*(three)}, time: {(time.time() - t0)*1e6:.5}µs")

    @functools.lru_cache(maxsize=len(sorted_array))
    def n_paths(idx):
        num_paths = 0
        val = sorted_array[idx]
        for i in range(idx + 1, idx + 4):
            try:
                if sorted_array[i] - val <= 3:
                    num_paths += n_paths(i)
                else:
                    break
            except IndexError:
                pass
        return max(num_paths, 1)

    t0 = time.time()
    print(f"Part 2: {n_paths(0)}, time: {(time.time() - t0)*1e6:.5}µs")


if __name__ == "__main__":
    main()

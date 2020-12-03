#!/usr/bin/env python3
import sys


import numpy as np


sys.path.append("..")
from inputreader import read_input  # pylint: disable=import-error


def transform_function(line):
    binary_str = line.replace(".", "0").replace("#", "1").strip()
    data = np.fromiter(binary_str, dtype=np.int8)
    return data


def part1(data, row=1, col=3):
    x, y = 0, 0
    count = 0
    # Assume we can't begin _on_ a tree
    while (y := y + row) < data.shape[0]:
        x += col
        if data[y, x % data.shape[1]]:
            count += 1
    return count


def part2(data):
    product = 1
    for row, col in [[1, 1], [3, 1], [5, 1], [7, 1], [1, 2]]:
        product *= part1(data, col, row)
    return product


def main():
    gen = read_input(transform_function=transform_function)
    data = next(gen)
    data = data[np.newaxis, :]
    for row in gen:
        data = np.vstack((data, row[np.newaxis, :]))
    print(f"part1: {part1(data)}")
    print(f"part2: {part2(data)}")


if __name__ == "__main__":
    main()

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
    pre_length = 25

    preamble = set(data[:pre_length])
    part1 = None
    for i, num in enumerate(data[pre_length:]):
        for n in preamble:
            if (num - n) in preamble and num != 2 * n:
                break
        else:
            part1 = num
            break
        preamble.discard(data[i])
        preamble.add(num)

    time_pt1 = (time.time() - t0) * 1e3
    print(f"Part 1: {part1}, time: {time_pt1}ms")

    t0 = time.time()
    start_idx = 0
    end_idx = 1
    the_sum = sum(data[start_idx : end_idx + 1])
    while True:
        if the_sum < part1:
            end_idx += 1
            the_sum += data[end_idx]
        elif the_sum == part1:
            break
        else:
            the_sum -= data[start_idx]
            start_idx += 1
    contig = data[start_idx : end_idx + 1]
    time_pt2 = (time.time() - t0) * 1e3
    print(f"Part 2: {max(contig) + min(contig)}, time: {time_pt2}ms")


if __name__ == "__main__":
    main()

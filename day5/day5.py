#!/usr/bin/env python3
from functools import partial
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
    """Format the lines into the expected data format"""
    return tuple(lines)


def split_interval(lower, upper, keep: str):
    """Split interval in two and keep 'upper' or 'lower'

    The interval includes the start and endpoints
    """
    interval_length = upper - lower + 1
    half = interval_length / 2
    if keep.lower() == "lower":
        upper = lower + half - 1
    elif keep.lower() == "upper":
        lower = lower + half
    else:
        raise ValueError(f"Keep must be 'upper' or 'lower'. Got {keep}")
    return lower, upper


def solve(data, length=128, width=8):
    highest_id = 0
    empty_seat = set(range(127 * 8 + 7))
    for bp in data:
        row = (0, length - 1)
        col = (0, width - 1)
        split_functions = {
            "f": partial(split_interval, keep="lower"),
            "l": partial(split_interval, keep="lower"),
            "b": partial(split_interval, keep="upper"),
            "r": partial(split_interval, keep="upper"),
        }
        for letter in bp:
            if letter.lower() in ["f", "b"]:
                row = split_functions[letter.lower()](*row)
            elif letter.lower() in ["r", "l"]:
                col = split_functions[letter.lower()](*col)
            else:
                pass

        seat_id = row[0] * 8 + col[0]
        empty_seat.remove(seat_id)
        if seat_id > highest_id:
            highest_id = seat_id

    print(f"Part 1: {highest_id}")

    # Part 2
    for potential in empty_seat:
        if not (
            (potential - 1) in empty_seat or (potential + 1) in empty_seat
        ):
            part2 = potential
            break
    else:
        part2 = None

    print(f"Part 2: {part2}")


if __name__ == "__main__":
    main()

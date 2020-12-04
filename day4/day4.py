#!/usr/bin/env python3
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
    return line


def format_input(lines: Generator[Any, None, None]) -> Any:
    """Format the lines into the expected data format"""
    total = "".join(lines)
    items = total.split("\n\n")
    return items


def part1(data, validation_function=lambda _: True):
    expected = set(("byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"))
    count = 0
    for item in data:
        existing = set()
        for field in item.split():
            existing.add(field.split(":")[0])
        if existing.issuperset(expected) and validation_function(item):
            count += 1
    return count


def part2(data):
    def validate(item):
        validation_regex = {
            "byr": re.compile(r"^(19[2-9]\d|200[0-2])$"),
            "iyr": re.compile(r"^20(1\d|20)$"),
            "eyr": re.compile(r"^20(2\d|30)$"),
            "hgt": re.compile(r"^(1([5-8]\d|9[0-3])cm|(59|6\d|7[0-6])in)$"),
            "hcl": re.compile(r"^#[\da-f]{6}$"),
            "ecl": re.compile(r"^(amb|blu|brn|gry|grn|hzl|oth)$"),
            "pid": re.compile(r"^\d{9}$"),
        }
        for entry in item.split():
            key, value = entry.strip().split(":")
            if not validation_regex.get(key, re.compile(".*")).match(value):
                return False
        return True

    return part1(data, validation_function=validate)


if __name__ == "__main__":
    main()

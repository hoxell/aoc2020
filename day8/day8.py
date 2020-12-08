#!/usr/bin/env python3
import os
import re
import sys
from typing import Any, Generator


file_dir = os.path.dirname(__file__)
sys.path.append(os.path.join(file_dir, ".."))
from inputreader import read_input  # pylint: disable=import-error
from intcode import IntCode


def main():
    lines = read_input(transform_function=transform_function)
    data = format_input(lines)
    solve(data)


def transform_function(line):
    instruction_reg = re.compile(r"[a-zA-Z]{3}")
    operand_reg = re.compile(r"[+-]?\d+")
    instruction = instruction_reg.search(line).group(0)
    operands = operand_reg.findall(line)
    return [instruction] + [int(operand) for operand in operands]


def format_input(lines: Generator[Any, None, None]) -> Any:
    """Format the lines into the expected data format"""
    return tuple(lines)


def solve(data):
    machine = IntCode(data, allow_repeat=False)
    machine.run()
    print(f"Part 1: {machine.accumulator}")

    for idx in range(len(data)):
        if data[idx][0] == "jmp":
            data[idx][0] = "nop"
        else:
            continue
        machine2 = IntCode(data, allow_repeat=False)
        if machine2.run():
            break
        data[idx][0] = "jmp"

    print(f"Part 2: {machine2.accumulator}")


if __name__ == "__main__":
    main()

"""Helper function to read input"""
from typing import Any, Callable, Generator


def _passthrough(value):
    return value


def read_input(
    transform_function: Callable[[str], Any] = _passthrough,
    filepath: str = "input.txt",
) -> Generator[Any, None, None]:
    """Reads the input line by line from filepath"""
    with open(filepath) as fh:
        for line in fh:
            yield transform_function(line)

![Python](https://github.com/hoxovic/aoc2020/workflows/Python/badge.svg)
[![Code style: black](https://img.shields.io/badge/code%20style-black-000000.svg)](https://github.com/psf/black)

# [![](https://adventofcode.com/favicon.png) Advent of code](https://adventofcode.com)
My solutions to [Advent of Code](https://adventofcode.com/)

## Scaffolding
This repo also contains some functionality to scaffold the files needed to solve the problems. Use like so,

```sh
$ ./scaffold.py <DayOfMonth>

# As per the documentation
$ ./scaffold.py -h
usage: scaffold.py [-h] DayOfMonth

Scaffold a new day from template

positional arguments:
  DayOfMonth

optional arguments:
  -h, --help  show this help message and exit

# For instance, for Dec. 10th
# $ ./scaffold.py 10 
```

This will create a new directory in the git root directory, name it `day<DayOfMonth>`, copy the contents of the `template` directory and rename the `.py` file accordingly.
If it already exists, an exception will be raised and nothing will be done.

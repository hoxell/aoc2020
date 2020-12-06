# [![](https://adventofcode.com/favicon.png) Advent of code](https://adventofcode.com)
My solutions to [Advent of Code](https://adventofcode.com/)

## Utils, templates and scaffolding
This repo also contains some functionality to scaffold the files needed to solve the problems. Use like so,

```sh
$ ./scaffold.py <numeric_date>
# For instance, for Dec. 10th
# $ ./scaffold.py 10 
```

This will create a new directory in the git root directory, name it `day<numeric_date>`, copy the contents of the `template` directory and rename the `.py` file accordingly.
If it already exists, an exception will be raised and nothing will be done.

#!/usr/bin/env python3
import argparse
import os
import shutil


def main():
    args = get_arguments()
    folder_name = "day" + str(args.DayNumber)
    bootstrap_folder(folder_name)


def get_arguments() -> argparse.Namespace:
    """Gets the cli arguments"""
    parser = argparse.ArgumentParser(
        description="Bootstrap a new day based on template"
    )
    parser.add_argument("DayNumber", type=int)

    return parser.parse_args()


def bootstrap_folder(name: str):
    """Bootstrap a folder from the template if the folder doesn't exist"""
    shutil.copytree("template", name, dirs_exist_ok=False)
    src = os.path.join(name, "template.py")
    dst = os.path.join(name, name + ".py")
    os.rename(src, dst)

    input_file = os.path.join(name, "input.txt")
    with open(input_file, "a"):
        pass


if __name__ == "__main__":
    main()

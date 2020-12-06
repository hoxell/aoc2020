#!/usr/bin/env python3
"""Create a new directory with the structure typically used for a day"""
import argparse
import os
import shutil


def main():
    """Entry point for script"""
    args = get_arguments()
    folder_name = "day" + str(args.DayOfMonth)
    scaffold_folder(folder_name)


def get_arguments() -> argparse.Namespace:
    """Gets the cli arguments"""
    parser = argparse.ArgumentParser(
        description="Scaffold a new day from template"
    )
    parser.add_argument("DayOfMonth", type=int)

    return parser.parse_args()


def scaffold_folder(name: str):
    """Create a new folder from the template if the folder doesn't exist"""
    parent_dir = os.path.dirname(__file__)
    template_dir = os.path.join(parent_dir, "template")
    dst_dir = os.path.join(parent_dir, name)
    shutil.copytree(template_dir, dst_dir, dirs_exist_ok=False)
    src = os.path.join(dst_dir, "template.py")
    dst = os.path.join(dst_dir, name + ".py")
    os.rename(src, dst)


if __name__ == "__main__":
    main()

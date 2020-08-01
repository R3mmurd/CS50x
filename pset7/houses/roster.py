"""
Program that prints a list of students for a given house in alphabetical order.

Author: Alejandro Mujica (aledrums@gmail.com)
"""
import sys

from cs50 import SQL


def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} house_name")
        exit(1)

    house_name = sys.argv[1]

    # Db connection
    db = SQL("sqlite:///students.db")

    result = db.execute(
        "SELECT * FROM students WHERE house = ? ORDER BY last, first",
        house_name
    )

    for item in result:
        middle = item['middle']
        if middle is None:
            middle = ''
        else:
            middle = f"{middle} "

        line = f"{item['first']} {middle}{item['last']}, born {item['birth']}"
        print(line)

if __name__ == "__main__":
    main()


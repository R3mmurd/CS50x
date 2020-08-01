"""
Program that imports data from a CSV spreadsheet and load it in a database.

Author: Alejandro Mujica (aledrums@gmail.com)
"""
import sys
import csv

from cs50 import SQL


def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} data.csv")
        exit(1)

    # Db connection
    db = SQL("sqlite:///students.db")

    # Open csv file
    with open(sys.argv[1], "r") as f:

        # csv reader
        reader = csv.reader(f)

        # Skip header row
        next(reader)

        for name, house, birth in reader:
            name_list = name.split(' ')
            first = name_list[0]
            last = name_list[-1]
            middle = name_list[1] if len(name_list) == 3 else None
            birth = int(birth)

            query = (
                "INSERT INTO students (first, middle, last, house, birth) "
                "VALUES (?, ?, ?, ?, ?)"
            )
            db.execute(query, first, middle, last, house, birth)

if __name__ == "__main__":
    main()


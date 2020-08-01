"""
Program that identifies a person based on their DNA.

Author: Alejandro Mujica (aledrums@gmail.com)
"""
import sys
import csv

import cs50


def usage(argv):
    print(f"Usage: {argv[0]} data.csv sequence.txt")
    exit(1)


def read_db(csv_file_name):
    """
    Returns the column names and rows as dictionaries.
    """
    with open(csv_file_name, 'r') as f:
        reader = csv.DictReader(f)
        cols = reader.fieldnames
        rows = [row for row in reader]

    return cols, rows


def read_sequence(txt_file_name):
    with open(txt_file_name, 'r') as f:
        seq = f.readline()
    return seq



def count_strs(strs, seq):
    counter = {}

    seq_size = len(seq)

    for s in strs:
        str_size = len(s)

        counter[s] = 0
        local_counter = 0
        i = 0

        while i < seq_size - str_size:
            ss = seq[i : i + str_size]

            if ss == s:
                i += str_size
                local_counter += 1
            else:
                i += 1

                if local_counter > counter[s]:
                    counter[s] = local_counter

                local_counter = 0

    return counter


def print_matching(rows, counter):
    for row in rows:
        matches = [int(row[k]) == counter[k] for k in counter]
        if all(matches):
            print(row['name'])
            return

    print('No match')


def main(argv):
    if len(argv) != 3:
        usage(argv)

    cols, rows = read_db(argv[1])
    seq = read_sequence(argv[2])
    counter = count_strs(cols[1:], seq)
    print_matching(rows, counter)


if __name__ == "__main__":
    main(sys.argv)


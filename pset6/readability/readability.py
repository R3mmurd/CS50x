"""
Program that computes the approximate grade level needed to
comprehend some text.

Author: Alejandro Mujica (aledrums@gmail.com)
"""
import cs50

import string


def main():
    text = cs50.get_string("Text: ")

    while not text:
        text = cs50.get_string("Text: ")

    num_letters = 0
    num_words = 0 if not text else 1
    num_sentences = 0

    for c in text:
        if c in string.ascii_letters:
            num_letters += 1
        elif c == ' ':
            num_words += 1
        elif c in '.!?':
            num_sentences += 1

    L = num_letters / num_words * 100
    S = num_sentences / num_words * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    grade = round(index)

    if grade < 1:
        print("Before Grade 1")
    elif grade  < 16:
        print(f"Grade {grade}")
    else:
        print("Grade 16+")


if __name__ == "__main__":
    main()


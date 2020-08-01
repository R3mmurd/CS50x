"""
program that determines whether a provided credit card number
is valid according to Luhn’s algorithm.

Author: Alejandro Mujica (aledrums@gmail.com)
"""
import cs50


def sum_digits(number):
    s = 0

    while number > 0:
        s += number % 10
        number //= 10

    return s


def checksum(number):
    s = 0
    even_flag = False
    while number > 0:
        last = number % 10

        if even_flag:
            last *= 2

        even_flag = not even_flag

        s += sum_digits(last)

        number //= 10

    return s % 10 == 0


def main():
    number = cs50.get_int("Number: ")
    str_number = str(number)

    t = "INVALID"

    if len(str_number) == 15 and str_number[:2] in ('34', '37'):
        if checksum(number):
            t = "AMEX"
    elif len(str_number) in (13, 16) and str_number[0] == '4':
        if checksum(number):
            t = "VISA"
    elif len(str_number) == 16 and 51 <= int(str_number[:2]) <= 55:
        if checksum(number):
            t = "MASTERCARD"

    print(t)

if __name__ == "__main__":
    main()


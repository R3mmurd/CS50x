"""
rogram that prints out a double half-pyramid of a specified height.

Author: Alejandro Mujica (aledrums@gmail.com)
"""
import cs50


def main():

    height = cs50.get_int("Height: ")

    while height < 1 or height > 8:
        height = cs50.get_int("Height: ")


    for i in range(1, height + 1):
        for _ in range(height - i):
            print(' ', end='')

        for _ in range(i):
            print('#', end='')

        print("  ", end='')

        for _ in range(i):
            print('#', end='')

        print('')


if __name__ == "__main__":
    main()


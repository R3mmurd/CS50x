"""
rogram that prints out a half-pyramid of a specified height.

Author: Alejandro Mujica (aledrums@gmail.com)
"""
import cs50


def main():

    # Getting height
    height = cs50.get_int("Height: ")

    # Reprompting while height is not valid
    while height < 1 or height > 8:
        height = cs50.get_int("Height: ")

    for i in range(1, height + 1):
        # Drawinges empty spaces
        for _ in range(height - i):
            print(' ', end='')

        # Drawing blocks
        for _ in range(i):
            print('#', end='')

        print()


if __name__ == "__main__":
    main()

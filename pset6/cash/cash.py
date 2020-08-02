"""
Program that first asks the user how much change is owed and then prints
the minimum number of coins with which that change can be made.

Author: Alejandro Mujica (aledrums@gmail.com)
"""
import cs50


def main():
    change = cs50.get_float("Change owed: ")

    while (change < 0):
        change = cs50.get_float("Change owed: ")

    # Converting dollars to cents
    cents = round(change * 100)

    # Compute number of quarters
    num_quarters = cents // 25

    # Set remaining cents
    cents -= num_quarters * 25

    # Compute number of dimes
    num_dimes = cents // 10

    # Set remaining cents
    cents -= num_dimes * 10

    # Compute number of nickels
    num_nickels = cents // 5

    # Set remaining cents
    cents -= num_nickels * 5

    # cents has the number of pennies
    total = num_quarters + num_dimes + num_nickels + cents
    print(total)


if __name__ == "__main__":
    main()

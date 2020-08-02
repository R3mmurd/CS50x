/*
    Program that first asks the user how much change is owed and then prints
    the minimum number of coins with which that change can be made.

    Author: Alejandro Mujica (aledrums@gmail.com)
*/
#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    float change = get_float("Change owed: ");

    while (change < 0)
    {
        change = get_float("Change owed: ");
    }

    // Converting dollars to cents
    int cents = round(change * 100.0);

    // Compute the maximum number of quartes
    int num_quarters = cents / 25;

    // Update remaining cents
    cents -= num_quarters * 25;

    // Compute the maximum number of dimes
    int num_dimes = cents / 10;

    // Update remaining cents
    cents -= num_dimes * 10;

    // Compute the maximum number of nickels
    int num_nickels = cents / 5;

    // Update remaining cents
    cents -= num_nickels * 5;

    // The remaining number of cents is the number of pennies.

    int num_coins = num_quarters + num_dimes + num_nickels + cents;

    printf("%i\n", num_coins);

    return 0;
}
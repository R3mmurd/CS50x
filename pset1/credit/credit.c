/*
    program that determines whether a provided credit card number
    is valid according to Luhn’s algorithm.

    Author: Alejandro Mujica (aledrums@gmail.com)
*/
#include <stdio.h>
#include <cs50.h>

// Count the number of digits in a number
int count_digits(long);

// Get the n first digits of number given a base
long get_first_digits(long, int);


// Add all digits in a number
long sum_digits(long);

bool checksum(long);

int main(void)
{
    // Ask for credit card number
    long number = get_long("Number: ");

    while (number ==  LONG_MAX)
    {
        number = get_long("Number: ");
    }

    int num_digits = count_digits(number);
    long fd = get_first_digits(number, 10);
    long tfd = get_first_digits(number, 100);

    string type = "INVALID";

    if (num_digits == 15 && ((tfd == 34 || tfd == 37)))
    {
        if (checksum(number))
        {
            type = "AMEX";
        }
    }
    else if ((num_digits == 13 || num_digits == 16) && fd == 4)
    {
        if (checksum(number))
        {
            type = "VISA";
        }
    }
    else if (num_digits == 16 && tfd >= 51 && tfd <= 55)
    {
        if (checksum(number))
        {
            type = "MASTERCARD";
        }
    }

    printf("%s\n", type);

    return 0;
}

int count_digits(long number)
{
    int counter = 0;

    while (number > 0)
    {
        ++counter;
        number /= 10;
    }

    return counter;
}

long get_first_digits(long number, int base)
{
    while (number > base)
    {
        number /= 10;
    }

    return number;
}

long sum_digits(long number)
{
    long sum = 0;

    while (number > 0)
    {
        long last = number % 10;
        sum += last;
        number /= 10;
    }

    return sum;
}


bool checksum(long number)
{
    long sum = 0;
    bool even_flag = false;

    while (number > 0)
    {
        long last = number % 10;

        if (even_flag)
        {
            last *= 2;
        }

        sum += sum_digits(last);

        even_flag = !even_flag;

        number /= 10;
    }
    return sum % 10 == 0;
}

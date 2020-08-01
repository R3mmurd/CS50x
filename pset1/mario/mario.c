/*
Program that prints out a double half-pyramid of a specified .

Author: Alejandro Mujica (aledrums@gmail.com)
*/
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Get pyramid height
    int height = get_int("Height: ");

    while (height < 1 || height > 8)
    {
        height = get_int("Height: ");
    }

    // Generatin each pyramid step
    for (int i = 1; i <= height; ++i)
    {
        // Filling left empty spaces
        for (int j = 0; j < height - i; ++j)
        {
            printf(" ");
        }

        // Drawing left blocks
        for (int j = 0; j < i; ++j)
        {
            printf("#");
        }

        // Middle space
        printf("  ");

        // Drawing right blocks
        for (int j = 0; j < i; ++j)
        {
            printf("#");
        }

        printf("\n");
    }

    return 0;
}

/*
    Program that prints out a simple greeting to the user.

    Author: Alejandro Mujica (aledrums@gmail.com)
*/
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Ask for name
    string name = get_string("What's your name? ");

    // Greeting
    printf("hello, %s\n", name);

    return 0;
}

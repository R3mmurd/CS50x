/*
Program that encrypts messages using Caesar’s cipher.

Author: Alejandro Mujica (aledrums@gmail.com)
*/
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

void usage(char *argv[])
{
    printf("Usage: %s key\n", argv[0]);
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        usage(argv);
    }

    for (char *c = argv[1]; *c != '\0'; ++c)
    {
        if (*c < '0' || *c > '9')
        {
            usage(argv);
        }
    }

    int k = atoi(argv[1]) % 26;

    string text = get_string("plaintext: ");

    for (char *c = text; *c != '\0'; ++c)
    {
        if (*c >= 'A' && *c <= 'Z')
        {
            char new_letter = (*c - 'A' + k) % 26 + 'A';
            *c = new_letter;
        }
        else if (*c >= 'a' && *c <= 'z')
        {
            char new_letter = (*c - 'a' + k) % 26 + 'a';
            *c = new_letter;
        }
    }

    printf("ciphertext: %s\n", text);

    return 0;
}
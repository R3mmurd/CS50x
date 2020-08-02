/*
    Program that implements a substitution cipher.

    Author: Alejandro Mujica (aledrums@gmail.com)
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage %s key\n", argv[0]);
        return 1;
    }

    string key = argv[1];

    // Validating key length
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Table to ask for letter existance
    bool table[26];
    memset(table, 0, sizeof(bool) * 26);

    // Validating key
    for (int i = 0; i < 26; ++i)
    {
        char c = toupper(key[i]);

        // Check for alphabetic characters only
        if (c < 'A' || c > 'Z')
        {
            printf("Key must contain only alphabetic characters.\n");
            return 1;
        }

        int p = c - 'A';

        // Check for repeated characters
        if (table[p])
        {
            printf("Each character in key must appear only once.\n");
            return 1;
        }

        table[p] = true;
    }

    string text = get_string("plaintext: ");

    for (char *c = text; *c != '\0'; ++c)
    {
        if (*c >= 'A' && *c <= 'Z')
        {
            int i = *c - 'A';
            *c = toupper(key[i]);
        }

        if (*c >= 'a' && *c <= 'z')
        {
            int i = *c - 'a';
            *c = tolower(key[i]);
        }
    }

    printf("ciphertext: %s\n", text);

    return 0;
}
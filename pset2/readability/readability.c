/*
    Program that computes the approximate grade level needed to
    comprehend some text.

    Author: Alejandro Mujica (aledrums@gmail.com)
*/
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string text = get_string("Text: ");

    while (text == NULL)
    {
        text = get_string("Text: ");
    }

    int num_letters = 0;
    int num_words = 0;
    int num_sentences = 0;

    char *c = text;

    if (*c != '\n')
    {
        ++num_words;
    }

    while (*c != '\0')
    {
        if ((*c >= 'A' && *c <= 'Z') || (*c >= 'a' && *c <= 'z'))
        {
            ++num_letters;
        }
        else if (*c == ' ')
        {
            ++num_words;
        }
        else if (*c == '.' || *c == '!' || *c ==  '?')
        {
            ++num_sentences;
        }

        ++c;
    }

    double L = (double) num_letters / ((double) num_words) * 100.0;
    double S = (double) num_sentences / ((double) num_words) * 100.0;

    double index = index = 0.0588 * L - 0.296 * S - 15.8;

    int grade = index;

    if (index - grade >= 0.5)
    {
        ++grade;
    }

    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }

    return 0;
}

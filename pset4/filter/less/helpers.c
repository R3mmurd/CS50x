/*
    Algorithms to filter images.

    Base program by CS50
    Solution by: Alejandro Mujica (aledrums@gmail.com)
*/
#include "helpers.h"
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            RGBTRIPLE pixel = image[i][j];
            BYTE avg = round((pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            BYTE originalRed = image[i][j].rgbtRed;
            BYTE originalGreen = image[i][j].rgbtGreen;
            BYTE originalBlue = image[i][j].rgbtBlue;
            double sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            double sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            double sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;
            image[i][j].rgbtBlue = MIN(255, round(sepiaBlue));
            image[i][j].rgbtGreen = MIN(255, round(sepiaGreen));
            image[i][j].rgbtRed = MIN(255, round(sepiaRed));
        }
    }
    return;
}

#undef MIN

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int l = 0, r = width - 1; l < r; ++l, --r)
        {
            RGBTRIPLE tmp = image[i][l];
            image[i][l] = image[i][r];
            image[i][r] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*image_cpy)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            image_cpy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int num_colors = 0;
            int r = 0, g = 0, b = 0;

            for (int ip = i - 1; ip <= i + 1; ++ip)
            {
                if (ip < 0 || ip >= height)
                {
                    continue;
                }

                for (int jp = j - 1; jp <= j + 1; ++jp)
                {
                    if (jp < 0 || jp >= width)
                    {
                        continue;
                    }

                    r += image_cpy[ip][jp].rgbtRed;
                    g += image_cpy[ip][jp].rgbtGreen;
                    b += image_cpy[ip][jp].rgbtBlue;
                    ++num_colors;
                }
            }

            image[i][j].rgbtRed = round(r / ((double) num_colors));
            image[i][j].rgbtGreen = round(g / ((double) num_colors));
            image[i][j].rgbtBlue = round(b / ((double) num_colors));
        }
    }

    return;
}

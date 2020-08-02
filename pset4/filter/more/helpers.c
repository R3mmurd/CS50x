/*
    Algorithms to filter images.

    Base program by CS50
    Solution by: Alejandro Mujica (aledrums@gmail.com)
*/
#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>
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
            image[i][j].rgbtGreen = round(g /  ((double) num_colors));
            image[i][j].rgbtBlue = round(b /  ((double) num_colors));
        }
    }

    return;
}

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

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
            long xr = 0, xg = 0, xb = 0;
            long yr = 0, yg = 0, yb = 0;
            int counter = 0;

            for (int ip = i - 1, ik = 0; ip <= i + 1; ++ip, ++ik)
            {
                if (ip < 0 || ip >= height)
                {
                    continue;
                }

                for (int jp = j - 1, jk = 0; jp <= j + 1; ++jp, ++jk)
                {
                    if (jp < 0 || jp >= width)
                    {
                        continue;
                    }

                    xr += image_cpy[ip][jp].rgbtRed * Gx[ik][jk];
                    xg += image_cpy[ip][jp].rgbtGreen * Gx[ik][jk];
                    xb += image_cpy[ip][jp].rgbtBlue * Gx[ik][jk];

                    yr += (int)image_cpy[ip][jp].rgbtRed * Gy[ik][jk];
                    yg += (int)image_cpy[ip][jp].rgbtGreen * Gy[ik][jk];
                    yb += (int)image_cpy[ip][jp].rgbtBlue * Gy[ik][jk];

                    ++counter;
                }
            }

            int r = round(sqrt(xr * xr + yr * yr));
            int g = round(sqrt(xg * xg + yg * yg));
            int b = round(sqrt(xb * xb + yb * yb));

            image[i][j].rgbtRed = MIN(r, 255);
            image[i][j].rgbtGreen = MIN(g, 255);
            image[i][j].rgbtBlue = MIN(b, 255);
        }
    }

    return;
}

#undef MIN

#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sum = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            int average = round(sum / 3.0);
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = average;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2 ; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*new_image)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average_count = 0;
            float red_average = 0;
            float green_average = 0;
            float blue_average = 0;

            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (i + k >= 0 && i + k < height && j + l >= 0 && j + l < width)
                    {
                        average_count++;
                        red_average += image[i + k][j + l].rgbtRed;
                        green_average += image[i + k][j + l].rgbtGreen;
                        blue_average += image[i + k][j + l].rgbtBlue;
                    }
                }
            }

            new_image[i][j].rgbtRed = round(red_average / average_count);
            new_image[i][j].rgbtGreen = round(green_average / average_count);
            new_image[i][j].rgbtBlue = round(blue_average / average_count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = new_image[i][j].rgbtRed;
            image[i][j].rgbtGreen = new_image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = new_image[i][j].rgbtBlue;
        }
    }
    free(new_image);
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*new_image)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    int gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    float red;
    float green;
    float blue;
    float gx_red = 0;
    float gy_red = 0;
    float gx_green = 0;
    float gy_green = 0;
    float gx_blue = 0;
    float gy_blue = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            gx_red = 0;
            gy_red = 0;
            gx_green = 0;
            gy_green = 0;
            gx_blue = 0;
            gy_blue = 0;

            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (i + k >= 0 && i + k < height && j + l >= 0 && j + l < width)
                    {
                        gx_red += image[i + k][j + l].rgbtRed * gx[k + 1][l + 1];
                        gy_red += image[i + k][j + l].rgbtRed * gy[k + 1][l + 1];
                        gx_green += image[i + k][j + l].rgbtGreen * gx[k + 1][l + 1];
                        gy_green += image[i + k][j + l].rgbtGreen * gy[k + 1][l + 1];
                        gx_blue += image[i + k][j + l].rgbtBlue * gx[k + 1][l + 1];
                        gy_blue += image[i + k][j + l].rgbtBlue * gy[k + 1][l + 1];
                    }
                }
            }
            red = pow((pow(gx_red, 2.0) + pow(gy_red, 2.0)), 0.5);
            green = pow((pow(gx_green, 2.0) + pow(gy_green, 2.0)), 0.5);
            blue = pow((pow(gx_blue, 2.0) + pow(gy_blue, 2.0)), 0.5);

            if (red > 255)
            {
                new_image[i][j].rgbtRed = 255;
            }
            else
            {
                new_image[i][j].rgbtRed = red + 0.5;
            }

            if (green > 255)
            {
                new_image[i][j].rgbtGreen = 255;
            }
            else
            {
                new_image[i][j].rgbtGreen = green + 0.5;
            }

            if (blue > 255)
            {
                new_image[i][j].rgbtBlue = 255;
            }
            else
            {
                new_image[i][j].rgbtBlue = blue + 0.5;
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = new_image[i][j].rgbtRed;
            image[i][j].rgbtGreen = new_image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = new_image[i][j].rgbtBlue;
        }
    }
    free(new_image);
}

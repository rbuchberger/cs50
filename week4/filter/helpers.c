#include "helpers.h"
#include <math.h>
#include <stdio.h>

// RGBTRIPLE: An array which encapsulates 3 bytes in BGR order.
// you can access them with .rgbt(Blue|Green|Red)

// Convert image to grayscale
int root_sum_squares(int a, int b);

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            float avg = ((float)image[y][x].rgbtBlue + (float)image[y][x].rgbtGreen + (float)image[y][x].rgbtRed) / 3.0;

            image[y][x].rgbtBlue = (int)round(avg);
            image[y][x].rgbtGreen = (int)round(avg);
            image[y][x].rgbtRed = (int)round(avg);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width / 2; x++)
        {
            int x_prime = width - (x + 1);
            RGBTRIPLE temp = image[y][x];

            image[y][x] = image[y][x_prime];
            image[y][x_prime] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // We need a temporary space to store the new values.
    RGBTRIPLE temp_image[height][width];

    // Each row in the image
    for (int y = 0; y < height; y++)
    {
        // Each pixel
        for (int x = 0; x < width; x++)
        {
            int sum_red = 0;
            int sum_green = 0;
            int sum_blue = 0;
            int boxes = 0;

            // Each row in the 3x3 box
            for (int y2 = y - 1; y2 <= y + 1; y2++)
            {
                // Stay inside the bounds of the image
                if (y2 >= 0 && y2 < height)
                {
                    // Each column in the 3x3 box
                    for (int x2 = x - 1; x2 <= x + 1; x2++)
                    {
                        // Stay inside the bounds of the image
                        if (x2 >= 0 && x2 < width)
                        {
                            sum_red += image[y2][x2].rgbtRed;
                            sum_green += image[y2][x2].rgbtGreen;
                            sum_blue += image[y2][x2].rgbtBlue;
                            boxes++;
                        }
                    }
                }
            }

            // Set each color value to the average of its surroundings
            temp_image[y][x].rgbtRed = (int)round((float)sum_red / (float)boxes);
            temp_image[y][x].rgbtGreen = (int)round((float)sum_green / (float)boxes);
            temp_image[y][x].rgbtBlue = (int)round((float)sum_blue / (float)boxes);
        }
    }

    // Copy temp image values to original image.
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            image[y][x] = temp_image[y][x];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx_kernel[3][3] = 
    {
        { -1, 0, 1 },
        { -2, 0, 2 },
        { -1, 0, 1 }
    };

    int gy_kernel[3][3] = 
    {
        { -1, -2, -1 },
        { 0, 0, 0 },
        { 1, 2, 1 }
    };

    // We need a temporary space to store the new values.
    RGBTRIPLE temp_image[height][width];

    // Each row in the image
    for (int y = 0; y < height; y++)
    {
        // Each pixel in the row
        for (int x = 0; x < width; x++)
        {
            // Hold the sum value for Gx and Gy, red, green, and blue.
            int gx_r = 0;
            int gy_r = 0;

            int gy_g = 0;
            int gx_g = 0;

            int gy_b = 0;
            int gx_b = 0;

            // Each row in the 3x3 box
            for (int box_y = 0; box_y < 3; box_y++)
            {
                // Each pixel in the 3x3 box
                for (int box_x = 0; box_x < 3; box_x++)
                {
                    // Translate box position to an image position
                    int box_x_trans = x + (box_x - 1);
                    int box_y_trans = y + (box_y - 1);

                    // Stay inside the bounds of the image
                    if (box_x_trans >= 0
                        && box_y_trans >= 0
                        && box_x_trans < width
                        && box_y_trans < height)
                    {

                        RGBTRIPLE pixel = image[box_y_trans][box_x_trans];

                        int gx = gx_kernel[box_y][box_x];
                        int gy = gy_kernel[box_y][box_x];

                        gx_r += pixel.rgbtRed * gx;
                        gy_r += pixel.rgbtRed * gy;

                        gx_g += pixel.rgbtGreen * gx;
                        gy_g += pixel.rgbtGreen * gy;

                        gx_b += pixel.rgbtBlue * gx;
                        gy_b += pixel.rgbtBlue * gy;
                    }
                }
            }

            temp_image[y][x].rgbtRed = root_sum_squares(gx_r, gy_r);
            temp_image[y][x].rgbtGreen = root_sum_squares(gx_g, gy_g);
            temp_image[y][x].rgbtBlue = root_sum_squares(gx_b, gy_b);
        }
    }

    // Copy temp image values to original image.
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            image[y][x] = temp_image[y][x];
        }
    }

    return;
}

int root_sum_squares(int a, int b)
{
    float value = sqrt(pow(a, 2) + pow(b, 2));
    if (value > 255)
    {
        return 255;
    }
    else
    {
        return (int)round(value);
    }
}

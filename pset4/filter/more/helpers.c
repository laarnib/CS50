#include "helpers.h"
#include <math.h>

void swapPixel(RGBTRIPLE *leftPixel, RGBTRIPLE *rightPixel);


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int averagePixelValue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculates the average of the pixel values of red, green, and blue
            averagePixelValue = (int) round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00);

            // Sets each color to the calculated average pixel value
            image[i][j].rgbtBlue = averagePixelValue;
            image[i][j].rgbtGreen = averagePixelValue;
            image[i][j].rgbtRed = averagePixelValue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int mid, tempRed, tempBlue, tempGreen;

    mid = width / 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < mid; j++)
        {
            // Swaps the pixels
            swapPixel(&image[i][j], &image[i][width - j - 1]);
        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurredImage[height][width];
    int i, j, redSum, greenSum, blueSum;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            redSum = 0;
            greenSum = 0;
            blueSum = 0;
            float counter = 0;

            // Get the new (blurred) value of the pixel by averaging the neighboring values within
            // one row and column of the original pixel
            for (int neighborRow = -1; neighborRow <= 1; neighborRow++)
            {
                for (int neighborColumn = -1; neighborColumn <= 1; neighborColumn++)
                {
                    // Check if pixel is valid
                    if (i + neighborRow < 0 || i + neighborRow >= height || j + neighborColumn < 0 || j + neighborColumn >= width)
                    {
                        continue;
                    }

                    redSum += image[i + neighborRow][j + neighborColumn].rgbtRed;
                    greenSum += image[i + neighborRow][j + neighborColumn].rgbtGreen;
                    blueSum += image[i + neighborRow][j + neighborColumn].rgbtBlue;

                    counter++;
                }
            }

            blurredImage[i][j].rgbtRed = round(redSum / counter);
            blurredImage[i][j].rgbtGreen = round(greenSum / counter);
            blurredImage[i][j].rgbtBlue = round(blueSum / counter);
        }
    }


    // Copy the pixel values of the blurred image to the pixels of the original image
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = blurredImage[i][j].rgbtRed;
            image[i][j].rgbtGreen = blurredImage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = blurredImage[i][j].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE edgedImage[height][width];
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int i, j;

    for (i = 0; i < height; i++)
    {
        int redGx, greenGx, blueGx, redGy, greenGy, blueGy, red, green, blue;
        for (j = 0; j < width; j++)
        {
            redGx = 0;
            greenGx = 0;
            blueGx = 0;

            redGy = 0;
            greenGy = 0;
            blueGy = 0;

            for (int neighborRow = -1; neighborRow <= 1; neighborRow++)
            {
                for (int neighborColumn = -1; neighborColumn <= 1; neighborColumn++)
                {
                    // If pixel is past the border, set the channel values to zero.
                    if (i + neighborRow < 0 || i + neighborRow >= height || j + neighborColumn < 0 || j + neighborColumn >= width)
                    {
                        // Compute the Gx value for each channel
                        redGx += gx[neighborRow + 1][neighborColumn + 1] * 0;
                        greenGx += gx[neighborRow + 1][neighborColumn + 1] * 0;
                        blueGx += gx[neighborRow + 1][neighborColumn + 1] * 0;

                        // Compute Gy value for each channel
                        redGy += gy[neighborRow + 1][neighborColumn + 1] * 0;
                        greenGy += gy[neighborRow + 1][neighborColumn + 1] * 0;
                        blueGy += gy[neighborRow + 1][neighborColumn + 1] * 0;

                        continue;
                    }

                    // Compute the Gx value for each channel
                    redGx += gx[neighborRow + 1][neighborColumn + 1] * image[i + neighborRow][j + neighborColumn].rgbtRed;
                    greenGx += gx[neighborRow + 1][neighborColumn + 1] * image[i + neighborRow][j + neighborColumn].rgbtGreen;
                    blueGx += gx[neighborRow + 1][neighborColumn + 1] * image[i + neighborRow][j + neighborColumn].rgbtBlue;

                    // Compute the Gy value for each channel
                    redGy += gy[neighborRow + 1][neighborColumn + 1] * image[i + neighborRow][j + neighborColumn].rgbtRed;
                    greenGy += gy[neighborRow + 1][neighborColumn + 1] * image[i + neighborRow][j + neighborColumn].rgbtGreen;
                    blueGy += gy[neighborRow + 1][neighborColumn + 1] * image[i + neighborRow][j + neighborColumn].rgbtBlue;
                }
            }

            // Get the new value of each color by squaring the sum of gx squared and gy squared
            // Round the resulting value and then cast it to an int because the sqrt() returns a double
            red = (int) round(sqrt((redGx * redGx) + (redGy * redGy)));
            green = (int) round(sqrt((greenGx * greenGx) + (greenGy * greenGy)));
            blue = (int) round(sqrt((blueGx * blueGx) + (blueGy * blueGy)));

            edgedImage[i][j].rgbtRed = red > 255 ? 255 : red;
            edgedImage[i][j].rgbtGreen = green > 255 ? 255 : green;
            edgedImage[i][j].rgbtBlue = blue > 255 ? 255 : blue;
        }
    }

    // Copy the pixel values of the edged image to the pixels of the original image
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = edgedImage[i][j].rgbtRed;
            image[i][j].rgbtGreen = edgedImage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = edgedImage[i][j].rgbtBlue;
        }
    }
    return;
}

// Added by : Laarni
// Swaps the left and right pixels
void swapPixel(RGBTRIPLE *leftPixel, RGBTRIPLE *rightPixel)
{
    int tempRed, tempGreen, tempBlue;

    tempRed = leftPixel->rgbtRed;
    tempGreen = leftPixel->rgbtGreen;
    tempBlue = leftPixel->rgbtBlue;

    leftPixel->rgbtRed = rightPixel->rgbtRed;
    leftPixel->rgbtGreen = rightPixel->rgbtGreen;
    leftPixel->rgbtBlue = rightPixel->rgbtBlue;

    rightPixel->rgbtRed = tempRed;
    rightPixel->rgbtGreen = tempGreen;
    rightPixel->rgbtBlue = tempBlue;
}

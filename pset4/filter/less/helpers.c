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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaGreen, sepiaBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculates the sepia values of each color
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            // Sets each color to the calculated sepia value
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
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

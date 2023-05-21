#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
            average = round(average);
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = average;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int tmpblue = 0;
    int tmpgreen = 0;
    int tmpred = 0;

    for (int i = 0; i < height - 1; i++)
    {
        for (int j = 0; j < width - 1; j++)
        {
            if (width - j == j)
            {
                break;
            }

            tmpblue = image[i][j].rgbtBlue;
            tmpgreen = image[i][j].rgbtGreen;
            tmpred = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j].rgbtRed;

            image[i][width - j].rgbtBlue = tmpblue;
            image[i][width - j].rgbtGreen = tmpgreen;
            image[i][width - j].rgbtRed = tmpred;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Copiar imagem original
    RGBTRIPLE copyimage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copyimage[i][j].rgbtBlue = image[i][j].rgbtBlue;
            copyimage[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copyimage[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }

    //Alterar imagem original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalblue, totalgreen, totalred;
            totalblue = totalgreen = totalred = 0;
            int counter_soma = 0;

            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int currentX = x + i;
                    int currentY = y + j;

                    if (currentX < 0 || currentY < 0 || currentX > (height - 1) || currentY > (width - 1))
                    {
                        continue;
                    }

                    totalblue += copyimage[currentX][currentY].rgbtBlue;
                    totalgreen += copyimage[currentX][currentY].rgbtGreen;
                    totalred += copyimage[currentX][currentY].rgbtRed;

                    counter_soma++;
                }
            }

            image[i][j].rgbtBlue = round(totalblue / counter_soma);
            image[i][j].rgbtGreen = round(totalgreen / counter_soma);
            image[i][j].rgbtRed = round(totalred / counter_soma);
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copyimage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copyimage[i][j] = image[i][j];
        }
    }

    int gx[3][3] = {
        {-1,  0,  1},
        {-2,  0,  2},
        {-1,  0,  1}
    };

    int gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalBlueX, totalGreenX, totalRedX, totalBlueY, totalGreenY, totalRedY;
            totalBlueX = totalGreenX = totalRedX = totalBlueY = totalGreenY = totalRedY = 0;

            for (int a = -1; a < 2; a++)
            {
                for (int b = -1; b < 2; b++)
                {
                    int currentX = i + a;
                    int currentY = j + b;

                    int row = a + 1;
                    int col = b + 1;

                    totalBlueX += gx[row][col] * copyimage[currentX][currentY].rgbtBlue;
                    totalGreenX += gx[row][col] * copyimage[currentX][currentY].rgbtGreen;
                    totalRedX += gx[row][col] * copyimage[currentX][currentY].rgbtRed;

                    totalBlueY += gy[row][col] * copyimage[currentX][currentY].rgbtBlue;
                    totalGreenY += gy[row][col] * copyimage[currentX][currentY].rgbtGreen;
                    totalRedY += gy[row][col] * copyimage[currentX][currentY].rgbtRed;
                }
            }

            int newb = round(sqrt(totalBlueX * totalBlueX + totalBlueY * totalBlueY));
            int newg = round(sqrt(totalGreenX * totalGreenX + totalGreenY * totalGreenY));
            int newr = round(sqrt(totalRedX * totalRedX + totalRedY * totalRedY));

            if (newb > 255)
            {
                newb = 255;
            }
            if (newg > 255)
            {
                newg = 255;
            }
            if (newr > 255)
            {
                newr = 255;
            }

            image[i][j].rgbtBlue = newb;
            image[i][j].rgbtGreen = newg;
            image[i][j].rgbtRed = newr;
        }
    }

    return;
}
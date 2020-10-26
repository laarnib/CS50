#include<stdio.h>
#include<cs50.h>


int get_pyramid_height(void);
void print_pyramid(int height);

int main(void)
{
    int height;

    height = get_pyramid_height();
    print_pyramid(height);

    return 0;
}

// Gets the pyramid's height, a positive numeric value between 1 and 8
int get_pyramid_height(void)
{
    int height;

    // get pyramid height
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    return height;
}

// Prints the pyramid
void print_pyramid(int height)
{
    int row, hash, space;

    for (row = height; row > 0; row--)
    {
        // print the spaces
        for (space = 1; space <= row - 1; space++)
        {
            printf(" ");
        }

        // print the hashes
        space--;
        for (hash = 1; hash <= height - space; hash++)
        {
            printf("#");
        }

        printf("\n");
    }
}



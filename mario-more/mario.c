#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get pyramid height and set initial number of hashes
    int height = 0;
    while (height > 8 || height < 1)
    {
        height = get_int("Height: ");
    }
    int num_hashes = 1;

    // Print pyramid
    while (height > 0) {
        for (int i = 1; i < height; i++)
        {
            printf(" ");
        }
        for (int i = 0; i < num_hashes; i++)
        {
            printf("#");
        }
        printf("  ");
        for (int i = 0; i < num_hashes; i++)
        {
            printf("#");
        }
        printf("\n");
        num_hashes++;
        height--;
    }
}
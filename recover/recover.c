#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

const int BLOCK_SIZE = 512;
const int FILE_NAME_LENGTH = 8;

int main(int argc, char *argv[])
{

    // Check for correct # of arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open memory card
    FILE *file = fopen(argv[1], "r");

    // Check if file can be read
    if (file == NULL)
    {
        printf("File cannot be read\n");
        return 1;
    }

    FILE *jpg;
    uint8_t block[BLOCK_SIZE];
    int file_num = 0;
    bool opened = false;

    // Read into memory and write to new files
    while (fread(block, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] >= 0xe0 && block[3] <= 0xef))
        {
            if (opened)
            {
                fclose(jpg);
            }
            char file_name[FILE_NAME_LENGTH];
            sprintf(file_name, "%03d.jpg", file_num);
            jpg = fopen(file_name, "a");
            opened = true;
            file_num++;
        }
        if (opened)
        {
            fwrite(block, 1, BLOCK_SIZE, jpg);
        }
    }
    fclose(jpg);
    fclose(file);
}
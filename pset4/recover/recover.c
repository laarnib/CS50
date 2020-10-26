#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCKSIZE 512
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Checks that the user specified the name of the forensic image file as a command-line argument
    if (argc != 2)
    {
        printf("Usage ./recover image\n");
        return 1;
    }

    // Checks if the correct forensic image file is entered
    if (strcmp(argv[1], "card.raw") != 0)
    {
        printf("That is not the correct file.\n");
        return 1;
    }

    // Open the forensic image file
    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("%s File can't be opened.\n", argv[1]);
    }
    else
    {
        BYTE buffer[BLOCKSIZE];
        char newFilename[8];
        int filenumber = 0;
        bool isAnotherJpeg = false;
        FILE *newFile;
        int jpegCounter = 0;

        // Read the file until end of the file is reached
        while (fread(buffer, sizeof(BYTE), BLOCKSIZE, file) == BLOCKSIZE)
        {
            // Check if the start of a 512-byte block is the start of a jpeg file
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                // Check if it's another jpeg file
                if (isAnotherJpeg == false)
                {
                    sprintf(newFilename, "%03i.jpg", jpegCounter++);
                    newFile = fopen(newFilename, "w");

                    // Write in 512 bytes until a new JPEG file is found
                    fwrite(buffer, sizeof(BYTE), BLOCKSIZE, newFile);
                }
                else
                {
                    fclose(newFile);
                }
            }
            else
            {
                fwrite(buffer, sizeof(BYTE), BLOCKSIZE, newFile);
            }
        }
    }

    fclose(file);

    return 0;
}

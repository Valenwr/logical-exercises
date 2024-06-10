#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Create an array of 512 elements to store 512 bytes from the memory card
    uint8_t buffer[512];
    // String to hold a filename
    char file[8] = {0};
    // Output pointer
    FILE *outptr = NULL;
    // Number of jpeg files found
    int jpeg_counter = 0;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Create JPEGs from the data
        if (buffer[0] == 0xff & buffer[1] == 0xd8 & buffer[2] == 0xff & (buffer[3] & 0xf0) == 0xe0)
        {
            if (outptr != NULL)
            {
                fclose(outptr);
            }

            sprintf(file, "%03i.jpg", jpeg_counter);
            jpeg_counter++;

            outptr = fopen(file, "w");
        }

        if (outptr != NULL)
        {
            fwrite(buffer, 1, 512, outptr);
        }
    }

    fclose(outptr);
    fclose(card);
}

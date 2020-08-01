/*
Program that recovers JPEGs from a forensic image.

Author: Alejandro Mujica (aledrums@gmail.com)
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s image\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    BYTE bs[512];

    int num_file = 0;

    FILE *new_jpg = NULL;
    char file_name[8];

    int num_read_elements = fread(bs, sizeof(BYTE), 512, file);

    while (num_read_elements > 0)
    {
        if (num_read_elements >= 4 && bs[0] == 0xff && bs[1] == 0xd8 && bs[2] == 0xff && (bs[3] & 0xf0) == 0xe0)
        {
            // Jepg header detected

            // Close the last opened file if it is opened
            if (new_jpg != NULL)
            {
                fclose(new_jpg);
            }

            // Generating new file name
            sprintf(file_name, "%03i.jpg", num_file);
            new_jpg = fopen(file_name, "w");
            ++num_file;
        }

        if (new_jpg != NULL)
        {
            fwrite(bs, sizeof(BYTE), 512, new_jpg);
        }

        num_read_elements = fread(bs, sizeof(BYTE), 512, file);
    }

    if (new_jpg != NULL)
    {
        fclose(new_jpg);
    }

    fclose(file);
}


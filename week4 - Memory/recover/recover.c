#include <errno.h>   // errno
#include <stdbool.h> // bool
#include <stdint.h>  // uint8_t (for BYTE)
#include <stdio.h>   // f*, *printf, NULL, stderr
#include <string.h>  // strerror


// Block size in FAT filesystems, in bytes
#define BLOCKSIZE 512

typedef uint8_t BYTE;


// Check data for JPEG signature
bool is_jpg(BYTE data[BLOCKSIZE])
{
    if (data[0] == 0xFF &&
        data[1] == 0xD8 &&
        data[2] == 0xFF &&
        (data[3] & 0xF0) == 0xE0)
    {
        return true;
    }
    return false;
}


int main(int argc, char *argv[])
{
    // Get the input path from command-line arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s IMAGE\n", argv[0]);
        return 1;
    }
    char *inpath = argv[1];

    // Open the input file
    FILE *infile = fopen(inpath, "rb");
    if (infile == NULL)
    {
        fprintf(stderr, "%s: %s\n", strerror(errno), inpath);
        return 2;
    }

    // Loop the input file data
    int idx = 0;
    char outpath[sizeof("000.jpg")];
    FILE *outfile = NULL;
    BYTE data[BLOCKSIZE];
    while (fread(data, sizeof(data), 1, infile))
    {
        // Check if there is a JPEG in this data block
        if (is_jpg(data))
        {
            // Close previous file, if any.
            if (outfile)
            {
                fclose(outfile);
            }

            // Open new output file
            sprintf(outpath, "%03i.jpg", idx++);
            if ((outfile = fopen(outpath, "w")) == NULL)
            {
                fprintf(stderr, "Could not create %s: %s\n",
                        outpath, strerror(errno));
                fclose(infile);
                return 3;
            }
        }

        // If in a jpg, write data
        if (outfile)
        {
            fwrite(data, sizeof(data), 1, outfile);
        }
    }

    // Close open files
    if (outfile)
    {
        fclose(outfile);
    }
    fclose(infile);
}

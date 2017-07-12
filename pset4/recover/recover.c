#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }
    
    char *infile = argv[1];
    
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    
    uint8_t buffer[512];
    int i = 0;
    int found = 0;
    FILE *img;

    while(fread(buffer, 512, 1, inptr) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if(i > 0)
                fclose(img);
                
            found = 1; 
            char filename[8];
            sprintf(filename, "%03i.jpg", i);
            img = fopen(filename, "w");
            i++;
        }
        
        if(found == 1)
            fwrite( buffer, 512, 1, img);
    }
    
    fclose(img);
  
    return 0;
}
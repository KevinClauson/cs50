#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TOTAL_ALPHA 26

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("INVALID ENTRY\n");
        return 1;
    }
    int i = 0;
    int key = atoi(argv[1]);
    
    printf("plaintext: ");
    string p = get_string();
    
    printf("ciphertext: ");
    
    while(p[i])
    {
        if(isupper(p[i]))
            printf("%c", (((p[i] - 'A') + key) % TOTAL_ALPHA) + 'A');
        else if(islower(p[i]))
            printf("%c", (((p[i] - 'a') + key) % TOTAL_ALPHA) + 'a');
        else
            printf("%c", p[i]);
            
        i++;
    }

    printf("\n");
    return 0;
}
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
    
    while(argv[1][i])
    {
        if(!isalpha(argv[1][i]))
        {
            printf("INVALID ENTRY\n");
            return 1;  
        }
        argv[1][i] = toupper(argv[1][i]);
        ++i;
    }
    int len_argv = i;
    
    printf("plaintext: ");
    string p = get_string();
    
    printf("ciphertext: \n");
    
    int j = 0;
    int t = 0;
    
    while(p[j])
    {
        if(isupper(p[j]))
        {
            printf("%c", (((p[j] - 'A') + (argv[1][(t%len_argv)] - 'A')) % TOTAL_ALPHA) + 'A');
            t++;
        }
        else if(islower(p[j]))
        {
            printf("%c", (((p[j] - 'a') + (argv[1][(t%len_argv)] - 'A')) % TOTAL_ALPHA) + 'a');
            t++;
        }
        else
            printf("%c", p[j]);
            
        j++;           
    }

    printf("\n");
    return 0;
}
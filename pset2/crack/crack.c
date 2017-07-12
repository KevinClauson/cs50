#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <crypt.h>
#include <string.h>

#define _XOPEN_SOURCE
#define JUMP_TO_a 6
#define ONE_PAST_Z 91

int main(int argc, string argv[])
{
    if(argc != 2)
        {
            printf("INVALID ENTRY\n");
            return 1;
        }
    
    char i, j, k, m;
    
    const char *salt = "50";
    
    for(i= 'A'; i <= 'z'; i++)
    {
        if(i == ONE_PAST_Z)
            i += JUMP_TO_a;
        char arr[5];
        arr[0] = i;
        arr[1] = '\0';
        //printf("%s, %s\n", arr, crypt(arr, salt));
        if(!strcmp(argv[1], crypt(arr, salt)))
        {
            printf("%s\n", arr);
            return 0;
        }
       
        for(j = 'A'; j <= 'z'; j++)
        {   
            if(j == ONE_PAST_Z)
                j += JUMP_TO_a;
            arr[0] = i;
            arr[1] = j;
            arr[2] = '\0';
            //printf("%s, %s\n", arr, crypt(arr, salt));
            if(!strcmp(argv[1], crypt(arr, salt)))
            {
                printf("%s\n", arr);
                return 0;
            }
            
            for(k = 'A'; k <= 'z'; k++)
            {
                if(k == ONE_PAST_Z)
                    k += JUMP_TO_a;
                arr[0] = i;
                arr[1] = j;
                arr[2] = k;
                arr[3] = '\0';
                //printf("%s, %s\n", arr, crypt(arr, salt));
                if(!strcmp(argv[1], crypt(arr, salt)))
                {
                    printf("%s\n", arr);
                    return 0;
                }
            
                for(m = 'A'; m <= 'z'; m++)
                {
                    if(m == ONE_PAST_Z)
                        m += JUMP_TO_a;
                    arr[0] = i;
                    arr[1] = j;
                    arr[2] = k;
                    arr[3] = m;
                    arr[4] = '\0';
                    //printf("%s, %s\n", arr, crypt(arr, salt));
                    if(!strcmp(argv[1], crypt(arr, salt)))
                    {
                        printf("%s\n", arr);
                        return 0;
                    }
                }   
            }
                
        }
    }
    
    
    return 0;       
}
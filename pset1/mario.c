#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n, i, k;
    
    do
    {
        printf("Height: ");
        n = get_int();
    }
    while(n < 0 || n > 23);
    
    for(i=0; i < n; i++)
    {
        for(k=0; k < n - 1 - i; k++)
            printf(" ");
            
        for(k=0; k < i+1; k++)
            printf("#");
            
        printf("  ");
        
        for(k=0; k < i+1; k++)
            printf("#");
            
        printf("\n");
    }
    
    
    
}
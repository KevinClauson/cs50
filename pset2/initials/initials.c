#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    string name = get_string();
    int i = 0;
    
    while(name[i])
    {
        name[i] = toupper(name[i]);
        if((i == 0 || name[i-1] == ' ') && (name[i] >= 'A' && name[i] <= 'Z'))
            printf("%c", name[i]);
        ++i;
    }
    printf("\n");
}
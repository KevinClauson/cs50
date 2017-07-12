#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long long cc_num;
    int r, j, i = 0, sum = 0;
    int amex_flag = 0, visa_flag = 0, master_flag = 0;
    
    doupdate
    {
        printf("Number: ");
        cc_num = get_long_long();
    }
    while(cc_num < 0 || cc_num > 9999999999999999);
                                 
    while(cc_num != 0)
    {
        i++;
        r = cc_num % 10;
        
        if(i % 2 == 0)
        {
            j = r * 2;
            if(j < 10)
                sum += j;
            else
                sum += (j % 10) + 1;
        }
        else
            sum += r;
        
        if(cc_num == 34 || cc_num == 37)
            amex_flag = 1;
        else if(cc_num < 56 && cc_num > 50)
            master_flag = 1;
        else if(cc_num == 4)
            visa_flag = 1;
        
        cc_num /= 10;
    }
    
    if(sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    else if((visa_flag == 1) && (i == 16 || i == 13))
    {
        printf("VISA\n");
        return 0;
    }
    else if(amex_flag == 1 && i == 15)
    {
        printf("AMEX\n");
        return 0;
    }
    else if(master_flag == 1 && i == 16)
    {
        printf("MASTERCARD\n");
        return 0;
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }
}
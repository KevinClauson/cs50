/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include "helpers.h"

#define MAX2 65536

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if(n <= 0)
        return false;
    
    //int i;
    int start = 0;
    int end = n - 1;
    int mid;
    
    while(start <= end)
    {
        mid  = (start + end) / 2;
        // question here is if i put in check for values[start] == value || values[end] == value would it make it faster
        if(values[mid] == value)
            return true;
        else
        {
            if(values[mid] < value)
            {
                start = mid + 1;
            }
            else
            {
                end = mid - 1;
            }
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int i, j;
    int count_arr[MAX2] = {0};
    for( i = 0; i < n; i++ )
    {
        count_arr[values[i]] += 1;
    }
    
    int t;
    for( i = 0, j = 0; j < n; i++)
    {
        if(count_arr[i] == 1)
        {
            values[j] = i;
            j++;
        }
        else if(count_arr[i] > 1)
        {
            for(t=0; t < count_arr[i]; t++)
            {
                values[j] = i;
                j++;
            }
        }
    }
}

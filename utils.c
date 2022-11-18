#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int* get_prefix_array(char* pattern)
{
    // allocate space for prefix array
    int* pfx_arr;
    pfx_arr = malloc(sizeof(int)*(strlen(pattern)));

    // set first value to 0
    pfx_arr[0] = 0;

    int k, i;
    k = 0;
    for (i = 1; i < strlen(pattern); i++)
    {
        while ( (k > 0) && (pattern[k] != pattern[i]) )
            k = pfx_arr[k];
        if (pattern[k] == pattern[i])
            k = k + 1;
        pfx_arr[i] = k;
    }
    return pfx_arr;
}

int knuth_morris_pratt(char* text, char* pattern)
{
    int* pfx_arr, n, m;
    n = strlen(text);
    m = strlen(pattern);

    pfx_arr = get_prefix_array(pattern);

    int count, shift, i;
    count = 0;
    shift = -1;
    for (i = 0; i < n; i++)
    {
        while ( (count > 0) && (pattern[count] != text[i]))
            count = pfx_arr[count];
        if (pattern[count] == text[i])
            count = count + 1;
        if (count == m)
        {
            shift = i - m + 1;
            break;
        }
    }
    return shift;
}
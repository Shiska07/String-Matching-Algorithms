#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int* get_prefix_array(char* pattern)
{
    // allocate space for prefix array
    int* pfx_arr;
    pfx_arr = malloc(sizeof(int)*strlen(pattern));

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

float* get_decimal_array(char* str)
{
    float* dec_arr;
    dec_arr = malloc(sizeof(float)*strlen(str));

    int i;
    char ch;
    for (i = 0; i < strlen(str); i++)
    {
        ch = str[i];
        dec_arr[i] = (float)((int)ch) - 65;
    }
    return dec_arr;
}

int robin_karp(char* text, char* pattern)
{
    int n,m;
    n = strlen(text);
    m = strlen(pattern);
    
    d_text = get_decimal_array(text);
    d_pattern = get_decimal_array(pattern);

    int i;
    for (i = 0; i < n; i++)
    {
        printf("%f ", d_text[i]);
    }
    return -1;
}

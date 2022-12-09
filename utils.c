#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "utils.h"

#define MAX_CHARS 256

// The naive string matching algorithm
// Running time: O(nm)
int naive_string_matcher(char *text, char *pattern)
{

    int n, m, i, j, count, match_count;
    match_count = 0;
    n = strlen(text);
    m = strlen(pattern);
    for (i = 0; i <= (n - m); i++)
    {
        j = 0;
        count = 0;
        while (text[i+j] == pattern[j])  // characters match
        {
            count = count + 1;
            j = j + 1;
            if (count == m)
            {
                match_count = match_count + 1;
                printf("Match found at index %d.\n", i);
                break;
            }
        }
    }
    return match_count;
}

// Rabin-karp string matcher
// Running time: worst case: O((nm) Average case: O(n + m)
int rabin_karp_matcher(char *text, char *pattern)
{
    int i, j, n, m, p_hash, t_hash, q, h, match_count, count;
    
    n = strlen(text);
    m = strlen(pattern);
    h = 1;
    p_hash = 0;
    t_hash = 0;
    match_count = 0;

    // as d is 75, d*q should fit within an unsigned int
    q = INT_MAX;

    // calculate the value of h for the pattern
    for (i = 0; i < (m - 1); i++)
        h = (h * MAX_CHARS) % q;

    // calculate hash value for pattern
    for (i = 0; i < m; i++) {
        p_hash = (MAX_CHARS * p_hash + pattern[i]) % q;
        t_hash = (MAX_CHARS * t_hash + text[i]) % q;
    }
    
    // calculate hash values and compare for remaining text
    for (i = 0; i <= (n - m); i++)
    {
        // if hash values are same check for pattern matching
        if (p_hash == t_hash)
        {
            count = 0;
            for (j = 0; j < m; j++)
            {
                if (text[j + i] == pattern[j])
                    count = count + 1;
                else
                    break;
            }
            if (count == m)
            {
                printf("Match found at index %d.\n", i);
                match_count = match_count + 1;
            }
        }

        // calculate hash value by removing leading digit and adding trailing digit
        if (i < n - m )
        {
            t_hash = (MAX_CHARS * (t_hash - (text[i] * h)) + text[i + m]) % q;
            if (t_hash < 0)
                t_hash = t_hash + q;
        }

    }
    return match_count;
}

// knuth_morris _pratt helper function: returns prefix array for a given string
// Running time: O(m)
int* compute_prefix_function(char *pattern)
{
    // allocate space for prefix array
    int *pfx_arr, m;
    m = strlen(pattern);
    pfx_arr = malloc(sizeof(int)*strlen(pattern));

    // set first value to 0
    pfx_arr[0] = 0;

    int k, i;
    k = 0;
    for (i = 1; i < m; i++)
    {
        while ( (k > 0) && (pattern[k] != pattern[i]) )
            k = pfx_arr[k-1];
        if (pattern[k] == pattern[i])
            k = k + 1;
        pfx_arr[i] = k;
    }
    return pfx_arr;
}

// knuth_morris_pratt matcher
// Running time: O(n)
int KMP_matcher(char *text, char *pattern)
{
    int *pfx_arr, n, m;
    n = strlen(text);
    m = strlen(pattern);

    pfx_arr = compute_prefix_function(pattern);

    int count, match_count, i;
    count = 0;
    match_count = 0;

    for (i = 0; i < n; i++)
    {
        while ( (count > 0) && (pattern[count] != text[i]))
            count = pfx_arr[count-1];
        if (pattern[count] == text[i])
            count = count + 1;
        if (count == m)
        {
            printf("Match found at index %d.\n", (i - m + 1));
            match_count = match_count + 1;
            count = pfx_arr[count-1];
        }
    }

    free(pfx_arr);
    return match_count;
}


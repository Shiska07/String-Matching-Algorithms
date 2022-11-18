#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/stat.h>
#include "utils.h"

char* text = NULL;
char* pattern = NULL;

void get_file_contents(char* argv[])
{
    
    char filename[100];
    char mode[] = "r";

    // get filename and desired string matching algorithm from command line
    strcpy(filename, *(argv + 1));

    FILE *fp = fopen(filename, mode);

    if (fp == NULL)
    {
        printf("file %s cannot be opened or does not exist.\n", filename);
        exit(0);
    }

    // get file size to alloate memory for text and pattern strings
    struct stat st;
    stat(filename, &st);
    long int f_size = st.st_size;

    text = malloc(sizeof(char)*f_size);
    pattern = malloc(sizeof(char)*f_size);

    fgets(text, f_size, fp);
    fgets(pattern, f_size, fp);

    // replace trailing '\n' with '\0'
    text[strlen(text)-2] = '\0';
    pattern[strlen(pattern)-2] = '\0';

    fclose(fp);
}


int main(int argc, char *argv[])
{
    
    get_file_contents(argv);

    int match_count_kmp, match_count_rk;
    match_count_kmp = 0;
    match_count_rk = 0;

    // call KMP to find match
    match_count_kmp = knuth_morris_pratt(text, pattern);

    if (match_count_kmp == 0)
    {
        printf("No matches found with Knuth-Morris-Pratt.\n");
    }
    else
    {
        printf("A total of %d match/es found with Knuth-Morris-Pratt.\n\n", match_count_kmp);
    }

    // call robin-karp to find match
    match_count_rk = robin_karp(text, pattern);

    if (match_count_rk == 0)
    {
        printf("No matches found with Robin_Karp.\n");
    }
    else
    {
        printf("A total of %d match/es found with Robin_Karp.\n\n", match_count_rk);
    }

    free(text);
    free(pattern);

    return 0;
}

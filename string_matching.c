#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "utils.h"

char* text = NULL;
char* pattern = NULL;

void read_file(char *argv[])
{
    
    char text_filename[100];
    char pattern_filename[100];
    char mode[] = "r";
    struct stat st1;
    struct stat st2;
    char ch;

    // get filename and desired string matching algorithm from command line
    strcpy(text_filename, *(argv + 1));
    strcpy(pattern_filename, *(argv + 2));


    // read text file
    FILE *fp1 = fopen(text_filename, mode);
    if (fp1 == NULL)
    {
        printf("%s cannot be opened or does not exist.\n", text_filename);
        exit(0);
    }

    // get file size to alloate memory for text and pattern strings
    stat(text_filename, &st1);
    long int f_size = st1.st_size;
    stat(pattern_filename, &st2);
    long int p_size = st2.st_size;

    text = malloc(sizeof(char)*f_size);
    pattern = malloc(sizeof(char)*p_size);

    // copy data from file into text array
    int n = 0;
    while ((ch = fgetc(fp1)) != EOF)
    {
        text[n++] = (char)ch;
    }
    text[n] = '\0';

    // printf("%s has a length of %d.\n", text, (int)strlen(text));

    fclose(fp1);

    // read pattern file
    FILE *fp2 = fopen(pattern_filename, mode);

    if (fp2 == NULL)
    {
        printf("%s cannot be opened or does not exist.\n", pattern_filename);
        exit(0);
    }

    // copy data from file into pattern array
    n = 0;
    while ((ch = fgetc(fp2)) != EOF)
    {
        pattern[n++] = (char)ch;
    }
    pattern[n] = '\0';

    // printf("%s has a length of %d.\n", pattern, (int)strlen(pattern));

    fclose(fp2);
}

int main(int argc, char *argv[])
{
    
    read_file(argv);

    int match_count;
    char algorithm[100];
    float time_diff, nano;
    struct timespec start, end;

    time_diff = 0.0;
    nano = 1000000000;
    match_count = 0;

    if (atoi(argv[3]) == 0)
    {
        strcpy(algorithm, "Naive String Matching");

        // call naive string matcher to find match
        clock_gettime(CLOCK_MONOTONIC, &start);
        match_count = naive_string_matcher(text, pattern);
        clock_gettime(CLOCK_MONOTONIC, &end);
    }
    else if (atoi(argv[3]) == 1)
    {
        strcpy(algorithm, "Rabin-Karp");

        // call rabin-karp to find match
        clock_gettime(CLOCK_MONOTONIC, &start);
        match_count = rabin_karp_matcher(text, pattern);
        clock_gettime(CLOCK_MONOTONIC, &end);
    }
    else
    {
        strcpy(algorithm, "Knuth-Morris-Pratt");

        // call KMP to find match
        clock_gettime(CLOCK_MONOTONIC, &start);
        match_count = KMP_matcher(text, pattern);
        clock_gettime(CLOCK_MONOTONIC, &end);
    }
    
    if (match_count == 0)
    {
        printf("No matches found with %s.\n", algorithm);
    }
    else
    {
        printf("A total of %d match/es found with %s.\n\n", match_count, algorithm);
    }

    // convert nano seconds to seconds and add to number of seconds elapsed
    time_diff = (float)((end.tv_sec - start.tv_sec) + ((end.tv_nsec - start.tv_nsec)/nano));
    printf("Time elapsed: %f seconds.\n", time_diff);
    
    free(text);
    free(pattern);

    return 0;
}


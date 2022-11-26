#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/stat.h>
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

    // get filename and desired string matching algorithm from command line
    strcpy(text_filename, *(argv + 1));
    strcpy(pattern_filename, *(argv + 2));

    FILE *fp1 = fopen(text_filename, mode);

    if (fp1 == NULL)
    {
        printf("%s cannot be opened or does not exist.\n", text_filename);
        exit(0);
    }

    // get file size to alloate memory for text and pattern strings
    stat(text_filename, &st1);
    long int f_size = st1.st_size;

    text = malloc(sizeof(char)*f_size);

    fgets(text, f_size, fp1);
    // replace trailing '\n' with '\0'
    text[strlen(text)-2] = '\0';

    printf("%s has a length of %d.\n", text, (int)strlen(text));

    fclose(fp1);

    // read pattern file

    FILE *fp2 = fopen(pattern_filename, mode);

    if (fp2 == NULL)
    {
        printf("%s cannot be opened or does not exist.\n", pattern_filename);
        exit(0);
    }

    stat(pattern_filename, &st2);
    long int p_size = st2.st_size;

    pattern = malloc(sizeof(char)*p_size);

    fgets(pattern, p_size, fp2);
    pattern[strlen(pattern)-2] = '\0';

    printf("%s has a length of %d.\n", pattern, (int)strlen(pattern));

    fclose(fp2);
}


int main(int argc, char *argv[])
{
    
    read_file(argv);

    int match_count;
    double run_time = 0.0;
    clock_t start, end;
    match_count = 0;

    char algorithm[100];

    if (atoi(argv[3]) == 0)
    {
        strcpy(algorithm, "Naive String Matching");

        // call KMP to find match
        start = clock();
        match_count = naive_string_matcher(text, pattern);
        end = clock();
    }
    else if (atoi(argv[3]) == 1)
    {
        strcpy(algorithm, "Knuth-Morris-Pratt");

        // call KMP to find match
        start = clock();
        match_count = KMP_matcher(text, pattern);
        end = clock();
    }
    else
    {
        strcpy(algorithm, "Robin-Karp");

        // call robin-karp to find match
        start = clock();
        match_count = rabin_karp_matcher(text, pattern);
        end = clock();
    }
    

    if (match_count == 0)
    {
        printf("No matches found with %s.\n", algorithm);
    }
    else
    {
        printf("A total of %d match/es found with %s.\n\n", match_count, algorithm);
    }

    run_time = (double)(end - start)/CLOCKS_PER_SEC;
    printf("CPU Time elapsed: %f seconds.\n", run_time);
    
    free(text);
    free(pattern);

    return 0;
}

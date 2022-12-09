#ifndef _UTILS_H
#define _UTILS_H

int naive_string_matcher(char *text, char *pattern);
int rabin_karp_matcher(char *text, char *pattern);
int* compute_prefix_function(char *pattern);
int KMP_matcher(char *text, char *pattern);

#endif

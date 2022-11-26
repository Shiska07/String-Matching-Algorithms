#ifndef _UTILS_H
#define _UTILS_H

int naive_string_matcher(char *text, char *pattern);
int* compute_prefix_function(char *pattern, int m);
int KMP_matcher(char *text, char *pattern);
float get_hash_value(char *str);
int rabin_karp_matcher(char *text, char *pattern);

#endif
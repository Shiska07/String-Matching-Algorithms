#ifndef _UTILS_H
#define _UTILS_H

int* get_prefix_array(char* pattern);
int knuth_morris_pratt(char* text, char* pattern);
float* get_decimal_array(char* str);
int robin_karp(char* text, char* pattern);

#endif
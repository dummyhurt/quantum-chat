#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

#include <oqs/kem.h>

#define ALG_MAXLEN 512

#define die(...) {fprintf(stderr, "[ERROR]: "); fprintf(stderr, __VA_ARGS__); fflush(stderr); exit(EXIT_FAILURE);}
#define warn(...) {fprintf(stderr, "[WARN]: "); fprintf(stderr, __VA_ARGS__); fflush(stderr);}

#define LOG
#ifdef LOG

#define log(...) {fprintf(stdout, "[LOG]: "); fprintf(stdout, __VA_ARGS__); fflush(stdout);}

#else

#define log(...) ((void)0)

#endif


// #define DEBUG
#ifdef DEBUG

#define debug(...) {fprintf(stdout, "[DEBUG]: "); fprintf(stdout, __VA_ARGS__); fflush(stdout);}

#else

#define debug(...) ((void)0)

#endif

char **dissect_server_algorithms(char *buffer);

void free_algorithm_array(char **alg_list);

int print_algorithms(char **alg_list);

int menu_algorithms(int n_algs);

void write_to_file(char *fname, uint8_t *key, size_t len);

void read_from_file(char *fname, uint8_t *key, size_t len);

#endif
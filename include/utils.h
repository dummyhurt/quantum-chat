#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

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

#endif
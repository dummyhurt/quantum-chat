#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char **dissect_server_algorithms(char *buffer) {
    char *list = strtok(buffer, "=");
    list = strtok(NULL, "=");

    char **alg_list = NULL;
    size_t count = 0;
    char *p = strtok(list, ",");
    do {
        char **tmp = realloc(alg_list, (count + 1) * sizeof(char*));
        if (tmp == NULL) {
            free(alg_list);
            die("dissect_server_algorithms realloc()\n");
        }
        alg_list = tmp;

        alg_list[count] = malloc(strlen(p) + 1);
        if (alg_list[count] == NULL) {
            for (size_t j = 0; j < count; j++) {
                free(alg_list[count]);
            }
            free(alg_list);
            die("dissect_server_algorithms malloc()\n");
        }
        strcpy(alg_list[count], p);
        count++;
    } while ((p = strtok(NULL, ",")));
    alg_list[count] = NULL;

    return alg_list;
}

void free_algorithm_array(char **alg_list) {
    for (int i = 0; alg_list[i] != NULL; i++)
        free(alg_list[i]);
    free(alg_list);
}

int print_algorithms(char **alg_list) {
    int i;
    for (i = 0; alg_list[i] != NULL; i++)
        printf("Algorithm #%d: %s\n", i, alg_list[i]);
    return i;
}

int menu_algorithms(int n_algs) {
    int choice = -1;
    char tmpbuf[32];
    while (choice < 0 || choice >= n_algs) {
        printf("choose algorithm => ");
        if (fgets(tmpbuf, sizeof(tmpbuf), stdin) != NULL) {
            if (strchr(tmpbuf, '\n') == NULL) {
                // Input 2 long...
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {
                    /* discard long input */
                }
                printf("Input too long, try again\n");
                choice = -1;
                continue;
            }

            tmpbuf[strcspn(tmpbuf, "\n")] = '\0';

            if (strlen(tmpbuf) == 0) {
                // Empty Input
                printf("Invalid input; please enter a number between 0 and %d\n", n_algs - 1);
                choice = -1;
                continue;
            }

            char *endptr;
            choice = strtol(tmpbuf, &endptr, 10);

            if (*endptr != '\0' || choice < 0 || choice >= n_algs) {
                // Check for invalid characters in input
                printf("Invalid input; please enter a number between 0 and %d\n", n_algs - 1);
                choice = -1;
                continue;
            }
        } else {
            die("menu_algorithms fgets()\n");
        }
    }
    return choice;
}

void write_to_file(char *fname, uint8_t *key, size_t len) {
    FILE *file;
    file = fopen(fname, "wb");
    if (file == NULL) die("write_to_file fopen()\n");
    size_t bytes_written = fwrite(key, 1, len, file);
    if (bytes_written != len) {
        fclose(file);
        die("write_to_file written != len\n");
    }
    fclose(file);
}

void read_from_file(char *fname, uint8_t *key, size_t len) {
    FILE *file;
    file = fopen(fname, "rb");
    if (file == NULL) die ("read_from_file fopen()\n");
    size_t bytes_read = fread(key, 1, len, file);
    if (bytes_read != len) {
        fclose(file);
        die("read_from_file read != len\n");
    }
    fclose(file);
}

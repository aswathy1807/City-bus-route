#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 100

typedef struct Stop {
    char name[NAME_LEN];
    struct Stop *next;
} Stop;

Stop* create_stop(const char *name) {
    Stop *node = (Stop*)malloc(sizeof(Stop));
    if (!node) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strncpy(node->name, name, NAME_LEN-1);
    node->name[NAME_LEN-1] = '\0';
    node->next = NULL;
    return node;
}
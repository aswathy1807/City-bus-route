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

void add_stop_end(Stop **head, const char *name) {
    Stop *node = create_stop(name);
    if (*head == NULL) {
        *head = node;
        return;
    }
    Stop *cur = *head;
    while (cur->next) cur = cur->next;
    cur->next = node;
}

void add_stop_at(Stop **head, const char *name, int pos) {
    if (pos <= 1 || *head == NULL) {
        Stop *node = create_stop(name);
        node->next = *head;
        *head = node;
        return;
    }
    Stop *cur = *head;
    int i = 1;
    while (cur->next && i < pos-1) {
        cur = cur->next;
        i++;
    }
    Stop *node = create_stop(name);
    node->next = cur->next;
    cur->next = node;
}

int remove_stop_by_name(Stop **head, const char *name) {
    if (*head == NULL) return 0;
    Stop *cur = *head, *prev = NULL;
    while (cur) {
        if (strcmp(cur->name, name) == 0) {
            if (prev) prev->next = cur->next;
            else *head = cur->next;
            free(cur);
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}

int remove_stop_at(Stop **head, int pos) {
    if (*head == NULL || pos < 1) return 0;
    Stop *cur = *head, *prev = NULL;
    int i = 1;
    while (cur && i < pos) {
        prev = cur;
        cur = cur->next;
        i++;
    }
    if (!cur) return 0;
    if (prev) prev->next = cur->next;
    else *head = cur->next;
    free(cur);
    return 1;
}

void display_route(Stop *head) {
    if (!head) {
        puts("Route is empty.");
        return;
    }
    printf("Bus route stops:\n");
    int i = 1;
    while (head) {
        printf("%d. %s\n", i++, head->name);
        head = head->next;
    }
}


int count_stops(Stop *head) {
    int c = 0;
    while (head) { c++; head = head->next; }
    return c;
}

void traverse_route(Stop *head) {
    if (!head) { puts("Route is empty. Nothing to traverse."); return; }
    puts("Starting route traversal...");
    int i = 1;
    while (head) {
        printf("Arriving at stop %d: %s\n", i++, head->name);
        head = head->next;
    }
    puts("Traversal finished. Bus completed its route.");
}

void free_route(Stop **head) {
    Stop *cur = *head;
    while (cur) {
        Stop *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    *head = NULL;
}

void read_line(char *buf, int len) {
    if (!fgets(buf, len, stdin)) {
        buf[0] = '\0';
        return;
    }
    size_t l = strlen(buf);
    if (l && buf[l-1] == '\n') buf[l-1] = '\0';
}
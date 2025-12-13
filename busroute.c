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

int main(void) {
    Stop *route = NULL;
    char choice[10];
    char name[NAME_LEN];
    int pos;

    puts("Simple Bus Route Manager (Singly Linked List)");

    while (1) {
        puts("\nMenu:\n1. Add stop at end\n2. Insert stop at position\n3. Remove stop by name\n4. Remove stop at position\n5. Display route\n6. Count stops\n7. Traverse route (simulate)\n8. Clear route\n9. Exit");
        printf("Choose an option (1-9): ");
        read_line(choice, sizeof(choice));

        switch (atoi(choice)) {
            case 1:
                printf("Enter stop name: ");
                read_line(name, sizeof(name));
                add_stop_end(&route, name);
                puts("Stop added at end.");
                break;
            case 2:
                printf("Enter stop name: ");
                read_line(name, sizeof(name));
                printf("Enter 1-based position to insert at: ");
                scanf("%d%*c", &pos); // consume newline
                add_stop_at(&route, name, pos);
                puts("Stop inserted.");
                break;
            case 3:
                printf("Enter exact stop name to remove: ");
                read_line(name, sizeof(name));
                if (remove_stop_by_name(&route, name)) puts("Stop removed.");
                else puts("Stop not found.");
                break;
            case 4:
                printf("Enter 1-based position to remove: ");
                scanf("%d%*c", &pos);
                if (remove_stop_at(&route, pos)) puts("Stop removed.");
                else puts("Invalid position.");
                break;
            case 5:
                display_route(route);
                break;
            case 6:
                printf("Total stops: %d\n", count_stops(route));
                break;
            case 7:
                traverse_route(route);
                break;
            case 8:
                free_route(&route);
                puts("Route cleared.");
                break;
            case 9:
                free_route(&route);
                puts("Goodbye!");
                return 0;
            default:
                puts("Invalid choice. Enter a number 1-9.");
        }
    }
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void run(char* file) {
    char *args[] = {"gcc",
    "-Wall",
    "-pedantic",
    file,
    "-o",
    "sort",
    NULL};

    if (fork() == 0) {
        execvp(args[0], args);
    } else {
        wait(NULL);
    }
    char *args2[] = {"./sort",
    NULL};

    execvp(args2[0], args2);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "4 arguments needed. Have %d\n", argc-1);
        exit(1);
    }

    char *type = NULL;
    char *comp = NULL;
    for (int i=1; i<=4; i++) {
        if (strcmp(argv[i], "--type") == 0) {
            type = argv[i+1];
        } else if(strcmp(argv[i], "--comp") == 0) {
            comp = argv[i+1];
        }
    }

    if (type == NULL || comp == NULL) {
        fprintf(stderr, "Bad arguments\n");
        exit(1);
    }
    if (strcmp(type, "insert") == 0) {
        if (strcmp(comp, "<=") == 0) {
            run("InsertionSortle.c");
        } else if (strcmp(comp, ">=") == 0) {
            run("InsertionSortge.c");
        }
    } else if (strcmp(type, "merge") == 0) {
        if (strcmp(comp, "<=") == 0) {
            run("MergeSortle.c");
        } else if (strcmp(comp, ">=") == 0) {
            run("MergeSortge.c");
        }
    } else if (strcmp(type, "quick") == 0) {
        if (strcmp(comp, "<=") == 0) {
            run("QuickSortle.c");
        } else if (strcmp(comp, ">=") == 0) {
            run("QuickSortge.c");
        }
    }

    return 0;
}
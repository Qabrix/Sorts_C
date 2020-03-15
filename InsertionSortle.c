#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int comp = 0;
int trans = 0;

void InsertionSort(int lenght, int *elements) {
    int temp;
    for (int i=lenght-1; i>0; i--) {
        for (int k=0; k<i; k++) {
            comp++;
            if (*(elements+k) > *(elements+k+1)) {
                temp = *(elements+k+1);
                *(elements+k+1) = *(elements+k);
                *(elements+k) = temp;
                trans++;
            }
        }
    }
}

void run_normal() {
    int lenght = 0;
    printf("Welcome to Insertion Sort <=, enter lenght: ");
    scanf("%d", &lenght);
    int *elements = malloc(sizeof(int)*lenght);
    printf("Insert %d elements: ", lenght);
    for (int i=0; i<lenght; i++) {
        scanf("%d", elements+i);
    }

    clock_t t1;
    t1 = clock();
    InsertionSort(lenght, elements);
    t1 = clock() - t1;
    fprintf(stderr, "Time clicks: %ld\nTime sec: %f\n", t1, ((double)t1/CLOCKS_PER_SEC));

    for (int i=1; i<lenght; i++) {
        if (*(elements+i) < *(elements+i-1)) {
            fprintf(stderr, "Array not sorted.\n");
            exit(1);
        }
    }

    for (int i=0; i<lenght; i++) {
        printf("%d, ", *(elements+i));
    }
    printf("\n");

    fprintf(stderr, "Comparisions = %d\n", comp);
    fprintf(stderr, "Transpositions = %d\n", trans);
}

void run_stats(FILE *file) {
    int saved_stdin = dup(0); // potrzebne do restore stdin
    int fd[2]; // file descriptors

    pipe(fd); // laczymy je
    dup2(fd[0], 0); // duplikujemy fd[0] na stdin
    close(fd[0]);

    int *elements;
    
    for (int i=1; i<=100; i++) { // nasze wszystkie proby ze 100
        elements = malloc(sizeof(int)*i*100); // malloc dla 100*i elementow
        for (int k=1; k<=i; k++) { // teraz losowanko i zapisywanie elementow pod pointer (zrobilem to pythonem bo ma fajne opcje random generator)
            if (fork() == 0) {
                dup2(fd[1], 1);
                close(fd[1]);

                char *args[] = {"python3",
                "./statistics/DataCreator.py",
                NULL
                };
                execvp(args[0], args);
            } else {
                wait(NULL);
            }

            for (int l=0; l<100; l++) {
                scanf("%d", elements+(l*k));
            }
        }

        comp = 0;
        trans = 0;

        clock_t t1;
        t1 = clock();
        InsertionSort(i*100, elements);
        t1 = clock() - t1;
        fprintf(stderr, "Time clicks: %ld\nTime sec: %f\n", t1, ((double)t1/CLOCKS_PER_SEC));

        for (int k=1; k<i*100; k++) {
            if (*(elements+k) < *(elements+k-1)) {
                fprintf(stderr, "Array not sorted.\n");
                exit(1);
            }
        }

        fprintf(stderr, "Comparisions = %d\n", comp);
        fprintf(stderr, "Transpositions = %d\n", trans);
        printf("------------------------------------\n");

        // Saving to file SIZE_OF_ARRAY;time_clicks;time_sec;comparisions;transpositions
        // size of array
        fprintf(file, "%d", i*100);
        fprintf(file, "%s", ";"); // separator

        // time clicks
        fprintf(file, "%ld", t1);
        fprintf(file, "%s", ";"); // separator

        // time sec
        fprintf(file, "%f", ((double)t1/CLOCKS_PER_SEC));
        fprintf(file, "%s", ";"); // separator

        // comparisions
        fprintf(file, "%d", comp);
        fprintf(file, "%s", ";"); // separator

        // transpositions
        fprintf(file, "%d", trans);
        fprintf(file, "%s", "\n"); // new line

        free(elements);
    }

    dup2(saved_stdin, 0);
    close(saved_stdin);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        run_normal();
    } else { // argv[1] <- filename | argv[2] <- ilosc
        int amount_of_tests = atoi(argv[2]);
        FILE *file = fopen(argv[1], "a");
        fprintf(file, "SIZE_OF_ARRAY;time_clicks;time_sec;comparisions;transpositions\n");
        for (int i=0; i<amount_of_tests; i++) {
            run_stats(file);
        }
        fclose(file);
    }

    return 0;
}
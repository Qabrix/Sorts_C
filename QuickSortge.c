#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int comp = 0;
int trans = 0;

void QuickSort(int lenght, int *elements) {
    if (lenght <= 1) {
        return;
    }

    int div_p = *(elements+lenght-1); // biore div_p jako ostatni element tablicy, zawsze
    int index_left = 0;
    int index_right = lenght-2;

    while (index_left < index_right) { // to nasz warunek, robie na dwa "pointery"
        comp++;
        if (*(elements+index_left) < div_p) {
            while (index_left < index_right) {
                comp++;
                if (*(elements+index_right) >= div_p) {
                    int swap = *(elements+index_right);
                    *(elements+index_right) = *(elements+index_left);
                    *(elements+index_left) = swap;
                    index_right--;
                    index_left++;
                    goto END; // jesli udal sie swap to robimy "break"
                } else {
                    index_right--;
                }
            }
            goto SWAP; // jesli nie bylo goto END to wtedy while() skonczyl sie na index_left == index_right i wiemy ze *(elements+index_right) <= div_p wiec mozemy swap
END:        trans++;
        } else {
            index_left++;
        }
    }

    comp++;
    if (*(elements+index_left) < div_p) {
SWAP:   *(elements+lenght-1) = *(elements+index_left);
        *(elements+index_left) = div_p;
        index_left--;
        trans++;
    } else { // w tym wypadku skonczylismy na ostatniej mniejszej lub rownej od div_p wiec swapujemy kolejna z div_p
        *(elements+lenght-1) = *(elements+index_left+1); // czasami swapniemy div_p z samym soba, probowalem jakos to zrobic ale jednak zostalo :(
        *(elements+index_left+1) = div_p;
        trans++;
    }

    QuickSort(index_left+1, elements);
    QuickSort(lenght-index_left-2, elements+index_left+2);
}

void run_normal() {
    int lenght = 0;
    printf("Welcome to Quick Sort >=, enter lenght: ");
    scanf("%d", &lenght);
    int *elements = malloc(sizeof(int)*lenght);
    printf("Insert %d elements: ", lenght);
    for (int i=0; i<lenght; i++) {
        scanf("%d", elements+i);
    }

    clock_t t1;
    t1 = clock();
    QuickSort(lenght, elements);
    t1 = clock() - t1;
    fprintf(stderr, "Time clicks: %ld\nTime sec: %f\n", t1, ((double)t1/CLOCKS_PER_SEC));

    for (int i=1; i<lenght; i++) {
        if (*(elements+i) > *(elements+i-1)) {
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
        QuickSort(i*100, elements);
        t1 = clock() - t1;
        fprintf(stderr, "Time clicks: %ld\nTime sec: %f\n", t1, ((double)t1/CLOCKS_PER_SEC));

        for (int k=1; k<i*100; k++) {
            if (*(elements+k) > *(elements+k-1)) {
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
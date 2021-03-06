#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pcg_basic.h"

int comp = 0;
int trans = 0;

int * MergeSort(int lenght, int *elements) { // Uwaga! Tutaj zakladam ze transpozycja to ogolne przestawienia w pamieci kluczy, nie tylko przestawienia kolejnosci
    if (lenght != 1) {
        int l = lenght/2;
        if (lenght%2 == 0) {
            int *a = MergeSort(l, elements);
            int *b = MergeSort(l, elements + l);

            int *temp = malloc(sizeof(int)*lenght);
            int t_ptr = 0;
            int b_indeks = 0;

            for (int i = 0; i<l; i++) {
                while (b_indeks < l && *(a+i) < *(b+b_indeks)) {
                    *(temp+t_ptr) = *(b+b_indeks);
                    t_ptr++;
                    b_indeks++;
                    comp++;
                    trans++;
                }

                if (b_indeks < l) { // to tylko na potrzeby danych, jesli while sie skonczyl przy b_indeks<l to znaczy ze porownalismy *(a+i) < *(b+b_indeks)
                    comp++;
                }

                *(temp+t_ptr) = *(a+i);
                t_ptr++;
                trans++;
            }

            while (b_indeks < l) {
                *(temp+t_ptr) = *(b+b_indeks);
                t_ptr++;
                b_indeks++;
                trans++;
            }

            if (l >= 2) {
                free(a);
                free(b);
            }

            return temp;
        } else {
            int *a = MergeSort(l, elements);
            int *b = MergeSort(l+1, elements + l);

            int *temp = malloc(sizeof(int)*lenght);
            int t_ptr = 0;
            int b_indeks = 0;

            for (int i = 0; i<l; i++) {
                while (b_indeks < l+1 && *(a+i) < *(b+b_indeks)) {
                    *(temp+t_ptr) = *(b+b_indeks);
                    t_ptr++;
                    b_indeks++;
                    comp++;
                    trans++;
                }

                if (b_indeks < l+1) { // to tylko na potrzeby danych, jesli while sie skonczyl przy b_indeks<l+1 to znaczy ze porownalismy *(a+i) < *(b+b_indeks)
                    comp++;
                }

                *(temp+t_ptr) = *(a+i);
                t_ptr++;
                trans++;
            }

            while (b_indeks < l+1) {
                *(temp+t_ptr) = *(b+b_indeks);
                t_ptr++;
                b_indeks++;
                trans++;
            }

            if (l == 1) {
                free(b);
            } else {
                free(a);
                free(b);
            }

            return temp;
        }
    } else {
        return elements;
    }
}

void run_normal() {
    int lenght;
    printf("Welcome to Merge Sort >=, enter lenght: ");
    scanf("%d", &lenght);
    int *elements = malloc(sizeof(int)*lenght);
    printf("Insert %d elements: ", lenght);

    for (int i=0; i<lenght; i++) {
        scanf("%d", elements+i);
    }

    clock_t t1;
    t1 = clock();
    int *sorted = MergeSort(lenght, elements);
    t1 = clock() - t1;
    fprintf(stderr, "Time clicks: %ld\nTime sec: %f\n", t1, ((double)t1/CLOCKS_PER_SEC));
    free(elements);

    for (int i=1; i<lenght; i++) {
        if (*(sorted+i) > *(sorted+i-1)) {
            fprintf(stderr, "Array not sorted.\n");
            exit(1);
        }
    }

    for (int i=0; i<lenght; i++) {
        printf("%d, ", *(sorted+i));
    }
    printf("\n");

    fprintf(stderr, "Comparisions = %d\n", comp);
    fprintf(stderr, "Transpositions = %d\n", trans);
}

void run_stats(FILE *file, pcg32_random_t *rng) {
    int *elements;
    
    for (int i=1; i<=100; i++) { // nasze wszystkie proby ze 100
        elements = malloc(sizeof(int)*i*100); // malloc dla 100*i elementow
        for (int k=0; k<i*100; k++) { // teraz losowanko i zapisywanie elementow pod pointer (zrobilem to pythonem bo ma fajne opcje random generator)
            *(elements+k) = (int)pcg32_boundedrand_r(rng, 20001) - 10000;
        }

        comp = 0;
        trans = 0;

        clock_t t1;
        t1 = clock();
        int *sorted = MergeSort(i*100, elements);
        t1 = clock() - t1;
        fprintf(stderr, "Time clicks: %ld\nTime sec: %f\n", t1, ((double)t1/CLOCKS_PER_SEC));
        free(elements);

        for (int k=1; k<i*100; k++) {
            if (*(sorted+k) > *(sorted+k-1)) {
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

        free(sorted);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        run_normal();
    } else { // argv[1] <- filename | argv[2] <- ilosc
        int amount_of_tests = atoi(argv[2]);
        FILE *file = fopen(argv[1], "a");
        fprintf(file, "SIZE_OF_ARRAY;time_clicks;time_sec;comparisions;transpositions\n");

        pcg32_random_t *rng = malloc(sizeof(pcg32_random_t));

        pcg32_srandom_r(rng, time(NULL) ^ (intptr_t)&printf, (intptr_t)&amount_of_tests); // seeding rng (non deterministic)

        for (int i=0; i<amount_of_tests; i++) {
            run_stats(file, rng);
        }
        fclose(file);
    }

    return 0;
}
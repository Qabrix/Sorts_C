#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
                while (b_indeks < l && *(a+i) > *(b+b_indeks)) {
                    *(temp+t_ptr) = *(b+b_indeks);
                    t_ptr++;
                    b_indeks++;
                    comp++;
                    trans++;
                }

                if (b_indeks < l) { // to tylko na potrzeby danych, jesli while sie skonczyl przy b_indeks<l to znaczy ze porownalismy *(a+i) > *(b+b_indeks)
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
                while (b_indeks < l+1 && *(a+i) > *(b+b_indeks)) {
                    *(temp+t_ptr) = *(b+b_indeks);
                    t_ptr++;
                    b_indeks++;
                    comp++;
                    trans++;
                }

                if (b_indeks < l+1) { // to tylko na potrzeby danych, jesli while sie skonczyl przy b_indeks<l+1 to znaczy ze porownalismy *(a+i) > *(b+b_indeks)
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

int main() {
    int lenght;
    printf("Welcome to Merge Sort <=, enter lenght: ");
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
        if (*(sorted+i) < *(sorted+i-1)) {
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

    return 0;
}
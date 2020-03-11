#include <stdio.h>
#include <stdlib.h>

int * MergeSort(int lenght, int *elements) {
    if (lenght != 1) {
        int l = lenght/2;
        if (lenght%2 == 0) {
            int *a = MergeSort(l, elements);
            int *b = MergeSort(l, elements + l);

            int *temp = malloc(sizeof(int)*lenght);
            int t_ptr = 0;
            int b_indeks = 0;

            for (int i = 0; i<l; i++) {
                while(b_indeks < l && *(a+i) > *(b+b_indeks)) {
                    *(temp+t_ptr) = *(b+b_indeks);
                    t_ptr++;
                    b_indeks++;
                }

                *(temp+t_ptr) = *(a+i);
                t_ptr++;
            }

            while (b_indeks < l) {
                *(temp+t_ptr) = *(b+b_indeks);
                t_ptr++;
                b_indeks++;
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
                while(b_indeks < l+1 && *(a+i) > *(b+b_indeks)) {
                    *(temp+t_ptr) = *(b+b_indeks);
                    t_ptr++;
                    b_indeks++;
                }

                *(temp+t_ptr) = *(a+i);
                t_ptr++;
            }

            while (b_indeks < l+1) {
                *(temp+t_ptr) = *(b+b_indeks);
                t_ptr++;
                b_indeks++;
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

    int *sorted = MergeSort(lenght, elements);
    free(elements);

    for (int i=0; i<lenght; i++) {
        printf("%d, ", *(sorted+i));
    }
    printf("\n");
}
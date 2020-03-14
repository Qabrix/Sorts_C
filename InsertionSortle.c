#include <stdio.h>
#include <stdlib.h>
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

int main() {
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

    return 0;
}